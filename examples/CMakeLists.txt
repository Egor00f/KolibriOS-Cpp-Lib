CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(KolibriLibExamples)

################################################
################### CONFIG #####################
################################################
                                               #
SET(DEBUG ON)                                  #
SET(KOLIBRIOS_REPO "../../kolibrios")          #
                                               #
################################################






SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")
SET(LIB_DIR ${SDK_DIR}/lib)

link_directories(${LIB_DIR})

SET(CMAKE_CXX_FLAGS  "-c -std=c++11 -fpermissive -Wpointer-arith -Wreturn-local-addr -O2 -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -Wparentheses")
SET(CMAKE_EXE_LINKER_FLAGS "-static -S -nostdlib -T $(SDK_DIR)/sources/newlib/app.lds -L ${LIB_DIR}/lib -lgcc -lc.dll  -lstdc++  -lsupc++")

if(DEBUG)
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -D DEBUG")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



if(WIN32)
    SET(TOOLCHAIN_DIR "C:/MinGW/msys/1.0/home/autobuild/tools/win32")
endif(WIN32)
if (UNIX)
    SET(TOOLCHAIN_DIR "/home/autobuild/tools/win32")
endif (UNIX)

#поключение newlib
include_directories(${SDK_DIR}/sources/libstdc++-v3/include)

#подключение libstdc++-v3
include_directories(${SDK_DIR}/sources/newlib/libc/include)

include_directories("../include")
include_directories("../include/C_Layer/INCLUDE")

# Compiler
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-g++)
SET(CMAKE_CXX_LINKER ${TOOLCHAIN_DIR}/bin/kos32-ld)
SET(CMAKE_AR ${TOOLCHAIN_DIR}/bin/kos32-ar)

SET(C_LAYER_OBJ ${KOLIBRIOS_REPO}/contrib/C_Layer/OBJ)




add_executable(Example example.cpp)

target_link_libraries(Example 
    ${C_LAYER_OBJ}/loadboxlib.obj 
    ${C_LAYER_OBJ}/loadbuf2d.obj 
    ${C_LAYER_OBJ}/loadlibimg.obj 
    ${C_LAYER_OBJ}/loadrasterworks.obj 
    ../build/libKolibriLib.a
)