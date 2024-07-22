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
set(KOLIBRIOS_REPO	../kolibrios)
#
#################################################




get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(IS_SUBPROJECT)
	set(BuildExamples OFF)
endif()


SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#enable FASM
include(CMakeDetermineASM_FASMCompiler)
include(CMakeASM_FASMInformation)
include(CMakeTestASM_FASMCompiler)

enable_language("ASM_FASM")

#include toochain
include(CMakeLoadToolchainPath)
if(CUSTOM_TOOCLAIN_PATH)
	SET(TOOLCHAIN_DIR CUSTOM_TOOCLAIN_PATH)
endif()

include(CMakeKOS32gcc)



set(CMAKE_CXX_STANDARD 11)




# CONFIGURED C_Layer ASM
set(C_Layer_Path ${KOLIBRIOS_REPO}/contrib/C_Layer)
set(C_Layer_SRC_PATH ${C_Layer_Path}/ASM)

set(C_LAYER_LOADERS_SOURCES
	${C_Layer_SRC_PATH}/loadlibimg.asm
	${C_Layer_SRC_PATH}/loadrasterworks.asm
	${C_Layer_SRC_PATH}/loadbuf2d.asm
)

# PATH TO KOLIBRILIb SOURCES
SET(SRC_PATH src/KolibriLib)

set(C_LAYER_KOLIBRILIB_SOURCES
	${SRC_PATH}/C_Layer/kolibri_buf2d.c
	${SRC_PATH}/C_Layer/kolibri_libimg.c
	${SRC_PATH}/C_Layer/kolibri_rasterworks.c
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
	${SRC_PATH}/button.cpp
	${SRC_PATH}/checkbox.cpp
	${SRC_PATH}/form.cpp
	#${SRC_PATH}/menu.cpp
)

#LOADERS THAT LOAD SHARED C_LAYER LIBS
ADD_LIBRARY(C_LAYER_LOADERS OBJECT ${C_LAYER_LOADERS_SOURCES})
target_include_directories(C_LAYER_LOADERS PRIVATE ${KOLIBRIOS_REPO}/programs)


ADD_LIBRARY(C_LAYER_KOLIBRILIB OBJECT ${C_LAYER_KOLIBRILIB_SOURCES})

target_link_libraries(C_LAYER_KOLIBRILIB PUBLIC C_LAYER_LOADERS)

target_include_directories(C_LAYER_KOLIBRILIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


ADD_LIBRARY(KolibriLib STATIC ${SOURCES})

target_link_libraries(KolibriLib PUBLIC C_LAYER_KOLIBRILIB)

target_compile_options(KolibriLib PUBLIC -c -fpermissive -fomit-frame-pointer)

target_compile_options(KolibriLib PUBLIC -D__MakeStaticLib__)

target_include_directories(KolibriLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# INCLUDE MACROSS FOR GENERATE DOXYGEN
include(Doxygen)

#GENERATE DOXYGEN ONLY THIS PROJECT ISNT SUBPROECT
if(NOT IS_SUBPROJECT)
	SET(DOXY_OUTPUT_LANGUAGE "Russian")

	SET(DOXY_INPUT ${PROJECT_SOURCE_DIR})

	ADD_DOCUMENTATION(doc "${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile")

endif()


#Examples build with make, see to examples/Makefile
set(ExamplesDir ${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_custom_target(
	Examples
	COMMAND make
	DEPENDS KolibriLib
	WORKING_DIRECTORY ${ExamplesDir}
	COMMENT "Build Example"
	SOURCES ${ExamplesDir}/example.cpp ${ExamplesDir}/Makefile
)
