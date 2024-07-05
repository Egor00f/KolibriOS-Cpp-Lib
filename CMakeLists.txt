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

#include_directories(${LIBS_DIR}/freetype/include)

SET(SRC_PATH src/KolibriLib)


# CONFIGURED C_Layer ASM
set(C_Layer_Path ${KOLIBRIOS_REPO}/contrib/C_Layer)
set(C_Layer_SRC_PATH ${C_Layer_Path}/ASM)

set(C_Layer_ASM_Sources
	${C_Layer_SRC_PATH}/loadlibimg.asm
	${C_Layer_SRC_PATH}/loadrasterworks.asm
	${C_Layer_SRC_PATH}/loadbuf2d.asm
)

set(C_Layer_C_Sources
	${SRC_PATH}/C_Layer/kolibri_buf2d.c
	${SRC_PATH}/C_Layer/kolibri_libimg.c
	${SRC_PATH}/C_Layer/kolibri_rasterworks.c
)

SET(SOURCES 
	${C_Layer_ASM_Sources}
	${C_Layer_C_Sources}
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

ADD_LIBRARY(KolibriLib STATIC ${SOURCES})

target_compile_options(KolibriLib PUBLIC -c -fpermissive -Wpointer-arith -Wreturn-local-addr -fomit-frame-pointer -Wparentheses -Wreorder -DDEBUG -Wall)

target_compile_options(KolibriLib PUBLIC -D__MakeStaticLib__)


target_include_directories(KolibriLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(KolibriLib PRIVATE ${KOLIBRIOS_REPO}/programs)



include(Doxygen)

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