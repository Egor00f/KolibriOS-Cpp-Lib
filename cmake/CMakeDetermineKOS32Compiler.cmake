set(TOOLCHAIN_DIR "")
#include toochain
include(CMakeLoadToolchainPath)
if(CUSTOM_TOOCLAIN_PATH)
	SET(TOOLCHAIN_DIR CUSTOM_TOOCLAIN_PATH)
endif()


get_filename_component(REPO ${KOLIBRIOS_REPO} REALPATH)
SET(SDK_DIR "${REPO}/contrib/sdk")

set(LIBS_DIR ${SDK_DIR}/sources)
set(NEWLIB_DIR ${LIBS_DIR}/newlib)
set(LIBC_DIR ${NEWLIB_DIR}/libc)
set(LIBSTDCPP_DIR ${LIBS_DIR}/libstdc++-v3)


set(C_FLAGS "-fno-ident -fomit-frame-pointer -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32")
set(CMAKE_C_COMPILER_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_COMPILER_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS}")


include_directories(
	${LIBC_DIR}/include
	${LIBSTDCPP_DIR}/include
)


set(CMAKE_C_LINK_EXECUTABLE   "<CMAKE_LINKER> <LINK_FLAGS> -o <TARGET> <OBJECTS> --start-group -lgcc -lc.dll <LINK_LIBRARIES> --end-group <CMAKE_C_LINK_FLAGS>")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> -o <TARGET> <OBJECTS> --start-group -lgcc -lc.dll -lstdc++ -lsupc++ <LINK_LIBRARIES> --end-group <CMAKE_CXX_LINK_FLAGS>")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -S --image-base 0 -nostdlib -T${NEWLIB_DIR}/app.lds -L${TOOLCHAIN_DIR}/lib -L${TOOLCHAIN_DIR}/mingw32/lib -L${SDK_DIR}/lib --subsystem native")
