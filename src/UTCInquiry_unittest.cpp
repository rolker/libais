#include <gtest/gtest.h>

#include <ais/UTCInquiry.h>

// !AIVDM,1,1,,B,:819<LQGWBg@,0*7B,b003669973,1360713437
// spare2 0
// dest_mmsi 367479540
// mmsi 538070130
// repeat_indicator 0
// spare 0
// id 10

TEST(TestUTCInquiry, AisMsg10) {
    ais::BinaryPayload bp(":819<LQGWBg@",0);
    ais::UTCInquiry m(bp);

    ASSERT_EQ(10,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(538070130,m.mmsi);
    
    ASSERT_EQ(0, m.spare);

    ASSERT_EQ(367479540, m.dest_mmsi);

    ASSERT_EQ(0, m.spare2);
}

