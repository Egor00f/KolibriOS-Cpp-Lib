CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(KolibriLibExamples CXX)

################################################
################### CONFIG #####################
################################################
                                               #
SET(DEBUG ON)                                  #
SET(KOLIBRIOS_REPO "../../kolibrios")          #
                                               #
################################################



set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

SET(SDK_DIR "${KOLIBRIOS_REPO}/contrib/sdk")
SET(LIB_DIR ${SDK_DIR}/lib)

include(CMakeLoadToolchainPath)
if(CUSTOM_TOOCLAIN_PATH)
	SET(TOOLCHAIN_DIR CUSTOM_TOOCLAIN_PATH)
endif()

include(CMakeKOS32gcc)



SET(C_LAYER_OBJ ${KOLIBRIOS_REPO}/contrib/C_Layer/OBJ)

include_directories("../include")

add_executable(Example example.cpp)

target_link_libraries(Example 
    ${C_LAYER_OBJ}/loadbuf2d.obj 
    ${C_LAYER_OBJ}/loadlibimg.obj 
    ${C_LAYER_OBJ}/loadrasterworks.obj 
    ../build/libKolibriLib.a
)
