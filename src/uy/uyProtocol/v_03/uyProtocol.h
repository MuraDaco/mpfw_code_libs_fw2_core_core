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
/*
 * uyProtocol.h
 *
 *  Created on: July, 26 2023
 *      Author: Marco Dau
 */

#include <cstdint>

#ifndef UY_PROTOCOL_H
#define UY_PROTOCOL_H

namespace fw2 { namespace core { namespace core	{


class uyProtocol {

    public:

    typedef void    (*callback_sdk_reg_write_t)     (void* p_ptrData, char c);
    typedef uint8_t (*callback_sdk_reg_read_t)      (void* p_ptrData);
    typedef void    (*callback_sdk_enable_t)        (void* p_ptrData);

    typedef struct _callback_sdk_functions {
        callback_sdk_reg_write_t    reg_write;
        callback_sdk_reg_read_t     reg_read;
    } callback_sdk_functions_t;

    typedef void    (*callback_sleep_t)     (uint16_t p_sleep_time);

    static uint8_t  body_start_get          (char* p_buffer);

    static uint8_t  get_packet_length       (uint8_t p_byte);
    static uint8_t  get_status              (void);
	static bool     check_packet_end        (uint8_t p_byte);
	static void     set_buffer_size         (uint8_t p_size_buffer);

    // sdk callback functions
    static void     tx_buffer_management        (void* p_PtrData);
    static void     rx_buffer_management        (void* p_PtrData);


    static uint8_t  status_get_tx__free          (void);
    static uint8_t  status_get_rx__free          (void);
    static void     status_set_tx__free          (void);
    static void     status_set_rx__free          (void);

    static uint8_t  status_get_tx__completed     (void);
    static uint8_t  status_get_rx__completed     (void);
    static void     status_set_tx__completed     (void);
    static void     status_set_rx__completed     (void);

    static uint8_t  status_get_tx__running       (void);
    static uint8_t  status_get_rx__running       (void);
    static void     status_set_tx__running       (void);
    static void     status_set_rx__running       (void);



    static void     buffer_management   (char c);
    static bool     status_free (void);
    static uint8_t  send_non_blocking   (uint8_t* p_ptrBuffer);
    static uint8_t  send_non_blocking   (uint8_t* p_ptrBuffer, uint8_t p_size_buffer);
    static uint8_t  send_non_blocking   (char const *p_ptrBuffer);
    static void     send_blocking   (uint8_t* p_ptrBuffer);
    static void     send_blocking   (char const *p_ptrBuffer);
    static void     send_blocking   (uint8_t* p_ptrBuffer, uint8_t p_size_buffer);
    static void     send_blocking   (uint8_t* p_ptrBuffer, uint8_t p_size_buffer, uint8_t p_length);

// ALL-THREAD function 

    static bool     receive_free    (void);
    static bool     receive_check   (void);
    static void     receive_non_blocking    (uint8_t p_length);
    static void     receive_non_blocking    (uint8_t* p_ptrBuffer, uint8_t p_size_buffer, uint8_t p_length);
    static void     receive_non_blocking    (uint8_t* p_ptrBuffer, uint8_t p_size_buffer);
    static void     receive_non_blocking    (char* p_ptrBuffer, uint8_t p_size_buffer);



    private:

    static void shift_buffer (uint8_t p_elements_num);


    static uint8_t  status_err;
    static uint8_t  status;
    static uint8_t  coding;
    static uint8_t  first_byte_counter;
    static uint16_t packet_length_100;
    static uint16_t packet_length_010;
    static uint16_t packet_length_001;
    static uint8_t  terminating_char_1;
    static uint8_t  terminating_char_1_default;

    static uint8_t  status_buffer;
    static uint8_t* ptrBuffer;
    static uint16_t buffer_size;
    static uint8_t* ptrBufferDefault;
    static uint16_t buffer_size_default;
    static uint16_t packet_length;
    static uint16_t DataCounter;

    static callback_sdk_functions_t g_callback_sdk_functions;
    static callback_sleep_t         g_sleep_ms;


};


} } }   // fw2::core::core


#endif 	// UY_PROTOCOL_H
