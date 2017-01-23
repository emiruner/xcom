/**
 * File    : Delegate.hpp
 * Author  : David Turner
 * Summary : Delegate type.
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

#ifndef XCOM_METADATA_DELEGATE_HPP_INCLUDED
#define XCOM_METADATA_DELEGATE_HPP_INCLUDED

#ifndef XCOM_METADATA_DECLARED_HPP_INCLUDED
#include <xcom/metadata/Declared.hpp>
#endif

#ifndef XCOM_IMPLHELPER_HPP_INCLUDED
#include <xcom/ImplHelper.hpp>
#endif

#include <string>
#include <vector>

namespace xcom { namespace metadata {

/**
 * Represents a delegate.
 *
 */
class Delegate : public Supports<Delegate, IDelegate>,
                 public RefCounted<Delegate>,
                 public DeclaredImpl
{
    ParamInfoSeq params_;

public:
    /**
     * Constructor takes a name
     */
    Delegate(char const* name, ParamInfoSeq const& params)
    : DeclaredImpl(TypeKind::Delegate, name), params_(params)
    {
    }

    inline ParamInfoSeq getParameters()
    {
        return params_;
    }
};

} } // namespace

#endif
