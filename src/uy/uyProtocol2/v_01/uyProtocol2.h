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
 * uyProtocol2.h
 *
 *  Created on: August, 22nd 2023
 *      Author: Marco Dau
 */

#include <cstdint>

#include "uyProtocol.h"

#ifndef UY_PROTOCOL2_H
#define UY_PROTOCOL2_H



namespace fw2 { namespace core { namespace core	{

#define UY_PROTOCOL2__ADDS                      RS485_ADDRESS
#define UY_PROTOCOL2__CMD__SET_MASTER           0x31
#define UY_PROTOCOL2__CMD__SET_SLAVE            0x32
#define UY_PROTOCOL2__CMD__SET_ADDS             0x33
#define UY_PROTOCOL2__ID_SRC_ADDS               0
#define UY_PROTOCOL2__ID_DST_ADDS               1
#define UY_PROTOCOL2__ID_CMD_CODE               2
#define UY_PROTOCOL2__ID_CMD_LENGTH             3
#define UY_PROTOCOL2__ID_CMD_DATA_START         4

class uyProtocol2 {

    public:
    static uint8_t  AddsGet         (void);
    static void     AddsSet         (uint8_t p_adds);
    static uint8_t  AddsSrcGet      (char* p_buffer);
    static void     AddsSrcSet      (char* p_buffer, uint8_t p_adds);
    static bool     AddsDstMatch    (char* p_buffer);
    static uint8_t  AddsDstGet      (char* p_buffer);
    static void     AddsDstSet      (char* p_buffer, uint8_t p_adds);

    static void     CommandSet      (char* p_buffer, uint8_t p_command);
    static uint8_t  CommandGet      (char* p_buffer);
    static uint8_t  CommandGetData  (char* p_buffer);

    static void     Set_Master      (void);
    static void     Set_Slave       (void);
    static bool     AmI_Master      (void);
    static bool     AmI_Slave       (void);
    

    private:
    static bool     g_Master;
    static uint8_t  g_adds;

};


} } }   // fw2::core::core


#endif 	// UY_PROTOCOL2_H
