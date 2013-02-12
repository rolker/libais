#ifndef AIS_BINARYPAYLOAD_H
#define AIS_BINARYPAYLOAD_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include <vector>
#include <bitset>

#include "AsciiPayload.h"
#include "exception.h"

namespace ais{
    
    /// Container for binary version of nmea payload.
    class BinaryPayload{
        std::vector<bool> _payload;

        void init(std::string const &s, int pad)
        {
            _payload.resize((s.size()*6)-pad);
            int pbit = 0;
            for(std::string::const_iterator c = s.begin(); c != s.end(); ++c)
            {
                int value = *c - 48;
                if (value > 40)
                    value -= 8;
                if (value < 0 || value > 63)
                    throw(exception("Invalid ASCII character"));
                
                int mask = 0x20;
                while (mask > 0 && pbit < _payload.size())
                {
                    _payload[pbit] =  value & mask;
                    mask >>= 1;
                    ++pbit;
                }
            }
        }
    public:
        class Cursor
        {
            std::vector<bool>::const_iterator _cursor;
            std::vector<bool>::const_iterator _ibegin, _iend;

            friend class BinaryPayload;
            
            Cursor(std::vector<bool>::const_iterator ibegin, std::vector<bool>::const_iterator iend):_cursor(ibegin),_ibegin(ibegin),_iend(iend){}
            
            void read(int len, std::bitset<32> &ret)
            {
                for (int i = len-1; i >= 0; --i)
                {
                    if (_cursor == _iend)
                        throw (exception("Attempt to read past binary payload"));
                    ret[i] = *_cursor;
                    ++_cursor;
                }
            }

        public:
            unsigned long uread(int len)
            {
                std::bitset<32> ret;
                read(len,ret);
                return ret.to_ulong();
            };
            
            long sread(int len)
            {
                std::bitset<32> ret;
                if(*_cursor)
                    ret.flip();
                read(len,ret);
                unsigned long tmp = ret.to_ulong();
                return *reinterpret_cast<long *>(&tmp);
            }
        };
        
        BinaryPayload(const AsciiPayload &ascii){
            init(ascii.payload, ascii.pad_bits);
        }
        
        BinaryPayload(const std::string &s, int pad){
            init(s, pad);
        }
        
        int get_message_id() const
        {
            return _payload[0];
        }
        
        Cursor new_cursor() const
        {
            return Cursor(_payload.begin(),_payload.end());
        }
    };
}

#endif
