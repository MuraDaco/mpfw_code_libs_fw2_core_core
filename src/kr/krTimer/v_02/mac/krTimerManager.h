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
 * krTimerManager.h
 *
 *  Created on: Sep, 19 2022
 *      Author: Marco Dau
 */

#ifndef KR_TIMER_MANAGER_H_
#define KR_TIMER_MANAGER_H_

// verify module version 
#include "../krTimerVerChk.h"
// verify platform 
#include "MacPlatformChk.h"

// module include
#include "krTimer.h"

// system include
#include <cstdint>

// lib include
#include "cg_krThread.h"



class krTimerManager {
public:

	static krTimerManager& getInstance()
	{
		static krTimerManager instance;

		return instance;
	}

	static void LoopUpdate	 			(krThreadId	p_u32Thread	);
	static void LoopCheck 				(krThreadId	p_u32Thread	);

	static void SetUnitPtrArrayPtr		(krTimer** p_PtrTimerRefObj);


private:
	krTimerManager() {}

	static krTimer** g_PtrTimerRefObj;


};



#endif /* KR_TIMER_MANAGER_H_ */
