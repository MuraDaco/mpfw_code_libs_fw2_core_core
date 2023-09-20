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
 * krTimerManager.cpp
 *
 *  Created on: Sep, 19 2022
 *      Author: Marco Dau
 */

// module include
#include "krTimerTbl.h"
#include "krTimerManager.h"

namespace fw2 { namespace core { namespace core {


void krTimerManager::LoopUpdate (krThreadId p_thread) {
	krTimer** l_PtrTimerRefObj;
	l_PtrTimerRefObj = krTimerTbl::krTimerPtrArray;
	while (l_PtrTimerRefObj[0]) {
		l_PtrTimerRefObj[0]->UpdateTimer(p_thread);
		l_PtrTimerRefObj++;
	}

	krTimer*** l_Ptr2TimerRefObj;
	l_Ptr2TimerRefObj = krTimerTbl::krTimerPtr2Array;
	while (l_Ptr2TimerRefObj[0]) {
		l_PtrTimerRefObj = l_Ptr2TimerRefObj[0];
		while (l_PtrTimerRefObj[0]) {
			l_PtrTimerRefObj[0]->UpdateTimer(p_thread);
			l_PtrTimerRefObj++;
		}
		l_Ptr2TimerRefObj++;
	}

}

void krTimerManager::LoopCheck (krThreadId p_thread) {
	krTimer** l_PtrTimerRefObj;

	l_PtrTimerRefObj = krTimerTbl::krTimerPtrArray;
	while (l_PtrTimerRefObj[0]) {
		l_PtrTimerRefObj[0]->CheckTimer(p_thread);
		l_PtrTimerRefObj++;
	}

	krTimer*** l_Ptr2TimerRefObj;
	l_Ptr2TimerRefObj = krTimerTbl::krTimerPtr2Array;
	while (l_Ptr2TimerRefObj[0]) {
		l_PtrTimerRefObj = l_Ptr2TimerRefObj[0];
		while (l_PtrTimerRefObj[0]) {
			l_PtrTimerRefObj[0]->CheckTimer(p_thread);
			l_PtrTimerRefObj++;
		}
		l_Ptr2TimerRefObj++;
	}
}


} } }	// namespace fw2::core::core

