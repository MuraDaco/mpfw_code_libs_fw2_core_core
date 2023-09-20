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
 * krThreadTbl.cpp
 *
 *  Created on: Sep, 19 2022
 *      Author: Marco Dau
 */

// verify module version 
#if (KR_THREAD_VER != 1)
	#error There is an error due to
	#error 1) wrong synchronization between .cpp compiling files and "../include/---.h" header files or
	#error 	  Please, update CmakeLists.txt file to synchronize the ".cpp" and "../include/---.h" files
	#error 2) not correct selection of header file version in the "../include/---.h" header file
	#error    Please, fix it
#endif

// lib include 
#include <kr/krThread/krThreadTbl.h>
#include <kr/krTimer/krTimerManager.h>
#include <sv/svStateMachine/svStateMachineManager.h>

#include <sv/svState/v_01/mg/tt_mg_StateManager.h>
#include <sv/svSync/v_01/mg/tt_mg_SyncManager.h>
#include <sv/svSync/v_02/mg/tt_mg_SyncManager_2.h>
#include <sv/svSync/v_03/mg/tt_mg_SyncManager_3.h>

krThreadTbl::ThreadLoopFunction_t krThreadTbl::LoopFunctionArray[] = {
    &krTimerManager                    ::LoopUpdate         ,
    &krTimerManager                    ::LoopCheck          ,
    &svStateMachineManager             ::Loop               ,
    &tt_mg_StateManager                ::ThreadUnitLoop     ,
    &tt_mg_SyncManager                 ::ThreadUnitLoop     ,
    &tt_mg_SyncManager_2               ::ThreadUnitLoop     ,
    &tt_mg_SyncManager_3               ::ThreadUnitLoop     ,
    nullptr                                                 
};


