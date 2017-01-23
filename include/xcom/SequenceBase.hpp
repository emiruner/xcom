/**
 * File    : SequenceBase.hpp
 * Author  : Emir Uner
 * Summary : SequenceBase class.
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

#ifndef XCOM_SEQUENCEBASE_HPP_INCLUDED
#define XCOM_SEQUENCEBASE_HPP_INCLUDED

#ifndef XCOM_MEMORY_HPP_INCLUDED
#include <xcom/Memory.hpp>
#endif

#include <new>
#include <string.h>

namespace xcom
{

/**
 * POD equivalent of an SequenceBase.
 */
struct SequenceData
{
    void* data;
    SizeT size;
    SizeT capacity;
};

/**
 * SequenceBase with elements that needs destruction.
 */
template <class T, class RawT>
class SequenceBase
{
public:

    typedef T value_type;
    typedef T const* const_iterator;
    typedef T* iterator;
    typedef T& reference;
    typedef T const& const_reference;

    inline iterator begin()
    {
        return &data_[0];
    }
    
    inline iterator end()
    {
        return &data_[size_];
    }
    
    inline const_iterator begin() const
    {
        return &data_[0];
    }
    
    inline const_iterator end() const
    {
        return &data_[size_];
    }

    SequenceBase()
    : data_(0), size_(0), capacity_(0)
    {
    }
    
    explicit SequenceBase(SizeT size)
    {
        data_ = allocArray<T>(size);
        size_ = capacity_ = size;
        
        for(SizeT i = 0; i < size; ++i)
        {
            new (&data_[i]) T();
        }
    }

    SequenceBase(SequenceBase const& other)
    : data_(allocArray<T>(other.size_)), size_(other.size_), capacity_(size_)
    {
        for(SizeT i = 0; i < size_; ++i)
        {
            new (&data_[i]) T(other.data_[i]);
        }
    }

    /**
     * Assumes pos < end()
     */
    iterator erase(iterator pos)
    {
        iterator origPos = pos;
        iterator lastPos = end();
        
        --lastPos;
        
        while(pos < lastPos)
        {
            *pos = *(pos + 1);
            ++pos;
        }
        pos->~T();
        
        --size_;

        return origPos;
    }
    
    /**
     * Assumes pos < end()
     */
    iterator erase(iterator start, iterator end)
    {
        iterator origPos = start;
        iterator lastPos = this->end();
        while(end != lastPos)
        {
            *start = *end;
            ++ start, ++ end;
        }
        while(start != lastPos)
        {
            start->~T();
            ++ start, --size_;
        }
        return origPos;
    }
    
    void push_back(value_type const& v)
    {
        if(size_ == capacity_)
        {
            if(capacity_ == 0)
            {
                capacity_ = 1;
            }
            else
            {
                capacity_ = capacity_ * 2;
            }
            
            T* newData = allocArray<T>(capacity_);
            
            for(SizeT i = 0; i < size_; ++i)
            {
                new (&newData[i]) T(data_[i]);
            }
            
            freeData();
            
            data_ = newData;
        }
        
        new (&data_[size_]) T(v);
        ++size_;
    }
    
    SequenceBase& operator=(SequenceBase const& rhs)
    {
        if(this != &rhs)
        {
            freeData();
            
            data_ = allocArray<T>(rhs.size_);
            size_ = rhs.size_;
            capacity_ = size_;
            
            for(SizeT i = 0; i < size_; ++i)
            {
                new (&data_[i]) T(rhs.data_[i]);
            }
        }

        return *this;
    }

    ~SequenceBase()
    {
        freeData();
    }

    inline void clear()
    {
        freeData();
        data_ = 0;
        size_ = 0;
        capacity_ = 0;
    }
    
private:
    inline void freeData()
    {
        if(data_ != 0)
        {
            for(SizeT i = 0; i < size_; ++i)
            {
                data_[i].~T();
            }
            
            xcomMemFree(data_);
        }
    }
    
public:    
    T& operator[](SizeT index)
    {
        return data_[index];
    }
    
    T const& operator[](SizeT index) const
    {
        return data_[index];
    }

    inline SizeT size() const
    {
        return size_;
    }
    
    inline SizeT capacity() const
    {
        return capacity_;
    }
    
    typedef SequenceData RawType;
    
    RawType detach()
    {
        RawType result;
        
        memcpy(&result, this, sizeof(RawType));
        
        size_ = 0;
        data_ = 0;
        capacity_ = 0;
        
        return result;
    }
    
private:
    T* data_;
    SizeT size_;
    SizeT capacity_;
};
    
} // namespace xcom

#endif
