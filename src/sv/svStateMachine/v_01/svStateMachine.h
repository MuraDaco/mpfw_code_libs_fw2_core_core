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
 * svStateMachine.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Marco Dau
 */

#ifndef SV_STATE_MACHINE_H_
#define SV_STATE_MACHINE_H_

// verify module version 
#include "svStateMachineVerChk.h"

#include <cstdint>
#include <array>
#include "../../../cg/cg_krThread.h"
#include "../../../cg/cg_lib_svState.h"
#include "../../../cg/cg_lib_svSync.h"
#include "../../../sv/svState/svState.h"
#include "../../../sv/svSync/svSync.h"




class svStateMachine {
public:


	enum k_StateMachine_STATUS {
		 k_StateMachine_STATUS_STOP
		,k_StateMachine_STATUS_RUN
	};
	
    static svStateMachine*  g_po[];
	svState*                g_svStateArray;
    svState::state_t        g_svStateStart;
    svState::state_t        g_svStateActive;
    k_StateMachine_STATUS   g_Status;
    
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// ---------------------------------------------------------------  SERVICE: SYNCHRONIZATION --------------
	// -------------------------------------------------- #include "../sv/svSync.h"

	// ************************************************************ CONSTANTS

	enum k_svSync_CMD {
		 k_svSync_CMD_STOP       = MAKE_svSyncSgn(k_cg_lib_svSyncSgn_Group_svStateMachine_01, 0)
		,k_svSync_CMD_RESUME
		,k_svSync_CMD_RESTART
		,k_svSync_CMD_JUMP_TO
	};
	


	// ************************************************************ ATTRIBUTE
    svSync  g_SyncCmd;

	// ************************************************************** METHODS
    static void SyncCmdHandler     (krThreadId, svSync::sync_sgn_t, svSync::sync_val_t);

	// ------------- END SERVICE: SYNCHRONIZATION ---------
	// ::::::::::::::::::::::::::::::::::::::::::::::::::::
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++

    svStateMachine (svState*, svState::state_t, k_StateMachine_STATUS);

    void StateHandlerCall   (krThreadId         );
    void CmdStop            (krThreadId         );
    void CmdResume          (krThreadId         );
    void CmdRestart         (krThreadId         );
    void CmdJumpTo          (krThreadId, svSync::sync_val_t);

};


#endif /* SV_STATE_MACHINE_H_ */
