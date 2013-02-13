#include <gtest/gtest.h>

#include <ais/ShipStaticAndVoyage.h>

// !AIVDM,2,1,3,A,577`K<02B:RqI8UCV20pTpL8v0@ti0PTr2222216GhS;E4V60N3QEp3lS1@C,0*57,b003669955,1360688444
// !AIVDM,2,2,3,A,`8888888880,2*7F,b003669955,1360688444
// destination NEW ORLEAN          
// dim_d 21
// name NINGBO DOLPHIN      
// eta_hour 6
// ais_version 0
// draught 12.0
// mmsi 477764400
// repeat_indicator 0
// dim_b 35
// dim_c 11
// dte 0
// dim_a 190
// eta_day 12
// eta_minute 0
// callsign VRIT9  
// spare 0
// eta_month 2
// type_and_cargo 70
// fix_type 1
// id 5
// imo_num 9579054

TEST(TestShipStaticAndVoyage, AisMsg5) {
    ais::BinaryPayload bp("577`K<02B:RqI8UCV20pTpL8v0@ti0PTr2222216GhS;E4V60N3QEp3lS1@C`8888888880",2);
    ais::ShipStaticAndVoyage m(bp);

    ASSERT_EQ(5,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(477764400,m.mmsi);

    ASSERT_EQ("VRIT9  ",m.callsign);
    ASSERT_EQ("NINGBO DOLPHIN      ",m.name);

    ASSERT_EQ(70,m.type_and_cargo);
    ASSERT_EQ("Cargo ships - All ships of this type", m.type_and_cargo_str());
    
    ASSERT_EQ(190, m.dim_a);
    ASSERT_EQ(35, m.dim_b);
    ASSERT_EQ(11, m.dim_c);
    ASSERT_EQ(21, m.dim_d);

    ASSERT_EQ(1,m.fix_type);
    ASSERT_EQ("global positioning system (GPS)",m.fix_type_str());
    
    ASSERT_EQ(2, m.eta_month);
    ASSERT_EQ(12, m.eta_day);
    ASSERT_EQ(6, m.eta_hour);
    ASSERT_EQ(0, m.eta_minute);
    
    ASSERT_FLOAT_EQ(12.0, m.draught);
    ASSERT_EQ("NEW ORLEAN          ",m.destination);
    ASSERT_EQ(0, m.dte);
    ASSERT_EQ(0, m.spare);
}