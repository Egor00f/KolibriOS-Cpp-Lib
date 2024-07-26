#
# 
#
#
#

message("Toolchain dir: " ${TOOLCHAIN_DIR})

# Compiler
SET(CMAKE_C_COMPILER	"${TOOLCHAIN_DIR}/bin/kos32-gcc")
SET(CMAKE_CXX_COMPILER	"${TOOLCHAIN_DIR}/bin/kos32-g++")
SET(CMAKE_LINKER	"${TOOLCHAIN_DIR}/bin/kos32-ld${SUFFIX}")
SET(CMAKE_AR	"${TOOLCHAIN_DIR}/bin/kos32-ar${SUFFIX}")
set(CMAKE_C_COMPILER_AR	"${TOOLCHAIN_DIR}/bin/kos32-gcc-ar${SUFFIX}")
set(CMAKE_CXX_COMPILER_AR	"${TOOLCHAIN_DIR}/bin/kos32-gcc-ar${SUFFIX}")
set(CMAKE_STRIP	"${TOOLCHAIN_DIR}/bin/kos32-strip${SUFFIX}")
#SET(CMAKE_C_LINK_EXECUTABLE ${CMAKE_LINKER})
#SET(CMAKE_CXX_LINK_EXECUTABLE ${CMAKE_LINKER})

set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "11")
set(CMAKE_CXX_COMPILER_VERSION "5.4.0")

set(CMAKE_C_USING_LINKER_LLD ${CMAKE_LINKER})
set(CMAKE_C_USING_LINKER_MODE TOOL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32")



SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")
set(LIBS_DIR ${SDK_DIR}/sources)

#поключение newlib
include_directories(
	${LIBS_DIR}/libstdc++-v3/include
	${LIBS_DIR}/newlib/libc/include
)

link_directories(
	${SDK_DIR}/lib
	${TOOLCHAIN_DIR}/mingw32/lib
	${TOOLCHAIN_DIR}/lib
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -S -nostdlib -T ${SDK_DIR}/sources/newlib/app.lds -L ${TOOLCHAIN_DIR}/lib -L ${LIB_DIR}/lib -lgcc -lc.dll -lstdc++ -lsupc++")