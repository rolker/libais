cmake_minimum_required (VERSION 2.8)
project (libais)

set (HEADERS
    ais.h
    ais8_001_22.h
    ais8_200_10.h
    ais8_366_22.h
)

set (SOURCES
    ais.cpp
    ais1_2_3
    ais4_11
    ais5
    ais7_13
    ais8 ais8_001_22 ais8_001_26 ais8_200_10 ais8_366_22
    ais9
    ais10 # :
    # ais11 ; - See 4
    ais12 # <
    # ais13 = See 7
    ais14 # >
    ais15 # ?
    ais16 # @
    ais17 # A
    ais18 # B
    ais19 # C
    ais20 # D
    ais21 # E
    ais22 # F
    ais23 # G
    ais24 # H
    ais25 # I
    ais26 # J
    ais27 # K
    # ais28 # L - Not yet defined
)

install(FILES ${HEADERS} DESTINATION include)

add_library(ais STATIC  ${SOURCES} )
install(TARGETS ais DESTINATION lib)

option(AIS_PYTHON "Build python bindings" ON)

if(AIS_PYTHON)
    find_package(PythonInterp REQUIRED)
    set (PYTHON_SOURCES ${SOURCES} ais_py.cpp)
    add_custom_target(python_build ALL ${PYTHON_EXECUTABLE} setup.py build --build-base ${CMAKE_BINARY_DIR}/python
                       DEPENDS ${SOURCES}
                       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                       COMMENT "python build"
                       SOURCES ${PYTHON_SOURCES}
                      )

    install(CODE "message(\"python install\")\n execute_process(COMMAND ${PYTHON_EXECUTABLE} setup.py -q build --build-base ${CMAKE_BINARY_DIR}/python install --prefix ${CMAKE_INSTALL_PREFIX} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})")
endif()

# testing support

option(BUILD_TESTS  "Enable testing." OFF)

if(BUILD_TESTS)
    add_subdirectory(gtest-1.6.0/)

    include_directories(${gtest_SOURCE_DIR}/include)

    set (TEST_SOURCES
        ais8_001_22_unittest
        ais8_200_10_unittest
    )

    enable_testing()

    add_executable(all_tests ${TEST_SOURCES})
    target_link_libraries(all_tests ais gtest_main)
    add_test(all_tests all_tests)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
