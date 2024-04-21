CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(KolibriLib)

################################################
################### CONFIG #####################
################################################
                                               #
set(DEBUG ON)                                  #
set(CUSTOM_TOOCLAIN_PATH OFF)                  #
set(KOLIBRIOS_REPO "../kolibrios")             #
                                               #
################################################







SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")
SET(LIB_DIR ${SDK_DIR}/lib)


set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")


#enable FASM
include(CMakeDetermineASM_FASMCompiler)
include(CMakeASM_FASMInformation)
include(CMakeTestASM_FASMCompiler)

enable_language("ASM_FASM")




if(WIN32)
    SET(TOOLCHAIN_DIR "C:/MinGW/msys/1.0/home/autobuild/tools/win32")
endif(WIN32)
if (UNIX)
    SET(TOOLCHAIN_DIR "/home/autobuild/tools/win32")
endif (UNIX)
if(CUSTOM_TOOCLAIN_PATH)
	SET(TOOLCHAIN_DIR CUSTOM_TOOCLAIN_PATH)
endif()

#Flags
SET(CMAKE_CXX_FLAGS  "-c -fpermissive -Wpointer-arith -Wreturn-local-addr -O2 -fomit-frame-pointer -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -Wparentheses")
SET(CMAKE_EXE_LINKER_FLAGS "-static -S -nostdlib --image-base 0 -T ${SDK_DIR}/sources/newlib/app.lds -L ${TOOLCHAIN_DIR}/lib -L ${LIB_DIR}/lib -lgcc -lc.dll  -lstdc++ -lsupc++ -lfreetype")

if(DEBUG)
	message("DEBUG ON")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MakeStaticLib__")

set(CMAKE_CXX_STANDARD 11)

set(LIBS_DIR ${SDK_DIR}/sources)

#поключение newlib
include_directories(${LIBS_DIR}/libstdc++-v3/include)

#подключение libstdc++-v3
include_directories(${LIBS_DIR}/newlib/libc/include)


include_directories(${LIBS_DIR}/freetype/include)

SET(SRC_PATH src)


# CONFIGURED C_Layer ASM
set(C_Layer_Path ${KOLIBRIOS_REPO}/contrib/C_Layer)
set(C_Layer_SRC_PATH ${C_Layer_Path}/ASM)

set(C_Layer_ASM_Sources
	${C_Layer_SRC_PATH}/loadlibimg.asm
	${C_Layer_SRC_PATH}/loadrasterworks.asm
	${C_Layer_SRC_PATH}/loadbuf2d.asm
)
include_directories(${KOLIBRIOS_REPO}/programs)


set(C_Layer_C_Sources
	${SRC_PATH}/C_Layer/kolibri_buf2d.c
	${SRC_PATH}/C_Layer/kolibri_libimg.c
	${SRC_PATH}/C_Layer/kolibri_rasterworks.c
)
include_directories("./include/C_Layer/INCLUDE")


# Compiler
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-g++)
SET(CMAKE_LINKER ${TOOLCHAIN_DIR}/bin/kos32-ld)
SET(CMAKE_AR ${TOOLCHAIN_DIR}/bin/kos32-ar)


include_directories("./include")






SET(SOURCES 
	${C_Layer_ASM_Sources}
	${C_Layer_C_Sources}
	${SRC_PATH}/freetypefuncs.cpp
	${SRC_PATH}/filesystem.cpp 
	${SRC_PATH}/color.cpp 
	${SRC_PATH}/os.cpp 
	${SRC_PATH}/graphic.cpp 
	${SRC_PATH}/font.cpp 
	${SRC_PATH}/thread.cpp 
	${SRC_PATH}/types.cpp 
	${SRC_PATH}/textBase.cpp 
	${SRC_PATH}/img.cpp 
	${SRC_PATH}/UI.cpp 
	${SRC_PATH}/image.cpp 
	${SRC_PATH}/char.cpp 
	${SRC_PATH}/text.cpp 
	${SRC_PATH}/textlabel.cpp 
	${SRC_PATH}/buttonsBase.cpp
	${SRC_PATH}/button.cpp 
	${SRC_PATH}/checkbox.cpp
	${SRC_PATH}/form.cpp
	${SRC_PATH}/menu.cpp
)


ADD_LIBRARY(KolibriLib STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(KolibriLib PUBLIC include)
TARGET_INCLUDE_DIRECTORIES(KolibriLib PUBLIC include/C_Layer/INCLUDE)