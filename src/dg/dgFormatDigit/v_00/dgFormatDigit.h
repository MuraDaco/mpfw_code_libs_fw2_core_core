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
 * dgFormatDigit.h
 *
 *  Created on: Jun 24, 2019
 *      Author: marco
 */

#ifndef DS_DGFORMATDIGIT_H_
#define DS_DGFORMATDIGIT_H_

// lib include
#include "lib/dg/dgInterface/v_00/dgInterface.h"


class dgFormatDigit: public dgInterface  {
public:
	dgFormatDigit   (
        void*       p_pTemporValue          ,
        uint8_t     p_ByteNum               ,
        uint8_t     p_DigitNum              ,   // must be coherent with m_ByteNum
        uint8_t     p_Encoding              ,   // Hex or Dec
        uint8_t     p_DecimalDigitNum       ,
		bool        p_Signed
    );

	dgFormatDigit   (
        void*       p_pTemporValue          ,
        uint8_t     p_ByteNum               ,
        uint8_t     p_DigitNum              ,   // must be coherent with m_ByteNum
        uint8_t     p_Encoding              ,   // Hex or Dec
        uint8_t     p_DecimalDigitNum       ,
        bool        p_Signed				,
		csCallback::boolOut_uint8In_t 	p_fDisplayable
    );

	dgFormatDigit   (
        void*  		p_pTemporValue          ,
		uint8_t		p_Index					,
        uint8_t     p_ByteNum               ,
        uint8_t     p_DigitNum              ,   // must be coherent with m_ByteNum
        uint8_t     p_Encoding              ,   // Hex or Dec
        uint8_t     p_DecimalDigitNum       ,
        bool        p_Signed				,
		csCallback::boolOut_uint8In_t 	p_fDisplayable
    );


    // ************************************************************ CONSTANTS
	enum kEncoding {
		kEncoding_Decimal,
		kEncoding_Hexadecimal,
		kEncoding_BCD,
		kEncodingNum
	};


    // ************************************************************ ATTRIBUTE

    void*       m_pTemporValue          ;
    uint8_t     m_DataType              ;
    uint8_t     m_ByteNum               ;
    uint8_t     m_DigitNum              ;   // must be coherent with m_ByteNum
    uint8_t     m_Encoding              ;   // Hex or Dec
    uint8_t     m_DecimalDigitNum       ;
    bool        m_Signed                ;
    // uint8_t     m_StartIdStringValue;
    
    static char*    m_StringValueField;
    static uint8_t  m_StringValueLength;




	// +++++++++++++++++++++ Interface
    virtual void    vValueToString     (void)   override;

	// --------------------- Subroutine
    void    vSetStringValueLength   		(void);
    template <class T>
    void    vValueToStringByType			(void);

    
};


#endif /* DS_DGFORMATDIGIT_H_ */
