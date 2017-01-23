/**
 * File    : ImplHelper.hpp
 * Author  : Emir Uner
 * Summary : Component implementation helper classes.
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

#ifndef XCOM_IMPLHELPER_HPP_INCLUDED
#define XCOM_IMPLHELPER_HPP_INCLUDED

#include <xcom/IUnknown.hpp>
#include <xcom/GUID.hpp>

namespace xcom
{

/**
 * addRef/release function implementation.
 */    
template <typename Impl>
struct RefCounted
{
    RefCounted()
    : refCount_(0)
    {
        addRef();
    }
    
    Int addRef()
    {
        return ++refCount_;
    }
    
    Int release()
    {
        Int newCount = --refCount_;
        
        if(newCount == 0)
        {
            delete static_cast<Impl*>(this);
        }
        
        return newCount;
    }
    
    Int refCount_;
};

/**
 * addRef/release implementation for non-heap objects.
 */
template <typename Impl>
struct Singleton 
{
    Int addRef()
    {
        return 3;
    }
    
    Int release()
    {
        return 2;
    }
};

template<typename Itf>
inline bool isType(GUID const& id)
{
    return id == Itf::thisInterfaceId() || isType<typename Itf::ParentClass>(id);
}

template<>
inline bool isType<IUnknown>(GUID const& id)
{
    return id == IUnknown::thisInterfaceId();
}

/**
 * Query interface implementation classes.
 */
template <typename Impl, typename Itf>
struct Supports : public Itf:: template Tie<Impl>::type
{
    IUnknown queryInterface(GUID const& id)
    {
        if(isType<Itf>(id))
        {
            Impl* me = static_cast<Impl*>(this);
            me->addRef();
            return static_cast<typename Itf::RawType>(me);
        }
        
        return 0;
    }
};

template <typename Impl, typename Itf1, typename Itf2>
struct Supports2 : public Itf1::template Tie<Impl>::type, public Itf2::template Tie<Impl>::type
{
    IUnknown queryInterface(GUID const& id)
    {
        Impl* me = static_cast<Impl*>(this);
        
        if(isType<Itf1>(id))
        {
            me->addRef();
            return static_cast<typename Itf1::RawType>(me);
        }

        if(isType<Itf2>(id))
        {
            me->addRef();
            return static_cast<typename Itf2::RawType>(me);
        }
        
        return 0;
    }

    operator IUnknown()
    {
        Impl* me = static_cast<Impl*>(this);
        me->addRef();
        return static_cast<typename Itf1::RawType>(me);
    }
};

template <typename Impl, typename Itf1, typename Itf2, typename Itf3>
struct Supports3
    : public Itf1::template Tie<Impl>::type,
      public Itf2::template Tie<Impl>::type,
      public Itf3::template Tie<Impl>::type
{
    IUnknown queryInterface(GUID const& id)
    {
        Impl* me = static_cast<Impl*>(this);

        if(isType<Itf1>(id))
        {
            me->addRef();
            return static_cast<typename Itf1::RawType>(me);
        }

        if(isType<Itf2>(id))
        {
            me->addRef();
            return static_cast<typename Itf2::RawType>(me);
        }

        if(isType<Itf3>(id))
        {
            me->addRef();
            return static_cast<typename Itf3::RawType>(me);
        }

        return 0;
    }
    
    operator IUnknown ()
    {
        Impl* me = static_cast<Impl*>(this);
        me->addRef();
        return static_cast<typename Itf1::RawType>(me);
    }
};

/**
 * Helper base class for DLLAccess* classes.
 * @see XCOM_PROVIDE_DLL_ACCESS
 */
struct DLLAccessBase
{
    xcom::GUID vendor;
    xcom::Version version;
    xcom::StringSeq classes;
    xcom::IUnknownSeq types;
    xcom::IUnknownSeq interfaces;

    void addInterface(xcom::Char const* name)
    {
        interfaces.push_back(xcom::rawFindMetadata(types, name));
    }
    
    DLLAccessBase(xcom::Char const* vendorStr, xcom::Int major = 0,
                  xcom::Int minor = 0, xcom::Int build = 0,
                  xcom::Int revision = 0)
    {
        xcomParseGUID(vendorStr, &vendor);
        version.major = major;
        version.minor = minor;
        version.build = build;
        version.revision = revision;
        xcom::populateBuiltin(types);
    }

    DLLAccessBase()
    {
        xcom::GUID nullGUID = XCOM_NULL_GUID_INITIALIZER;
        xcom::Version nullVersion = XCOM_NULL_VERSION_INITIALIZER;
        
        vendor = nullGUID;
        version = nullVersion;
        xcom::populateBuiltin(types);
    }

    void dllGetVersion(xcom::Version& ver, xcom::GUID& ven)
    {
        ver = version;
        ven = vendor;
    }
    
    xcom::StringSeq dllGetClassNames()
    {
        return classes;
    }
    
    xcom::IUnknownSeq dllGetMetadata()
    {
        return interfaces;
    }

    xcom::Bool dllCanUnloadNow()
    {
        return false;
    }
};

} // namespace xcom

/**
 * Creata a class like the below and pass its name to th
 * XCOM_DLL_PROVIDE_ACCESS macro to provide required functions for shared
 * libraries.
 */
// struct DLLAccess : public xcom::DLLAccessBase
// {
//     // * In constructor call one of the two base constructors
//     // * Populate classes string vector with list of classes
//     // * Register QI'd interfaces using the types
//     // * Call addInterface with each of the QI returned interfaces
//     DLLAccess();
//
//     xcom::IUnknown dllCreateObject(const xcom::Char* classname)
//     {
//     }
//    
//     // May write this function to override default which returns false
//     // always
//     static xcom::Bool dllCanUnloadNow()
//     {
//     }
// }

/**
 * Use this macro to supply required shared library functions.
 */
#define XCOM_PROVIDE_DLL_ACCESS(InfoClass) \
    namespace { InfoClass componentInfo; }                                      \
    extern "C" void dllGetVersion(xcom::Version* version, xcom::GUID* vendor) \
    {                                                                           \
        componentInfo.dllGetVersion(*version, *vendor);                         \
    }                                                                           \
                                                                                \
    extern "C" xcom::StringSeq::RawType dllGetClassNames()                      \
    {                                                                           \
        return componentInfo.dllGetClassNames().detach();                       \
    }                                                                           \
                                                                                \
    extern "C" xcom::IUnknownSeq::RawType dllGetMetadata()                      \
    {                                                                           \
        return componentInfo.dllGetMetadata().detach();                         \
    }                                                                           \
                                                                                \
    extern "C" xcom::IUnknownRaw* dllCreateObject(const xcom::Char* classname)  \
    {                                                                           \
        return componentInfo.dllCreateObject(classname).detach();               \
    }                                                                           \
                                                                                \
    extern "C" xcom::Bool dllCanUnloadNow()                                     \
    {                                                                           \
        return componentInfo.dllCanUnloadNow();                                 \
    }

#endif
