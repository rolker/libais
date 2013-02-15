#ifndef AIS_GNSSBROADCASTBINARYMESSAGE_H
#define AIS_GNSSBROADCASTBINARYMESSAGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    /// Message 17: GNSS broadcast binary message.
    /// This message should be transmitted by a base station, which is connected to a DGNSS reference
    /// source, and configured to provide DGNSS data to receiving stations. The contents of the data
    /// should be in accordance with Recommendation ITU-R M.823, excluding preamble and parity
    /// formatting. 
    struct GNSSBroadcastBinaryMessage: public Header, GNSSDifferentialCorrectionData
    {
        /// Spare.
        /// Not used. Should be set to zero. Reserved for future use
        int spare;

        /// Longitude.
        /// Surveyed longitude of DGNSS reference station in 1/10 min (±180 deg,
        /// East = positive, West = negative). If interrogated and differential
        /// correction service not available, the longitude should be set to 181 deg
        float x;

        /// Latitude.
        /// Surveyed latitude of DGNSS reference station in 1/10 min (±90 deg,
        /// North = positive, South = negative). If interrogated and differential
        /// correction service not available, the latitude should be set to 91 deg
        float y;

        /// Spare.
        /// Not used. Should be set to zero. Reserved for future use
        int spare2;

        GNSSBroadcastBinaryMessage()
        :spare(0),x(181.0),y(91.0),spare2(0)
        {}

        GNSSBroadcastBinaryMessage(const BinaryPayload& payload)
        :spare(0),x(181.0),y(91.0),spare2(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            spare = payload_cursor.uread(2);

            x = payload_cursor.sread(18)/600.0;
            y = payload_cursor.sread(17)/600.0;

            spare2 = payload_cursor.uread(5);

            GNSSDifferentialCorrectionData::decode(payload_cursor);
        }

    };
}

#endif
