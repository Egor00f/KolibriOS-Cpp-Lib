cmake_minimum_required(VERSION 3.10)

project(KolibriLib)

set(SDK_DIR "F:/KolibriOs/contrib/sdk")
set(TOOLCHAIN_DIR "C:/MinGW/msys/1.0/home/autobuild/tool//win32")

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-g++)
set(CMAKE_LINKER ${TOOLCHAIN_DIR}/bin/kos32-ld)

set(NEWLIB_INCLUDE ${SDK_DIR}/source/libstdc++-v3/include)
set(LIBSTDCppV3_INCLUDE ${SDK_DIR}/source/newlib/libc/include)



include_directories(include)

add_subdirectory(executables)
add_subdirectory(examples)