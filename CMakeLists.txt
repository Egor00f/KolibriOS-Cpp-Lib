CMAKE_MINIMUM_REQUIRED(VERSION 3.8)


project(
	KolibriLib
	VERSION 0.0.3
)

#################################################
################### CONFIG ######################
#################################################
#
set(CUSTOM_TOOCLAIN_PATH	OFF)
set(KOLIBRIOS_REPO	${CMAKE_CURRENT_SOURCE_DIR}/../kolibrios)#Репозиторий нужен только для libc, libstdc++-v3 и C_Layer, можете указать свой если очень хочется
#
#################################################


set(CMAKE_CXX_STANDARD 11)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)


set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#enable FASM
include(CMakeDetermineASM_FASMCompiler)
include(CMakeASM_FASMInformation)
include(CMakeTestASM_FASMCompiler)

enable_language("ASM_FASM")

SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")


get_filename_component(REPO ${KOLIBRIOS_REPO} REALPATH)
set(KOLIBRIOS_REPO ${REPO})
if(EXISTS "${REPO}")
	message("KOLIBRIOS REPO Found: ${KOLIBRIOS_REPO}")
else()
	message(FATAL_ERROR "KOLIBRIOS Repo not found, try set KOLIBRIOS_REPO or download kolibros repo")
endif()





#include toochain
include(CMakeLoadToolchainPath)
if(CUSTOM_TOOCLAIN_PATH)
	SET(TOOLCHAIN_DIR CUSTOM_TOOCLAIN_PATH)
endif()

set(LIBS_DIR ${SDK_DIR}/sources)

set(NEWLIB_DIR ${LIBS_DIR}/newlib)
set(LIBC_DIR ${NEWLIB_DIR}/libc)
set(LIBSTDCPP_DIR ${LIBS_DIR}/libstdc++-v3)

#поключение newlib
include_directories(
	${LIBC_DIR}/include
	${LIBSTDCPP_DIR}/include
)

link_directories(
	${SDK_DIR}/lib
	${TOOLCHAIN_DIR}/mingw32/lib
	${TOOLCHAIN_DIR}/lib
)





set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

set(CMAKE_C_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

# CONFIGURED C_Layer ASM
set(C_Layer_Path ${KOLIBRIOS_REPO}/contrib/C_Layer)
set(C_Layer_SRC_PATH ${C_Layer_Path}/ASM)

# PATH TO KOLIBRILIB SOURCES
SET(SRC_PATH src/KolibriLib)
SET(HEADERS_PATH include/kolibriLib)
SET(C_LAYER_HEADERS include/C_Layer/INCLUDE)

set(C_LAYER_LOADERS_SOURCES
	${C_Layer_SRC_PATH}/loadlibimg.asm
	${C_Layer_SRC_PATH}/loadrasterworks.asm
	${C_Layer_SRC_PATH}/loadbuf2d.asm
	${C_LAYER_HEADERS}/kolibri_buf2d.h
	${C_LAYER_HEADERS}/kolibri_libimg.h
	${C_LAYER_HEADERS}/kolibri_rasterworks.h
)

set(C_LAYER_KOLIBRILIB_SOURCES
	${SRC_PATH}/C_Layer/kolibri_buf2d.c
	${SRC_PATH}/C_Layer/kolibri_libimg.c
	${SRC_PATH}/C_Layer/kolibri_rasterworks.c
	${C_LAYER_HEADERS}/kolibri_buf2d.h
	${C_LAYER_HEADERS}/kolibri_libimg.h
	${C_LAYER_HEADERS}/kolibri_rasterworks.h
)

SET(SOURCES
	${SRC_PATH}/filesystem.cpp
	${SRC_PATH}/color.cpp
	${SRC_PATH}/os.cpp
	${SRC_PATH}/graphic.cpp
	${SRC_PATH}/img.cpp
	${SRC_PATH}/thread.cpp
	${SRC_PATH}/types.cpp
	${SRC_PATH}/textBase.cpp
	${SRC_PATH}/UI.cpp
	${SRC_PATH}/image.cpp
	${SRC_PATH}/text.cpp
	${SRC_PATH}/textlabel.cpp
	${SRC_PATH}/buttonsBase.cpp
	${SRC_PATH}/BaseButton.cpp
	${SRC_PATH}/Button.cpp
	${SRC_PATH}/TextButton.cpp
	${SRC_PATH}/ImageButton.cpp
	${SRC_PATH}/checkbox.cpp
	${SRC_PATH}/form.cpp
	#${SRC_PATH}/menu.cpp
	${SRC_PATH}/window.cpp
	${SRC_PATH}/windowAttached.cpp
	${SRC_PATH}/debug.cpp
	${SRC_PATH}/globals.cpp
	${SRC_PATH}/freetype.cpp
	${SRC_PATH}/keyboard.cpp
	${HEADERS_PATH}/init.hpp
	${HEADERS_PATH}/types.hpp
	${HEADERS_PATH}/color.hpp
	${HEADERS_PATH}/system/os.hpp
	${HEADERS_PATH}/system/thread.hpp
	${HEADERS_PATH}/system/filesystem.hpp
	${HEADERS_PATH}/UI/UI.hpp
	${HEADERS_PATH}/UI/checkbox.hpp
	${HEADERS_PATH}/UI/buttons/button.hpp
	${HEADERS_PATH}/UI/buttons/buttonsBase.hpp
	${HEADERS_PATH}/UI/buttons/TextButton.hpp
	${HEADERS_PATH}/UI/buttons/ImageButton.hpp
	${HEADERS_PATH}/window/window.hpp
	${HEADERS_PATH}/window/windowBase.hpp
	${HEADERS_PATH}/window/windowAttached.hpp
)

#LOADERS THAT LOAD SHARED C_LAYER LIBS
ADD_LIBRARY(C_LAYER_LOADERS OBJECT ${C_LAYER_LOADERS_SOURCES})

target_include_directories(C_LAYER_LOADERS PRIVATE ${KOLIBRIOS_REPO}/programs)


ADD_LIBRARY(C_LAYER_KOLIBRILIB OBJECT ${C_LAYER_KOLIBRILIB_SOURCES})

target_include_directories(C_LAYER_KOLIBRILIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(C_LAYER_KOLIBRILIB
	PRIVATE -c -D__MakeStaticLib__
)

ADD_LIBRARY(KolibriLib STATIC ${SOURCES})
target_link_libraries(KolibriLib 
	PUBLIC C_LAYER_KOLIBRILIB
	PUBLIC C_LAYER_LOADERS
)


target_compile_options(KolibriLib 
	PRIVATE -c -D__MakeStaticLib__
	PUBLIC -fomit-frame-pointer
)

target_include_directories(KolibriLib
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PUBLIC ${KOLIBRIOS_REPO}/contrib/sdk/sources/freetype/include
)

# INCLUDE MACROSS FOR GENERATE DOXYGEN
include(Doxygen)

#GENERATE DOXYGEN ONLY THIS PROJECT ISNT SUBPROECT
if(NOT IS_SUBPROJECT)
	SET(DOXY_OUTPUT_LANGUAGE "Russian")

	SET(DOXY_INPUT ${PROJECT_SOURCE_DIR})

	ADD_DOCUMENTATION(doc ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile)

endif()


#Examples build with make, see to examples/Makefile
set(ExamplesDir ${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_custom_target(
	Example
	COMMAND make
	DEPENDS KolibriLib
	WORKING_DIRECTORY ${ExamplesDir}
	COMMENT "Build Example"
	SOURCES ${ExamplesDir}/example.cpp ${ExamplesDir}/Makefile
)

#add_executable(Example ${ExamplesDir}/example.cpp)
#target_link_libraries(Example PUBLIC KolibriLib)
