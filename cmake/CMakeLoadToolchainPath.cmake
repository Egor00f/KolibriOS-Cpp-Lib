if(CMAKE_HOST_WIN32)
    SET(TOOLCHAIN_DIR "C:/MinGW/msys/1.0/home/autobuild/tools/win32")
else()
    SET(TOOLCHAIN_DIR "/home/autobuild/tools/win32")
endif()

get_filename_component(TOOLCHAIN_DIR_REAL ${TOOLCHAIN_DIR} REALPATH)
if(EXISTS "${TOOLCHAIN_DIR_REAL}")
	message("KOLIBRIOS toolchain Found: ${TOOLCHAIN_DIR_REAL}")
else()
	message(FATAL_ERROR "KOLIBRIOS toolchain not found, try set CUSTOM_TOOCLAIN_PATH or download toolchain repo" ${TOOLCHAIN_DIR_REAL})
endif()

set(TOOLCHAIN_DIR ${TOOLCHAIN_DIR_REAL})