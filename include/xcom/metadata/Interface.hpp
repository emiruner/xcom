/**
 * File    : Interface.hpp
 * Author  : Emir Uner
 * Summary : Interface class definitions.
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

#ifndef XCOM_METADATA_INTERFACE_HPP_INCLUDED
#define XCOM_METADATA_INTERFACE_HPP_INCLUDED

#ifndef XCOM_METADATA_DECLARED_HPP_INCLUDED
#include <xcom/metadata/Declared.hpp>
#endif

#ifndef XCOM_METADATA_EXCEPTION_HPP_INCLUDED
#include <xcom/metadata/Exception.hpp>
#endif

#ifndef XCOM_IMPLHELPER_HPP_INCLUDED
#include <xcom/ImplHelper.hpp>
#endif

#include <string>
#include <vector>

namespace xcom { namespace metadata {

/**
 * Information about a method.
 */
struct MethodInfo
{
    MethodInfo() {}
    MethodInfo(std::string nm, ParamInfoSeq const& ps)
    : name(nm), params(ps){}
    
    std::string name;
    ParamInfoSeq params;
};

inline void destroyParams(ParamInfoSeq& params)
{
    ParamInfoSeq::iterator param = params.begin(), end = params.end();
    
    while(param != end)
    {
        IType(param->type.detach());
        ++param;
    }
}

typedef std::vector<MethodInfo> MethodInfoVec;

/**
 * Represents an Interface.
 * Can also be used for forward declared interfaces.
 *
 */
class Interface : public Supports<Interface, IInterface>,
                  public RefCounted<Interface>,
                  public DeclaredImpl
{
public:
    /**
     * An interface for forward declared interfaces.
     */
    inline Interface(char const* name)
    : DeclaredImpl(TypeKind::Interface, name), forward_(true)
    {
    }
    
    /**
     * An interface with given name, iid and base.
     */
    Interface(char const* name, GUID const& iid, IInterface const& base)
    : DeclaredImpl(TypeKind::Interface, name),
      iid_(iid), base_(base), forward_(false)
    {
    }

    // IInterface method implementations.

    /**
     * Get iid of this interface.
     *
     * @pre isForward == false
     */
    inline GUID getId() const
    {
        return iid_;
    }
    
    /**
     * Get base interface. May be nil if none specified.
     *
     * @pre isForward == false
     */
    IInterface getBase() const
    {
        return base_;
    }

    inline int getMethodCount() const
    {
        return methods_.size();
    }
    
    inline String getMethodName(int idx) const
    {
        return String(methods_[idx].name.c_str());
    }
    
    inline ParamInfoSeq getParameters(int idx)
    {
        return methods_[idx].params;
    }

    /**
     * Must be called when the interface declaration found for this
     * forward declared interface.
     *
     * @pre isForward == true
     */
    void satisfyForward(GUID const& iid, IInterface const& base)
    {
        iid_ = iid;
        base_ = base;
        forward_ = false;
    }

    /**
     * Adds a new method definition.
     *
     * @pre isForward == false
     */
    void addMethod(char const* name, ParamInfoSeq const& params)
    {
        methods_.push_back(MethodInfo(name, params));
    }

    /**
     * Get method vector.
     *
     * @pre isForward == false
     */
    inline MethodInfoVec const& getMethods() const
    {
        return methods_;
    }

    /**
     * Complete definition supplied?
     */
    inline bool isForward() const
    {
        return forward_;
    }

    /**
     * Destroy embedded interface pointers.
     */
    inline void destroy()
    {
        MethodInfoVec::iterator method= methods_.begin(), end = methods_.end();
        
        while(method != end)
        {
            destroyParams(method->params);
            ++method;
        }

        IInterface(base_.detach());
    }
    
private:
    GUID iid_;
    IInterface base_;
    bool forward_;
    MethodInfoVec methods_;
};

} } // namespace

#endif
