#ifndef AIS_ADDRESSEDSAFETYMESSAGE_H
#define AIS_ADDRESSEDSAFETYMESSAGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"

namespace ais
{
    /// Message 12: Addressed safety related message.
    /// The addressed safety related message could be variable in length, based on the amount of safety
    /// related text. The length should vary between 1 and 5 slots.
    struct AddressedSafetyMessage: public Header, Addressed
    {
        /// Safety related text.
        /// 6-bit ASCII as defined in Table 44
        std::string text;

        AddressedSafetyMessage()
        {}

        AddressedSafetyMessage(const BinaryPayload &payload)
        {
            BinaryPayload::Cursor c = payload.new_cursor();
            decode(c);
        }

        void decode(BinaryPayload::Cursor &payload_cursor)
        {
            Header::decode(payload_cursor);
            Addressed::decode(payload_cursor);

            text = payload_cursor.str_read();
        }
    };
    
}

#endif
