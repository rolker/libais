#include <gtest/gtest.h>

#include <ais/Acknowledge.h>

// !AIVDM,1,1,,A,=?lMpOGvtOPKDu8,2*20,d-125,S0195,t221905.00,T05.21261628,r05RTUC1,1360707552

TEST(TestAcknowledge, AisMsg13) {
    ais::BinaryPayload bp("=?lMpOGvtOPKDu8",2);
    ASSERT_THROW(ais::Acknowledge m(bp), ais::exception);
}
