#ifndef AIS_HEADER_H
#define AIS_HEADER_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013
#include "BinaryPayload.h"

namespace ais{

/// Header common to all AIS messages.
/// See Recommendation  ITU-R  M.1371-4
/// http://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1371-4-201004-I!!PDF-E.pdf
struct Header{
    /// Message ID.
    /// Identifier for this Message
    int message_id;
    
    /// Repeat indicator.
    /// Used by the repeater to indicate how many times a message has been 
    /// repeated. See § 4.6.1, Annex 2; 0-3; 0 = default; 3 = do not repeat any 
    /// more
    int repeat_indicator;
    
    /// User ID.
    /// Unique identifier such as MMSI number
    int mmsi;
    
    Header():message_id(0),repeat_indicator(0),mmsi(-1){}
    Header(const BinaryPayload &payload):message_id(0),repeat_indicator(0),mmsi(-1)
    {
        BinaryPayload::Cursor c = payload.new_cursor();
        decode(c);
    }
    
    void decode(BinaryPayload::Cursor &payload_cursor)
    {
        message_id = payload_cursor.uread(6);
        repeat_indicator = payload_cursor.uread(2);
        mmsi = payload_cursor.uread(30);
    }
};
    
}

#endif
