if(WIN32)
    set(SDK_DIR "F:/kolibrios/contrib/sdk")
    set(TOOLCHAIN_DIR "C:/MinGW/msys/1.0/home/autobuild/tool/win32")
endif(WIN32)
if (UNIX)
    set(SDK_DIR "~/kolbrios/contrib")
    set(TOOLCHAIN_DIR "/home/autobuild/toold/win32")
endif (UNIX)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/kos32-g++)
set(CMAKE_LINKER ${TOOLCHAIN_DIR}/bin/kos32-ld)

set(NEWLIB_INCLUDE ${SDK_DIR}/source/libstdc++-v3/include)
set(LIBSTDCppV3_INCLUDE ${SDK_DIR}/source/newlib/libc/include)

#поключение newlib
include_directories(${NEWLIB_INCLUDE})

#подключение libstdc++-v3
include_directories(${LIBSTDCppV3_INCLUDE})

include_directories(src/include)