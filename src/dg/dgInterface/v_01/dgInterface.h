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
 * dgInterface.h
 *
 *  Created on: Jun 24, 2019
 *      Author: marco
 */

#ifndef DS_DGINTERFACE_H_
#define DS_DGINTERFACE_H_

#include <stdint.h>

// lib include
#include "csCallback.h"

namespace fw2 { namespace core { namespace core {


class dgInterface {
public:

	dgInterface(																);
	dgInterface(uint8_t	p_Index													);
	dgInterface(				 csCallback::boolOut_uint8In_t 	p_fDisplayable	);
	dgInterface(uint8_t	p_Index	,csCallback::boolOut_uint8In_t 	p_fDisplayable	);

protected:
	static 			char    m_StringValue[30];

public:
	static const	char*	m_pStringValue;

	uint8_t							m_Index			;
	csCallback::boolOut_uint8In_t 	m_fDisplayable	;


	virtual void vValueToString		(void)  {};
			bool bDisplayable		(void);

};

} } }	// namespace fw2::core::core

#endif /* DS_DGINTERFACE_H_ */
