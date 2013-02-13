#include <gtest/gtest.h>

#include <ais/AddressedBinaryMessage.h>

// !AIVDM,1,1,,A,6FwfE5SBKW7iodeUCuoWRH6GVgIwo7P,2*3F,d-127,S1503,t183040.00,T40.08412724,r003669946,1360693840
// not_parsed 6 ** DAC **: 891 11
// not_parsed True
// retransmit True
// seq 0
// dac 891
// mmsi 469472534
// repeat_indicator 1
// mmsi_dest 882613372
// spare 1
// fi 11
// id 6

TEST(TestAddressedBinaryMessage, AisMsg6_891_11) {
    ais::BinaryPayload bp("6FwfE5SBKW7iodeUCuoWRH6GVgIwo7P",2);
    ais::AddressedBinaryMessage m(bp);
    
    ASSERT_EQ(6,m.message_id);
    ASSERT_EQ(1,m.repeat_indicator);
    ASSERT_EQ(469472534,m.mmsi);
    
    ASSERT_EQ(0, m.seq);
    ASSERT_EQ(882613372, m.dest_mmsi);
    ASSERT_FALSE(m.retransmit);
    ASSERT_EQ(1, m.spare);
    
    ASSERT_EQ(891, m.dac);
    ASSERT_EQ(11, m.fi);
}
    

// !AIVDM,2,1,7,B,6MUnjGnrEk3vo4cw1vE=6FmEfsgsC36mi2LUWaMoSwL,0*37,r17MSGI1,1360694606
// !AIVDM,2,2,7,B,m,0*7F,r17MSGI1,1360694606
// not_parsed 6 ** DAC **: 881 10
// not_parsed True
// retransmit False
// seq 1
// dac 881
// mmsi 912110175
// repeat_indicator 1
// mmsi_dest 781569087
// spare 0
// fi 10
// id 6

TEST(TestAddressedBinaryMessage, AisMsg6_881_10) {
    ais::BinaryPayload bp("6MUnjGnrEk3vo4cw1vE=6FmEfsgsC36mi2LUWaMoSwL",0);
    ais::AddressedBinaryMessage m(bp);

    ASSERT_EQ(6,m.message_id);
    ASSERT_EQ(1,m.repeat_indicator);
    ASSERT_EQ(912110175,m.mmsi);

    ASSERT_EQ(1, m.seq);
    ASSERT_EQ(781569087, m.dest_mmsi);
    ASSERT_TRUE(m.retransmit);
    ASSERT_EQ(0, m.spare);

    ASSERT_EQ(881, m.dac);
    ASSERT_EQ(10, m.fi);
}


// !AIVDM,1,1,,B,6COgCous39MVSmAkk2T,2*58,d-126,S1511,t184740.00,T40.2924467,r01RTRO1,1360694863
// not_parsed 6 ** DAC **: 573 20
// not_parsed True
// retransmit False
// seq 3
// dac 573
// mmsi 234607583
// repeat_indicator 1
// mmsi_dest 516105689
// spare 0
// fi 20
// id 6

TEST(TestAddressedBinaryMessage, AisMsg6_573_20) {
    ais::BinaryPayload bp("6COgCous39MVSmAkk2T",2);
    ais::AddressedBinaryMessage m(bp);

    ASSERT_EQ(6,m.message_id);
    ASSERT_EQ(1,m.repeat_indicator);
    ASSERT_EQ(234607583,m.mmsi);

    ASSERT_EQ(3, m.seq);
    ASSERT_EQ(516105689, m.dest_mmsi);
    ASSERT_TRUE(m.retransmit);
    ASSERT_EQ(0, m.spare);

    ASSERT_EQ(573, m.dac);
    ASSERT_EQ(20, m.fi);
}
