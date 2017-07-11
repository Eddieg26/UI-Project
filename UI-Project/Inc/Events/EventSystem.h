#pragma once

#include "EventDefs.h"
#include "../Core/Object.h"
#include "../Containers/HashMap.h"

namespace Pyro {

    class EventSystem : public Object {
        PYRO_OBJECT(EventSystem, Object)

    private:
        /// Map of events seperated by event type
        HashMap<ActionType, HashMap<StringHash, IEvent*>> events;

    public:
        /// Construct
        EventSystem(Context* context);
        /// Destruct
        ~EventSystem();

        /// Start listening for an event
        template <typename Type> void StartListening(const String& eventName, Action<Type> action) {
            typedef Event<Type> PyroEvent;

            ActionType actionType(Type::GetTypeStatic());
            StringHash eventHash(eventName);

            auto actionIter = events.Map().find(actionType);
            if (actionIter != events.Map().end()) {
                auto eventIter = actionIter->second.Map().find(eventHash);
                if (eventIter != actionIter->second.Map().end()) {
                    PyroEvent* thisEvent = reinterpret_cast<PyroEvent*>(eventIter->second);
                    thisEvent->AddAction(action);
                }
                else {
                    PyroEvent* thisEvent = new PyroEvent;
                    thisEvent->AddAction(action);
                    actionIter->second.Add(eventHash, thisEvent);
                }
            }
            else {
                HashMap<StringHash, IEvent*> eventMap;
                PyroEvent* thisEvent = new PyroEvent;
            }
        }

        template<typename Type> void StopListening(const String& eventName, Action<Type> action) {
            typedef Event<Type> PyroEvent;

            ActionType actionType(Type::GetTypeStatic());
            StringHash eventHash(eventName);

            auto actionIter = events.Map().find(actionType);
            if (actionIter != events.Map().end()) {
                auto eventIter = actionIter->second.Map().find(eventHash);
                if (eventIter != actionIter->second.Map().end()) {
                    PyroEvent* thisEvent = reinterpret_cast<PyroEvent*>(eventIter->second);
                    thisEvent->RemoveAction(action);
                }
            }
        }

        template<typename Type> void SendEvent(const String& eventName, Type& args) {
            typedef Event<Type> PyroEvent;

            ActionType actionType(Type::GetTypeStatic());
            StringHash eventHash(eventName);

            auto actionIter = events.Map().find(actionType);
            if (actionIter != events.Map().end()) {
                auto eventIter = actionIter->second.Map().find(eventHash);
                if (eventIter != actionIter->second.Map().end()) {
                    PyroEvent* thisEvent = reinterpret_cast<PyroEvent*>(eventIter->second);
                    thisEvent->invoke(args);
                }
            }
        }
    };
}