CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-ProgressBar)

include(kolibriexe)

add_kolibri_executable(ProgressBar ProgressBar.cpp)
target_link_libraries(ProgressBar PRIVATE KolibriLib)