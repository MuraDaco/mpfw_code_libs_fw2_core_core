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

// verify module version 
#include "svSyncVerChk.h"

// module include
#include "svSync.h"

#define DYNAMIC_THREAD	krThread_Num

svSync::svSync(SyncResourcesHandler_t p_Handler)	:
	 g_Handler	{p_Handler		}
	,g_ThreadId	{DYNAMIC_THREAD	}
{
	for(uint8_t i=0; i<krThread_Num; i++)	{
		g_ArrayWrt[i] = 0;
		g_ArrayRdr[i] = 0;
		g_ArrayPar[i] = 0;
	}
}

svSync::svSync(SyncResourcesHandler_t p_Handler	,krThreadId p_ThreadId)	:
	 g_Handler	{p_Handler	}
	,g_ThreadId	{p_ThreadId	}
{
	for(uint8_t i=0; i<krThread_Num; i++)	{
		g_ArrayWrt[i] = 0;
		g_ArrayRdr[i] = 0;
		g_ArrayPar[i] = 0;
	}
}

void svSync::UpdateSyncResorces	(krThreadId p_ThreadId, __attribute__((unused)) sync_val_t p_param)	{
	if(
		(g_ThreadId == p_ThreadId		) ||
		(g_ThreadId == DYNAMIC_THREAD	)
	)	{
		bool l_cmd_performed = false;
		uint8_t l_Rdr;
		uint8_t l_Wrt;
		uint8_t l_Par;

		for(uint8_t i=0; i<krThread_Num; i++)	{
			l_Rdr = g_ArrayRdr[i];
			l_Wrt = g_ArrayWrt[i];
			l_Par = g_ArrayPar[i];

			if(k_svSyncSgn_NULL != l_Wrt)	{
				// RESET section

				// it means a command has been performed
				// now it needs to reset command signal
				// therefore ...

				// check if the reader are set to NULL
				if(k_svSyncSgn_NULL == l_Rdr)	{
					// the reader received the ACK and its command is set to NULL,
					// therefore ...
					// reset writer
					g_ArrayWrt[i] = k_svSyncSgn_NULL;
				} else {
					if(l_Wrt != l_Rdr)	{
						// there is a new command, 
						// it is not necessary reset writer
						g_ArrayWrt[i] = l_Rdr;
						l_cmd_performed = true;
						break;
					}
				}
			} else {
				// SET section

				if (k_svSyncSgn_NULL != l_Rdr)	{
					g_ArrayWrt[i] = l_Rdr;
					l_cmd_performed = true;
					break;
				}
			}
		}

		if(l_cmd_performed)	{
			g_Handler(p_ThreadId, l_Rdr, 			l_Par	);
		} else {
			g_Handler(p_ThreadId, k_svSyncSgn_NULL, p_param	);
		}	
		// WARNING !!!
		// VERY IMPORTANT !!!
		// no other statement must be put/appended after the following one
	}
}

void svSync::ResetSyncSignals	(krThreadId p_ThreadId)	{

	// RDR section
	uint8_t l_Rdr 	= g_ArrayRdr[p_ThreadId];
	if(k_svSyncSgn_NULL != l_Rdr)	{
		// it means a command request has been set from someone
		// now it needs to know if
		// . the command was performed
		// . or the command has to be performed yet
		// therefore ...

		// check results of previous execution
		if (l_Rdr == g_ArrayWrt[p_ThreadId])	{
			// At least one writer performed the command,
			// therefore ...
			// reset reader
			g_ArrayRdr[p_ThreadId] = k_svSyncSgn_NULL;
		}
	}

}

uint8_t svSync::Send		(krThreadId p_ThreadId, sync_sgn_t p_SyncSignal)	{
	uint8_t result = 0;
	if(p_SyncSignal != g_ArrayWrt[p_ThreadId])	{
		result = 1;
		g_ArrayRdr[p_ThreadId] = p_SyncSignal;
	}
	return result;
}

uint8_t svSync::Send		(krThreadId p_ThreadId, sync_sgn_t p_SyncSignal, sync_val_t p_param)	{
	uint8_t result = 0;
	if(p_SyncSignal != g_ArrayWrt[p_ThreadId])	{
		result = 1;
		g_ArrayRdr[p_ThreadId] = p_SyncSignal;
		g_ArrayPar[p_ThreadId] = p_param;
	}
	return result;
}

