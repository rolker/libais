#ifndef AIS_ASCIIPAYLOAD_H
#define AIS_ASCIIPAYLOAD_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include <string>

namespace ais{

    struct AsciiPayload{
        std::string payload;
        int pad_bits;

        /// @arg pad Padding bits, this is the last value before the checksum in the NMEA string.
        AsciiPayload(const std::string &pl, int pad):payload(pl),pad_bits(pad){}

        int get_message_id() const
        {
            return payload[0] - 48;
        }
    };
}

#endif
