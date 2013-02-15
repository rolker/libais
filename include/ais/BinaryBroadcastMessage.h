#ifndef AIS_BINARYBROADCASTMESSAGE_H
#define AIS_BINARYBROADCASTMESSAGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    /// Message 8: Binary broadcast message.
    /// This message will be variable in length, based on the amount of binary data. The length should vary
    /// between 1 and 5 slots.
    struct BinaryBroadcastMessage: public Header, BinaryData
    {
        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare;

        BinaryBroadcastMessage()
        :spare(0)
        {}

        BinaryBroadcastMessage(const BinaryPayload &payload)
        :spare(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            spare = payload_cursor.uread(2);

            BinaryData::decode(payload_cursor);
        }
    };
}

#endif
