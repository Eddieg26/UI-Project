#pragma once

#include "Object.h"
#include "../Containers/HashMap.h"

namespace Pyro
{
    class Context : public RefCounted {
        REFCOUNTED(Context);

        typedef HashMap<StringHash, SharedPtr<ObjectFactory>> ObjectFactoryMap;
        typedef HashMap<StringHash, SharedPtr<Object>> SubSystemMap;

    private:
        /// Object factories
        ObjectFactoryMap objectFactories;
        /// Subsystems
        SubSystemMap subSystems;

    public:
        /// Construct
        Context();
        /// Destruct
        virtual ~Context();

        /// Create an object by type. Return pointer to it or null if no factory found.
        SharedPtr<Object> CreateObject(StringHash type);
        /// Register a factory for an object type
        void RegisterFactory(ObjectFactory* factory);
        /// Register a subsystem
        void RegisterSubSystem(Object* subSystem);
        /// Remove a subsystem
        void RemoveSubSystem(StringHash objectType);
        /// Return subsystem by type
        Object* GetSubSystem(StringHash type) const;

        /// Create an object by type. Return pointer to it or null if no factory found.
        template <typename T> SharedPtr<T> CreateObject();
        /// Template version of registering an object factory
        template <typename T> void RegisterFactory();
        /// Template version of removing a subsystem
        template <typename T> void RemoveSubSystem();
        /// Template version of returning a subsystem
        template <typename T> T* GetSubSystem() const;

        /// Return object factories
        const ObjectFactoryMap& GetFactories() const { return objectFactories; }
        /// Return subsystems
        const SubSystemMap& GetSubSystems() const { return subSystems; }
    };


    template <typename T> SharedPtr<T> Context::CreateObject() {
        return StaticCast<T>(CreateObject(T::GetTypeStatic()));
    }

    template <typename T>
    void Context::RegisterFactory() {
        RegisterFactory(new ObjectFactoryImpl<T>(this));
    }

    template <typename T>
    void Context::RemoveSubSystem() {
        StringHash hash = T::GetTypeStatic();
        subSystems.Remove(hash);
    }

    template <typename T>
    T* Context::GetSubSystem() const {
        return static_cast<T*>(GetSubSystem(T::GetTypeStatic()));
    }
}