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


SET(C_LAYER_OBJ ${KOLIBRIOS_REPO}/contrib/C_Layer/OBJ)

include_directories("../include")

add_executable(Example example.cpp)

target_link_libraries(Example 
    ${C_LAYER_OBJ}/loadboxlib.obj 
    ${C_LAYER_OBJ}/loadbuf2d.obj 
    ${C_LAYER_OBJ}/loadlibimg.obj 
    ${C_LAYER_OBJ}/loadrasterworks.obj 
    ../build/libKolibriLib.a
)
