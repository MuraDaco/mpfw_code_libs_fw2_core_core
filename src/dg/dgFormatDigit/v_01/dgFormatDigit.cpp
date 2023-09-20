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
 * dgFormatDigit.cpp
 *
 *  Created on: Jun 24, 2019
 *      Author: marco
 */

// module include
#include "dgFormatDigit.h"

// lib/dt include
#include "dtDef.h"

namespace fw2 { namespace core { namespace core {
    
char*	dgFormatDigit::m_StringValueField   {m_StringValue};
uint8_t dgFormatDigit::m_StringValueLength;

dgFormatDigit::dgFormatDigit(
        void*	    		p_pTemporValue          	,
        uint8_t     		p_ByteNum               	,
        uint8_t     		p_DigitNum              	,   // must be coherent with m_ByteNum
        uint8_t     		p_Encoding              	,   // Hex or Dec
        uint8_t     		p_DecimalDigitNum       	,
        bool        		p_Signed
) :
    m_pTemporValue        	{p_pTemporValue       		},
	m_DataType			  	{dtDef::kDataType_Standard	},
    m_ByteNum             	{p_ByteNum            		},
    m_DigitNum            	{p_DigitNum           		},
    m_Encoding            	{p_Encoding           		},
    m_DecimalDigitNum     	{p_DecimalDigitNum    		},
    m_Signed              	{p_Signed             		}
{}

dgFormatDigit::dgFormatDigit(
        void*	    		p_pTemporValue          	,
        uint8_t     		p_ByteNum               	,
        uint8_t     		p_DigitNum              	,   // must be coherent with m_ByteNum
        uint8_t     		p_Encoding              	,   // Hex or Dec
        uint8_t     		p_DecimalDigitNum       	,
        bool        		p_Signed					,
		csCallback::boolOut_uint8In_t 	p_fDisplayable
) :
	dgInterface				(p_fDisplayable				),
    m_pTemporValue        	{p_pTemporValue       		},
	m_DataType			  	{dtDef::kDataType_Standard	},
    m_ByteNum             	{p_ByteNum            		},
    m_DigitNum            	{p_DigitNum           		},
    m_Encoding            	{p_Encoding           		},
    m_DecimalDigitNum     	{p_DecimalDigitNum    		},
    m_Signed              	{p_Signed             		}
{}

dgFormatDigit::dgFormatDigit(
        void*	    		p_pTemporValue          	,
		uint8_t				p_Index						,
        uint8_t     		p_ByteNum               	,
        uint8_t     		p_DigitNum              	,   // must be coherent with m_ByteNum
        uint8_t     		p_Encoding              	,   // Hex or Dec
        uint8_t     		p_DecimalDigitNum       	,
        bool        		p_Signed					,
		csCallback::boolOut_uint8In_t 	p_fDisplayable
) :
	dgInterface				(p_Index	,p_fDisplayable	),
    m_pTemporValue        	{p_pTemporValue       		},
	m_DataType			  	{dtDef::kDataType_Standard	},
    m_ByteNum             	{p_ByteNum            		},
    m_DigitNum            	{p_DigitNum           		},
    m_Encoding            	{p_Encoding           		},
    m_DecimalDigitNum     	{p_DecimalDigitNum    		},
    m_Signed              	{p_Signed             		}
{}




void	dgFormatDigit::vValueToString	(void)	{
	if(m_Signed) {
		// ******************************************** Signed parameter
		switch (m_ByteNum) {
		case 1:	vValueToStringByType <int8_t>	(); break;
		case 2: vValueToStringByType <int16_t>	();	break;
		case 4:	vValueToStringByType <int32_t>	();	break;
		}
	} else {
		// ******************************************** Unsigned parameter
		switch (m_ByteNum) {
		case 1:	vValueToStringByType <uint8_t> 	();	break;
		case 2:	vValueToStringByType <uint16_t> ();	break;
		case 4:	vValueToStringByType <uint32_t>	();	break;
		}
	}
    m_pStringValue = m_StringValue;

}




	// --------------------- Subroutine
void	dgFormatDigit::vSetStringValueLength	(void)	{
	m_StringValueLength 			= m_DigitNum;
	if(m_DecimalDigitNum)	m_StringValueLength++;
	if(m_Signed)			m_StringValueLength++;
}


template <class T>
void    dgFormatDigit::vValueToStringByType    (void) {

	//char* l_strData				{m_StringValue};
	uint8_t l_ExtraDigit		{0};
	uint8_t l_remandier;
	T		l_value 			{*(reinterpret_cast<T *>(m_pTemporValue))};

	vSetStringValueLength();
	uint8_t l_DecimalPointPosition {m_StringValueLength};

	if(m_Signed) {
		if(l_value < 0) {
			// execute the 1s'complement
			l_value = static_cast<T>(~l_value + 1);
			if(l_value < 0) {
				for(uint8_t i=0;i<m_StringValueLength;i++) {
					m_StringValueField[i] = '*';
				}
				m_StringValueField[m_StringValueLength] = 0;
				return;

			} else {
				m_StringValueField[0] = '-';
			}
		} else {
			m_StringValueField[0] = ' ';
		}
	}

	for(uint8_t i=0; i<m_StringValueLength; i++) {
		if((m_DecimalDigitNum==i) & (i)) {
			// set decimal point
			l_DecimalPointPosition						=  static_cast<uint8_t>(m_StringValueLength - (i+1));
			m_StringValueField[l_DecimalPointPosition]	= '.';
			l_ExtraDigit++;
		}
		switch (m_Encoding) {
		case kEncoding_Decimal:
			l_remandier	= static_cast<char>(l_value % 10);
			l_value		= l_value / 10;
			// m_StringValueLength - (i[digit] + l_ExtraDigit + 1[string null terminator])
			m_StringValueField[m_StringValueLength - (i+l_ExtraDigit+1)] = static_cast<char>('0' + l_remandier);
			break;
		case kEncoding_Hexadecimal:
		case kEncoding_BCD:
			char l_charDigit;
			l_remandier	= static_cast<char>(l_value & 0x0F);
			l_value		= static_cast<T>(l_value >> 4);
			if(l_remandier < 10) {
				l_charDigit = '0';
			} else {
				l_charDigit = static_cast<char>('A' - 10);
			}
			// m_StringValueLength - (i[digit] + l_ExtraDigit + 1[string null terminator])
			m_StringValueField[m_StringValueLength - (i+l_ExtraDigit+1)] = static_cast<char>(l_charDigit + l_remandier);
			break;
		}
	}

	m_StringValueField[m_StringValueLength] = 0;

	// leading zero trimming
	if(m_Signed) {
		for(uint8_t i=1;i<(m_StringValueLength-1);i++) {
			if('0' == m_StringValueField[i]) {
				if(l_DecimalPointPosition == i+1) {
					break;
				} else {
					m_StringValueField[i]	= m_StringValueField[i-1];
					m_StringValueField[i-1] = ' ';
				}
			} else {
				break;
			}
		}
	}
}

} } }	// namespace fw2::core::core
