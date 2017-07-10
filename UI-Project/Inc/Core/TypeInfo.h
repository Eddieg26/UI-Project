#pragma once

#include "../Containers/Str.h"
#include "../Util/StringHash.h"

namespace Pyro
{
    /// Info used for class type identification
    class TypeInfo {
    private:
        /// Type
        StringHash type;
        /// Type name
        String typeName;
        /// Base type calss info
        const TypeInfo* baseTypeInfo;

    public:
        /// Construct
        TypeInfo(const char* typeName, const TypeInfo* baseTypeInfo);
        /// Destruct
        ~TypeInfo() = default;

        /// Check if current type is type of specified type
        bool IsTypeOf(StringHash type) const;
        /// Check if current type is type of specified type
        bool IsTypeOf(const TypeInfo* typeInfo) const;
        /// Check if current type is type of specified type
        template<typename T> bool IsTypeOf() const { return IsTypeOf(T::GetTypeInfoStatic()); }

        /// Return type
        StringHash GetType() const { return type; }
        /// Return type name
        String GetTypeName() const { return typeName; }

        const TypeInfo* GetBaseTypeInfo() const { return baseTypeInfo; }
    };
}