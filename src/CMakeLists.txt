
set (SOURCES 
)

set (TEST_SOURCES
    ais_unittest.cpp
    PositionReport_unittest.cpp
)

if(BUILD_TESTS)
    add_executable(gtests ${TEST_SOURCES})
    target_link_libraries(gtests ais ${TEST_LIBS})
    add_test(gtests all_tests)

endif()