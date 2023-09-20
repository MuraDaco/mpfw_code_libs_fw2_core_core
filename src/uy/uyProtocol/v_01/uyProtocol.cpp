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
uint16_t uyProtocol::packet_length = 0;
uint16_t uyProtocol::packet_length_100;
uint16_t uyProtocol::packet_length_010;
uint16_t uyProtocol::packet_length_001;
uint8_t  uyProtocol::terminating_char_1;
uint8_t  uyProtocol::terminating_char_1_default = UTY_PROTOCOL_DEFAULT_TERMINATING_CHAR;
uint16_t uyProtocol::buffer_size;
uint8_t  uyProtocol::first_byte_counter = 0;




uint8_t uyProtocol::get_status (void)	{
	return status;
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
			case UTY_PROTOCOL_WAITING_TERMINATING_CHAR_1:
				terminating_char_1 = p_rx_byte;
				packet_length = UTY_PROTOCOL_STATUS_LENGTH_UNDETERMINED;
				l_length = packet_length;
				status = UTY_PROTOCOL_WAITING_HEADER;
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
				}
				status = UTY_PROTOCOL_WAITING_HEADER;
				break;
			default:
				break;
		}

	return l_length;
}

bool uyProtocol::check_packet_end        (uint8_t p_byte_rx)	{
	if(
		( (0                                       == packet_length) && (terminating_char_1_default == p_byte_rx) ) ||
		( (UTY_PROTOCOL_STATUS_LENGTH_UNDETERMINED == packet_length) && (terminating_char_1 == p_byte_rx)         )
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

} } }   // fw2::core::core
