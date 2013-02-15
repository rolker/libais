#ifndef AIS_SAFETYBROADCASTMESSAGE_H
#define AIS_SAFETYBROADCASTMESSAGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    /// Message 14: Safety related broadcast message.
    /// The safety related broadcast message could be variable in length, based on the amount of safety
    /// related text. The length should vary between 1 and 5 slots.
    struct SafetyBroadcastMessage: public Header
    {
        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare;

        /// Safety related text.
        /// 6-bit ASCII as defined in Table 44
        std::string text;

        SafetyBroadcastMessage()
        :spare(0)
        {}
        
        SafetyBroadcastMessage(const BinaryPayload &payload)
        :spare(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }
        
        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            spare = payload_cursor.uread(2);

            text = payload_cursor.str_read();
        }
    };
}

#endif
