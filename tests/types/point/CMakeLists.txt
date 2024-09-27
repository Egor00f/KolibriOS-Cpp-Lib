CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

include(kolibriexe)

add_kolibri_executable(KolibriLib-point-test point_test.cpp)
target_link_libraries(KolibriLib-point-test PRIVATE KolibriLib)