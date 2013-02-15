#ifndef AIS_ASSIGNEDMODECOMMAND_H
#define AIS_ASSIGNEDMODECOMMAND_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"

namespace ais
{
    /// Message 16: Assigned mode command.
    /// Assignment should be transmitted by a base station when operating as a controlling entity. Other
    /// stations can be assigned a transmission schedule, other than the currently used one. If a station is
    /// assigned a schedule, it will also enter assigned mode.
    ///
    /// Two stations can be assigned simultaneously.
    ///
    /// To assign a reporting rate for a station, the parameter increment should be set to zero. The parameter
    /// offset should then be interpreted as the number of reports in a time interval of 10 min.
    
    struct AssignedModeCommand: public Header
    {
        /// Spare.
        /// Not used. Should be zero. Reserved for future use
        int spare;

        /// Destination ID A.
        /// MMSI number. Destination identifier A
        int dest_mmsi_a;

        /// Offset A.
        /// Offset from current slot to first assigned slot.
        int offset_a;

        /// Increment A.
        /// Increment to next assigned slot.
        int inc_a;

        /// Destination ID B.
        /// MMSI number. Destination identifier B. Should be omitted if there is
        /// assignment to station A, only
        int dest_mmsi_b;

        /// Offset B.
        /// Offset from current slot to first assigned slot. Should be omitted if there
        /// is assignment to station A, only
        int offset_b;

        /// Increment B.
        /// Increment to next assigned slot. Should be omitted, if there is
        /// assignment to station A, only
        int inc_b;

        /// Spare.
        /// Spare. Not used. Should be set to zero. The number of spare bits, which
        /// should be 0 or 4, should be adjusted in order to observe byte boundaries.
        /// Reserved for future use 
        int spare2;

        AssignedModeCommand()
        :spare(0),dest_mmsi_a(-1),offset_a(-1),inc_a(-1),
        dest_mmsi_b(-1),offset_b(-1),inc_b(-1),spare2(-1)
        {}

        AssignedModeCommand(const BinaryPayload &payload)
        :spare(0),dest_mmsi_a(-1),offset_a(-1),inc_a(-1),
        dest_mmsi_b(-1),offset_b(-1),inc_b(-1),spare2(-1)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            spare = payload_cursor.uread(2);

            dest_mmsi_a = payload_cursor.uread(30);
            offset_a = payload_cursor.uread(12);
            inc_a = payload_cursor.uread(10);

            dest_mmsi_b = payload_cursor.uread(30);
            offset_b = payload_cursor.uread(12);
            inc_b = payload_cursor.uread(10);

            spare2 = payload_cursor.uread(4);
        }

    };
}

#endif
