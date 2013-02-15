#ifndef AIS_ACKNOWLEDGE_H
#define AIS_ACKNOWLEDGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"
namespace ais
{
    /// Message 7: Binary acknowledge and Message 13: Safety related acknowledge
    /// Message 7 should be used as an acknowledgement of up to four Message 6 messages received
    /// (see 5.3.1, Annex 2) and should be transmitted on the channel, where the addressed message to be
    /// acknowledged was received.
    /// Message 13 should be used as an acknowledgement of up to four Message 12 messages received
    /// (see 5.3.1, Annex 2) and should be transmitted on the channel, where the addressed message to be
    /// acknowledged was received.
    /// These acknowledgements should be applicable only to the VHF data link (see § 5.3.1, Annex 2).
    /// Other means must be employed for acknowledging applications.
    struct Acknowledge: public Header
    {
        /// Spare.
        /// Not used. Should be set to zero. Reserved for future use
        int spare;

        /// Destination IDs.
        /// MMSI number(s) of  destination(s) of this ACK
        std::vector<int> dest_mmsi;

        /// Sequence numbers
        /// Sequence number of message to be acknowledged; 0-3
        std::vector<int> seq_num;

        Acknowledge(const BinaryPayload &payload)
        :spare(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);
            
            spare = payload_cursor.uread(2);
            while(!payload_cursor.empty())
            {
                dest_mmsi.push_back(payload_cursor.uread(30));
                seq_num.push_back(payload_cursor.uread(2));
            }
        }
    };
}

#endif
