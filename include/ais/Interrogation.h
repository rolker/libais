#ifndef AIS_INTERROGATION_H
#define AIS_INTERROGATION_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"

namespace ais
{
    /// Message 15: Interrogation.
    /// This message should be used for interrogations via the TDMA (not DSC) VHF data link other than
    /// requests for UTC and date. The response should be transmitted on the channel where the
    /// interrogation was received.
    struct Interrogation: public Header
    {
        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare;

        /// Destination ID1.
        /// MMSI number of first interrogated station
        int mmsi_1;

        /// Message ID1.1.
        /// First requested message type from first interrogated station
        int msg_1_1;

        /// Slot offset 1.1.
        /// Response slot offset for first requested message from first interrogated
        /// station
        int slot_offset_1_1;

        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare2;

        /// Message ID1.2.
        /// Second requested message type from first interrogated station
        int msg_1_2;

        /// Slot offset 1.2.
        /// Response slot offset for second requested message from first
        /// interrogated station 
        int slot_offset_1_2;

        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare3;

        /// Destination ID 2.
        /// MMSI number of second interrogated station
        int mmsi_2;

        /// Message ID 2.1.
        /// Requested message type from second interrogated station
        int msg_2;

        /// Slot offset 2.1.
        /// Response slot offset for requested message from second interrogated
        /// station
        int slot_offset_2;

        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare4;

        Interrogation()
        :spare(0),mmsi_1(-1),msg_1_1(-1),slot_offset_1_1(0),
        spare2(0),msg_1_2(-1),slot_offset_1_2(0),
        spare3(0),mmsi_2(-1),msg_2(-1),slot_offset_2(0),spare4(0)
        {}

        Interrogation(const BinaryPayload &payload)
        :spare(0),mmsi_1(-1),msg_1_1(-1),slot_offset_1_1(0),
        spare2(0),msg_1_2(-1),slot_offset_1_2(0),
        spare3(0),mmsi_2(-1),msg_2(-1),slot_offset_2(0),spare4(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            spare = payload_cursor.uread(2);
            mmsi_1 = payload_cursor.uread(30);
            msg_1_1 = payload_cursor.uread(6);
            slot_offset_1_1 = payload_cursor.uread(12);

            spare2 = payload_cursor.uread(2);
            msg_1_2 = payload_cursor.uread(6);
            slot_offset_1_2 = payload_cursor.uread(12);

            spare3 = payload_cursor.uread(2);
            mmsi_2 =  payload_cursor.uread(30);
            msg_2 = payload_cursor.uread(6);
            slot_offset_2 = payload_cursor.uread(12);
            spare4 = payload_cursor.uread(2);
        }

    };
}

#endif
