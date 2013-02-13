#include <gtest/gtest.h>

#include <ais/BaseStationReport.h>

// !AIVDM,1,1,,A,403OtKQulV@:`re6NdFu4tg020S:,0*21,d-055,S1467,t161039.00,T39.13667909,r05RMSQ1,1360685440
// slot_timeout 0
// sync_state 0
// slot_offset 2250
// fix_type 15
// hour 16
// mmsi 3669102
// repeat_indicator 0
// raim True
// transmission_ctl 0
// month 2
// second 40
// spare 0
// minute 10
// year 2013
// y 40.1156044006
// x -74.0335617065
// position_accuracy 1
// id 4
// day 12

TEST(TestBaseStationReport, AisMsg4) {
    ais::BinaryPayload bp("403OtKQulV@:`re6NdFu4tg020S:",0);
    ais::BaseStationReport m(bp);

    ASSERT_EQ(4,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(3669102,m.mmsi);

    ASSERT_EQ(2013,m.year);
    ASSERT_EQ(2,m.month);
    ASSERT_EQ(12,m.day);
    ASSERT_EQ(16,m.hour);
    ASSERT_EQ(10,m.minute);
    ASSERT_EQ(40,m.second);

    ASSERT_TRUE(m.position_accuracy);
    ASSERT_FLOAT_EQ(-74.0335617065,m.x);
    ASSERT_FLOAT_EQ(40.1156044006,m.y);

    ASSERT_EQ(15,m.fix_type);
    ASSERT_EQ("internal GNSS",m.fix_type_str());

    ASSERT_EQ(0,m.transmission_ctl);
    ASSERT_EQ(0,m.spare);

    ASSERT_TRUE(m.raim);
    
    ASSERT_EQ(0,m.sync_state);
    ASSERT_EQ(0,m.slot_timeout);
    ASSERT_EQ(-1,m.received_stations);
    ASSERT_EQ(-1,m.slot_number);
    ASSERT_EQ(-1,m.utc_hour);
    ASSERT_EQ(-1,m.utc_min);
    ASSERT_EQ(-1,m.utc_spare);
    ASSERT_EQ(2250,m.slot_offset);
}

// !AIVDM,1,1,,B,;5@WU41ulV@LkI3HOJ?s==Q00000,0*5E,r08VCCH1,1360686532
// slot_timeout 0
// sync_state 0
// slot_offset 0
// fix_type 1
// hour 16
// mmsi 352970000
// repeat_indicator 0
// raim False
// transmission_ctl 0
// month 2
// second 51
// spare 0
// minute 28
// year 2013
// y 27.8311290741
// x -97.1281356812
// position_accuracy 0
// id 11
// day 12

TEST(TestBaseStationReport, AisMsg11) {
    ais::BinaryPayload bp(";5@WU41ulV@LkI3HOJ?s==Q00000",0);
    ais::BaseStationReport m(bp);
    
    ASSERT_EQ(11,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(352970000,m.mmsi);
    
    ASSERT_EQ(2013,m.year);
    ASSERT_EQ(2,m.month);
    ASSERT_EQ(12,m.day);
    ASSERT_EQ(16,m.hour);
    ASSERT_EQ(28,m.minute);
    ASSERT_EQ(51,m.second);
    
    ASSERT_FALSE(m.position_accuracy);
    ASSERT_FLOAT_EQ(-97.1281356812,m.x);
    ASSERT_FLOAT_EQ(27.8311290741,m.y);
    
    ASSERT_EQ(1,m.fix_type);
    ASSERT_EQ("global positioning system (GPS)",m.fix_type_str());
    
    ASSERT_EQ(0,m.transmission_ctl);
    ASSERT_EQ(0,m.spare);
    
    ASSERT_FALSE(m.raim);
    
    ASSERT_EQ(0,m.sync_state);
    ASSERT_EQ(0,m.slot_timeout);
    ASSERT_EQ(-1,m.received_stations);
    ASSERT_EQ(-1,m.slot_number);
    ASSERT_EQ(-1,m.utc_hour);
    ASSERT_EQ(-1,m.utc_min);
    ASSERT_EQ(-1,m.utc_spare);
    ASSERT_EQ(0,m.slot_offset);
}
