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
 * krTimer.cpp
 *
 *  Created on: Sep, 16 2022
 *      Author: Marco Dau
 */

// verify module version 
#include "../krTimerVerChk.h"
// verify platform 
#include "MacPlatformChk.h"


// module include
#include "krTimer.h"

krTimer::krTimer(ptrEventHandler_t tmrEventHandler, krThreadId p_ThreadId, krTimer_STATUS p_StatusInit) :
	 krEvent 				{tmrEventHandler}
	,g_RdrThreadId 			{p_ThreadId}
	,g_StatusRdr 			{static_cast<uint8_t>(p_StatusInit)}
	,g_TimerRechargeValue 	{300}
	,g_Timer				{g_TimerRechargeValue}

{
}


void krTimer::UpdateTimer	(krThreadId p_ThreadId)	{
	// this function MUST be called from the writer thread
	// check thread id
	if(krThread_InterruptRIT == p_ThreadId) {
		uint8_t l_CmdRdr 	= g_CmdRdr;		// read command from reader
		uint8_t l_StatusRdr = g_StatusRdr;	// read status from reader

		// check commands
		if (g_CmdWtr != l_CmdRdr) {
			if (kTimer_CMD_RECHARGE == l_CmdRdr)	{
				// new cmd has to be execute
				g_Timer  = g_TimerRechargeValue;
				// update cmd writer to avoid repeat the command in the next cycle
				// and send the ack to the reader
				g_CmdWtr = kTimer_CMD_RECHARGE;
			} else if (kTimer_CMD_NONE == l_CmdRdr) {
				// reset cmd writer 
				// it stands the reader received the ACK
				// and this the ACK of ACK of reader
				g_CmdWtr = kTimer_CMD_NONE;
			}
		}	// if (g_CmdWtr == l_CmdRdr) => nothing has to be done

		// check status
		if(krTimer_STATUS_RUN == l_StatusRdr)	{
			if(g_Timer > 1) {
				g_Timer--;
			} else if(g_Timer == 1) {
				if(krTimer_FLIP_FLOP_TIMER_NOT_ELAPSED == g_StatusFlipFlop)	{
					g_StatusFlipFlop = krTimer_FLIP_FLOP_TIMER_ELAPSED; 
				}
				if(krTimer_MODE_REPEAT == g_Mode) {
					g_Timer = g_TimerRechargeValue;
				} else {
					g_Timer = 0;
				}
			}
		}

	}
}

void krTimer::CheckTimer	(krThreadId p_ThreadId)	{
	// this function MUST be called from the reader thread (thread with id = g_RdrThreadId)

	if(g_RdrThreadId == p_ThreadId) {
		// check status
		if(krTimer_FLIP_FLOP_TIMER_ELAPSED == g_StatusFlipFlop)	{
			// call event function
			eventHandler();
			// "reset" status timer to "not elapsed"
			g_StatusFlipFlop = krTimer_FLIP_FLOP_TIMER_NOT_ELAPSED;
		}

		uint8_t l_CmdWtr 	= g_CmdWtr;		// read command from writer
		// check commands
		if (l_CmdWtr == g_CmdRdr) {
			if (kTimer_CMD_RECHARGE == g_CmdRdr)	{
				// OK! the command has been processed
				// this is an ACK from writer
				// now the command can be reset
				g_CmdRdr = kTimer_CMD_NONE;
			}
		} 

	}
}

void krTimer::SetCmd	(krThreadId p_ThreadId, kTimer_CMD p_cmd)	{
	// this function MUST be called from the reader thread

	if(g_RdrThreadId == p_ThreadId) {
		switch (p_cmd)	{
			case kTimer_CMD_RECHARGE:
				g_CmdRdr = p_cmd;
				g_StatusRdr = krTimer_STATUS_RUN;
			break;
			case kTimer_CMD_STOP:
				g_StatusRdr = krTimer_STATUS_STOP;
			break;
			case kTimer_CMD_RESUME:
				g_StatusRdr = krTimer_STATUS_RUN;
			break;
			case kTimer_CMD_NONE:
			default:
			break;
		}
	}
}

void krTimer::SetMode	(krThreadId p_ThreadId, krTimer_MODE p_mode)	{
	// this function MUST be called from the reader thread

	if(g_RdrThreadId == p_ThreadId) {
		switch (p_mode)	{
			case krTimer_MODE_REPEAT:
			case krTimer_MODE_NONE:
				g_Mode = p_mode;
			break;
			default:
			break;
		}
	}
}

void krTimer::SetChargeValue	(krThreadId p_ThreadId, uint32_t  p_value)	{
	// this function MUST be called from the reader thread

	if(g_RdrThreadId == p_ThreadId) {
		g_TimerRechargeValue = p_value;
	}
}


void krTimer::IncChargeValue	(krThreadId p_ThreadId, uint32_t  p_value)	{
	// this function MUST be called from the reader thread

	if(g_RdrThreadId == p_ThreadId) {
		uint32_t l_value = g_TimerRechargeValue;
		l_value += p_value;
		g_TimerRechargeValue = l_value;
	}
}

void krTimer::DecChargeValue	(krThreadId p_ThreadId, uint32_t  p_value)	{
	// this function MUST be called from the reader thread

	if(g_RdrThreadId == p_ThreadId) {
		uint32_t l_value = g_TimerRechargeValue;
		if(l_value > p_value) {
			l_value -= p_value;
			g_TimerRechargeValue = l_value;
		}
	}
}
