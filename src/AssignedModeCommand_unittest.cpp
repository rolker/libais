#include <gtest/gtest.h>

#include <ais/AssignedModeCommand.h>

// !AIVDM,1,1,,A,@01EO1@P00PBH2pML78RU?w<24B<,0*51,raishub,1333247738
// inc_a 737
// inc_b 972
// mmsi 1400581
// repeat_indicator 0
// offset_a 2432
// offset_b 1343
// dest_mmsi_b 901892234
// spare 0
// id 16
// dest_mmsi_a 134218244

TEST(TestAssignedModeCommand, AisMsg16) {
    ais::BinaryPayload bp("@01EO1@P00PBH2pML78RU?w<24B<",0);
    ais::AssignedModeCommand m(bp);

    ASSERT_EQ(16,m.message_id);
    EXPECT_EQ(0,m.repeat_indicator);
    EXPECT_EQ(1400581,m.mmsi);

    EXPECT_EQ(0,m.spare);

    EXPECT_EQ(134218244, m.dest_mmsi_a);
    EXPECT_EQ(2432, m.offset_a);
    EXPECT_EQ(737, m.inc_a);

    EXPECT_EQ(901892234, m.dest_mmsi_b);
    EXPECT_EQ(1343, m.offset_b);
    EXPECT_EQ(972, m.inc_b);

    EXPECT_EQ(0,m.spare2);
}
