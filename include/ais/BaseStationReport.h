#ifndef AIS_BASESTATIONREPORT_H
#define AIS_BASESTATIONREPORT_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    
    /// Message 4: Base station report and message 11: UTC and date response.
    /// Should be used for reporting UTC time and date  and, at the same time, position. A base station 
    /// should use Message 4 in its periodical transmissions. A mobile station should output Message 11 
    /// only in response to interrogation by Message 10. 
    /// Message 11 is only transmitted as a result of a UTC request message (Message 10). The UTC and 
    /// date response should be transmitted on the channel, where the UTC request message was received.
    struct BaseStationReport: public Header, LonLatAccuracy, FixType, RAIM, SyncState, SOTDMA
    {
        /// UTC year.
        /// 1-9999; 0 = UTC year not available = default
        int year;
        
        /// UTC month.
        /// 1-12; 0 = UTC month not available = default; 13-15 not used
        int month;
        
        /// UTC day.
        /// 1-31; 0 = UTC day not available = default
        int day;
        
        /// UTC hour.
        /// 0-23; 24 = UTC hour not available = default; 25-31 not used
        int hour;
        
        /// UTC minute.
        /// 0-59; 60 = UTC minute not available = default; 61-63 not used
        int minute;
        
        /// UTC second.
        /// 0-59; 60 = UTC second not available = default; 61-63 not used
        int second;

        /// Transmission control for longrange broadcast message.
        /// 0 = default – Class-A AIS station stops transmission of Message 27
        /// within an AIS base station coverage area.
        /// 1 = Request Class-A station to transmit Message 27 within an AIS base
        /// station coverage area.
        int transmission_ctl;

        /// Spare.
        /// Not used. Should be set to zero. Reserved for future use
        int spare;

        BaseStationReport()
            :year(0),month(0),day(0),hour(24),minute(60),second(60),
            transmission_ctl(0),spare(0)
        {}

        BaseStationReport(const BinaryPayload &payload)
            :year(0),month(0),day(0),hour(24),minute(60),second(60),
            transmission_ctl(0),spare(0)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);

            year = payload_cursor.uread(14);
            month = payload_cursor.uread(4);
            day = payload_cursor.uread(5);
            hour = payload_cursor.uread(5);
            minute = payload_cursor.uread(6);
            second = payload_cursor.uread(6);

            LonLatAccuracy::decode(payload_cursor);
            FixType::decode(payload_cursor);

            transmission_ctl = payload_cursor.uread(1);
            spare = payload_cursor.uread(9);

            RAIM::decode(payload_cursor);
            SyncState::decode(payload_cursor);
            SOTDMA::decode(payload_cursor);
        }

    };
}

#endif
