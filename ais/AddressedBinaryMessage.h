#ifndef AIS_ADDRESSEDBINARYMESSAGE_H
#define AIS_ADDRESSEDBINARYMESSAGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "common.h"
namespace ais
{

/// Message 6: Addressed binary message.
/// The addressed binary message should be variable in length, based on the amount of binary data. The
/// length should vary between 1 and 5 slots. See application identifiers in 2.1, Annex 5.
struct AddressedBinaryMessage: public Header, Addressed, BinaryData
{
    AddressedBinaryMessage()
    {}

    AddressedBinaryMessage(const BinaryPayload &payload)
    {
        BinaryPayload::Cursor c = payload.new_cursor();
        decode(c);
    }

    void decode(BinaryPayload::Cursor &payload_cursor)
    {
        Header::decode(payload_cursor);
        Addressed::decode(payload_cursor);
        BinaryData::decode(payload_cursor);
    }
};

}

#endif
    