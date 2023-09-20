//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork 
//      library that contains the essential code that is used in every application
//  Copyright (C) (2023) Marco Dau
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  
//  You can contact me by the following email address
//  marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
//  
//  *******************************************************************************
#include "uyProtocol.h"

// #include <stdlib.h>	// define of 'NULL'

//#include <iostream>
// #include <thread>
// #include <chrono>
// using namespace std::this_thread;     // sleep_for, sleep_until
// using namespace std::chrono_literals; // ns, us, ms, s, h, etc.


#define SDK_USART_DEFAULT_BUFFER_SIZE          99
#define SDK_USART_DEFAULT_TERMINATED_CHAR		0	

#define SDK_USART_TX_STATUS__FREE               0 // 
#define SDK_USART_TX_STATUS__RUNNING	        1 // kUSART_TxBusy
#define SDK_USART_TX_STATUS__COMPLETED     		2 // kUSART_TxIdle
#define SDK_USART_RX_STATUS__FREE               0
#define SDK_USART_RX_STATUS__RUNNING            3 // kUSART_RxBusy
#define SDK_USART_RX_STATUS__COMPLETED          4 // kUSART_RxIdle


#define UTY_PROTOCOL_HEADER               			0x30
#define UTY_PROTOCOL_CODING_NULL					0
#define UTY_PROTOCOL_CODING_BINARY					0x31
#define UTY_PROTOCOL_CODING_BCD						0x32
#define UTY_PROTOCOL_HEADER_TERMINATING_CHAR        'u'
#define UTY_PROTOCOL_DEFAULT_TERMINATING_CHAR       0

#define UTY_PROTOCOL_FIRST_CHARACTER_COUNTER		5				

#define UTY_PROTOCOL_WAITING_HEADER         		0
#define UTY_PROTOCOL_WAITING_CODING	        		1
#define UTY_PROTOCOL_WAITING_LENGTH_100				2
#define UTY_PROTOCOL_WAITING_TERMINATING_CHAR_1 	3
#define UTY_PROTOCOL_WAITING_LENGTH_010				4
#define UTY_PROTOCOL_WAITING_LENGTH_001				5
#define UTY_PROTOCOL_WATING_TERMINATING_NULL		6


#define UTY_PROTOCOL_ERROR_NONE			0
#define UTY_PROTOCOL_ERROR_FIRST_BYTE	1
#define UTY_PROTOCOL_ERROR_CODING		2
#define UTY_PROTOCOL_ERROR_OWERFLOW		3

#define UTY_PROTOCOL_STATUS_LENGTH_UNDETERMINED		(buffer_size+1)

namespace fw2 { namespace core { namespace core	{

uint8_t  uyProtocol::status_err = UTY_PROTOCOL_ERROR_NONE;
uint8_t  uyProtocol::status = UTY_PROTOCOL_WAITING_HEADER;
uint8_t  uyProtocol::coding = UTY_PROTOCOL_CODING_NULL;
uint8_t  uyProtocol::first_byte_counter = 0;
uint16_t uyProtocol::packet_length_100;
uint16_t uyProtocol::packet_length_010;
uint16_t uyProtocol::packet_length_001;
uint8_t  uyProtocol::terminating_char_1;
uint8_t  uyProtocol::terminating_char_1_default = UTY_PROTOCOL_DEFAULT_TERMINATING_CHAR;

uint8_t  uyProtocol::status_buffer;
uint8_t* uyProtocol::ptrBuffer;
uint16_t uyProtocol::buffer_size;
uint8_t* uyProtocol::ptrBufferDefault;
uint16_t uyProtocol::buffer_size_default;
uint16_t uyProtocol::packet_length = 0;
uint16_t uyProtocol::DataCounter;


uint8_t uyProtocol::get_status (void)	{
	return status;
}

void uyProtocol::shift_buffer (uint8_t p_elements_num)	{
	// reset buffer pointer to initial
	ptrBuffer -= (DataCounter-1);
	for(uint8_t i=0;i<p_elements_num;i++) {
		*ptrBuffer = ptrBuffer[DataCounter - p_elements_num];
		ptrBuffer++;
	}
	ptrBuffer--;
	// reset DataCounter
	DataCounter = p_elements_num;
}

uint8_t uyProtocol::get_packet_length (uint8_t p_rx_byte)	{
	uint8_t l_length = 0;

		switch (status) {
			case UTY_PROTOCOL_WAITING_HEADER:
				if(UTY_PROTOCOL_HEADER == p_rx_byte) {
					status = UTY_PROTOCOL_WAITING_CODING;
					first_byte_counter = 0;
				} else {
					status_err = UTY_PROTOCOL_ERROR_FIRST_BYTE;
					if(first_byte_counter < UTY_PROTOCOL_FIRST_CHARACTER_COUNTER) {
						first_byte_counter++;
					} else {
						status = UTY_PROTOCOL_WATING_TERMINATING_NULL;
						first_byte_counter = 0;
					}
				}
				break;
			case UTY_PROTOCOL_WAITING_CODING:
				if(
					(UTY_PROTOCOL_CODING_BINARY == p_rx_byte) ||
					(UTY_PROTOCOL_CODING_BCD    == p_rx_byte)
				) {
					coding = p_rx_byte;
					status = UTY_PROTOCOL_WAITING_LENGTH_100;
				} else {
					// return an error code
					status_err = UTY_PROTOCOL_ERROR_CODING;
					// reset status (the header byte previously received is false)
					status = UTY_PROTOCOL_WAITING_HEADER;
				}
				break;
			case UTY_PROTOCOL_WAITING_TERMINATING_CHAR_1:
				terminating_char_1 = p_rx_byte;
				packet_length = UTY_PROTOCOL_STATUS_LENGTH_UNDETERMINED;
				l_length = packet_length;
				status = UTY_PROTOCOL_WAITING_HEADER;
				if(DataCounter > 4) shift_buffer(4);
				break;
			case UTY_PROTOCOL_WAITING_LENGTH_100:
				if(UTY_PROTOCOL_HEADER_TERMINATING_CHAR == p_rx_byte) {
					status = UTY_PROTOCOL_WAITING_TERMINATING_CHAR_1;
				} else {
					packet_length_100 = (p_rx_byte - 0x30);
					if(packet_length_100 > 9) {
						status = UTY_PROTOCOL_WAITING_HEADER;
					} else {
						packet_length_100 = packet_length_100*100;
						status = UTY_PROTOCOL_WAITING_LENGTH_010;
					}
				}
				break;
			case UTY_PROTOCOL_WAITING_LENGTH_010:
				packet_length_010 = (p_rx_byte - 0x30);
				if (packet_length_010 > 9) {
					status = UTY_PROTOCOL_WAITING_HEADER;
				} else {
					packet_length_010 = packet_length_010*10;
					status = UTY_PROTOCOL_WAITING_LENGTH_001;
				}
				break;
			case UTY_PROTOCOL_WAITING_LENGTH_001:
				packet_length_001 = (p_rx_byte - 0x30);
				if (packet_length_001 <= 9) {
					packet_length = packet_length_100 + packet_length_010 + packet_length_001 + 5;
					l_length = packet_length;
					if(DataCounter > 5) shift_buffer(5);
				}
				status = UTY_PROTOCOL_WAITING_HEADER;
				break;
			default:
				break;
		}

	return l_length;
}

uint8_t     uyProtocol::status_get_tx__running       (void)	{
	return (SDK_USART_TX_STATUS__RUNNING   == status_buffer);
}

uint8_t     uyProtocol::status_get_tx__completed     (void)	{
	return (SDK_USART_TX_STATUS__COMPLETED == status_buffer);
}

uint8_t     uyProtocol::status_get_rx__running       (void)	{
	return (SDK_USART_RX_STATUS__RUNNING   == status_buffer);
}

uint8_t     uyProtocol::status_get_rx__completed     (void)	{
	return (SDK_USART_RX_STATUS__COMPLETED == status_buffer);
}


uint8_t     uyProtocol::status_get_tx__free          (void)	{
	return (SDK_USART_TX_STATUS__FREE == status_buffer);
}

uint8_t     uyProtocol::status_get_rx__free          (void)	{
	return (SDK_USART_RX_STATUS__FREE == status_buffer);
}



void     uyProtocol::status_set_tx__free          (void)	{
	status_buffer = SDK_USART_TX_STATUS__FREE;
}

void     uyProtocol::status_set_rx__free          (void)	{
	status_buffer = SDK_USART_RX_STATUS__FREE;
}


void     uyProtocol::status_set_tx__completed     (void)	{
	status_buffer = SDK_USART_TX_STATUS__COMPLETED;
}

void     uyProtocol::status_set_rx__completed     (void)	{
	status_buffer = SDK_USART_RX_STATUS__COMPLETED;
}

void     uyProtocol::status_set_tx__running     (void)	{
	status_buffer = SDK_USART_TX_STATUS__COMPLETED;
}

void     uyProtocol::status_set_rx__running     (void)	{
	status_buffer = SDK_USART_RX_STATUS__COMPLETED;
}



void uyProtocol::tx_buffer_management(void* p_PtrData)	{
	if(status_get_tx__running()) {
		int c = *ptrBuffer;	
		buffer_management(c);
		g_callback_sdk_functions.reg_write(p_PtrData, c);
	}
	
}

void uyProtocol::rx_buffer_management(void* p_PtrData)	{
	if(status_get_rx__running()) {
		int c = g_callback_sdk_functions.reg_read(p_PtrData);
		*ptrBuffer = c;		
		buffer_management(c);
	}
	
}

void uyProtocol::buffer_management(char c)	{

	// increment tx byte counter
	DataCounter++;

	// check packet length
	if(packet_length == 0) {

		// check the end of packet via terminating character = 0
		if(check_packet_end(c)) {
			// a null terminated character is received (terminated char = 0)
			// a char string is received

			// set the packet end condition
			packet_length = DataCounter;

		} else {
			// get packet length
			packet_length = get_packet_length(c);
		}
	} else {

		// check the end of packet via terminating character that is set reading header
		if(check_packet_end(c)) {
			// set the packet end condition
			packet_length = DataCounter;
		}
	}

	// check the end of packet via terminated character set in packet header
	if((DataCounter == packet_length) || (DataCounter == buffer_size)) {
		switch (status_buffer) {
			case SDK_USART_TX_STATUS__RUNNING:
				// the end of packet is reached
				//-- g_callback_sdk_functions.reg_write(c);
				status_buffer = SDK_USART_TX_STATUS__COMPLETED;
				break;
			case SDK_USART_RX_STATUS__RUNNING:
				// the end of packet is reached
				status_buffer = SDK_USART_RX_STATUS__COMPLETED;
				break;
		}

	} else {
		// the end of packet is NOT reached yet

		// increment pointer of tx buffer to point the next byte to send
		ptrBuffer++;
	}

}

uint8_t uyProtocol::body_start_get(char* p_buffer)	{

	// ptrBuffer 		= (uint8_t*) p_buffer; 						// ptr_buffer = p_ptrBuffer;
	// buffer_size   	= SDK_USART_DEFAULT_BUFFER_SIZE; 	// g_buffer_size = SDK_USART_DEFAULT_BUFFER_SIZE;
	// status 			= UTY_PROTOCOL_WAITING_HEADER;
	// packet_length = 0;
	// for(uint8_t i=0; i<SDK_USART_DEFAULT_BUFFER_SIZE; i++)	{
	// 	char c = p_buffer[i];
	// 	if(0==c) break;
	// 	// check the end of packet via terminating character = 0
	// 	if(!( (0 == packet_length) && (terminating_char_1_default == c) )) {
	// 		if(0 != get_packet_length(c)) return (i+1);
	// 	}
	// }

	//ptrBuffer = nullptr;
	return 4;
}

bool uyProtocol::check_packet_end        (uint8_t p_byte_rx)	{
	if(
		( (0                                       == packet_length) && (terminating_char_1_default == p_byte_rx) ) ||
		( (UTY_PROTOCOL_STATUS_LENGTH_UNDETERMINED == packet_length) && (terminating_char_1         == p_byte_rx) )
	) {
		packet_length = 0;
		status = UTY_PROTOCOL_WAITING_HEADER;
		return true;		
	}

	return false;
}


void uyProtocol::set_buffer_size         (uint8_t p_size_buffer)	{
	packet_length = 0;
	status = UTY_PROTOCOL_WAITING_HEADER;
	buffer_size = p_size_buffer;
}


bool uyProtocol::status_free(void)	{
	return (
		(SDK_USART_TX_STATUS__FREE == status_buffer) ||
		(SDK_USART_RX_STATUS__FREE == status_buffer)
	);
}

// ALL-THREAD function 

uint8_t uyProtocol::send_non_blocking(uint8_t* p_ptrBuffer)	{
	uint8_t result = 0;

	if(status_free())	{
		ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
		buffer_size   	= SDK_USART_DEFAULT_BUFFER_SIZE; 	// g_buffer_size = SDK_USART_DEFAULT_BUFFER_SIZE;
		packet_length 	= 0;								// g_packet_length = 0;
		DataCounter  	= 0;								// tx_byte_counter = 0;
		status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
		result = 1;
	}

	return result;
}

uint8_t uyProtocol::send_non_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer)	{
	uint8_t result = 0;

	if(status_free())	{
		ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
		buffer_size   	= p_size_buffer;
		packet_length 	= 0;								// g_packet_length = 0;
		DataCounter  	= 0;								// tx_byte_counter = 0;
		status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
		result = 1;
	}

	return result;
}

uint8_t uyProtocol::send_non_blocking(char const *p_ptrBuffer)	{
	uint8_t result = 0;

	if(status_free())	{
		ptrBuffer 		= (uint8_t* ) p_ptrBuffer; 			// ptr_buffer = (uint8_t* ) p_ptrBuffer;
		buffer_size   	= SDK_USART_DEFAULT_BUFFER_SIZE; 	// g_buffer_size = SDK_USART_DEFAULT_BUFFER_SIZE;
		packet_length 	= 0;								// g_packet_length = 0;
		DataCounter  	= 0;								// tx_byte_counter = 0;
		status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
		result = 1;
	}

	return result;
}

void uyProtocol::send_blocking(uint8_t* p_ptrBuffer)	{
	while(!status_free()){g_sleep_ms(10);}

	ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
	buffer_size   	= SDK_USART_DEFAULT_BUFFER_SIZE; 	// g_buffer_size = SDK_USART_DEFAULT_BUFFER_SIZE;
	packet_length 	= 0;								// g_packet_length = 0;
	DataCounter  	= 0;								// tx_byte_counter = 0;
	status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
	status = UTY_PROTOCOL_WAITING_HEADER;

	while(!status_free()){g_sleep_ms(10);}						// while(SDK_USART_TX_STATUS__RUNNING == status){g_sleep_ms(10);}

}

void uyProtocol::send_blocking(char const *p_ptrBuffer)	{
	while(!status_free()){g_sleep_ms(10);}

	ptrBuffer 		= (uint8_t* ) p_ptrBuffer; 			// ptr_buffer = (uint8_t* ) p_ptrBuffer;
	buffer_size   	= SDK_USART_DEFAULT_BUFFER_SIZE; 	// g_buffer_size = SDK_USART_DEFAULT_BUFFER_SIZE;
	packet_length 	= 0;								// g_packet_length = 0;
	DataCounter  	= 0;								// tx_byte_counter = 0;
	status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
	status = UTY_PROTOCOL_WAITING_HEADER;

	while(!status_free()){g_sleep_ms(10);}						// while(SDK_USART_TX_STATUS__RUNNING == status){g_sleep_ms(10);}

}


void uyProtocol::send_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer)	{
	while(!status_free()){g_sleep_ms(10);}

	ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
	buffer_size   	= p_size_buffer;
	packet_length 	= 0;								// g_packet_length = 0;
	DataCounter  	= 0;								// tx_byte_counter = 0;
	status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
	status = UTY_PROTOCOL_WAITING_HEADER;

	while(!status_free()){g_sleep_ms(10);}						// while(SDK_USART_TX_STATUS__RUNNING == status){g_sleep_ms(10);}

}

void uyProtocol::send_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer, uint8_t p_length)	{
	while(!status_free()){g_sleep_ms(10);}

	ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
	buffer_size   	= p_size_buffer;
	packet_length 	= p_length;					    	// g_packet_length = 0;
	DataCounter  	= 0;								// tx_byte_counter = 0;
	status_buffer			= SDK_USART_TX_STATUS__RUNNING;		// status = SDK_USART_TX_STATUS__RUNNING;
	status = UTY_PROTOCOL_WAITING_HEADER;

	// while(!status_free()){g_sleep_ms(10);}						// while(SDK_USART_TX_STATUS__RUNNING == status){g_sleep_ms(10);}

}

// ALL-THREAD function 

bool uyProtocol::receive_free	(void)	{
	return (SDK_USART_RX_STATUS__FREE == status_buffer);
}

bool uyProtocol::receive_check	(void)	{
	if(SDK_USART_RX_STATUS__COMPLETED == status_buffer)	{
		status_buffer			= SDK_USART_RX_STATUS__FREE;		// status = SDK_USART_RX_STATUS__FREE;
		return true;
	}
	return false;
}

void uyProtocol::receive_non_blocking(uint8_t p_length)	{
	if(SDK_USART_RX_STATUS__FREE == status_buffer)	{
		ptrBuffer 		= ptrBufferDefault; 				
		buffer_size   	= buffer_size_default;				
		packet_length 	= p_length;							// g_packet_length = p_length;
		DataCounter  	= 0;								// rx_byte_counter = 0;
		status_buffer			= SDK_USART_RX_STATUS__RUNNING;		// status = SDK_USART_RX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
	}
}


void uyProtocol::receive_non_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer, uint8_t p_length)	{
	if(SDK_USART_RX_STATUS__FREE == status_buffer)	{
		ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
		buffer_size   	= p_size_buffer;				 	// g_buffer_size = p_size_buffer;
		packet_length 	= p_length;							// g_packet_length = p_length;
		DataCounter  	= 0;								// rx_byte_counter = 0;
		status_buffer			= SDK_USART_RX_STATUS__RUNNING;		// status = SDK_USART_RX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
	}
}

void uyProtocol::receive_non_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer)	{
	if(SDK_USART_RX_STATUS__FREE == status_buffer)	{
		ptrBuffer 		= p_ptrBuffer; 						// ptr_buffer = p_ptrBuffer;
		buffer_size   	= p_size_buffer;				 	// g_buffer_size = p_size_buffer;
		packet_length 	= 0;								// g_packet_length = 0;
		DataCounter  	= 0;								// rx_byte_counter = 0;
		status_buffer			= SDK_USART_RX_STATUS__RUNNING;		// status = SDK_USART_RX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
	}
}

void uyProtocol::receive_non_blocking(char* p_ptrBuffer, uint8_t p_size_buffer)	{
	if(SDK_USART_RX_STATUS__FREE == status_buffer)	{
		ptrBuffer 		= (uint8_t *) p_ptrBuffer; 			// ptr_buffer = (uint8_t *) p_ptrBuffer;
		buffer_size   	= p_size_buffer;				 	// g_buffer_size = p_size_buffer;
		packet_length 	= 0;								// g_packet_length = 0;
		DataCounter  	= 0;								// rx_byte_counter = 0;
		status_buffer			= SDK_USART_RX_STATUS__RUNNING;		// status = SDK_USART_RX_STATUS__RUNNING;
		status = UTY_PROTOCOL_WAITING_HEADER;
		
	}
}




} } }   // fw2::core::core
