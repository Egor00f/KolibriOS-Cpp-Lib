################### Doxygen #####################################

MACRO(ADD_DOCUMENTATION)

   FIND_PACKAGE(Doxygen)

   IF(DOXYGEN_FOUND)
      set(DOXYGEN_GENERATE_HTML YES)
      set(DOXYGEN_PROJECT_NUMBER ${PROJECT_NUMBER})
      set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Docs)
      set(DOXYGEN_IMAGE_PATH ${DOXYGEN_OUTPUT_DIRECTORY}/media)
      doxygen_add_docs(doc ${CMAKE_SOURCE_DIR} )

   ELSE(DOXYGEN_FOUND)
      MESSAGE(STATUS "Doxygen not found. Documentation will not be generated")
   ENDIF(DOXYGEN_FOUND)
   
ENDMACRO(ADD_DOCUMENTATION)