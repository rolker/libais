#include <gtest/gtest.h>

#include <ais/Acknowledge.h>

// !AIVDM,1,1,,A,=?lMpOGvtOPKDu8,2*20,d-125,S0195,t221905.00,T05.21261628,r05RTUC1,1360707552

TEST(TestAcknowledge, AisMsg13Exception) {
    ais::BinaryPayload bp("=?lMpOGvtOPKDu8",2);
    ASSERT_THROW(ais::Acknowledge m(bp), ais::exception);
}

// !AIVDM,1,1,,B,=9aGlQ8Sk3RbfkM=<gmH08u;Pp2`,0*0E
// mmsi 647361668
// repeat_indicator 0
// id 13
// acks [(150146602L, 2L), (785240908L, 2L), (1062600739L, 3L), (316727338L, 0L)]

TEST(TestAcknowledge, AisMsg13) {
    ais::BinaryPayload bp("=9aGlQ8Sk3RbfkM=<gmH08u;Pp2`",0);
    ais::Acknowledge m(bp);

    ASSERT_EQ(13,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(647361668,m.mmsi);

    ASSERT_EQ(150146602,m.dest_mmsi[0]);
    ASSERT_EQ(2,m.seq_num[0]);

    ASSERT_EQ(785240908,m.dest_mmsi[1]);
    ASSERT_EQ(2,m.seq_num[1]);

    ASSERT_EQ(1062600739,m.dest_mmsi[2]);
    ASSERT_EQ(3,m.seq_num[2]);

    ASSERT_EQ(316727338,m.dest_mmsi[3]);
    ASSERT_EQ(0,m.seq_num[3]);
}
