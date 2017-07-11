#include "Context.h"

namespace Pyro
{
    Context::Context() = default;

    Context::~Context() {
        objectFactories.Clear();
        subSystems.Clear();
    }

    SharedPtr<Object> Context::CreateObject(StringHash type) {
        auto i = objectFactories.Map().find(type);
        if (i != objectFactories.Map().end())
            return i->second->CreateObject();

        return SharedPtr<Object>(nullptr);
    }

    void Context::RegisterFactory(ObjectFactory* factory) {
        if (!factory) return;

        objectFactories[factory->GetType()] = factory;
    }

    void Context::RegisterSubSystem(Object* subSystem) {
        if (!subSystem) return;

        subSystems[subSystem->GetType()] = subSystem;
    }

    void Context::RemoveSubSystem(StringHash objectType) {
        subSystems.Remove(objectType);
    }

    Object* Context::GetSubSystem(StringHash type) const {
        auto i = subSystems.Map().find(type);
        if (i != subSystems.Map().end())
            return i->second.Get();

        return nullptr;
    }
}