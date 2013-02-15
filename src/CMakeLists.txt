
set (SOURCES 
)

set (TEST_SOURCES
    ais_unittest.cpp
    PositionReport_unittest.cpp
    BaseStationReport_unittest.cpp
    ShipStaticAndVoyage_unittest.cpp
    AddressedBinaryMessage_unittest.cpp
    Acknowledge_unittest.cpp
    BinaryBroadcastMessage_unittest.cpp
    UTCInquiry_unittest.cpp
    AddressedSafetyMessage_unittest.cpp
    SafetyBroadcastMessage_unittest.cpp
    Interrogation_unittest.cpp
    AssignedModeCommand_unittest.cpp
)

if(BUILD_TESTS)
    add_executable(gtests ${TEST_SOURCES})
    target_link_libraries(gtests gtest_main)
    add_test(gtests all_tests)
endif()
