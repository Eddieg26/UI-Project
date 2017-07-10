#pragma once

#include <functional>
#include "../Util/StringHash.h"
#include "../Containers/Str.h"

namespace Pyro
{
    typedef const void* EventID;
    typedef StringHash ActionType;

#define BindEventFunction(Function) { std::bind(Function, this, std::placeholders::_1) }

    template <typename Return, typename Arg>
    class Action {
        typedef std::function<Return(Arg)> FunctionType;

    private:
        /// Action
        ActionType actionID;
        /// Invoking object
        void* invokingObject;
        /// Function to invoke
        FunctionType function;

    public:
        Action() {
            invokingObject = nullptr;
        }

        Action(const Action& rhs) :
            actionID(rhs.actionID),
            invokingObject(rhs.invokingObject),
            function(rhs.function) {}

        Action(ActionType id, void* object, FunctionType func) :
            actionID(id),
            invokingObject(object),
            function(func) {}

        Action& operator=(const Action& rhs) {
            actionID = rhs.callbackID;
            invokingObject = rhs.invokingObject;
            function = rhs.function;
        }

        bool operator==(const Action& rhs) {
            return invokingObject == rhs.invokingObject && actionID == rhs.actionID;
        }

        bool operator!=(const Action& rhs) {
            return !(*this == rhs);
        }

        Return invoke(Arg arg) {
            return function(arg);
        }

        Return operator()(Arg arg) {
            return function(arg);
        }

        void* InvokingObject() const { return invokingObject; }

        ActionType ID() const { return actionID; }
    };

    class IEvent {

    };

    template <typename Arg>
    class Event : public IEvent {
        typedef Action<void, Arg> Listener;

    private:
        Vector<Listener*> listeners;

    public:
        Event() = default;

        ~Event() {
            for (uint i = 0; uint < listeners.Size(); ++i) {
                delete listeners[i];
            }

            listeners.Clear();
        }

        void AddListener(const Listener* listener) {
            if (!Contains(listener))
                listeners.Add(listener);
        }

        void RemoveListener(const Listener* listener) {
            listeners.Remove(listener);
        }

        bool Contains(const Listener* listener) const {
            return listeners.Contains(listener);
        }

        String EventType() const { return Arg::GetTypeStatic(); }

        static String EventTypeStatic() const { return Arg::GetTypeStatic(); }
    };

#define EventData(typeName) \
    public: \
    typedef typeName ClassName; \
    StringHash GetType() const { return GetTypeStatic(); } \
    const String& GetTypeName() const { return GetTypeNameStatic(); } \
    EventID GetEventID() const { return GetEventIDStatic(); } \
    static EventID GetEventIDStatic() { static const int eventID = 0; return (EventID)&eventID; } \
    static StringHash GetTypeStatic() { return StringHash type(#typeName); } \
    static const String& GetTypeNameStatic() { return String(#typeName); } 
}