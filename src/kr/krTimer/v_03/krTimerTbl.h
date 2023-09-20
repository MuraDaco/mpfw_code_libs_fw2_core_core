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
 * krTimerTbl.h
 *
 *  Created on: Sep, 19 2022
 *      Author: Marco Dau
 */

#ifndef KR_TIMER_TBL_H_
#define KR_TIMER_TBL_H_

// module include
#include "krTimer.h"

namespace fw2 { namespace core { namespace core {


class krTimerTbl {
public:

	static krTimer*  krTimerPtrArray[];
	static krTimer** krTimerPtr2Array[];

};

} } }	// namespace fw2::core::core

#endif /* KR_TIMER_TBL_H_ */
