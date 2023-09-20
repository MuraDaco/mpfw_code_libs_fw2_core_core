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
 * svState.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Marco Dau
 */

#ifndef SV_STATE_H_
#define SV_STATE_H_

// verify module version 
#include "svStateVerChk.h"

// system include
#include <atomic>
#include <cstdint>

// lib include
#include "cg_krThread.h"

#define MAKE_svStateId(group, code) ((((svState::k_SvState_END) + (group)*20) + (code)))

class svState {
public:

	// ************* TYPEDEF ******************************
	typedef uint8_t state_t;
	typedef state_t (*StateHandler_t)	(krThreadId, state_t);
	// ************* END TYPEDEF **************************

	enum k_SvState {
		 k_SvState_NULL
		,k_SvState_THREAD_NOT_MATCH
		,k_SvState_NO_ACTIVE
		,k_SvState_DEFAULT_NEXT
		,k_SvState_REPEAT
		,k_SvState_END
	};

	StateHandler_t	g_StateHandler;
	krThreadId		g_ThreadId;
	state_t			g_State;
	state_t			g_StateNext;
	bool			g_Status;		// true: actived - false: dis-actived

	svState(														);
	svState(							state_t						);
	svState(StateHandler_t, krThreadId, state_t						);
	svState(StateHandler_t, krThreadId, state_t, state_t			);
	svState(StateHandler_t, krThreadId, state_t, state_t,	bool	);

	state_t StateRun		(krThreadId);
	state_t StateRunStatus	(krThreadId);
	bool    CheckThread	(krThreadId);
	void	StatusSet	(void);
	void	StatusClr	(void);
	bool	StatusChk	(void);

	static svState svStateNull;
};


#endif /* SV_STATE_H_ */
