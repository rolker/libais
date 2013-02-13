#include <gtest/gtest.h>

#include <ais/Interrogation.h>

// !AIVDM,1,1,,A,?000<@j@C`<PD00000000000000,2*76
// spare4 0
// mmsi_2 0
// slot_offset_2 0
// spare3 0
// spare2 0
// mmsi_1 605266120
// mmsi 3139
// repeat_indicator 0
// msg_2 0
// slot_offset_1_1 0
// dest_msg_1_2 0
// spare 0
// msg_1_1 5
// id 15
// slot_offset_1_2 0


TEST(TestInterrogation, AisMsg15) {
    ais::BinaryPayload bp("?000<@j@C`<PD00000000000000",2);
    ais::Interrogation m(bp);

    ASSERT_EQ(15,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(3139,m.mmsi);

    ASSERT_EQ(605266120,m.mmsi_1);
    ASSERT_EQ(5, m.msg_1_1);
    ASSERT_EQ(0, m.slot_offset_1_1);
    ASSERT_EQ(0, m.msg_1_2);
    ASSERT_EQ(0, m.slot_offset_1_1);

    ASSERT_EQ(0,m.mmsi_2);
    ASSERT_EQ(0, m.msg_2);
    ASSERT_EQ(0, m.slot_offset_2);
}

// !AIVDM,1,1,,B,?3a=j00rEmE@D01?nOqnHVrF0ECE,0*5D
// Ais15: AIS_ERR_BAD_BIT_COUNT

TEST(TestInterrogation, AisMsg15_2) {
    ais::BinaryPayload bp("?3a=j00rEmE@D01?nOqnHVrF0ECE",2);
    ais::Interrogation m(bp);

    ASSERT_EQ(15,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(244544000,m.mmsi);

    ASSERT_EQ(244700500,m.mmsi_1);
    ASSERT_EQ(5, m.msg_1_1);
    ASSERT_EQ(0, m.slot_offset_1_1);
    ASSERT_EQ(15, m.msg_1_2);
    ASSERT_EQ(0, m.slot_offset_1_1);

    ASSERT_EQ(661006057,m.mmsi_2);
    ASSERT_EQ(24, m.msg_2);
    ASSERT_EQ(85, m.slot_offset_2);
}
