/**
 * File    : GUIDC.hpp
 * Author  : Emir Uner
 * Summary : C linkage GUID parsing/printing functions.
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

#ifndef XCOM_GUIDC_HPP_INCLUDED
#define XCOM_GUIDC_HPP_INCLUDED

#ifndef XCOM_TYPES_HPP_INCLUDED
#include <xcom/Types.hpp>
#endif

#include <string.h>
#include <ostream>

/**
 * Parse a given guid string and write result.
 */
extern "C"
int xcomParseGUID(xcom::Char const* str, xcom::GUID* guid);

/**
 * Generate a string representation for the given guid.
 * Assumes that the string parameter contains at least
 * 37 chars.
 */
extern "C"
void xcomGUIDToString(xcom::GUID const* guid, xcom::Char* s);

namespace xcom
{

inline bool operator==(GUID const& lhs, GUID const& rhs)
{
    return memcmp(&lhs, &rhs, 16) == 0;
}

inline bool operator!=(GUID const& lhs, GUID const& rhs)
{
    return memcmp(&lhs, &rhs, 16) != 0;
}

inline bool operator<(GUID const& lhs, GUID const& rhs)
{
    return memcmp(&lhs, &rhs, 16) < 0;
}

inline std::ostream& operator<<(std::ostream& os, GUID const& guid)
{
    char buf[37]; 
    xcomGUIDToString(&guid, buf);
    return os << buf;
}

} // namespace xcom

#endif
