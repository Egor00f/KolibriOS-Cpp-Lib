CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-MousePosition)


include(kolibriexe)

add_kolibri_executable(KolibriLib-MousePosition mousePosition.cpp)
target_link_libraries(KolibriLib-MousePosition PRIVATE KolibriLib)