#ifndef INC_IUNKNOWNTIE_HPP_E6227639_7DD6_4107_8C55_681EFE9B8C1E
#define INC_IUNKNOWNTIE_HPP_E6227639_7DD6_4107_8C55_681EFE9B8C1E

#include "IUnknown.hpp"
namespace xcom
{

    template <class Impl>
    class IUnknownTie : public IUnknownRaw
    {
    public:
        static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
        {
            try {
            return static_cast<Impl*>(static_cast<IUnknownTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::IUnknown().detach();
            
        }
        
        static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
        {
            return IUnknown::thisInterfaceId();
        }
        
        static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
        {
            try {
            return static_cast<Impl*>(static_cast<IUnknownTie<Impl>*>(ptr))->addRef();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::Int();
            
        }
        
        static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
        {
            try {
            return static_cast<Impl*>(static_cast<IUnknownTie<Impl>*>(ptr))->release();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::Int();
            
        }
        
        
        
        IUnknownTie()
        {
            vptr_ = &IUnknownTieVtbl;
        }
    
    private:
        static IUnknownVtbl IUnknownTieVtbl;
    };
    
    template <class Impl>
    IUnknownVtbl IUnknownTie<Impl>::IUnknownTieVtbl =
    {
        &IUnknownTie<Impl>::queryInterface__call,
        &IUnknownTie<Impl>::getInterfaceId__call,
        &IUnknownTie<Impl>::addRef__call,
        &IUnknownTie<Impl>::release__call,
        
    };
    
}

#endif
