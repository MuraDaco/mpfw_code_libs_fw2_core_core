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
 * apTestState01.cpp
 *
 *  Created on: Sep, 20 2022
 *      Author: Marco Dau
 */

#include "svMutex.h"


svMutex::svMutex()  :
    g_StMach    {svMutex::StMach_StateArray, k_State_THREAD_0, svStateMachine::k_StateMachine_STATUS_RUN   }
{}


svMutex*  svMutex::g_this[krThread_Num];

void svMutex::Loop	(krThreadId p_Thread)  {

    g_this[p_Thread] = this;
    g_StMach.StateHandlerCall(p_Thread);
}

bool svMutex::IsReady	(krThreadId p_Thread)  {
    bool result = false;
    if(k_ResourceStatus_READY == ResourceStatus[p_Thread]) {
        result = true;
    } else {
        // this statement allow to handle simultaneous request of the resource
        ResourceStatus[p_Thread] = k_ResourceStatus_WAITING;
    }
    return result;
}

void svMutex::Lock	    (krThreadId p_Thread)  {
    ResourceStatus[p_Thread] = k_ResourceStatus_WAITING;
}

void svMutex::Free	    (krThreadId p_Thread)  {
    ResourceStatus[p_Thread] = k_ResourceStatus_FREE;
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ---------------------------------------------------------------  SERVICE: STATE ------------------------
// -------------------------------------------------- #include "../sv/svState.h"

//
// State definition for svStateMachine_funct1
//


// ******************************************************************************************
// ******************************************************************************************
svState::state_t svMutex::StMach_StateThread_Handler (krThreadId p_Thread, svState::state_t p_State)  {
    // -----------------------------------------------------------------

    // check resource status
    if(k_ResourceStatus_FREE == g_this[p_Thread]->ResourceStatus[p_Thread])  {
        // the resource is free
        // jump to the next state/thread
        return svState::k_SvState_DEFAULT_NEXT;
    } else {
        g_this[p_Thread]->ResourceStatus[p_Thread] = k_ResourceStatus_READY;
    }
    
    // -----------------------------------------------------------------
    return p_State;
}

// ******************************************************************************************
// ******************************************************************************************
svState svMutex::StMach_StateArray [] = {
// -- status handler                        ,thread          ,state             ,next state
     {svMutex::StMach_StateThread_Handler   ,krThread_Zero   ,k_State_THREAD_0  ,k_State_THREAD_1}
    ,{svMutex::StMach_StateThread_Handler   ,krThread_One    ,k_State_THREAD_1  ,k_State_THREAD_2}
    ,{svMutex::StMach_StateThread_Handler   ,krThread_Two    ,k_State_THREAD_2  ,k_State_THREAD_3}
    ,{svMutex::StMach_StateThread_Handler   ,krThread_Three  ,k_State_THREAD_3  ,k_State_THREAD_0}
    ,svState::svStateNull
};


// ------------- END SERVICE: STATE -------------------
// ::::::::::::::::::::::::::::::::::::::::::::::::::::
// ++++++++++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ---------------------------------------------------------------  SERVICE: STATE MACHINE ----------------
// -------------------------------------------------- #include "../sv/svStateMachine.h"




