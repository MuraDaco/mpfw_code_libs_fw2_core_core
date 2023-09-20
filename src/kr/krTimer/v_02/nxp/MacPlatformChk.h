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
 * MacPlatformChk.h
 *
 *  Created on: Nov, 22 2022
 *      Author: Marco Dau
 */

#include "lib/cg/cg_Platform.h"
#if (CG_PLATFORM != CG_PLATFORM_NXP)
	#error There is an error in platform selection due to
	#error 1) wrong synchronization between .cpp compiling files and ".h" header files or
	#error 	  Please, update CmakeLists.txt file to synchronize the ".cpp" and ".h" files
	#error 2) not correct selection of header file version in the ".h" header file
	#error    Please, fix it
#endif
