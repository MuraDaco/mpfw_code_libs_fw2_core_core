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
 * uyProtocol2.cpp
 *
 *  Created on: August, 22nd 2023
 *      Author: Marco Dau
 */

#include "uyProtocol2.h"


namespace fw2 { namespace core { namespace core	{


bool     uyProtocol2::g_Master = false;
uint8_t  uyProtocol2::g_adds = UY_PROTOCOL2__ADDS;

uint8_t uyProtocol2::AddsGet (void)	{
	uint8_t l_result = UY_PROTOCOL2__ADDS;
	if(0 != g_adds)	l_result = g_adds;
	return l_result;
}

void uyProtocol2::AddsSet (uint8_t p_adds)	{
	if(
		('1' <= g_adds) &&
		('9' >= g_adds)
	) {
		g_adds = p_adds;
	}
}

uint8_t uyProtocol2::AddsSrcGet (char* p_buffer)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		return p_buffer[l_body_start + UY_PROTOCOL2__ID_SRC_ADDS];
	}
	return 0;
}

void uyProtocol2::AddsSrcSet (char* p_buffer, uint8_t p_adds)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		p_buffer[l_body_start + UY_PROTOCOL2__ID_SRC_ADDS] = p_adds;
	}
}

bool	uyProtocol2::AddsDstMatch    (char* p_buffer)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		return (g_adds == p_buffer[l_body_start + UY_PROTOCOL2__ID_DST_ADDS]);
	}
	return false;
}

uint8_t uyProtocol2::AddsDstGet (char* p_buffer)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		return p_buffer[l_body_start + UY_PROTOCOL2__ID_DST_ADDS];
	}
	return 0;
}

void uyProtocol2::AddsDstSet (char* p_buffer, uint8_t p_adds)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		p_buffer[l_body_start + UY_PROTOCOL2__ID_DST_ADDS] = p_adds;
	}
}

uint8_t uyProtocol2::CommandGet (char* p_buffer)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		return p_buffer[l_body_start + UY_PROTOCOL2__ID_CMD_CODE];
	}
	return 0;
}

void uyProtocol2::CommandSet (char* p_buffer, uint8_t p_cmd)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		p_buffer[l_body_start + UY_PROTOCOL2__ID_CMD_CODE] = p_cmd;
	}
}

uint8_t  uyProtocol2::CommandGetData  (char* p_buffer)	{
	uint8_t l_body_start = uyProtocol::body_start_get(p_buffer);
	if(l_body_start)	{
		return p_buffer[l_body_start + UY_PROTOCOL2__ID_CMD_DATA_START];
	}
	return 0;
}


void uyProtocol2::Set_Master  (void)	{
	g_Master = true;
}

void uyProtocol2::Set_Slave   (void)	{
	g_Master = false;
}

bool uyProtocol2::AmI_Master  (void)	{
	return 	g_Master;
}

bool uyProtocol2::AmI_Slave   (void)	{
	return 	!g_Master;
}





} } }   // fw2::core::core
