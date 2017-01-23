#ifndef INC_MDTYPES_HPP_B09BC14E_61A1_4107_AFAA_F72731714243
#define INC_MDTYPES_HPP_B09BC14E_61A1_4107_AFAA_F72731714243

#include <xcom/Types.hpp>

#include <xcom/IUnknown.hpp>
namespace xcom
{
    namespace metadata
    {
        namespace TypeKind
        {
            enum type
            {
                Void,
                Bool,
                Octet,
                Short,
                Int,
                Long,
                Float,
                Double,
                Char,
                WChar,
                String,
                WString,
                Enum,
                Array,
                Sequence,
                Struct,
                Interface,
                Exception,
                Delegate,
                Any,
                
            };
        }
        typedef TypeKind::type TypeKindEnum;
        
        struct ITypeRaw : public xcom::IUnknownRaw
        {
        };
        struct ITypeVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class ITypeTie;
        class IType : public xcom::IUnknown
        {
        public:
            typedef ITypeRaw* RawType;
            typedef xcom::IUnknown ParentClass;
            template<typename T>
            struct Tie { typedef ITypeTie<T> type; };
            IType() {}
            IType(ITypeRaw* ptr) : xcom::IUnknown((xcom::IUnknownRaw*)ptr) {}
            xcom::Int getKind() const;
            
            static IType adopt(ITypeRaw* src)
            {
                return IType(src);
            }
            
            ITypeRaw* detach()
            {
                ITypeRaw* result = (ITypeRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    -785461477, 1632, 20067,
                    {0x8a, 0x74, 0xdb, 0x25, 0xbb, 0x91, 0xa6, 0xe4}
                };
                
                return id;
            }
            
        };
        
        struct IDeclaredRaw : public xcom::metadata::ITypeRaw
        {
        };
        struct IDeclaredVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class IDeclaredTie;
        class IDeclared : public xcom::metadata::IType
        {
        public:
            typedef IDeclaredRaw* RawType;
            typedef xcom::metadata::IType ParentClass;
            template<typename T>
            struct Tie { typedef IDeclaredTie<T> type; };
            IDeclared() {}
            IDeclared(IDeclaredRaw* ptr) : xcom::metadata::IType((xcom::metadata::ITypeRaw*)ptr) {}
            xcom::String getName() const;
            
            static IDeclared adopt(IDeclaredRaw* src)
            {
                return IDeclared(src);
            }
            
            IDeclaredRaw* detach()
            {
                IDeclaredRaw* result = (IDeclaredRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    -191025327, 30572, 17884,
                    {0x8d, 0xde, 0x0e, 0x00, 0x70, 0x4d, 0xd9, 0x3a}
                };
                
                return id;
            }
            
        };
        
        struct ISequenceRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct ISequenceVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::metadata::ITypeRaw* (*getElementType)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class ISequenceTie;
        class ISequence : public xcom::metadata::IDeclared
        {
        public:
            typedef ISequenceRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef ISequenceTie<T> type; };
            ISequence() {}
            ISequence(ISequenceRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::metadata::IType getElementType() const;
            
            static ISequence adopt(ISequenceRaw* src)
            {
                return ISequence(src);
            }
            
            ISequenceRaw* detach()
            {
                ISequenceRaw* result = (ISequenceRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    -1171420259, -28912, 17930,
                    {0xb5, 0x36, 0xea, 0xd7, 0xf8, 0x5e, 0x8f, 0x8c}
                };
                
                return id;
            }
            
        };
        
        struct IArrayRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct IArrayVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::metadata::ITypeRaw* (*getElementType)(void*, xcom::Environment*);
            xcom::Int (*getSize)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class IArrayTie;
        class IArray : public xcom::metadata::IDeclared
        {
        public:
            typedef IArrayRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef IArrayTie<T> type; };
            IArray() {}
            IArray(IArrayRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::metadata::IType getElementType() const;
            xcom::Int getSize() const;
            
            static IArray adopt(IArrayRaw* src)
            {
                return IArray(src);
            }
            
            IArrayRaw* detach()
            {
                IArrayRaw* result = (IArrayRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    -547090619, -9952, 18083,
                    {0xa0, 0x18, 0xdc, 0xe3, 0x21, 0xb5, 0x02, 0x06}
                };
                
                return id;
            }
            
        };
        
        struct IEnumRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct IEnumVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::Int (*getElementCount)(void*, xcom::Environment*);
            xcom::Char* (*getElement)(void*, xcom::Environment*, xcom::Int idx);
            
        };
        template<typename Impl> class IEnumTie;
        class IEnum : public xcom::metadata::IDeclared
        {
        public:
            typedef IEnumRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef IEnumTie<T> type; };
            IEnum() {}
            IEnum(IEnumRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::Int getElementCount() const;
            xcom::String getElement(xcom::Int idx) const;
            
            static IEnum adopt(IEnumRaw* src)
            {
                return IEnum(src);
            }
            
            IEnumRaw* detach()
            {
                IEnumRaw* result = (IEnumRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    1577563742, -7891, 19102,
                    {0xaf, 0x6a, 0x14, 0x7d, 0xa2, 0x19, 0x88, 0xbe}
                };
                
                return id;
            }
            
        };
        
        struct IStructRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct IStructVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::Int (*getMemberCount)(void*, xcom::Environment*);
            xcom::metadata::ITypeRaw* (*getMemberType)(void*, xcom::Environment*, xcom::Int idx);
            xcom::Char* (*getMemberName)(void*, xcom::Environment*, xcom::Int idx);
            xcom::Int (*getMemberOffset)(void*, xcom::Environment*, xcom::Int idx);
            xcom::Int (*getSize)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class IStructTie;
        class IStruct : public xcom::metadata::IDeclared
        {
        public:
            typedef IStructRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef IStructTie<T> type; };
            IStruct() {}
            IStruct(IStructRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::Int getMemberCount() const;
            xcom::metadata::IType getMemberType(xcom::Int idx) const;
            xcom::String getMemberName(xcom::Int idx) const;
            xcom::Int getMemberOffset(xcom::Int idx) const;
            xcom::Int getSize() const;
            
            static IStruct adopt(IStructRaw* src)
            {
                return IStruct(src);
            }
            
            IStructRaw* detach()
            {
                IStructRaw* result = (IStructRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    1816857442, -16383, 19256,
                    {0xbc, 0xc1, 0x17, 0x0c, 0xea, 0x25, 0x1b, 0x1f}
                };
                
                return id;
            }
            
        };
        
        struct IExceptionRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct IExceptionVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::metadata::IExceptionRaw* (*getBase)(void*, xcom::Environment*);
            xcom::Int (*getMemberCount)(void*, xcom::Environment*);
            xcom::metadata::ITypeRaw* (*getMemberType)(void*, xcom::Environment*, xcom::Int idx);
            xcom::Char* (*getMemberName)(void*, xcom::Environment*, xcom::Int idx);
            xcom::Int (*getMemberOffset)(void*, xcom::Environment*, xcom::Int idx);
            xcom::Int (*getSize)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class IExceptionTie;
        class IException : public xcom::metadata::IDeclared
        {
        public:
            typedef IExceptionRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef IExceptionTie<T> type; };
            IException() {}
            IException(IExceptionRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::metadata::IException getBase() const;
            xcom::Int getMemberCount() const;
            xcom::metadata::IType getMemberType(xcom::Int idx) const;
            xcom::String getMemberName(xcom::Int idx) const;
            xcom::Int getMemberOffset(xcom::Int idx) const;
            xcom::Int getSize() const;
            
            static IException adopt(IExceptionRaw* src)
            {
                return IException(src);
            }
            
            IExceptionRaw* detach()
            {
                IExceptionRaw* result = (IExceptionRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    583173305, -19520, 20242,
                    {0x9a, 0xa3, 0x89, 0xba, 0xb1, 0x80, 0xe2, 0xb3}
                };
                
                return id;
            }
            
        };
        
        namespace PassMode
        {
            enum type
            {
                In,
                Out,
                InOut,
                Return,
                
            };
        }
        typedef PassMode::type PassModeEnum;
        
        
        struct ParamInfoData
        {
            xcom::Int mode;
            xcom::metadata::ITypeRaw* type;
            xcom::Char* name;
            
        };
        
        struct ParamInfo
        {
            xcom::Int mode;
            xcom::metadata::IType type;
            xcom::String name;
            
            typedef ParamInfoData RawType;
            RawType detach()
            {
                RawType result;
                
                result.mode = mode;
                result.type = type.detach();
                result.name = name.detach();
                
                
                return result;
            };
            
            static ParamInfo adopt(RawType const& raw)
            {
                ParamInfo result;
                ::memcpy(&result, &raw, sizeof(RawType));
                return result;
            }
            
        };
        
        class ParamInfoSeq : public xcom::SequenceBase<xcom::metadata::ParamInfo, xcom::metadata::ParamInfoData>
        {
        public:
            static ParamInfoSeq adopt(RawType const& src)
            {
                ParamInfoSeq result;
                ::memcpy(&result, &src, sizeof(RawType));
                return result;
            }
            
            ParamInfoSeq() {}
            explicit ParamInfoSeq(xcom::Int size)
            : xcom::SequenceBase<xcom::metadata::ParamInfo, xcom::metadata::ParamInfoData>(size)
            {
            }
        };
        
        struct IInterfaceRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct IInterfaceVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::GUID (*getId)(void*, xcom::Environment*);
            xcom::metadata::IInterfaceRaw* (*getBase)(void*, xcom::Environment*);
            xcom::Int (*getMethodCount)(void*, xcom::Environment*);
            xcom::Char* (*getMethodName)(void*, xcom::Environment*, xcom::Int idx);
            xcom::metadata::ParamInfoSeq::RawType (*getParameters)(void*, xcom::Environment*, xcom::Int idx);
            void (*destroy)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class IInterfaceTie;
        class IInterface : public xcom::metadata::IDeclared
        {
        public:
            typedef IInterfaceRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef IInterfaceTie<T> type; };
            IInterface() {}
            IInterface(IInterfaceRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::GUID getId() const;
            xcom::metadata::IInterface getBase() const;
            xcom::Int getMethodCount() const;
            xcom::String getMethodName(xcom::Int idx) const;
            xcom::metadata::ParamInfoSeq getParameters(xcom::Int idx) const;
            void destroy() const;
            
            static IInterface adopt(IInterfaceRaw* src)
            {
                return IInterface(src);
            }
            
            IInterfaceRaw* detach()
            {
                IInterfaceRaw* result = (IInterfaceRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    -121253088, 24083, 18935,
                    {0xb3, 0x45, 0xaf, 0x64, 0x12, 0x95, 0xc8, 0x15}
                };
                
                return id;
            }
            
        };
        
        struct IDelegateRaw : public xcom::metadata::IDeclaredRaw
        {
        };
        struct IDelegateVtbl
        {
            xcom::IUnknownRaw* (*queryInterface)(void*, xcom::Environment*, xcom::GUID const* iid);
            xcom::GUID (*getInterfaceId)(void*, xcom::Environment*);
            xcom::Int (*addRef)(void*, xcom::Environment*);
            xcom::Int (*release)(void*, xcom::Environment*);
            xcom::Int (*getKind)(void*, xcom::Environment*);
            xcom::Char* (*getName)(void*, xcom::Environment*);
            xcom::metadata::ParamInfoSeq::RawType (*getParameters)(void*, xcom::Environment*);
            
        };
        template<typename Impl> class IDelegateTie;
        class IDelegate : public xcom::metadata::IDeclared
        {
        public:
            typedef IDelegateRaw* RawType;
            typedef xcom::metadata::IDeclared ParentClass;
            template<typename T>
            struct Tie { typedef IDelegateTie<T> type; };
            IDelegate() {}
            IDelegate(IDelegateRaw* ptr) : xcom::metadata::IDeclared((xcom::metadata::IDeclaredRaw*)ptr) {}
            xcom::metadata::ParamInfoSeq getParameters() const;
            
            static IDelegate adopt(IDelegateRaw* src)
            {
                return IDelegate(src);
            }
            
            IDelegateRaw* detach()
            {
                IDelegateRaw* result = (IDelegateRaw*)ptr_;
                ptr_ = 0;
                return result;
            }
            
            static inline xcom::GUID const& thisInterfaceId()
            {
                static const xcom::GUID id =
                {
                    -1479626736, 15748, 20295,
                    {0x89, 0xcc, 0xd0, 0x8b, 0x9d, 0x27, 0xf8, 0x82}
                };
                
                return id;
            }
            
        };
        
    }
}
namespace xcom
{
    namespace metadata
    {
        inline xcom::Int IType::getKind() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<ITypeVtbl*>(static_cast<ITypeRaw*>(ptr_)->vptr_)->getKind(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::String IDeclared::getName() const
        {
            xcom::Environment __exc_info;
            xcom::String result(xcom::String::adopt(static_cast<IDeclaredVtbl*>(static_cast<IDeclaredRaw*>(ptr_)->vptr_)->getName(ptr_, &__exc_info)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::metadata::IType ISequence::getElementType() const
        {
            xcom::Environment __exc_info;
            xcom::metadata::IType result(xcom::metadata::IType::adopt(static_cast<ISequenceVtbl*>(static_cast<ISequenceRaw*>(ptr_)->vptr_)->getElementType(ptr_, &__exc_info)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::metadata::IType IArray::getElementType() const
        {
            xcom::Environment __exc_info;
            xcom::metadata::IType result(xcom::metadata::IType::adopt(static_cast<IArrayVtbl*>(static_cast<IArrayRaw*>(ptr_)->vptr_)->getElementType(ptr_, &__exc_info)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IArray::getSize() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IArrayVtbl*>(static_cast<IArrayRaw*>(ptr_)->vptr_)->getSize(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::Int IEnum::getElementCount() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IEnumVtbl*>(static_cast<IEnumRaw*>(ptr_)->vptr_)->getElementCount(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::String IEnum::getElement(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::String result(xcom::String::adopt(static_cast<IEnumVtbl*>(static_cast<IEnumRaw*>(ptr_)->vptr_)->getElement(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::Int IStruct::getMemberCount() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IStructVtbl*>(static_cast<IStructRaw*>(ptr_)->vptr_)->getMemberCount(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::metadata::IType IStruct::getMemberType(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::metadata::IType result(xcom::metadata::IType::adopt(static_cast<IStructVtbl*>(static_cast<IStructRaw*>(ptr_)->vptr_)->getMemberType(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::String IStruct::getMemberName(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::String result(xcom::String::adopt(static_cast<IStructVtbl*>(static_cast<IStructRaw*>(ptr_)->vptr_)->getMemberName(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IStruct::getMemberOffset(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IStructVtbl*>(static_cast<IStructRaw*>(ptr_)->vptr_)->getMemberOffset(ptr_, &__exc_info, idx));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IStruct::getSize() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IStructVtbl*>(static_cast<IStructRaw*>(ptr_)->vptr_)->getSize(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::metadata::IException IException::getBase() const
        {
            xcom::Environment __exc_info;
            xcom::metadata::IException result(xcom::metadata::IException::adopt(static_cast<IExceptionVtbl*>(static_cast<IExceptionRaw*>(ptr_)->vptr_)->getBase(ptr_, &__exc_info)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IException::getMemberCount() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IExceptionVtbl*>(static_cast<IExceptionRaw*>(ptr_)->vptr_)->getMemberCount(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::metadata::IType IException::getMemberType(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::metadata::IType result(xcom::metadata::IType::adopt(static_cast<IExceptionVtbl*>(static_cast<IExceptionRaw*>(ptr_)->vptr_)->getMemberType(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::String IException::getMemberName(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::String result(xcom::String::adopt(static_cast<IExceptionVtbl*>(static_cast<IExceptionRaw*>(ptr_)->vptr_)->getMemberName(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IException::getMemberOffset(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IExceptionVtbl*>(static_cast<IExceptionRaw*>(ptr_)->vptr_)->getMemberOffset(ptr_, &__exc_info, idx));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IException::getSize() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IExceptionVtbl*>(static_cast<IExceptionRaw*>(ptr_)->vptr_)->getSize(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
        inline xcom::GUID IInterface::getId() const
        {
            xcom::Environment __exc_info;
            xcom::GUID result(static_cast<IInterfaceVtbl*>(static_cast<IInterfaceRaw*>(ptr_)->vptr_)->getId(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::metadata::IInterface IInterface::getBase() const
        {
            xcom::Environment __exc_info;
            xcom::metadata::IInterface result(xcom::metadata::IInterface::adopt(static_cast<IInterfaceVtbl*>(static_cast<IInterfaceRaw*>(ptr_)->vptr_)->getBase(ptr_, &__exc_info)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::Int IInterface::getMethodCount() const
        {
            xcom::Environment __exc_info;
            xcom::Int result(static_cast<IInterfaceVtbl*>(static_cast<IInterfaceRaw*>(ptr_)->vptr_)->getMethodCount(ptr_, &__exc_info));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::String IInterface::getMethodName(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::String result(xcom::String::adopt(static_cast<IInterfaceVtbl*>(static_cast<IInterfaceRaw*>(ptr_)->vptr_)->getMethodName(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline xcom::metadata::ParamInfoSeq IInterface::getParameters(xcom::Int idx) const
        {
            xcom::Environment __exc_info;
            xcom::metadata::ParamInfoSeq result(xcom::metadata::ParamInfoSeq::adopt(static_cast<IInterfaceVtbl*>(static_cast<IInterfaceRaw*>(ptr_)->vptr_)->getParameters(ptr_, &__exc_info, idx)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        inline void IInterface::destroy() const
        {
            xcom::Environment __exc_info;
            static_cast<IInterfaceVtbl*>(static_cast<IInterfaceRaw*>(ptr_)->vptr_)->destroy(ptr_, &__exc_info);
        if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
        
        }
        
        inline xcom::metadata::ParamInfoSeq IDelegate::getParameters() const
        {
            xcom::Environment __exc_info;
            xcom::metadata::ParamInfoSeq result(xcom::metadata::ParamInfoSeq::adopt(static_cast<IDelegateVtbl*>(static_cast<IDelegateRaw*>(ptr_)->vptr_)->getParameters(ptr_, &__exc_info)));
            if(__exc_info.exception) xcomFindAndThrow(&__exc_info);
            
            return result;
        }
        
    }
}
#include <xcom/MDHelper.hpp>
namespace xcom
{

    template<> struct TypeDesc<xcom::metadata::IType>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IDeclared>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::ISequence>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IArray>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IEnum>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IStruct>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IException>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IInterface>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template<> struct TypeDesc<xcom::metadata::IDelegate>
    {
        static void addSelf(IUnknownSeq& types);
    };
    
    template <>
    struct TypeDesc<xcom::metadata::TypeKindEnum>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.metadata.TypeKind"))
            {
                Char const* elements[20] = { "Void", "Bool", "Octet", "Short", "Int", "Long", "Float", "Double", "Char", "WChar", "String", "WString", "Enum", "Array", "Sequence", "Struct", "Interface", "Exception", "Delegate", "Any",  };
                addType(types, xcomCreateEnumMD("xcom.metadata.TypeKind", elements, 20));
            }
        }
    };
    inline void TypeDesc<xcom::metadata::IType>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IType"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.IUnknown", &TypeDesc<xcom::IUnknown>::addSelf));
            Char const* pnames[1];
            IUnknownRaw* ptypes[1];
            Int pmodes[1];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IType", &xcom::metadata::IType::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getKind", rawFindOrReg(types, "xcom.metadata.TypeKind", &TypeDesc<xcom::metadata::TypeKindEnum>::addSelf), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::IDeclared>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IDeclared"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IType", &TypeDesc<xcom::metadata::IType>::addSelf));
            Char const* pnames[1];
            IUnknownRaw* ptypes[1];
            Int pmodes[1];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IDeclared", &xcom::metadata::IDeclared::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getName", rawFindMetadata(types, "string"), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::ISequence>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.ISequence"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[1];
            IUnknownRaw* ptypes[1];
            Int pmodes[1];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.ISequence", &xcom::metadata::ISequence::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getElementType", rawFindOrReg(types, "xcom.metadata.IType", &TypeDesc<xcom::metadata::IType>::addSelf), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::IArray>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IArray"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[1];
            IUnknownRaw* ptypes[1];
            Int pmodes[1];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IArray", &xcom::metadata::IArray::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getElementType", rawFindOrReg(types, "xcom.metadata.IType", &TypeDesc<xcom::metadata::IType>::addSelf), 0, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getSize", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::IEnum>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IEnum"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[2];
            IUnknownRaw* ptypes[2];
            Int pmodes[2];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IEnum", &xcom::metadata::IEnum::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getElementCount", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getElement", rawFindMetadata(types, "string"), 1, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::IStruct>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IStruct"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[2];
            IUnknownRaw* ptypes[2];
            Int pmodes[2];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IStruct", &xcom::metadata::IStruct::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getMemberCount", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMemberType", rawFindOrReg(types, "xcom.metadata.IType", &TypeDesc<xcom::metadata::IType>::addSelf), 1, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMemberName", rawFindMetadata(types, "string"), 1, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMemberOffset", rawFindMetadata(types, "int"), 1, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getSize", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::IException>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IException"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[2];
            IUnknownRaw* ptypes[2];
            Int pmodes[2];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IException", &xcom::metadata::IException::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getBase", rawFindOrReg(types, "xcom.metadata.IException", &TypeDesc<xcom::metadata::IException>::addSelf), 0, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getMemberCount", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMemberType", rawFindOrReg(types, "xcom.metadata.IType", &TypeDesc<xcom::metadata::IType>::addSelf), 1, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMemberName", rawFindMetadata(types, "string"), 1, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMemberOffset", rawFindMetadata(types, "int"), 1, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getSize", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    template <>
    struct TypeDesc<xcom::metadata::PassModeEnum>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.metadata.PassMode"))
            {
                Char const* elements[4] = { "In", "Out", "InOut", "Return",  };
                addType(types, xcomCreateEnumMD("xcom.metadata.PassMode", elements, 4));
            }
        }
    };
    template <>
    struct TypeDesc<xcom::metadata::ParamInfo>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.metadata.ParamInfo"))
            {
                IUnknownRaw* mtypes[3] =
                {
                    rawFindOrReg(types, "xcom.metadata.PassMode", &TypeDesc<xcom::metadata::PassModeEnum>::addSelf),
                    rawFindOrReg(types, "xcom.metadata.IType", &TypeDesc<xcom::metadata::IType>::addSelf),
                    rawFindMetadata(types, "string"),
                    
                };
                
                const Char* mnames[3] =
                {
                    "mode",
                    "type",
                    "name",
                    
                };
                
                Int moffsets[3] =
                {
                    offsetof(xcom::metadata::ParamInfoData, mode),
                    offsetof(xcom::metadata::ParamInfoData, type),
                    offsetof(xcom::metadata::ParamInfoData, name),
                    
                };
                
                addType(types, xcomCreateStructMD("xcom.metadata.ParamInfo", sizeof(xcom::metadata::ParamInfoData), 3, mtypes, mnames, moffsets));
            }
        }
    };
    
    template <>
    struct TypeDesc<xcom::metadata::ParamInfoSeq>
    {
        static void addSelf(IUnknownSeq& types)
        {
            if(!typeExists(types, "xcom.metadata.ParamInfoSeq"))
            {
                addType(types, xcomCreateSequenceMD("xcom.metadata.ParamInfoSeq", rawFindOrReg(types, "xcom.metadata.ParamInfo", &TypeDesc<xcom::metadata::ParamInfo>::addSelf)));
            }
        }
    };
    
    inline void TypeDesc<xcom::metadata::IInterface>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IInterface"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[2];
            IUnknownRaw* ptypes[2];
            Int pmodes[2];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IInterface", &xcom::metadata::IInterface::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getId", rawFindOrReg(types, "xcom.GUID", &TypeDesc<xcom::GUID>::addSelf), 0, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getBase", rawFindOrReg(types, "xcom.metadata.IInterface", &TypeDesc<xcom::metadata::IInterface>::addSelf), 0, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "getMethodCount", rawFindMetadata(types, "int"), 0, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getMethodName", rawFindMetadata(types, "string"), 1, pmodes, ptypes, pnames);
            pnames[0] = "idx";
            
            ptypes[0] = rawFindMetadata(types, "int");
            
            pmodes[0] = 0;
            
            xcomAddMethodToItf(cookie, "getParameters", rawFindOrReg(types, "xcom.metadata.ParamInfoSeq", &TypeDesc<xcom::metadata::ParamInfoSeq>::addSelf), 1, pmodes, ptypes, pnames);
            
            
            
            xcomAddMethodToItf(cookie, "destroy", rawFindMetadata(types, "void"), 0, pmodes, ptypes, pnames);
            
        }
    }
    
    inline void TypeDesc<xcom::metadata::IDelegate>::addSelf(IUnknownSeq& types)
    {
        if(!typeExists(types, "xcom.metadata.IDelegate"))
        {
            void* cookie;
            IUnknown base(findOrRegister(types, "xcom.metadata.IDeclared", &TypeDesc<xcom::metadata::IDeclared>::addSelf));
            Char const* pnames[1];
            IUnknownRaw* ptypes[1];
            Int pmodes[1];
            types.push_back(xcomCreateInterfaceMD("xcom.metadata.IDelegate", &xcom::metadata::IDelegate::thisInterfaceId(), base.detach(), &cookie));
            
            
            
            
            xcomAddMethodToItf(cookie, "getParameters", rawFindOrReg(types, "xcom.metadata.ParamInfoSeq", &TypeDesc<xcom::metadata::ParamInfoSeq>::addSelf), 0, pmodes, ptypes, pnames);
            
        }
    }
    
} // namespace xcom

#include <xcom/ExcHelper.hpp>

namespace xcom
{

    namespace metadata
    {
    
    }
    
}

#endif
