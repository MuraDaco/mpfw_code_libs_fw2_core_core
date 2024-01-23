#   *******************************************************************************
#   
#   mpfw / fw2 - Multi Platform FirmWare FrameWork 
#       library that contains the essential code that is used in every application
#   Copyright (C) (2023) Marco Dau
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#   
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
#   
#   You can contact me by the following email address
#   marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
#   
#   *******************************************************************************
##################################################################################
## _______________________________________________________________________________
## RELATIVE PATH Definitions

##################################################################################
## Relative path from CMakeLists.txt project folder                             ##
##################################################################################

#set(LIBS_FW2_CORE_CORE_SRC_DIR      ${LIBS_FW2_CORE_CORE_DIR}/src                               )


set(CODE_FILES_LIB_KR_EVENT
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_EVENT_DIR}/krEvent.cpp
)

set(CODE_FILES_LIB_KR_INIT
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_INIT_DIR}/krInit.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_INIT_DIR}/krInitStaticManager.cpp
)

set(CODE_FILES_LIB_KR_TIMER
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_TIMER_DIR}/krTimer.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_TIMER_DIR}/krTimerManager.cpp
)

set(CODE_FILES_LIB_SV_SYNC
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_SYNC_DIR}/svSync.cpp
)

set(CODE_FILES_LIB_SV_STATE
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_STATE_DIR}/svState.cpp
)

set(CODE_FILES_LIB_SV_STATE_MACHINE
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_STATE_MACHINE_DIR}/svStateMachine.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_STATE_MACHINE_DIR}/svStateMachineManager.cpp
)

set(CODE_FILES_LIB_UY_PROTOCOL
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/uy/${UY_PROTOCOL_DIR}/uyProtocol.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/uy/${UY_PROTOCOL2_DIR}/uyProtocol2.cpp
)

set(CODE_FILES_LIB_DG_INTERFACE
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/dg/${DG_INTERFACE_DIR}/dgInterface.cpp
)

set(CODE_FILES_LIB_DG_FORMAT_DIGIT
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/dg/${DG_FORMAT_DIGIT_DIR}/dgFormatDigit.cpp
)


set(CODE_FILES_LIB_TB
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/tb/${TB_KR_THREAD_CPP_DIR}/krThreadTbl.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/tb/${TB_KR_INIT_CPP_DIR}/krInitStaticTbl.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/tb/${TB_KR_TIMER_CPP_DIR}/krTimerTbl.cpp
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/tb/${TB_SV_STATE_MACHINE_CPP_DIR}/svStateMachineTbl.cpp
)



## ******************************************************************
#________________________________________
## LIB FILES

set(CODE_CPP_FILES_FW2_LIB

    ${CODE_FILES_LIB_KR_EVENT}
    ${CODE_FILES_LIB_KR_INIT}
    ${CODE_FILES_LIB_KR_TIMER}

    ${CODE_FILES_LIB_SV_SYNC}
    ${CODE_FILES_LIB_SV_STATE}
    ${CODE_FILES_LIB_SV_STATE_MACHINE}

    ${CODE_FILES_LIB_UY_PROTOCOL}
    ${CODE_FILES_LIB_DG_FORMAT_DIGIT}
    ${CODE_FILES_LIB_DG_INTERFACE}

    ${CODE_FILES_LIB_TB}

)
