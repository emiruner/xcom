#ifndef INC_ILIBRARYTIE_HPP_08E75F30_EC3F_49FA_919D_56F08C72FD23
#define INC_ILIBRARYTIE_HPP_08E75F30_EC3F_49FA_919D_56F08C72FD23

#include "ILibrary.hpp"
namespace xcom
{

    template <class Impl>
    class ILibraryTie : public ILibraryRaw
    {
    public:
        static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
        {
            try {
            return static_cast<Impl*>(static_cast<ILibraryTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::IUnknown().detach();
            
        }
        
        static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
        {
            return ILibrary::thisInterfaceId();
        }
        
        static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
        {
            try {
            return static_cast<Impl*>(static_cast<ILibraryTie<Impl>*>(ptr))->addRef();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::Int();
            
        }
        
        static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
        {
            try {
            return static_cast<Impl*>(static_cast<ILibraryTie<Impl>*>(ptr))->release();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::Int();
            
        }
        
        static xcom::IUnknownRaw* createObject__call(void* ptr, ::xcom::Environment* __exc_info, const xcom::Char* name)
        {
            try {
            return static_cast<Impl*>(static_cast<ILibraryTie<Impl>*>(ptr))->createObject(name).detach();
            } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
            return xcom::IUnknown().detach();
            
        }
        
        
        
        ILibraryTie()
        {
            vptr_ = &ILibraryTieVtbl;
        }
    
    private:
        static ILibraryVtbl ILibraryTieVtbl;
    };
    
    template <class Impl>
    ILibraryVtbl ILibraryTie<Impl>::ILibraryTieVtbl =
    {
        &ILibraryTie<Impl>::queryInterface__call,
        &ILibraryTie<Impl>::getInterfaceId__call,
        &ILibraryTie<Impl>::addRef__call,
        &ILibraryTie<Impl>::release__call,
        &ILibraryTie<Impl>::createObject__call,
        
    };
    
}

#endif
