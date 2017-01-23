/**
 * File    : ExcSupport.inc
 * Author  : Emir Uner
 * Summary : Convenience header used for supplying default implementation of
 *           required exception helper functions.
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

#include <xcom/metadata/MDTypes.hpp>
#include <stdexcept>

using namespace xcom::metadata;

namespace
{
    struct ThrowerDataRaw
    {
        xcom::ThrowerFn thrower;
        IExceptionRaw* metadata;
    };
    
    struct ThrowerData
    {
        xcom::ThrowerFn thrower;
        IException metadata;
    };    

    typedef xcom::SequenceBase<ThrowerData, ThrowerDataRaw> ThrowerSeq;
    
    inline xcom::IUnknownSeq defaultTypes()
    {
        xcom::IUnknownSeq types;
        xcom::IUnknownSeq::RawType typesRaw = types.detach();
        
        xcomPopulateBuiltin(&typesRaw);

        return xcom::IUnknownSeq::adopt(typesRaw);
    }
    
    ThrowerSeq& getThrowers()
    {
        static ThrowerSeq throwers;
        return throwers;
    }

} // namespace <unnamed>

extern "C" void xcomRegisterThrower(xcom::ThrowerFn thrower, void* metadata)
{
    ThrowerData td;
    
    td.thrower = thrower;
    td.metadata = IException::adopt(static_cast<IExceptionRaw*>(metadata));

    getThrowers().push_back(td);
}

extern "C" void* xcomGetExceptionTypes()
{
    static xcom::IUnknownSeq types(defaultTypes());
    return &types;
}

extern "C" void xcomFindAndThrow(xcom::Environment* excInfo)
{
    if(excInfo->metadata == 0)
    {
        return;
    }
    
    ThrowerSeq& throwers = getThrowers();
    IException excmd(static_cast<IExceptionRaw*>(excInfo->metadata));
    
    const int count = throwers.size();

    for(int i = 0; i < count; ++i)
    {
        if(throwers[i].metadata.getName() == excmd.getName())
        {
            throwers[i].thrower(excInfo->exception);
        }
    }

    xcomGenericDestroy(excInfo->exception, excmd.ptr_);
    xcomMemFree(excInfo->exception);

    throw std::runtime_error("unknown xcom exception:");
}

