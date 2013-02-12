#include <gtest/gtest.h>

#include <ais/PositionReport.h>

/*
~/projects/src/noaadata/ais/ais_msg_1_handcoded.py -d '!AIVDM,1,1,,B,15Mq4J0P01EREODRv4@74gv00HRq,0*72,b003669970,1272412824'
position:
	MessageID:          1
	RepeatIndicator:    0
	UserID:             366888040
	NavigationStatus:   0
	ROT:                -128
	SOG:                0.1
	PositionAccuracy:   0
	longitude:          -146.2903833333333333333333333
	latitude:           61.11413333333333333333333333
	COG:                181
	TrueHeading:        511
	TimeStamp:          0
	RegionalReserved:   0
	Spare:              0
	RAIM:               False
	sync_state:                   0
	slot_timeout:                 6
	received_stations:            n/a
	slot_number:                  2233
	commstate_utc_hour:           n/a
	commstate_utc_min:            n/a
	commstate_utc_spare:          n/a
	slot_offset:                  n/a
*/

TEST(TestPositionReport, AisMsg1) {
    ais::BinaryPayload bp("15Mq4J0P01EREODRv4@74gv00HRq",0);
    ais::PositionReport m(bp);
    
    ASSERT_EQ(1,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(366888040,m.mmsi);
    ASSERT_EQ(0,m.nav_status);

    ASSERT_TRUE(m.rot_not_available);

    ASSERT_FLOAT_EQ(0.1,m.sog);

    ASSERT_FALSE(m.position_accuracy);
    ASSERT_FLOAT_EQ(-146.2903833,m.x);
    ASSERT_FLOAT_EQ(  61.1141333,m.y);

    ASSERT_FLOAT_EQ(181.0,m.cog);
    ASSERT_EQ(511, m.true_heading);
    ASSERT_EQ(0, m.timestamp);
    ASSERT_EQ(0, m.special_manoeuvre); // Pre ITU 1371-3, this and the spare were one
    ASSERT_EQ(0, m.spare);
    ASSERT_FALSE(m.raim);
}

TEST(TestPositionReport, AisMsg1SOTDMA) {
    ais::BinaryPayload bp("15Mq4J0P01EREODRv4@74gv00HRq",0);
    ais::PositionReport_SOTDMA m(bp);
    
    ASSERT_EQ(1,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(366888040,m.mmsi);
    ASSERT_EQ(0,m.nav_status);
    
    ASSERT_TRUE(m.rot_not_available);
    
    ASSERT_FLOAT_EQ(0.1,m.sog);
    
    ASSERT_FALSE(m.position_accuracy);
    ASSERT_FLOAT_EQ(-146.2903833,m.x);
    ASSERT_FLOAT_EQ(  61.1141333,m.y);
    
    ASSERT_FLOAT_EQ(181.0,m.cog);
    ASSERT_EQ(511, m.true_heading);
    ASSERT_EQ(0, m.timestamp);
    ASSERT_EQ(0, m.special_manoeuvre); // Pre ITU 1371-3, this and the spare were one
    ASSERT_EQ(0, m.spare);
    ASSERT_FALSE(m.raim);
    
    ASSERT_EQ(0, m.sync_state);
    ASSERT_EQ(6, m.slot_timeout);
    ASSERT_EQ(-1, m.received_stations);
    ASSERT_EQ(2233, m.slot_number);
    ASSERT_EQ(-1,m.utc_hour);
    ASSERT_EQ(-1,m.utc_min);
    ASSERT_EQ(-1,m.utc_spare);
    ASSERT_EQ(-1,m.slot_offset);
}

