#pragma once

#include "TypeInfo.h"
#include "RefCounted.h"
#include "../Containers/Ptr.h"

namespace Pyro
{

#define PYRO_OBJECT(typeName, baseTypeName) \
	public: \
		typedef typeName ClassName; \
		typedef baseTypeName BaseClassName; \
		virtual StringHash GetType() const { return GetTypeInfoStatic()->GetType(); } \
		virtual const String& GetTypeName() const { return GetTypeInfoStatic()->GetTypeName(); } \
		virtual const TypeInfo* GetTypeInfo() const { return GetTypeInfoStatic(); } \
		static StringHash GetTypeStatic() {return GetTypeInfoStatic()->GetType(); } \
		static const String& GetTypeNameStatic() { return GetTypeInfoStatic()->GetTypeName(); } \
		static const TypeInfo* GetTypeInfoStatic() { static const TypeInfo typeInfoStatic(#typeName, BaseClassName::GetTypeInfoStatic()); return &typeInfoStatic; } \
		virtual StringHash GetBaseType() const { return GetBaseTypeStatic(); }  \
		virtual ClassID GetClassID() const { return GetClassIDStatic(); } \
		static ClassID GetClassIDStatic() { static const int typeID = 0; return (ClassID)&typeID; } \
		static StringHash GetBaseTypeStatic() { static const StringHash baseTypeStatic(#baseTypeName); return baseTypeStatic; }

    class Context;

    class Object : public RefCounted{
        friend class Context;

    protected:
        /// Execution context
        Context* context;
    public:
        /// Construct
        Object(Context* executionContext);
        /// Destruct
        virtual ~Object();

        /// Return type hash.
        virtual StringHash GetType() const = 0;
        /// Return type name.
        virtual const String& GetTypeName() const = 0;
        /// Return type info.
        virtual const TypeInfo* GetTypeInfo() const = 0;
        /// Return type info static.
        static const TypeInfo* GetTypeInfoStatic() { return 0; }
        /// Check current type is type of specified type.
        static bool IsTypeOf(StringHash type);
        /// Check current type is type of specified type.
        static bool IsTypeOf(const TypeInfo* typeInfo);
        /// Check current type is type of specified class.
        template<typename T> static bool IsTypeOf() { return IsTypeOf(T::GetTypeInfoStatic()); }
        /// Check current instance is type of specified type.
        bool IsInstanceOf(StringHash type) const;
        /// Check current instance is type of specified type.
        bool IsInstanceOf(const TypeInfo* typeInfo) const;
        /// Check current instance is type of specified class.
        template<typename T> bool IsInstanceOf() const { return IsInstanceOf(T::GetTypeInfoStatic()); }

        /// Return subsystem by type
        Object* GetSubSystem(StringHash type) const;
        /// Template version of returning a subsystem
        template <typename T> T* GetSubSystem() const;

        virtual bool IsObject() const override { return true; }

        /// Return execution context
        Context* GetContext() const { return context; }

        static ClassID GetClassIDStatic() { static const int typeID = 0; return (ClassID)&typeID; }
        static const String& GetTypeNameStatic() { static const String typeNameStatic("Object"); return typeNameStatic; }
    };

    template <typename T> T* Object::GetSubSystem() const {
        StringHash type = T::GetTypeStatic();
        return (T*)GetSubSystem(type);
    }

    /// Object Factory class
    class ObjectFactory : public RefCounted {

        REFCOUNTED(ObjectFactory)

    protected:
        /// Execution context
        Context* context;
        /// Type info
        const TypeInfo* typeInfo;

    public:
        /// Construct
        ObjectFactory(Context* _context) : context(_context) {}

        /// Return execution context
        Context* GetContext() const { return context; }

        /// Return type info
        const TypeInfo* GetTypeInfo() const { return typeInfo; }

        /// Return type hash of objects created by this factory.
        StringHash GetType() const { return typeInfo->GetType(); }

        /// Return type name of objects created by this factory.
        const String& GetTypeName() const { return typeInfo->GetTypeName(); }

        /// Create an object. Implemented in templated subclasses.
        virtual SharedPtr<Object> CreateObject() = 0;
    };

    /// Template implementation of the object factory.
    template<typename T> class ObjectFactoryImpl : public ObjectFactory {

    public:
        /// Construct
        ObjectFactoryImpl(Context* _context) : ObjectFactory(_context) {
            typeInfo = T::GetTypeInfoStatic();
        }

        /// Create an object of the specific type
        virtual SharedPtr<Object> CreateObject() { return SharedPtr<Object>(new T(context)); }
    };
}