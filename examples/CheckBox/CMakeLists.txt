CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-CheckBox)

include(kolibriexe)

add_kolibri_executable(CheckBox Checkbox.cpp)
target_link_libraries(CheckBox PRIVATE KolibriLib)