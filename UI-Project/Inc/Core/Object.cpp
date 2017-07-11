#include "Object.h"
#include "Context.h"

namespace Pyro
{
    Object::Object(Context* executionContext) : context(executionContext) {}

    Object::~Object() = default;

    bool Object::IsTypeOf(StringHash type) {
        return GetTypeInfoStatic()->IsTypeOf(type);
    }

    bool Object::IsTypeOf(const TypeInfo* typeInfo) {
        return GetTypeInfoStatic()->IsTypeOf(typeInfo);
    }

    bool Object::IsInstanceOf(StringHash type) const {
        return GetTypeInfo()->IsTypeOf(type);
    }

    bool Object::IsInstanceOf(const TypeInfo* typeInfo) const {
        return GetTypeInfo()->IsTypeOf(typeInfo);
    }

    Object* Object::GetSubSystem(StringHash type) const {
        return context ? context->GetSubSystem(type) : nullptr;
    }
}