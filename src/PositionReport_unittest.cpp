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
    ASSERT_EQ("under way using engine", m.nav_status_str());

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

// !AIVDM,1,1,,A,239Rb>5000JRUmPE8<buoc6n08@c,0*4C,b003669730,1360678349
// slot_timeout 2
// sync_state 0
// true_heading 355
// sog 0.0
// rot 0.0
// nav_status 5
// repeat_indicator 0
// raim False
// id 2
// slot_number 1067
// spare 0
// cog 355.0
// timestamp 27
// y 36.9240188599
// x -76.3295211792
// position_accuracy 0
// rot_over_range False
// mmsi 211331640
// special_manoeuvre 0

TEST(TestPositionReport, AisMsg2SOTDMA) {
    ais::BinaryPayload bp("239Rb>5000JRUmPE8<buoc6n08@c",0);
    ais::PositionReport_SOTDMA m(bp);
    
    ASSERT_EQ(2,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(211331640,m.mmsi);
    ASSERT_EQ(5,m.nav_status);
    ASSERT_EQ("moored",m.nav_status_str());
    
    ASSERT_FLOAT_EQ(0.0,m.rot);
    ASSERT_FALSE(m.rot_not_available);
    ASSERT_FALSE(m.rot_no_ti);
    
    ASSERT_FLOAT_EQ(0.0,m.sog);
    
    ASSERT_FALSE(m.position_accuracy);
    ASSERT_FLOAT_EQ(-76.3295211792,m.x);
    ASSERT_FLOAT_EQ(36.9240188599,m.y);
    
    ASSERT_FLOAT_EQ(355.0,m.cog);
    ASSERT_EQ(355, m.true_heading);
    ASSERT_EQ(27, m.timestamp);
    ASSERT_EQ(0, m.special_manoeuvre); // Pre ITU 1371-3, this and the spare were one
    ASSERT_EQ(0, m.spare);
    ASSERT_FALSE(m.raim);
    
    ASSERT_EQ(0, m.sync_state);
    ASSERT_EQ(2, m.slot_timeout);
    ASSERT_EQ(-1, m.received_stations);
    ASSERT_EQ(1067, m.slot_number);
    ASSERT_EQ(-1,m.utc_hour);
    ASSERT_EQ(-1,m.utc_min);
    ASSERT_EQ(-1,m.utc_spare);
    ASSERT_EQ(-1,m.slot_offset);
}


// !AIVDM,1,1,,A,35Oo<:SvB4rTdFtE59`;@9E@0553,0*48,b003669794,1360681300
// slot_increment 1300
// sync_state 0
// true_heading 298
// sog 13.1999998093
// slots_to_allocate 1
// rot -2.18737411499
// nav_status 3
// repeat_indicator 0
// raim False
// id 3
// spare 0
// keep_flag True
// cog 288.0
// timestamp 40
// y 36.840801239
// x -75.8703536987
// position_accuracy 1
// rot_over_range False
// mmsi 368954410
// special_manoeuvre 0

TEST(TestPositionReport, AisMsg3ITDMA) {
    ais::BinaryPayload bp("35Oo<:SvB4rTdFtE59`;@9E@0553",0);
    ais::PositionReport_ITDMA m(bp);
    
    ASSERT_EQ(3,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(368954410,m.mmsi);
    ASSERT_EQ(3,m.nav_status);
    ASSERT_EQ("restricted manoeuvrability",m.nav_status_str());
    
    ASSERT_FLOAT_EQ(-2.18737411499,m.rot);
    ASSERT_FALSE(m.rot_not_available);
    ASSERT_FALSE(m.rot_no_ti);
    
    ASSERT_FLOAT_EQ(13.1999998093,m.sog);
    
    ASSERT_TRUE(m.position_accuracy);
    ASSERT_FLOAT_EQ(-75.8703536987,m.x);
    ASSERT_FLOAT_EQ(36.840801239,m.y);
    
    ASSERT_FLOAT_EQ(288.0,m.cog);
    ASSERT_EQ(298, m.true_heading);
    ASSERT_EQ(40, m.timestamp);
    ASSERT_EQ(0, m.special_manoeuvre);
    ASSERT_EQ(0, m.spare);
    ASSERT_FALSE(m.raim);
    
    ASSERT_EQ(0, m.sync_state);
    ASSERT_EQ(1300, m.slot_increment);
    ASSERT_EQ(1, m.slots_to_allocate);
    ASSERT_TRUE(m.keep_flag);
}

// !AIVDM,1,1,,A,91b=GaAQioJPuJDFCK?Kv502040L,0*23,d-069,S0765,t000720.00,T20.4152327,r05SANA1,1360714040
// slot_increment 32184024
// sog 11.8999996185
// spare2 0
// slots_to_allocate 0
// timestamp 20
// mmsi 111368101
// repeat_indicator 0
// alt_sensor 0
// raim False
// dte 1
// alt 391
// spare 0
// keep_flag False
// cog 306.399993896
// y 38.9782333374
// x -76.6859588623
// position_accuracy 0
// id 9

TEST(TestSARPositionReport, AisMsg9) {
    ais::BinaryPayload bp("91b=GaAQioJPuJDFCK?Kv502040L",0);
    ais::SARPositionReport m(bp);

    ASSERT_EQ(9,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(111368101,m.mmsi);
    
    ASSERT_EQ(391,m.alt);
    ASSERT_EQ(119,m.sog);

    ASSERT_EQ(0, m.position_accuracy);
    ASSERT_FLOAT_EQ(-76.6859588623, m.x);
    ASSERT_FLOAT_EQ(38.9782333374, m.y);

    ASSERT_FLOAT_EQ(306.399993896, m.cog);
    ASSERT_FALSE(m.cog_not_available);
    
    ASSERT_EQ(20, m.timestamp);
    ASSERT_EQ(0, m.alt_sensor);
    ASSERT_EQ(0, m.spare);
    ASSERT_EQ(1, m.dte);
    ASSERT_EQ(0, m.spare2);
    ASSERT_EQ(0, m.assigned_mode);
    ASSERT_FALSE(m.raim);
    ASSERT_EQ(0, m.commstate_flag);

    ASSERT_EQ(0, m.sync_state);

    ASSERT_EQ(-1, m.slot_increment);
    ASSERT_EQ(-1, m.slots_to_allocate);
    ASSERT_FALSE(m.keep_flag);

    ASSERT_EQ(1, m.slot_timeout);
    ASSERT_EQ(-1, m.received_stations);
    ASSERT_EQ(-1, m.slot_number);
    ASSERT_EQ(0,m.utc_hour);
    ASSERT_EQ(7,m.utc_min);
    ASSERT_EQ(0,m.utc_spare);
    ASSERT_EQ(-1,m.slot_offset);
}
