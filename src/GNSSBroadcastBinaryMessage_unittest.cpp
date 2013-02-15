#include <gtest/gtest.h>

#include <ais/GNSSBroadcastBinaryMessage.h>


// !AIVDM,2,1,1,B,A02V?Hib3Qba07h1fg5h8wuJ40dhwAwv2k;uoOT;<wu4vPdiwiOk2jCvIgT;,0*3D,raishub,1333238404
// !AIVDM,2,2,1,B,:gmM4@dawKd@2h00,0*5A,raishub,1333238404
// Ais17: AIS_ERR_MSG_TOO_LONG

TEST(TestGNSSBroadcastBinaryMessage, AisMsg17) {
    ais::BinaryPayload bp("A02V?Hib3Qba07h1fg5h8wuJ40dhwAwv2k;uoOT;<wu4vPdiwiOk2jCvIgT;:gmM4@dawKd@2h00",0);
    ais::GNSSBroadcastBinaryMessage m(bp);

    ASSERT_EQ(17,m.message_id);
    EXPECT_EQ(0,m.repeat_indicator);
    EXPECT_EQ(2723683,m.mmsi);

    EXPECT_EQ(0,m.spare);
    EXPECT_FLOAT_EQ(181, m.x);
    EXPECT_FLOAT_EQ(91, m.y);
    EXPECT_EQ(0,m.spare2);
    
    EXPECT_EQ(31,m.msg_type);
    EXPECT_EQ(1,m.station_id);
    EXPECT_FLOAT_EQ(3589.2,m.z_cnt);
    EXPECT_EQ(1,m.seq_num);
    EXPECT_EQ(0,m.health);
    EXPECT_EQ(14,m.dgnss_data.size());
}



// !AIVDM,1,1,,A,A04757QAv0agH2Jd0=`@2?m9wj8,2*01,raishub,1333238403
// spare2 0
// mmsi 4310302
// repeat_indicator 0
// spare 0
// y 35.6183319092
// x 139.893325806
// id 17

TEST(TestGNSSBroadcastBinaryMessage, AisMsg17_2words) {
    ais::BinaryPayload bp("A04757QAv0agH2Jd0=`@2?m9wj8",2);
    // The payload seems to be short 8 bits...
    ASSERT_THROW(ais::GNSSBroadcastBinaryMessage m(bp),ais::exception);

//     ASSERT_EQ(17,m.message_id);
//     EXPECT_EQ(0,m.repeat_indicator);
//     EXPECT_EQ(4310302,m.mmsi);
// 
//     EXPECT_EQ(0,m.spare);
//     EXPECT_FLOAT_EQ(139.893325806, m.x);
//     EXPECT_FLOAT_EQ(35.6183319092, m.y);
//     EXPECT_EQ(0,m.spare2);
// 
//     EXPECT_EQ(-1,m.msg_type);
//     EXPECT_EQ(-1,m.station_id);
//     EXPECT_FLOAT_EQ(-1.0,m.z_cnt);
//     EXPECT_EQ(-1,m.seq_num);
//     EXPECT_EQ(-1,m.health);
//     EXPECT_EQ(0,m.dgnss_data.size());
}

