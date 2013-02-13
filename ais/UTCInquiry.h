#ifndef AIS_UTCINQUIRY_H
#define AIS_UTCINQUIRY_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    /// Message 10: UTC and date inquiry
    /// This message should be used when a station is requesting UTC and date from another station.
    struct UTCInquiry: public Header, Destination
    {
        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare;

        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare2;

        UTCInquiry()
        :spare(0),spare2(0)
        {}

        UTCInquiry(const BinaryPayload &payload)
        :spare(0),spare2(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            spare = payload_cursor.uread(2);

            Destination::decode(payload_cursor);

            spare2 = payload_cursor.uread(2);
        }
    };
}

#endif
