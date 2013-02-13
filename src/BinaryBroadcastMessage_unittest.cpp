#include <gtest/gtest.h>

#include <ais/BinaryBroadcastMessage.h>

// Testing NOAA DMAs
// !AIVDM,2,1,1,A,803Ovrh0EPJ0Vvch00@=w52I9BK<00000VFHkP0>D>3,0*24
// !AIVDM,2,2,1,A,;J005>?11PBGP4=1PPP,0*3F

TEST(TestBinaryBraodcastMessage, AisMsg8) {
    ais::BinaryPayload bp("803Ovrh0EPJ0Vvch00@=w52I9BK<00000VFHkP0>D>3;J005>?11PBGP4=1PPP",0);
    ais::BinaryBroadcastMessage m(bp);
    
    ASSERT_EQ(8,m.message_id);
    ASSERT_EQ(0,m.repeat_indicator);
    ASSERT_EQ(3669739,m.mmsi);

    ASSERT_EQ(0, m.spare);
    
    ASSERT_EQ(1, m.dac);
    ASSERT_EQ(22, m.fi);
}

