#ifndef INC_MDTYPESTIE_HPP_AE396C67_2ECC_44E8_9BB2_2F54052463F1
#define INC_MDTYPESTIE_HPP_AE396C67_2ECC_44E8_9BB2_2F54052463F1

#include "MDTypes.hpp"
namespace xcom
{

    namespace metadata
    {
    
        template <class Impl>
        class ITypeTie : public ITypeRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<ITypeTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IType::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ITypeTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ITypeTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ITypeTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            
            
            ITypeTie()
            {
                vptr_ = &ITypeTieVtbl;
            }
        
        private:
            static ITypeVtbl ITypeTieVtbl;
        };
        
        template <class Impl>
        ITypeVtbl ITypeTie<Impl>::ITypeTieVtbl =
        {
            &ITypeTie<Impl>::queryInterface__call,
            &ITypeTie<Impl>::getInterfaceId__call,
            &ITypeTie<Impl>::addRef__call,
            &ITypeTie<Impl>::release__call,
            &ITypeTie<Impl>::getKind__call,
            
        };
        
        template <class Impl>
        class IDeclaredTie : public IDeclaredRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IDeclaredTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IDeclared::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDeclaredTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDeclaredTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDeclaredTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDeclaredTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            
            
            IDeclaredTie()
            {
                vptr_ = &IDeclaredTieVtbl;
            }
        
        private:
            static IDeclaredVtbl IDeclaredTieVtbl;
        };
        
        template <class Impl>
        IDeclaredVtbl IDeclaredTie<Impl>::IDeclaredTieVtbl =
        {
            &IDeclaredTie<Impl>::queryInterface__call,
            &IDeclaredTie<Impl>::getInterfaceId__call,
            &IDeclaredTie<Impl>::addRef__call,
            &IDeclaredTie<Impl>::release__call,
            &IDeclaredTie<Impl>::getKind__call,
            &IDeclaredTie<Impl>::getName__call,
            
        };
        
        template <class Impl>
        class ISequenceTie : public ISequenceRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<ISequenceTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return ISequence::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ISequenceTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ISequenceTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ISequenceTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ISequenceTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::metadata::ITypeRaw* getElementType__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<ISequenceTie<Impl>*>(ptr))->getElementType().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::IType().detach();
                
            }
            
            
            
            ISequenceTie()
            {
                vptr_ = &ISequenceTieVtbl;
            }
        
        private:
            static ISequenceVtbl ISequenceTieVtbl;
        };
        
        template <class Impl>
        ISequenceVtbl ISequenceTie<Impl>::ISequenceTieVtbl =
        {
            &ISequenceTie<Impl>::queryInterface__call,
            &ISequenceTie<Impl>::getInterfaceId__call,
            &ISequenceTie<Impl>::addRef__call,
            &ISequenceTie<Impl>::release__call,
            &ISequenceTie<Impl>::getKind__call,
            &ISequenceTie<Impl>::getName__call,
            &ISequenceTie<Impl>::getElementType__call,
            
        };
        
        template <class Impl>
        class IArrayTie : public IArrayRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IArray::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::metadata::ITypeRaw* getElementType__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->getElementType().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::IType().detach();
                
            }
            
            static xcom::Int getSize__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IArrayTie<Impl>*>(ptr))->getSize();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            
            
            IArrayTie()
            {
                vptr_ = &IArrayTieVtbl;
            }
        
        private:
            static IArrayVtbl IArrayTieVtbl;
        };
        
        template <class Impl>
        IArrayVtbl IArrayTie<Impl>::IArrayTieVtbl =
        {
            &IArrayTie<Impl>::queryInterface__call,
            &IArrayTie<Impl>::getInterfaceId__call,
            &IArrayTie<Impl>::addRef__call,
            &IArrayTie<Impl>::release__call,
            &IArrayTie<Impl>::getKind__call,
            &IArrayTie<Impl>::getName__call,
            &IArrayTie<Impl>::getElementType__call,
            &IArrayTie<Impl>::getSize__call,
            
        };
        
        template <class Impl>
        class IEnumTie : public IEnumRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IEnum::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::Int getElementCount__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->getElementCount();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getElement__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IEnumTie<Impl>*>(ptr))->getElement(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            
            
            IEnumTie()
            {
                vptr_ = &IEnumTieVtbl;
            }
        
        private:
            static IEnumVtbl IEnumTieVtbl;
        };
        
        template <class Impl>
        IEnumVtbl IEnumTie<Impl>::IEnumTieVtbl =
        {
            &IEnumTie<Impl>::queryInterface__call,
            &IEnumTie<Impl>::getInterfaceId__call,
            &IEnumTie<Impl>::addRef__call,
            &IEnumTie<Impl>::release__call,
            &IEnumTie<Impl>::getKind__call,
            &IEnumTie<Impl>::getName__call,
            &IEnumTie<Impl>::getElementCount__call,
            &IEnumTie<Impl>::getElement__call,
            
        };
        
        template <class Impl>
        class IStructTie : public IStructRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IStruct::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::Int getMemberCount__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getMemberCount();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::metadata::ITypeRaw* getMemberType__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getMemberType(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::IType().detach();
                
            }
            
            static xcom::Char* getMemberName__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getMemberName(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::Int getMemberOffset__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getMemberOffset(idx);
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getSize__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IStructTie<Impl>*>(ptr))->getSize();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            
            
            IStructTie()
            {
                vptr_ = &IStructTieVtbl;
            }
        
        private:
            static IStructVtbl IStructTieVtbl;
        };
        
        template <class Impl>
        IStructVtbl IStructTie<Impl>::IStructTieVtbl =
        {
            &IStructTie<Impl>::queryInterface__call,
            &IStructTie<Impl>::getInterfaceId__call,
            &IStructTie<Impl>::addRef__call,
            &IStructTie<Impl>::release__call,
            &IStructTie<Impl>::getKind__call,
            &IStructTie<Impl>::getName__call,
            &IStructTie<Impl>::getMemberCount__call,
            &IStructTie<Impl>::getMemberType__call,
            &IStructTie<Impl>::getMemberName__call,
            &IStructTie<Impl>::getMemberOffset__call,
            &IStructTie<Impl>::getSize__call,
            
        };
        
        template <class Impl>
        class IExceptionTie : public IExceptionRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IException::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::metadata::IExceptionRaw* getBase__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getBase().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::IException().detach();
                
            }
            
            static xcom::Int getMemberCount__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getMemberCount();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::metadata::ITypeRaw* getMemberType__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getMemberType(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::IType().detach();
                
            }
            
            static xcom::Char* getMemberName__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getMemberName(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::Int getMemberOffset__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getMemberOffset(idx);
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getSize__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IExceptionTie<Impl>*>(ptr))->getSize();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            
            
            IExceptionTie()
            {
                vptr_ = &IExceptionTieVtbl;
            }
        
        private:
            static IExceptionVtbl IExceptionTieVtbl;
        };
        
        template <class Impl>
        IExceptionVtbl IExceptionTie<Impl>::IExceptionTieVtbl =
        {
            &IExceptionTie<Impl>::queryInterface__call,
            &IExceptionTie<Impl>::getInterfaceId__call,
            &IExceptionTie<Impl>::addRef__call,
            &IExceptionTie<Impl>::release__call,
            &IExceptionTie<Impl>::getKind__call,
            &IExceptionTie<Impl>::getName__call,
            &IExceptionTie<Impl>::getBase__call,
            &IExceptionTie<Impl>::getMemberCount__call,
            &IExceptionTie<Impl>::getMemberType__call,
            &IExceptionTie<Impl>::getMemberName__call,
            &IExceptionTie<Impl>::getMemberOffset__call,
            &IExceptionTie<Impl>::getSize__call,
            
        };
        
        template <class Impl>
        class IInterfaceTie : public IInterfaceRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IInterface::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::GUID getId__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getId();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::GUID();
                
            }
            
            static xcom::metadata::IInterfaceRaw* getBase__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getBase().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::IInterface().detach();
                
            }
            
            static xcom::Int getMethodCount__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getMethodCount();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getMethodName__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getMethodName(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::metadata::ParamInfoSeq::RawType getParameters__call(void* ptr, ::xcom::Environment* __exc_info, xcom::Int idx)
            {
                try {
                return static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->getParameters(idx).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::ParamInfoSeq().detach();
                
            }
            
            static void destroy__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try
                {
                    static_cast<Impl*>(static_cast<IInterfaceTie<Impl>*>(ptr))->destroy();
                    
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                }
                
            
            
            IInterfaceTie()
            {
                vptr_ = &IInterfaceTieVtbl;
            }
        
        private:
            static IInterfaceVtbl IInterfaceTieVtbl;
        };
        
        template <class Impl>
        IInterfaceVtbl IInterfaceTie<Impl>::IInterfaceTieVtbl =
        {
            &IInterfaceTie<Impl>::queryInterface__call,
            &IInterfaceTie<Impl>::getInterfaceId__call,
            &IInterfaceTie<Impl>::addRef__call,
            &IInterfaceTie<Impl>::release__call,
            &IInterfaceTie<Impl>::getKind__call,
            &IInterfaceTie<Impl>::getName__call,
            &IInterfaceTie<Impl>::getId__call,
            &IInterfaceTie<Impl>::getBase__call,
            &IInterfaceTie<Impl>::getMethodCount__call,
            &IInterfaceTie<Impl>::getMethodName__call,
            &IInterfaceTie<Impl>::getParameters__call,
            &IInterfaceTie<Impl>::destroy__call,
            
        };
        
        template <class Impl>
        class IDelegateTie : public IDelegateRaw
        {
        public:
            static xcom::IUnknownRaw* queryInterface__call(void* ptr, ::xcom::Environment* __exc_info, xcom::GUID const* iid)
            {
                try {
                return static_cast<Impl*>(static_cast<IDelegateTie<Impl>*>(ptr))->queryInterface(*(xcom::GUID*)iid).detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::IUnknown().detach();
                
            }
            
            static xcom::GUID getInterfaceId__call(void*, ::xcom::Environment*)
            {
                return IDelegate::thisInterfaceId();
            }
            
            static xcom::Int addRef__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDelegateTie<Impl>*>(ptr))->addRef();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int release__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDelegateTie<Impl>*>(ptr))->release();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Int getKind__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDelegateTie<Impl>*>(ptr))->getKind();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::Int();
                
            }
            
            static xcom::Char* getName__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDelegateTie<Impl>*>(ptr))->getName().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::String().detach();
                
            }
            
            static xcom::metadata::ParamInfoSeq::RawType getParameters__call(void* ptr, ::xcom::Environment* __exc_info)
            {
                try {
                return static_cast<Impl*>(static_cast<IDelegateTie<Impl>*>(ptr))->getParameters().detach();
                } catch(xcom::UserExc& ue) { ue.detach(__exc_info); }
                return xcom::metadata::ParamInfoSeq().detach();
                
            }
            
            
            
            IDelegateTie()
            {
                vptr_ = &IDelegateTieVtbl;
            }
        
        private:
            static IDelegateVtbl IDelegateTieVtbl;
        };
        
        template <class Impl>
        IDelegateVtbl IDelegateTie<Impl>::IDelegateTieVtbl =
        {
            &IDelegateTie<Impl>::queryInterface__call,
            &IDelegateTie<Impl>::getInterfaceId__call,
            &IDelegateTie<Impl>::addRef__call,
            &IDelegateTie<Impl>::release__call,
            &IDelegateTie<Impl>::getKind__call,
            &IDelegateTie<Impl>::getName__call,
            &IDelegateTie<Impl>::getParameters__call,
            
        };
        
    }
    
}

#endif
