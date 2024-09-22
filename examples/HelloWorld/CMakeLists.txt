CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-MousePosition)

include(kolibriexe)

add_kolibri_executable(KolibriLib-HelloWorld HelloWorld.cpp)
target_link_libraries(KolibriLib-HelloWorld PRIVATE KolibriLib)