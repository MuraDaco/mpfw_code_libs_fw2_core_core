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
 * krTimer.h
 *
 *  Created on: Sep, 16 2022
 *      Author: Marco Dau
 */

#ifndef KR_TIMER_H_
#define KR_TIMER_H_

// system include
#include <cstdint>

// lib/cg include
#include "cg_krThread.h"
#include "krEvent.h"


namespace fw2 { namespace core { namespace core {


class krTimer: public krEvent {
public:
	krThreadId g_RdrThreadId;

	uint8_t  g_StatusRdr;			// only reader thread modifies it
	uint8_t  g_CmdRdr;				// only reader thread modifies it
	uint8_t  g_Mode;				// only reader thread modifies it

	uint8_t  g_StatusFlipFlop;		// writer & reader can write only in a specific states; the two sets of status are disjunct between them

	uint8_t  g_CmdWtr;				// only writer thread modifies it
	uint32_t g_TimerRechargeValue;	// writer thread may only read it
	uint32_t g_Timer;				// only writer thread modifies it


	enum kTimer_CMD {
		 kTimer_CMD_NONE						= 0
		,kTimer_CMD_RECHARGE					= 1
		,kTimer_CMD_STOP						= 2
		,kTimer_CMD_RESUME						= 3
	};
	
	enum krTimer_STATUS {
		krTimer_STATUS_STOP						= 0,
		krTimer_STATUS_RUN						= 1
	};
	
	enum krTimer_FLIP_FLOP {
		krTimer_FLIP_FLOP_TIMER_NOT_ELAPSED		= 0,	// when set, only writer can write
		krTimer_FLIP_FLOP_TIMER_ELAPSED			= 1		// when set, only reader can write
	};
	
	enum krTimer_MODE {
		krTimer_MODE_NONE						= 0,
		krTimer_MODE_REPEAT						= 1
	};
	
	

	krTimer(ptrEventHandler_t tmrEventHandler, krThreadId p_ThreadId, krTimer_STATUS p_StatusInit);

	void UpdateTimer	(krThreadId p_ThreadId);
	void CheckTimer		(krThreadId p_ThreadId);
	void SetCmd			(krThreadId p_ThreadId, kTimer_CMD  p_cmd);
	void SetMode		(krThreadId p_ThreadId, krTimer_MODE p_mode);
	void SetChargeValue	(krThreadId p_ThreadId, uint32_t     p_value);
	void IncChargeValue	(krThreadId p_ThreadId, uint32_t     p_value);
	void DecChargeValue	(krThreadId p_ThreadId, uint32_t     p_value);
};

} } }	// namespace fw2::core::core

#endif /* KR_TIMER_H_ */
