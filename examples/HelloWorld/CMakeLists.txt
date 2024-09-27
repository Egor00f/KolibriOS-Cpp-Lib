CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-HelloWorld)

include(kolibriexe)

add_kolibri_executable(HelloWorld HelloWorld.cpp)
target_link_libraries(HelloWorld PRIVATE KolibriLib)