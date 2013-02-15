#ifndef AIS_MESSAGE_H
#define AIS_HESSAGE_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include "Header.h"
#include "BinaryPayload.h"

namespace ais{
    
    /// AIS message with just the common header decoded.
    class Message: public BinaryPayload, Header
    {
    public:
        Message(std::string ascii, int pad_bits):BinaryPayload(AsciiPayload(ascii,pad_bits))
        {
            
        }
    };
    
}

#endif
