/**
 * File    : StrHelper.cpp
 * Author  : Emir Uner
 * Summary : Helper function for BasicString template.
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

#include <xcom/String.hpp>

using namespace xcom;

namespace
{
    inline Char* localStrCpy(Char* target, Char const* src)
    {
        return strcpy(target, src);
    }
    
    inline WChar* localStrCpy(WChar* target, WChar const* src)
    {
        WChar* orig = target;
        
        while(*src != 0)
        {
            *target = *src;
            ++target;
            ++src;
        }
        
        *target = 0;
        return orig;
    }
    
    template <typename CharType>
    inline CharType* localStrDup(CharType const* src)
    {
        return localStrCpy(allocArray<CharType>(lengthOf(src) + 1), src);
    }
    
    template <typename CharType>
    inline CharType* localConcatenate(CharType const* s1, CharType const* s2)
    {
        Int llen = lengthOf(s1), rlen = lengthOf(s2);   
        CharType* target = allocArray<CharType>(llen + rlen + 1);
    
        ::memcpy(target, s1, llen * sizeof(CharType));
        ::memcpy(target + llen, s2, rlen * sizeof(CharType));
        target[llen + rlen] = 0;
    
        return target;
    }
    
} // namespace <unnamed>

extern "C"
Char* xcomDuplicateString(Char const* src)
{
    return localStrDup(src);
}

extern "C"
WChar* xcomDuplicateWString(WChar const* src)
{
    return localStrDup(src);
}
    
extern "C"
xcom::SizeT xcomWStringLength(WChar const* str)
{
    xcom::SizeT length = 0;
    
    while(*str != 0)
    {
        ++str;
        ++length;
    }
    
    return length;
}

extern "C"
Char* xcomConcatenateString(Char const* s1, Char const* s2)
{
    return localConcatenate(s1, s2);
}

extern "C"
WChar* xcomConcatenateWString(WChar const* s1, WChar const* s2)
{
    return localConcatenate(s1, s2);
}
