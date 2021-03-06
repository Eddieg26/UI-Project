#pragma once

#include <functional>
#include "../Util/StringHash.h"
#include "../Containers/Str.h"

namespace Pyro
{
    typedef const void* EventID;
    typedef StringHash ActionType;

#define BindEventFunction(Function) { std::bind(Function, this, std::placeholders::_1) }

    template <typename Arg>
    class Action {
        typedef std::function<void(Arg)> FunctionType;

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

        void invoke(Arg arg) {
            function(arg);
        }

        void operator()(Arg arg) {
            function(arg);
        }

        void* InvokingObject() const { return invokingObject; }

        ActionType ID() const { return actionID; }
    };

    class IEvent {
        virtual StringHash EventType() const = 0;
        virtual String EventTypeName() const = 0;
    };

    template <typename Arg>
    class Event : public IEvent {
        typedef Action<Arg> EventAction;

    private:
        /// List of actions
        Vector<EventAction*> actions;

    public:
        /// Construct
        Event() = default;

        /// Destruct
        ~Event() {
            Clear();
        }

        void AddAction(const EventAction* action) {
            if (!Contains(action))
                actions.Add(action);
        }

        void RemoveAction(const EventAction* action) {
            listeners.Remove(action);
        }

        void Clear() {
            actions.Clear();
        }

        bool Contains(const EventAction* action) const {
            return actions.Contains(action);
        }

        void invoke(Arg& arg) {
            for (uint i = 0; i < actions.Size(); ++i) {
                EventAction* action = actions[i];
                action->invoke(arg);
            }
        }

        void operator()(Arg arg) {
            for (uint i = 0; i < actions.Size(); ++i) {
                EventAction* action = actions[i];
                action->invoke(arg);
            }
        }

        virtual StringHash EventType() const override { return EventTypeStatic(); }
        virtual String EventTypeName() const override { return EventTypeNameStatic(); }

        static StringHash EventTypeStatic() { return Arg::GetTypeNameStatic(); }
        static String EventTypeNameStatic() { return Arg::GetTypeStatic(); }

    private:
        /// Prevent copy construction
        Event(const Event&) = delete;
        /// Prevent assignment
        Event& operator=(const Event&) = delete;
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