/**
 * File    : Types.hpp
 * Author  : Emir Uner
 * Summary : Common types for XCOM.
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

#ifndef XCOM_TYPES_HPP_INCLUDED
#define XCOM_TYPES_HPP_INCLUDED

#ifndef XCOM_INTEGRAL_HPP_INCLUDED
#include <xcom/Integral.hpp>
#endif

#ifndef XCOM_ARRAYBASE_HPP_INCLUDED
#include <xcom/ArrayBase.hpp>
#endif

#ifndef XCOM_SEQUENCEBASE_HPP_INCLUDED
#include <xcom/SequenceBase.hpp>
#endif

#ifndef XCOM_STRING_HPP_INCLUDED
#include <xcom/String.hpp>
#endif

#include <stddef.h>
#include <set>

namespace xcom
{

typedef float Float;
typedef double Double;
    
#ifndef XCOM_GUID_DEFINED
#define XCOM_GUID_DEFINED
struct GUID
{
    Int data1;
    Short data2;
    Short data3;
    Octet data4[8];
};
#endif // XCOM_GUID_DEFINED

/**
 * Static null initializer for xcom::GUID.
 */
#define XCOM_NULL_GUID_INITIALIZER { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } }

/**
 * Static null initializer for xcom::Version.
 */
#define XCOM_NULL_VERSION_INITIALIZER { 0, 0, 0, 0 }

/**
 * For every user defined type that can be used by the XCOM system
 * a specialization of this struct must be provided to supply the functions
 * specified in the following comments.
 */
template <class T>
struct TypeDesc
{
    /**
     * Register the type information with the given repository.
     * This function must first register depended type(s) using
     * their TypeDesc::addSelf function then must adds itself to the sequence.
     */
    // static inline void addSelf(IUnknownSeq& types);

    /**
     * Other functions may be defined specific to the type for which
     * this struct is specialized. This can be used for compile time
     * template magic in the future.
     */
};

/**
 * The structure that is used to transfer exception information in
 * interface methods. If metadata member is null then
 * there is no exception and other members are not valid.
 */
struct Environment
{
    /**
     * This will be an IExceptionRaw*.
     */
    void* metadata;

    /**
     * This will be a pointer to exception data.
     */
    void* exception;

    Environment()
    : metadata(0), exception(0)
    {
    }    
};

/**
 * All idl defined exceptions inherit from this.
 */
struct UserExc
{
    /**
     * A xcom::metadata::IExceptionRaw*.
     */
    void* metadata;

    /**
     * ExceptionData pointer.
     */
    void* excdata;

    /**
     * Inheritance level.
     */
    int level;

    /**
     * Pass exception and it's metadata to the given environment.
     */
    inline void detach(Environment* env)
    {
        env->metadata = metadata;
        env->exception = excdata;
        metadata = 0;
    }
    
private:
    // Disable until idl compiler generates for subclasses.
    UserExc& operator=(UserExc const&);
};

/**
 * Exception thrower function type.
 */
typedef void (*ThrowerFn)(void*);

/**
 * Raw type for delegate. Just to be complete.
 */
struct DelegateData
{
    void (*function)(void*, Environment*);
    void* context;
};

/**
 * The base class for delegates.
 */
struct Delegate
{
    typedef void (*FunctionType)(void*, Environment*);
    FunctionType function;
    void *context;

    Delegate()
    {
        function = 0;
        context = 0;
    }

    bool operator==(const Delegate& rhs) const
    {
        return function == rhs.function &&
            context == rhs.context;
    }

    bool operator<(const Delegate& rhs) const
    {
        return function < rhs.function ||
            function == rhs.function && context < rhs.context;
    }

    bool operator!=(const Delegate& rhs) const
    {
        return !(*this == rhs);
    }

    operator bool() const
    {
        return function != 0;
    }

    bool operator!() const
    {
        return function == 0;
    }
};

/**
 * A binder for member functions
 */
template<typename ObjectType, typename FunctionType>
struct MemberBinder
{
    ObjectType* obj;
    FunctionType fun;

    operator size_t() const
    {
        return (size_t)obj;
    }
    
    bool operator<(const MemberBinder& rhs) const
    {
        if(obj < rhs.obj) return true;
        if(rhs.obj < obj) return false;
        
        union
        {
            FunctionType fun;
            char cmp[sizeof(FunctionType)];
        }
        cl, cr;

        cl.fun = fun;
        cr.fun = rhs.fun;

        for(int i = 0; i< sizeof(cl); ++i)
        {
            if(cl.cmp[i] < cr.cmp[i]) return true;
            if(cr.cmp[i] < cl.cmp[i]) return false;
        }
        
        return false;
    }
};

} // namespace xcom

/**
 * Exception support functions. The implementations for these
 * functions must be provided by the programmer to support
 * exceptions for C++ programs. Default implementations
 * are given in xcom/ExcImpl.inc and including this file is enough.
 */

/**
 * Must return a xcom::IUnknownSeq::RawType* .
 */
extern "C" void* xcomGetExceptionTypes();

/**
 * Register the thrower function associated with exception type given with md.
 * The md actually is a xcom.metadata.IException and
 * the function must adopt the interface pointer.
 */
extern "C" void xcomRegisterThrower(xcom::ThrowerFn thrower, void* md);

/**
 * Throw the exception specified in the environment.
 */
extern "C" void xcomFindAndThrow(xcom::Environment* excInfo);

#endif
