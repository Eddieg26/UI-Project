#include "TypeInfo.h"

namespace Pyro
{
    TypeInfo::TypeInfo(const char* _typeName, const TypeInfo* _baseTypeInfo) {
        this->typeName = _typeName;
        this->baseTypeInfo = _baseTypeInfo;
        this->type = StringHash(_typeName);
    }

    bool TypeInfo::IsTypeOf(StringHash type) const {
        const TypeInfo* current = this;
        while (current) {
            if (current->GetType() == type)
                return true;

            current = current->GetBaseTypeInfo();
        }

        return false;
    }

    bool TypeInfo::IsTypeOf(const TypeInfo* typeInfo) const {
        const TypeInfo* current = this;
        while (current) {
            if (current == typeInfo)
                return true;

            current = current->GetBaseTypeInfo();
        }

        return false;
    }
}