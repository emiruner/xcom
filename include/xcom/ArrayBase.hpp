/**
 * File    : ArrayBase.hpp
 * Author  : Emir Uner
 * Summary : ArrayBase class.
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

#ifndef XCOM_ARRAYBASE_HPP_INCLUDED
#define XCOM_ARRAYBASE_HPP_INCLUDED

#ifndef XCOM_MEMORY_HPP_INCLUDED
#include <xcom/Memory.hpp>
#endif

#include <string.h>

namespace xcom
{

/**
 * ArrayBase with elements that does not need destruction.
 */
template <class T, SizeT Size, class RawT = T>
struct SimpleArrayBase
{
    typedef T value_type;    
    typedef T* iterator;
    typedef T const* const_iterator;
    
    T data_[Size];
    
    inline iterator begin()
    {
        return &data_[0];
    }
    
    inline iterator end()
    {
        return &data_[Size];
    }
    
    inline const_iterator begin() const
    {
        return &data_[0];
    }
    
    inline const_iterator end() const
    {
        return &data_[Size];
    }
    
    T& operator[](SizeT index)
    {
        return data_[index];
    }
    
    T const& operator[](SizeT index) const
    {
        return data_[index];
    }
};

/**
 * ArrayBase with elements that needs destruction.
 */
template <class T, SizeT Size, class RawT>
class ArrayBase
{
public:
    typedef T value_type;    
    typedef T* iterator;
    typedef T const* const_iterator;
    
    inline iterator begin()
    {
        return &data_[0];
    }
    
    inline iterator end()
    {
        return &data_[Size];
    }
    
    inline const_iterator begin() const
    {
        return &data_[0];
    }
    
    inline const_iterator end() const
    {
        return &data_[Size];
    }
    
    typedef SimpleArrayBase<RawT, Size, RawT> RawType;
    
    T& operator[](SizeT index)
    {
        return data_[index];
    }
    
    T const& operator[](SizeT index) const
    {
        return data_[index];
    }

    RawType detach()
    {
        RawType result;
        
        for(SizeT i = 0; i < Size; ++i)
        {
            result[i] = data_[i].detach();
        }
        
        return result;
    }
    
    static ArrayBase adopt(RawType const& src)
    {
        ArrayBase result;
        ::memcpy(&result, &src, sizeof(RawType));
        return result;
    }
    
protected:
    T data_[Size];                
};
    
} // namespace xcom

#endif
