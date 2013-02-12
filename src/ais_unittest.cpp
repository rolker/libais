#include <gtest/gtest.h>

#include <ais/Header.h>

TEST(TestAis,Header) {
    ais::AsciiPayload ap("15Mq4J0P01EREODRv4@74gv00HRq",0);
    ais::BinaryPayload bp(ap);
    
    ais::Header h(bp);
    
    ASSERT_EQ(1,h.message_id);
    ASSERT_EQ(0,h.repeat_indicator);
    ASSERT_EQ(366888040,h.mmsi);
}

