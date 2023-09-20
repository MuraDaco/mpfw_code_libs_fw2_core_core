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
 * apTestState01.h
 *
 *  Created on: Sep, 20 2022
 *      Author: Marco Dau
 */

#ifndef SV_MUTEX_H_
#define SV_MUTEX_H_

#include <array>
#include <cstdint>

#include "../kr/krThreadId.h"
#include "../cg/lib/cg_lib_svState.h"
#include "../sv/svStateMachine.h"


class svMutex {
public:

	svMutex();
    static svMutex*  g_this[];


	// ************************************************************ CONSTANTS
	enum k_ResourceStatus	{
		 k_ResourceStatus_FREE
		,k_ResourceStatus_WAITING
		,k_ResourceStatus_READY
	};


	k_ResourceStatus ResourceStatus[krThread_Num];

	void Loop		(krThreadId);
	bool IsReady	(krThreadId);
	void Lock		(krThreadId);
	void Free		(krThreadId);

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// ---------------------------------------------------------------  SERVICE: STATE ------------------------
	// -------------------------------------------------- #include "../sv/svState.h"
	// -------------------------------------------------- #include "../cg/cg_svState.h"

	//
	// State definition for svStateMachine_funct1
	//
	// ************************************************************ CONSTANTS
		enum k_State	{
			 k_State_THREAD_0		= MAKE_svStateId(k_cg_lib_svState_Group_svMutex,0)
			,k_State_THREAD_1
			,k_State_THREAD_2
			,k_State_THREAD_3
		};

	// ************************************************************ ATTRIBUTE
		static svState StMach_StateArray[];

	// ************************************************************** METHODS
		static svState::state_t StMach_StateThread_Handler (krThreadId, svState::state_t);

		// ------------- END SERVICE: STATE -------------------
	// ::::::::::::::::::::::::::::::::::::::::::::::::::::
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// ---------------------------------------------------------------  SERVICE: STATE MACHINE ----------------
	// -------------------------------------------------- #include "../sv/svStateMachine.h"

	// ************************************************************ CONSTANTS

	// ************************************************************ ATTRIBUTE
	svStateMachine g_StMach;

	// ************************************************************** METHODS

	// ------------- END SERVICE: STATE MACHINE -----------
	// ::::::::::::::::::::::::::::::::::::::::::::::::::::
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++

};


#endif /* SV_MUTEX_H_ */
