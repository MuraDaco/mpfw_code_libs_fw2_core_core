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
 * svState.cpp
 *
 *  Created on: Sep 20, 2022
 *      Author: Marco Dau
 */

// module include
#include "svState.h"

namespace fw2 { namespace core { namespace core {


svState::svState() :
	 g_StateHandler		{nullptr				}
	,g_State			{svState::k_SvState_NULL}
	,g_Status			{false					}
{}

svState::svState(state_t p_State) :
	 g_StateHandler		{nullptr	}
	,g_State			{p_State	}
	,g_Status			{false		}
{}

svState::svState(StateHandler_t p_StateHandler, krThreadId p_ThreadId, state_t p_State) :
	 g_StateHandler		{p_StateHandler	}
	,g_ThreadId			{p_ThreadId		}
	,g_State			{p_State		}
	,g_StateNext		{p_State		}
	,g_Status			{false			}
{}

svState::svState(StateHandler_t p_StateHandler, krThreadId p_ThreadId, state_t p_State, state_t p_StateNext) :
	 g_StateHandler		{p_StateHandler	}
	,g_ThreadId			{p_ThreadId		}
	,g_State			{p_State		}
	,g_StateNext		{p_StateNext	}
	,g_Status			{false			}
{}

svState::svState(StateHandler_t p_StateHandler, krThreadId p_ThreadId, state_t p_State, state_t p_StateNext, bool p_Status) :
	 g_StateHandler		{p_StateHandler	}
	,g_ThreadId			{p_ThreadId		}
	,g_State			{p_State		}
	,g_StateNext		{p_StateNext	}
	,g_Status			{p_Status		}
{}

svState::state_t svState::StateRun	(krThreadId p_ThreadId)	{
	state_t result = k_SvState_THREAD_NOT_MATCH;
	if (g_ThreadId == p_ThreadId) {
		result = g_StateHandler(p_ThreadId, g_State);
		if(k_SvState_DEFAULT_NEXT == result) result = g_StateNext;
	};
	return result;
}

svState::state_t svState::StateRunStatus	(krThreadId p_ThreadId)	{
	state_t result = k_SvState_THREAD_NOT_MATCH;
	if (g_ThreadId == p_ThreadId) {
		result = k_SvState_NO_ACTIVE;
		if(g_Status)	{
			result = g_StateHandler(p_ThreadId, g_State);
			if(k_SvState_DEFAULT_NEXT == result) result = g_StateNext;
			if (g_State != result)	{
				// the handler return a value different from g_Status, 
				// it means that the current state instance must be disabled
				// therefore ...
				// turn off the state
				g_Status = false;
			}
		}
	}
	return result;
}

bool svState::CheckThread	(krThreadId p_ThreadId)	{
	return (g_ThreadId == p_ThreadId);
}


void svState::StatusSet		(void)	{
	g_Status = true;
}

void svState::StatusClr		(void)	{
	g_Status = false;
}

bool svState::StatusChk		(void)	{
	return g_Status;
}



svState svState::svStateNull(svState::k_SvState_NULL);
//svState svState::svStateNull();

} } }	// namespace fw2::core::core
