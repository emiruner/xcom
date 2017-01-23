/**
 * File    : Integral.hpp
 * Author  : Emir Uner
 * Summary : Integral type definitions.
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

#ifndef XCOM_INTEGRAL_HPP_INCLUDED
#define XCOM_INTEGRAL_HPP_INCLUDED

/**
 * Exact width integral type definitions.
 * Hacked by D. Turner to support most systems without requiring boost.
 */

# include <stddef.h>    // for size_t

# if defined(_MSC_VER)

typedef unsigned __int8     xcom_uint8_t;
typedef __int8              xcom_int8_t;
typedef unsigned __int16    xcom_uint16_t;
typedef __int16             xcom_int16_t;
typedef unsigned __int32    xcom_uint32_t;
typedef __int32             xcom_int32_t;
typedef unsigned __int64    xcom_uint64_t;
typedef __int64             xcom_int64_t;

# elif defined(__hpux) || defined(__FreeBSD__) || defined(__IBMCPP__)
#define XCOM_INTEGRALS_FROM_HEADER
#  include <inttypes.h>
# elif defined(__linux)
#define XCOM_INTEGRALS_FROM_HEADER
#  include <stdint.h>
# elif defined (__CYGWIN__)
#define XCOM_INTEGRALS_FROM_HEADER
#  include <sys/types.h>
# else

#  include <limits.h>

#  if UCHAR_MAX == 0xff
typedef unsigned char   xcom_uint8_t;
typedef char            xcom_int8_t;
#  else
#   error Cannot find an 8-bit type!
#  endif

#  if USHRT_MAX == 0xffff
typedef unsigned short  xcom_uint16_t;
typedef short           xcom_int16_t;
#  else
#   error Cannot find a 16-bit type!
#  endif

#  if ULONG_MAX == 0xffffffff
typedef unsigned long   xcom_uint32_t;
typedef long            xcom_int32_t;
#  elif UINT_MAX == 0xffffffff
typedef unsigned int    xcom_uint32_t;
typedef long            xcom_int32_t;
#  else
#   error Cannot find a 32-bit type!
#  endif

#  if (defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX))
typedef unsigned long long  xcom_uint64_t;
typedef long long           xcom_int64_t;
#  elif ULONG_MAX != 0xffffffff
#   if ULONG_MAX == 18446744073709551615
typedef unsigned long       xcom_uint64_t;
typedef long                xcom_int64_t;
#   else
#    error Cannot find a 64-bit type!
#   endif
#  else
#   error Cannot find a 64-bit type!
#  endif
# endif

#ifdef XCOM_INTEGRALS_FROM_HEADER

typedef int8_t xcom_int8_t;
typedef uint8_t xcom_uint8_t;
typedef int16_t xcom_int16_t;
typedef uint16_t xcom_uint16_t;
typedef int32_t xcom_int32_t;
typedef uint32_t xcom_uint32_t;
typedef int64_t xcom_int64_t;
typedef uint64_t xcom_uint64_t;

#endif
    
namespace xcom
{
    typedef xcom_uint8_t Octet;
    typedef xcom_int16_t Short;
    typedef xcom_int32_t Int;
    typedef xcom_int64_t Long;
    typedef char Char;
    typedef xcom_int32_t WChar;
    typedef size_t SizeT;
    typedef xcom_uint8_t Bool;
}

#endif
