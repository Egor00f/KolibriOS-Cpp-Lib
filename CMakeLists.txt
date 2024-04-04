CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(KolibriLib)

################################################
################### CONFIG #####################
################################################
                                               #
SET(DEBUG ON)                                  #
SET(KOLIBRIOS_REPO "../kolibrios")             #
                                               #
################################################










SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")
SET(LIB_DIR ${SDK_DIR}/lib)


SET(CMAKE_CXX_FLAGS  "-c -std=c++11 -fpermissive -Wpointer-arith -Wreturn-local-addr -O2 -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -Wparentheses")
SET(CMAKE_EXE_LINKER_FLAGS "-static -S -nostdlib --image-base 0 -T $(SDK_DIR)/sources/newlib/app.lds -L ${LIB_DIR}/lib -lgcc -lc.dll  -lstdc++  -lsupc++")


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MakeStaticLib__")

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

# stdlib
SET(NEWLIB_INCLUDE ${SDK_DIR}/sources/libstdc++-v3/include)
SET(LIBSTDCppV3_INCLUDE ${SDK_DIR}/sources/newlib/libc/include)

#поключение newlib
include_directories(${NEWLIB_INCLUDE})

#подключение libstdc++-v3
include_directories(${LIBSTDCppV3_INCLUDE})



# Compiler
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-g++)
SET(CMAKE_LINKER ${TOOLCHAIN_DIR}/bin/kos32-ld)
SET(CMAKE_AR ${TOOLCHAIN_DIR}/bin/kos32-ar)





include_directories("./include")
include_directories("./include/C_Layer/INCLUDE")


SET(SRC_PATH src)

SET(SOURCES 
	${SRC_PATH}/C_Layer/kolibri_buf2d.c
	${SRC_PATH}/C_Layer/kolibri_libimg.c
	${SRC_PATH}/filesystem.cpp 
	${SRC_PATH}/color.cpp 
	${SRC_PATH}/os.cpp 
	${SRC_PATH}/graphic.cpp 
	${SRC_PATH}/fonts.cpp 
	${SRC_PATH}/thread.cpp 
	${SRC_PATH}/types.cpp 
	${SRC_PATH}/textBase.cpp 
	${SRC_PATH}/img.cpp 
	${SRC_PATH}/UI.cpp 
	${SRC_PATH}/image.cpp 
	${SRC_PATH}/char.cpp 
	${SRC_PATH}/text.cpp 
	${SRC_PATH}/textlabel.cpp 
	${SRC_PATH}/button.cpp 
	${SRC_PATH}/checkbox.cpp
)


ADD_LIBRARY(KolibriLib STATIC ${SOURCES})
TARGET_INCLUDE_DIRECTORIES(KolibriLib PUBLIC include)

target_link_libraries(KolibriLib PUBLIC ${KOLIBRIOS_REPO}/contrib/C_Layer/OBJ/loadlibimg.obj)
target_link_libraries(KolibriLib PUBLIC ${KOLIBRIOS_REPO}/contrib/C_Layer/OBJ/loadbuf2d.obj)
target_link_libraries(KolibriLib PUBLIC ${KOLIBRIOS_REPO}/contrib/C_Layer/OBJ/loadrasterworks.obj)



