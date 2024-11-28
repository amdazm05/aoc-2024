file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/inputs/*.in)

foreach(TF ${TEST_FILES})
    cmake_path(GET TF FILENAME filename)
    cmake_path(GET filename STEM exename)
    file(COPY_FILE ${TF} ${CMAKE_BINARY_DIR}/tests/${exename}.in)
endforeach()
