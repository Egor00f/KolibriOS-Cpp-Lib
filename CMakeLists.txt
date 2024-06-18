CMAKE_MINIMUM_REQUIRED(VERSION 3.8)


project(
	KolibriLib
	VERSION 0.0.3
)

#################################################
################### CONFIG ######################
#################################################
#
set(DEBUG	ON)
set(CUSTOM_TOOCLAIN_PATH	OFF)
set(KOLIBRIOS_REPO	"../kolibrios")
set(BuildExamples	ON)
set(INSTALL_LIB	ON)
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



#Flags
SET(CMAKE_CXX_FLAGS  "-c -fpermissive -Wpointer-arith -Wreturn-local-addr -fomit-frame-pointer -Wparentheses")
#SET(CMAKE_EXE_LINKER_FLAGS "-lfreetype")

if(DEBUG)
	message("DEBUG ON")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
else()
	message("DEBUG OFF")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__MakeStaticLib__")

set(CMAKE_CXX_STANDARD 11)

#include_directories(${LIBS_DIR}/freetype/include)

include_directories(any)

SET(SRC_PATH src)


# CONFIGURED C_Layer ASM
set(C_Layer_Path ${KOLIBRIOS_REPO}/contrib/C_Layer)
set(C_Layer_SRC_PATH ${C_Layer_Path}/ASM)

set(C_Layer_ASM_Sources
	${C_Layer_SRC_PATH}/loadlibimg.asm
	${C_Layer_SRC_PATH}/loadrasterworks.asm
	${C_Layer_SRC_PATH}/loadbuf2d.asm
)
include_directories(${KOLIBRIOS_REPO}/programs)


set(C_Layer_C_Sources
	${SRC_PATH}/C_Layer/kolibri_buf2d.c
	${SRC_PATH}/C_Layer/kolibri_libimg.c
	${SRC_PATH}/C_Layer/kolibri_rasterworks.c
)
include_directories("./include/C_Layer/INCLUDE")


include_directories("./include")

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
	${SRC_PATH}/menu.cpp
)

ADD_LIBRARY(KolibriLib STATIC ${SOURCES})


target_include_directories(KolibriLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

################### Doxygen #####################################

MACRO(CONFIGURE_DOXYGEN_FILE DOXYGEN_CONFIG_FILE FILE_NAME_SUFFIX)

 IF(EXISTS ${DOXYGEN_CONFIG_FILE})

    FILE(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/doxy-${FILE_NAME_SUFFIX}.conf)

    FILE(READ ${DOXYGEN_CONFIG_FILE} DOXYFILE_CONTENTS)

     STRING(REGEX REPLACE ";" "\\\\;" DOXYFILE_CONTENTS "${DOXYFILE_CONTENTS}")

     STRING(REGEX REPLACE "\n" ";" DOXYFILE_LINES "${DOXYFILE_CONTENTS}")

     LIST(LENGTH DOXYFILE_LINES ROW)

     MATH(EXPR ROW "${ROW} - 1")

     FOREACH(I RANGE ${ROW})

        LIST(GET DOXYFILE_LINES ${I} LINE)

        IF(LINE STRGREATER "")

         STRING(REGEX MATCH "^[a-zA-Z]([^ ])+" DOXY_PARAM ${LINE})

         IF(DEFINED DOXY_${DOXY_PARAM})

            STRING(REGEX REPLACE "=([^\n])+" "= ${DOXY_${DOXY_PARAM}}" LINE ${LINE})

         ENDIF(DEFINED DOXY_${DOXY_PARAM})

        ENDIF()

        FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/doxy-${FILE_NAME_SUFFIX}.conf "${LINE}\n")

     ENDFOREACH()

 ELSE()

    MESSAGE(SEND_ERROR "Doxygen configuration file '${DOXYGEN_CONFIG_FILE}' not found. Documentation will not be generated")

 ENDIF()

ENDMACRO(CONFIGURE_DOXYGEN_FILE)


MACRO(ADD_DOCUMENTATION TARGET DOXYGEN_CONFIG_FILE)

   FIND_PACKAGE(Doxygen)

   IF(DOXYGEN_FOUND)
      CONFIGURE_DOXYGEN_FILE(${DOXYGEN_CONFIG_FILE} ${TARGET})

      ADD_CUSTOM_TARGET(${TARGET} COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxy-${TARGET}.conf)

   ELSE(DOXYGEN_FOUND)
      MESSAGE(STATUS "Doxygen not found. Documentation will not be generated")

   ENDIF(DOXYGEN_FOUND)
   
ENDMACRO(ADD_DOCUMENTATION)



if(NOT IS_SUBPROJECT)
	SET(DOXY_OUTPUT_LANGUAGE "Russian")

	SET(DOXY_INPUT ${PROJECT_SOURCE_DIR})

	ADD_DOCUMENTATION(doc "${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile")

endif()


if(INSTALL_LIB)
	
	message("Install Lib ON")
	
	add_custom_command(TARGET KolibriLib POST_BUILD
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/install ${TOOLCHAIN_DIR} ${CMAKE_CURRENT_BINARY_DIR}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Install Lib"
	)
	
endif(INSTALL_LIB)

if(BuildExamples)
	message("Build Examples ON")
	
	
	#Examples build with make, see to examples/Makefile
	add_custom_command(TARGET KolibriLib POST_BUILD
		COMMAND make
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples
		COMMENT "Build Example"
	)
endif(BuildExamples)