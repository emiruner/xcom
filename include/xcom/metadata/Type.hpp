/**
 * File    : Type.hpp
 * Author  : Emir Uner
 * Summary : Type class.
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

#ifndef XCOM_METADATA_TYPE_HPP_INCLUDED
#define XCOM_METADATA_TYPE_HPP_INCLUDED

#include <xcom/metadata/MDTypesTie.hpp>
#include <xcom/ImplHelper.hpp>

namespace xcom { namespace metadata {

/**
 * Return string equivalent of a built-in type as used in IDL.
 */
inline char const* kindAsString(int kind)
{
    switch(kind)
    {
    case TypeKind::Void: return "void";
    case TypeKind::Bool: return "bool";
    case TypeKind::Octet: return "octet";
    case TypeKind::Short: return "short";
    case TypeKind::Int: return "int";
    case TypeKind::Long: return "long";
    case TypeKind::Float: return "float";
    case TypeKind::Double: return "double";
    case TypeKind::Char: return "char";
    case TypeKind::WChar: return "wchar";
    case TypeKind::String: return "string";
    case TypeKind::WString: return "wstring";
    case TypeKind::Any: return "any";
    default: break;
    }
    
    return "<<invalid>>";
}    

/**
 * Returns true if the kind belongs to built-in type.
 */
inline bool isBuiltin(int kind)
{
    switch(kind)
    {
    case TypeKind::Enum:
    case TypeKind::Array:
    case TypeKind::Sequence:
    case TypeKind::Struct:
    case TypeKind::Interface:
    case TypeKind::Exception:
    case TypeKind::Delegate:
        return false;
    default:
        return true;
    }
}

/**
 * Implementations of IType functions.
 */
class TypeImpl
{
public:
    inline explicit TypeImpl(int kind)
    : kind_(kind)
    {
    }

    inline int getKind() const
    {
        return kind_;
    }

private:
    int kind_;
};

/**
 * Base type for user defined types.
 */
class Type : public Supports<Type, IType>,
             public RefCounted<Type>,
             public TypeImpl
{
public:
    /**
     * Type  with given name and type.
     */
    inline explicit Type(int kind)
    : TypeImpl(kind)
    {
    }
};

/**
 * IType implementation designed as a static/on stack object.
 */
class StaticType : public Supports<StaticType, IType>,
                   public TypeImpl,
                   public Singleton<StaticType>
{
public:
    explicit StaticType(int kind)
    : TypeImpl(kind)
    {
    }
};

} } // namespace

#endif
