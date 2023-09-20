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
 * dgInterface.cpp
 *
 *  Created on: Jun 24, 2019
 *      Author: marco
 */

// module include
#include "dgInterface.h"


dgInterface::dgInterface	(																)
	:
	m_Index			{0xff			},
	m_fDisplayable	{nullptr		}
{}

dgInterface::dgInterface(uint8_t	p_Index													)
	:
	m_Index			{p_Index		},
	m_fDisplayable	{nullptr		}
{}

dgInterface::dgInterface	(				 csCallback::boolOut_uint8In_t 	p_fDisplayable	)
	:
	m_Index			{0xff			},
	m_fDisplayable	{p_fDisplayable	}
{}

dgInterface::dgInterface(uint8_t	p_Index	,csCallback::boolOut_uint8In_t 	p_fDisplayable	)
	:
	m_Index			{p_Index		},
	m_fDisplayable	{p_fDisplayable	}
{}


		char    dgInterface::m_StringValue[30];
const	char*	dgInterface::m_pStringValue				{m_StringValue};


bool	dgInterface::bDisplayable		(void)	{
	if(m_fDisplayable)	{
		return m_fDisplayable(m_Index);
	}
	return true;
}




