#pragma once

#include "EventDefs.h"
#include "../Containers/HashMap.h"

namespace Pyro {

    class EventSystem {
    private:
        HashMap<ActionType, HashMap<StringHash, IEvent*>> events;

    public:
        /// Start listening for an event
        template <typename Type> void StartListening(const String& eventName, Action<void, Type> listener) {
            ActionType actionType(Type::GetTypeStatic());
            StringHash eventHash(eventName);

            auto iter = events.Map().find(actionType);
            if (iter != events.Map().end()) {
                auto eventIter = iter->first.Map().find(eventHash);
                if (eventIter != iter->first.Map().end()) {
                    Event<Type>* thisEvent = reinterpret_cast<Event<Type>*>(eventIter->second);
                    thisEvent->AddListener(listener);
                }
                else {
                    Event<Type>* newEvent = new Event<Type>();
                    newEvent->AddListener(listener);
                    eventIter->second.Add(actionType, newEvent);
                }
            }
            else {
                Event<Type>* newEvent = new Event<Type>();
                newEvent->AddListener(listener);

                HashMap<StringHash, IEvent> eventMap;
                eventMap.Add(eventHash, newEvent);

                events.Add(actionType, eventMap);
            }
        }
    };
}