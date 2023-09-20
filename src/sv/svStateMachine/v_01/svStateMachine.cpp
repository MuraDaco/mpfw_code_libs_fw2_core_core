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
 * svStateMachine.cpp
 *
 *  Created on: Sep 20, 2022
 *      Author: Marco Dau
 */

// verify module version 
#include "svStateMachineVerChk.h"

#include "svStateMachine.h"

svStateMachine*  svStateMachine::g_po[krThread_Num];

svStateMachine::svStateMachine (svState* p_StateArray, svState::state_t p_svStateStart, k_StateMachine_STATUS p_Status) :
     g_svStateArray     {p_StateArray   }
    ,g_svStateStart     {p_svStateStart }
    ,g_svStateActive    {p_svStateStart }
    ,g_Status           {p_Status       }
    ,g_SyncCmd          {svStateMachine::SyncCmdHandler }
{}


void svStateMachine::StateHandlerCall   (krThreadId p_ThreadId)  {

    for(uint8_t i=0;i<250;i++) {
		svState::state_t result;
        // check the end of svState Array
        if (svState::k_SvState_NULL == g_svStateArray[i].g_State) break;

        // check if the current svState instance is the active one
		if(g_svStateActive == g_svStateArray[i].g_State) {

            // check the state machine status
            if(k_StateMachine_STATUS_RUN == g_Status)   {
                result = g_svStateArray[i].StateRun(p_ThreadId);
            } else {
                result = svState::k_SvState_NULL;
            }

            // check if thread matches
            if (svState::k_SvState_THREAD_NOT_MATCH != result)  {
                // thread fits
                // therefore ...

                // perform the command/signal synchronization
                g_po[p_ThreadId] = this;
                g_SyncCmd.UpdateSyncResorces(p_ThreadId, result);
            }
        }
    }

	// SECTION - svSync
	g_SyncCmd.ResetSyncSignals	(p_ThreadId	);

}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ---------------------------------------------------------------  SERVICE: SYNCHRONIZATION --------------
// -------------------------------------------------- #include "../sv/svSync.h"

// ************************************************************ ATTRIBUTE

// ************************************************************** METHODS
void svStateMachine::SyncCmdHandler     (krThreadId p_ThreadId, svSync::sync_sgn_t p_sync_cmd, svSync::sync_val_t p_param)      {
    switch (p_sync_cmd) {
        // no signal and therefore no cmd to perform
        case svSync::k_svSyncSgn_NULL:
            if(svState::k_SvState_REPEAT != p_param) g_po[p_ThreadId]->g_svStateActive = p_param;
            return;
        break;
        // stop
        case k_svSync_CMD_STOP:
            g_po[p_ThreadId]->g_Status = k_StateMachine_STATUS_STOP;
        break;
        // -----
        // resume
        case k_svSync_CMD_RESUME:
            g_po[p_ThreadId]->g_Status = k_StateMachine_STATUS_RUN;
        break;
        // -----
        // restart
        case k_svSync_CMD_RESTART:
            g_po[p_ThreadId]->g_Status = k_StateMachine_STATUS_RUN;
            g_po[p_ThreadId]->g_svStateActive = g_po[p_ThreadId]->g_svStateStart;
            // when the active state is set/modified 
            // no other instruction can be done otherwise race condition may happen
            // so, immediately ... EXIT!!!
            return;
        break;
        // -----
        // jump to
        case k_svSync_CMD_JUMP_TO:
            g_po[p_ThreadId]->g_svStateActive = p_param;
            // when the active state is set/modified
            // no other instruction can be done otherwise race condition may happen
            // so, immediately ... EXIT!!!
            return;
        break;
        default:
        break;
    };
}

// ------------- END SERVICE: SYNCHRONIZATION ---------
// ::::::::::::::::::::::::::::::::::::::::::::::::::::
// ++++++++++++++++++++++++++++++++++++++++++++++++++++



void svStateMachine::CmdResume   (krThreadId p_ThreadId)  {
    g_SyncCmd.Send(p_ThreadId, k_svSync_CMD_RESUME);
    // the [status] will be modified         -> g_Status         = RUN
}

void svStateMachine::CmdStop   (krThreadId p_ThreadId)  {
    g_SyncCmd.Send(p_ThreadId, k_svSync_CMD_STOP);
    // the [status] will be modified         -> g_Status         = STOP
}

void svStateMachine::CmdRestart   (krThreadId p_ThreadId)  {
    g_SyncCmd.Send(p_ThreadId, k_svSync_CMD_RESTART);
    // the [active state] will be modified   -> g_svStateActive  = g_svStateStart
    // the [status] will be modified         -> g_Status         = RUN
}

void svStateMachine::CmdJumpTo   (krThreadId p_ThreadId, svSync::sync_val_t p_param)  {
    g_SyncCmd.Send(p_ThreadId, k_svSync_CMD_JUMP_TO, p_param);
    // the [active state] will be modified   -> g_svStateActive  = p_param
}

