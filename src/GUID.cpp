/**
 * File    : GUID.cpp
 * Author  : Emir Uner
 * Summary : C linkage GUID parsing/printing function implementations.
 */

/**
 * This file is part of XCOM.
 *
 * Copyright (C) 2003 Emir Uner
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <xcom/GUID.hpp>

#include <ctype.h>
#include <string.h>

// FIXME: Force xcomGenerateGUID to link.
#include <xcom/Portability.hpp>
namespace
{
    void* address = (void*)&xcomGenerateGUID;
    void* add2 = (void*)&xcomInterlockedIncrement;
    void* add3 = (void*)&xcomInterlockedDecrement;
}

namespace
{

/** 
 * Convert a given hexadecimal digit to decimal. This routine
 * assumes that given character is a valid hexadecimal digit. So
 * no checks will be performed.
 * 
 * @param the hexadecimal digit.
 */
inline int hexToDec(char hexch)
{
    int ch = ::tolower(hexch);

    if(ch > '9')
    {
        return (ch - 'a' + 10);
    }
    else
    {
        return (ch - '0');
    }
}

/**
 * Convert a given decimal number in range 0-15 to a
 * hexadecimal digit. No range checks done on the given decimal digit.
 * 
 * @param the decimal digit.
 */
inline char decToHex(int digit)
{
    if(digit > 9)
    {
        return ('a' + digit - 10);
    }
    else
    {
        return ('0' + digit);
    }
}
 
// Holds the byte starting points in a string representation of an GUID.
const int kBytePos[16] = {6, 4, 2, 0, 11, 9, 16, 14, 19,
                          21, 24, 26, 28, 30, 32, 34};

// The length of the string form of an GUID
const unsigned int kGUIDStrLen = 36;

// The size of an GUID
const unsigned int kGUIDSize = 16;

} // namespace <anonymous>

using namespace xcom;

extern "C"
int xcomParseGUID(Char const* s, GUID* guid)
{
    Octet data[kGUIDSize];

    // Check the length.
    if(::strlen(s) < kGUIDStrLen)
    {
        return false;
    }
    
    // Check the '-' chars at fixed locations.
    if((s[8] != '-') || (s[13] != '-') || (s[18] != '-') || (s[23] != '-'))
    {
        return false;
    }
    
    // Check the numeric parts for validity and extract the values.
    for(unsigned int pos = 0; pos < kGUIDSize; ++pos)
    {
        char d0 = s[kBytePos[pos]];
        char d1 = s[kBytePos[pos] + 1];
        
        if(::isxdigit(d0) == 0 || ::isxdigit(d1) == 0)
        {
            return false;
        }
        
        data[pos] = hexToDec(d0) * 16 + hexToDec(d1);
    }
    
    // If we have reached this point then the given string parsed correctly
    // and the value is written in data. So write its value.
    ::memcpy(guid, data, kGUIDSize);
    
    return true;
}

extern "C"
void xcomGUIDToString(GUID const* guid, Char* s)
{
    // Place non-number characters to correct places.
    s[8] = '-'; s[13] = '-'; s[18] = '-'; s[23] = '-'; s[36] = 0;

    // See self as an array of bytes
    Octet const* data = reinterpret_cast<Octet const*>(guid);

    // Process byte by byte
    for(unsigned int pos = 0; pos < kGUIDSize; ++pos)
    {
        // Write the hex value to the appropriate place to the string.
        s[kBytePos[pos]] = decToHex(data[pos] / 16) ;
        s[kBytePos[pos] + 1] = decToHex(data[pos] & 0x0f);
    }
}
