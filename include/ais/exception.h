#ifndef AIS_EXCEPTION_H
#define AIS_EXCEPTION_H

// Based on https://github.com/schwehr/libais
// Copyright 2010 Kurt Schwehr.  Released under the LGPL v3
// 
// Additions copyright by Roland Arsenault 2012-2013

#include <exception>
#include <string>

namespace ais{
    class exception: public std::exception
    {
        std::string _msg;
        
    public:
        exception(std::string const &msg):_msg(msg){}
        ~exception() throw(){};
        char const *what() const throw(){return _msg.c_str();}
    };
    
}

#endif