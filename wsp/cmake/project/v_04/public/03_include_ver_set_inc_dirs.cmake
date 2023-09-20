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

## ******************************************************************
## __________________________________________________________________
## INCLUDE DIRECTORIES Definitions

include(${CODE_MAIN_CMAKE_LIBS_FW2_CORE_CORE_VER_DEF_DIR}/set_class_src_ver.cmake)

## MODULE DIRECTORY Definitions
set(KR_EVENT_DIR                        krEvent/v_${KR_EVENT_VER}                                   )
set(KR_INIT_DIR                         krInit/v_${KR_INIT_VER}                                     )
set(KR_TIMER_DIR                        krTimer/v_${KR_TIMER_VER}                                   )

set(SV_SYNC_DIR                         svSync/v_${SV_SYNC_VER}                                     )
set(SV_STATE_DIR                        svState/v_${SV_STATE_VER}                                   )
set(SV_STATE_MACHINE_DIR                svStateMachine/v_${SV_STATE_MACHINE_VER}                    )

set(UY_PROTOCOL_DIR                     uyProtocol/v_${UY_PROTOCOL_VER}                             )
set(UY_PROTOCOL2_DIR                    uyProtocol2/v_${UY_PROTOCOL2_VER}                           )

set(DG_INTERFACE_DIR                    dgInterface/v_${DG_INTERFACE_VER}                           )
set(DG_FORMAT_DIGIT_DIR                 dgFormatDigit/v_${DG_FORMAT_DIGIT_VER}                      )


# TABLE MODULE DIRECTORY Definitions
set(TB_KR_THREAD_CPP_DIR                kr/krThread/v_${TB_KR_THREAD_VER}                           )
set(TB_KR_INIT_CPP_DIR                  kr/krInit/v_${TB_KR_INIT_VER}                               )
set(TB_KR_TIMER_CPP_DIR                 kr/krTimer/v_${TB_KR_TIMER_VER}                             )
set(TB_SV_STATE_MACHINE_CPP_DIR         sv/svStateMachine/v_${TB_SV_STATE_MACHINE_VER}              )


# INCLUDE CONFIG DIRECTORY Definitions
set(DT_DEF_DIR                          dtDef/v_${DT_DEF_VER}                                       )


set(LIBS_FW2_CORE_CORE_SRC_DIR      ${LIBS_FW2_CORE_CORE_DIR}/src                               )

set(CODE_DIR_LIB_FW2_INCLUDE
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/cg
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/cs
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/dt/${DT_DEF_DIR}

    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_EVENT_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_INIT_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/kr/${KR_TIMER_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_SYNC_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_STATE_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/sv/${SV_STATE_MACHINE_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/uy/${UY_PROTOCOL_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/uy/${UY_PROTOCOL2_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/dg/${DG_INTERFACE_DIR}
    ${LIBS_FW2_CORE_CORE_SRC_DIR}/dg/${DG_FORMAT_DIGIT_DIR}

)

