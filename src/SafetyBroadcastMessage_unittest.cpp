#include <gtest/gtest.h>

#include <ais/SafetyBroadcastMessage.h>

// !AIVDM,3,1,3,A,>0476BPTpHu8l5@Ttr08U<4r0l59@U?qA84HHT>0<tqA8tj1<TLp4j3;8pCb0lUa,0*03
// !AIVDM,3,2,3,A,E<PTl637?32o7C3228v:vv0pU<PTpu<4dV37;G2o7C3F29>:vv0lUA=Ddu<PTl63,0*1D
// !AIVDM,3,3,3,A,7;?2o7C?229>:02un?q4B,0*2C
// text INFORMATION BISAN MARTIS>TRAFFIC CONTROL SIGNAL 22ND: MIZUSHIMA 1300-1400 "O"// NISHINOSAKI 1250-1405 "S"// MITSUKOSHIMA 1230-1430 "S" @/]#>QD
// mmsi 4310602
// repeat_indicator 0
// spare 0
// id 14


TEST(TestSafetyBroadcastMessage, AisMsg14) {
    ais::BinaryPayload bp(">0476BPTpHu8l5@Ttr08U<4r0l59@U?qA84HHT>0<tqA8tj1<TLp4j3;8pCb0lUaE<PTl637?32o7C3228v:vv0pU<PTpu<4dV37;G2o7C3F29>:vv0lUA=Ddu<PTl637;?2o7C?229>:02un?q4B",0);
    ais::SafetyBroadcastMessage m(bp);
    
    ASSERT_EQ(14,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(4310602,m.mmsi);
    
    ASSERT_EQ(0, m.spare);
    
    ASSERT_EQ("INFORMATION BISAN MARTIS>TRAFFIC CONTROL SIGNAL 22ND: MIZUSHIMA 1300-1400 \"O\"// NISHINOSAKI 1250-1405 \"S\"// MITSUKOSHIMA 1230-1430 \"S\" @/]#>QD",m.text);
}

// !AIVDM,2,1,7,A,>0476BPTpHu8l5@Ttr08U<4r0l59@U?p<5E@Tts`l4Tq@Dp4p<F1Lu8f0tr08TpL,0*74
// !AIVDM,2,2,7,A,tp4@609DuV0pvsN0puN1Dp@E9L5Vr01=>os7;,0*3F
// text INFORMATION BISAN MARTIS>CAUTION:MAINTENANCE WORK ON BINGONADA BUOY NO.7 NOW UNDERWAY. @SS->12
// mmsi 4310602
// repeat_indicator 0
// spare 0
// id 14


TEST(TestSafetyBroadcastMessage, AisMsg14_2) {
    ais::BinaryPayload bp(">0476BPTpHu8l5@Ttr08U<4r0l59@U?p<5E@Tts`l4Tq@Dp4p<F1Lu8f0tr08TpLtp4@609DuV0pvsN0puN1Dp@E9L5Vr01=>os7;",0);
    ais::SafetyBroadcastMessage m(bp);
    
    ASSERT_EQ(14,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(4310602,m.mmsi);
    
    ASSERT_EQ(0, m.spare);
    
    ASSERT_EQ("INFORMATION BISAN MARTIS>CAUTION:MAINTENANCE WORK ON BINGONADA BUOY NO.7 NOW UNDERWAY. @SS->12",m.text);
}


// !AIVDM,1,1,,A,>4`6wB04U>1@E=Br0LttB1L5@<Rp,0*31
// text AIS TEST. GOOD WATCH.
// mmsi 310493000
// repeat_indicator 0
// spare 0
// id 14

TEST(TestSafetyBroadcastMessage, AisMsg14GoodWatch) {
    ais::BinaryPayload bp(">4`6wB04U>1@E=Br0LttB1L5@<Rp",0);
    ais::SafetyBroadcastMessage m(bp);

    ASSERT_EQ(14,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(310493000,m.mmsi);

    ASSERT_EQ(0, m.spare);

    ASSERT_EQ("AIS TEST. GOOD WATCH.",m.text);
}
