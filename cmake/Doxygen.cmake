################### Doxygen #####################################

MACRO(ADD_DOCUMENTATION)

   FIND_PACKAGE(Doxygen)

   IF(DOXYGEN_FOUND)
      set(DOXYGEN_GENERATE_HTML YES)
      set(DOXYGEN_PROJECT_NUMBER ${PROJECT_NUMBER})
      set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Docs)
      doxygen_add_docs(doc ${CMAKE_SOURCE_DIR})

   ELSE(DOXYGEN_FOUND)
      MESSAGE(STATUS "Doxygen not found. Documentation will not be generated")
   ENDIF(DOXYGEN_FOUND)
   
ENDMACRO(ADD_DOCUMENTATION)