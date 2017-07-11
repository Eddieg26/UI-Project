#include "EventSystem.h"

namespace Pyro
{
    EventSystem::EventSystem(Context* context) : Object(context) {}

    EventSystem::~EventSystem() {
        for (auto actionIter = events.Map().begin(); actionIter != events.Map().end(); ++actionIter) {
            auto& eventMap = actionIter->second;
            for (auto eventIter = eventMap.Map().begin(); eventIter != eventMap.Map().end(); ++eventIter) {
                delete eventIter->second;
            }
        }
    }

}