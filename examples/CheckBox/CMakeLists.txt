CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-MousePosition)

include(CMakeDetermineKOS32Compiler)
include(CMakeTestKOS32Compiler)
include(kolibriexe)

add_kolibri_executable(KolibriLib-CheckBox Checkbox.cpp)
target_link_libraries(KolibriLib-CheckBox PRIVATE KolibriLib)