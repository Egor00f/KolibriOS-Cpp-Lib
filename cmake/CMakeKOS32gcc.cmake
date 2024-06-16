
message("Toolchain dir: " ${TOOLCHAIN_DIR})

# Compiler
SET(CMAKE_C_COMPILER "kos32-gcc")
SET(CMAKE_CXX_COMPILER "kos32-g++")
SET(CMAKE_LINKER "kos32-ld")
SET(CMAKE_AR "kos32-ar")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32")

set(LIBS_DIR ${SDK_DIR}/sources)

#поключение newlib
include_directories(${LIBS_DIR}/libstdc++-v3/include)

#подключение libstdc++-v3
include_directories(${LIBS_DIR}/newlib/libc/include)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -S -nostdlib --image-base 0 -T ${SDK_DIR}/sources/newlib/app.lds -L ${TOOLCHAIN_DIR}/lib -L ${LIB_DIR}/lib -lgcc -lc.dll  -lstdc++ -lsupc++")