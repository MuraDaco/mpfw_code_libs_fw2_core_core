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
 * cg_lib_svSync.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Marco Dau
 */

#ifndef CG_SV_SYNC_H_
#define CG_SV_SYNC_H_

#define MAKE_svSyncSgn_Group(group) ((k_cg_lib_svSyncSgn_Group_END) + (group))

namespace fw2 { namespace core { namespace core {

enum k_cg_lib_svSyncSgn_Group {
	 k_cg_lib_svSyncSgn_Group_svState_01
	,k_cg_lib_svSyncSgn_Group_svState_02
	,k_cg_lib_svSyncSgn_Group_svStateMachine_01
	,k_cg_lib_svSyncSgn_Group_krTimer_01
	,k_cg_lib_svSyncSgn_Group_END
};

} } }	// namespace fw2::core::core


#endif /* CG_SV_SYNC_H_ */
