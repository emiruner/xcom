/**
 * File    : StructBase.hpp
 * Author  : Emir Uner
 * Summary : SturctBase class definitions.
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

#ifndef XCOM_METADATA_STRUCTBASE_HPP_INCLUDED
#define XCOM_METADATA_STRUCTBASE_HPP_INCLUDED

#ifndef XCOM_METADATA_DECLARED_HPP_INCLUDED
#include <xcom/metadata/Declared.hpp>
#endif

#include <vector>
#include <string>

namespace xcom { namespace metadata {

/**
 * Information about a member.
 */
struct MemberInfo
{
    std::string name;
    IType type;
    int offset;
};

typedef std::vector<MemberInfo> MemberInfoVec;
    
/**
 * Base type for Exception and Struct classes.
 */
class StructBase : public DeclaredImpl
{
public:
    /**
     * A StructBase with given name.
     */
    inline StructBase(TypeKindEnum type, char const* name, int size)
    : DeclaredImpl(type, name)
    {
    }

    // IStruct and IException methods implementations.
    inline int getMemberCount() const
    {
        return members_.size();
    }
    
    inline IType getMemberType(int idx) const
    {
        return members_[idx].type;
    }
    
    inline String getMemberName(int idx) const
    {
        return String(members_[idx].name.c_str());
    }

    inline int getMemberOffset(int idx) const
    {
        return members_[idx].offset;
    }

    inline int getSize() const
    {
        return size_;
    }
    
    /**
     * Assumes that type is not destroyed until this object.
     */
    void addMember(std::string name, IType type, int offset = -1)
    {
        MemberInfo mi;
        
        mi.name = name;
        mi.type = type;
        mi.offset = offset;
        
        members_.push_back(mi);
    }
    
private:
    MemberInfoVec members_;
    int size_;
};

} } // namespace

#endif
