/**
 * File    : String.hpp
 * Author  : Emir Uner
 * Summary : String classes.
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

#ifndef XCOM_STRING_HPP_INCLUDED
#define XCOM_STRING_HPP_INCLUDED

#ifndef XCOM_MEMORY_HPP_INCLUDED
#include <xcom/Memory.hpp>
#endif

#include <string.h>
#include <ostream>

/**
 * Duplicate given Char string.
 */
extern "C"
xcom::Char* xcomDuplicateString(xcom::Char const* src);

/**
 * Duplicate given WChar string.
 */
extern "C"
xcom::WChar* xcomDuplicateWString(xcom::WChar const* src);

/**
 * Return length of WChar string.
 */
extern "C"
xcom::SizeT xcomWStringLength(xcom::WChar const* str);

/**
 * Concatenate two Char strings by creating new string.
 */
extern "C"
xcom::Char* xcomConcatenateString(xcom::Char const* s1, xcom::Char const* s2);

/**
 * Concatenate two WChar strings.
 */
extern "C"
xcom::WChar* xcomConcatenateWString(xcom::WChar const* s1,
                                    xcom::WChar const* s2);

namespace xcom
{

inline SizeT lengthOf(Char const* str)
{
    return strlen(str);
}

inline SizeT lengthOf(WChar const* str)
{
    return xcomWStringLength(str);
}

inline Char* duplicateString(Char const* src)
{
    return xcomDuplicateString(src);
}

inline WChar* duplicateString(WChar const* src)
{
    return xcomDuplicateWString(src);
}

inline Char* concatenateString(Char const* s1, Char const* s2)
{
    return xcomConcatenateString(s1, s2);
}

inline WChar* concatenateString(WChar const* s1, WChar const* s2)
{
    return xcomConcatenateWString(s1, s2);
}

inline Char const* findSubstring(Char const* haystack, Char const* needle)
{
    return strstr(haystack, needle);
}

/**
 * BasicString of XCOM.
 */
template <typename CharType>
class BasicString
{
public:
    static const SizeT npos = -1;
    
    typedef CharType value_type;
    typedef value_type* iterator;
    typedef value_type const* const_iterator;
    
    iterator begin()
    {
        return &str_[0];
    }
    
    iterator end()
    {
        return &str_[length()];
    }
    
    const_iterator begin() const
    {
        return &str_[0];
    }
    
    const_iterator end() const
    {
        return &str_[length()];
    }
    

    typedef CharType* RawType;

    BasicString()
    : str_(0)
    {
    }

    BasicString(CharType const* other)
    : str_(duplicateString(other))
    {
    }
           
    BasicString(BasicString const& other)
    : str_(duplicateString(other.str_))
    {
    }

    BasicString(const_iterator srcBegin, const_iterator srcEnd)
    {
        str_ = allocArray<value_type>(srcEnd - srcBegin + 1);
        iterator target = str_;
        
        while(srcBegin != srcEnd)
        {
            *target = *srcBegin;
            ++target;
            ++srcBegin;
        }
        
        *target = '\0';
    }
    
    ~BasicString()
    {
        destroyContents();
    }
    
    BasicString& operator=(BasicString const& rhs)
    {
        if(this != &rhs)
        {
            CharType* copy = duplicateString(rhs.str_);
            destroyContents();
            str_ = copy;
        }
        
        return *this;
    }

    CharType& operator[](SizeT index)
    {
        return str_[index];
    }
    
    CharType const& operator[](SizeT index) const
    {
        return str_[index];
    }
    
    SizeT size() const
    {
        if(str_ == 0)
        {
            return 0;
        }
        
        return lengthOf(str_);
    }

    SizeT length() const
    {
        return size();
    }

    SizeT find(BasicString const& needle) const
    {
        CharType const* found = findSubstring(str_, needle.str_);

        if(found == 0)
        {
            return npos;
        }
        else
        {
            return str_ - found;
        }
    }
    
    CharType const* c_str() const
    {
        if(str_ == 0)
        {
            return "";
        }
        
        return str_;
    }

    inline operator std::basic_string<CharType>() const
    {
        return std::basic_string<CharType>(str_);
    }
    
    inline BasicString<CharType>& operator+=(BasicString<CharType> const& rhs)
    {
        CharType* newStr = concatenateString(str_, rhs.c_str());
        destroyContents();
        str_ = newStr;

        return *this;
    }
    
    inline BasicString<CharType>& operator+=(CharType const* rhs)
    {
        CharType* newStr = concatenateString(str_, rhs);
        destroyContents();
        str_ = newStr;

        return *this;
    }
    
    CharType* detach()
    {
        CharType* result = str_;
        str_ = 0;
        return result;
    }
    
    inline bool operator <(const BasicString& rhs) const
    {
        const_iterator i = begin(), ie = end(), j = rhs.begin(), je = rhs.end();

        while(i != ie && j != je)
        {
            if(*i < *j)
                return true;
            if(*j < *i)
                return false;
        }
        return j != je;
    }

    static inline BasicString<CharType> adopt(CharType* src)
    {
        BasicString<CharType> result;
        result.str_ = src;
        return result;
    }

private:
    CharType* str_;
    
    inline void destroyContents()
    {
        if(str_ != 0)
        {            
            xcomMemFree(str_);
        }
    }    
};

template <typename CharType>
inline BasicString<CharType> operator+(BasicString<CharType> const& lhs,
                                       BasicString<CharType> const& rhs)
{
    return BasicString<CharType>::adopt(
        concatenateString(lhs.c_str(), rhs.c_str())
        );
}

template <typename CharType>
inline BasicString<CharType> operator+(BasicString<CharType> const& lhs,
                                       CharType const* rhs)
{
    return BasicString<CharType>::adopt(
        concatenateString(lhs.c_str(), rhs)
        );
}

typedef BasicString<Char> String;
typedef BasicString<WChar> WString;

inline bool operator==(String const& lhs, String const& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

inline bool operator==(String const& lhs, char const* rhs)
{
    return strcmp(lhs.c_str(), rhs) == 0;
}

inline bool operator!=(String const& lhs, String const& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

inline bool operator!=(String const& lhs, char const* rhs)
{
    return strcmp(lhs.c_str(), rhs) != 0;
}

} // namespace xcom

namespace std
{
    
template<typename CharType>
inline basic_ostream<CharType>&
operator<<(basic_ostream<CharType>& os,
           const ::xcom::BasicString<CharType>& str)
{
	return os << str.c_str();
}
 
} // namespace std

#endif
