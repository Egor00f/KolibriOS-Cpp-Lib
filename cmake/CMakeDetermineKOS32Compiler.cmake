

SET(SDK_DIR "${REPO}/contrib/sdk")

set(LIBS_DIR ${SDK_DIR}/sources)
set(NEWLIB_DIR ${LIBS_DIR}/newlib)
set(LIBC_DIR ${NEWLIB_DIR}/libc)
set(LIBSTDCPP_DIR ${LIBS_DIR}/libstdc++-v3)


set(C_FLAGS "-fno-ident -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32")
set(CMAKE_C_COMPILER_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_COMPILER_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS}")

include_directories(
	${LIBC_DIR}/include
	${LIBSTDCPP_DIR}/include
)

link_directories(
	${SDK_DIR}/lib
	${TOOLCHAIN_DIR}/mingw32/lib
	${TOOLCHAIN_DIR}/lib
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -S -nostdlib --image-base 0 -T${NEWLIB_DIR}/app.lds -lgcc -lc.dll -lstdc++ -lsupc++")