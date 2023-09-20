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

    static uint8_t  get_packet_length       (uint8_t p_rx_byte);
    static uint8_t  get_status              (void);
	static bool     check_packet_end        (uint8_t p_byte_rx);
	static void     set_buffer_size         (uint8_t p_size_buffer);

    private:

    static uint8_t  status_err;
    static uint8_t  status;
    static uint8_t  coding;
    static uint16_t packet_length;
    static uint16_t packet_length_100;
    static uint16_t packet_length_010;
    static uint16_t packet_length_001;
    static uint8_t  terminating_char_1;
    static uint8_t  terminating_char_1_default;
    static uint16_t buffer_size;
    static uint8_t  first_byte_counter;

};


} } }   // fw2::core::core


#endif 	// UY_PROTOCOL_H
