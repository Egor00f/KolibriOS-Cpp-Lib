CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(KolibriLib-MousePosition)


include(kolibriexe)

add_kolibri_executable(MousePosition mousePosition.cpp)
target_link_libraries(MousePosition PRIVATE KolibriLib)