#pragma once

#include "Hash.h"

#include <unordered_map>

namespace Pyro
{
    template <typename TKey, typename TValue>
    class HashMap {

    private:
        std::unordered_map<TKey, TValue> map;

    public:
        /// Construct
        HashMap() {}
        /// Copy-construct
        HashMap(const HashMap<TKey, TValue>& rhs) {
            map = rhs.map;
        }
        /// Assignment operator
        HashMap<TKey, TValue>& operator=(const HashMap<TKey, TValue>& rhs) {
            if (this != &rhs)
                map = rhs.map;

            return *this;
        }
        /// Destruct
        ~HashMap() {
            map.clear();
        }

        bool Add(const TKey& key, const TValue& value) {
            auto prevSize = map.size();
            map.emplace(key, value);
            return prevSize != map.size();
        }

        void Remove(const TKey& key) {
            auto it = map.find(key);

            if (it != map.end())
                it = map.erase(it);
        }

        void Clear() {
            map.clear();
        }

        bool Contains(const TKey& key) const {
            return map.find(key) != map.end();
        }

        bool TryGetValue(const TKey& key, TValue& value) {
            auto it = map.find(key);

            if (it != map.end()) {
                value = it->second;
                return true;
            }

            return false;
        }

        TValue& operator[](const TKey& key) {
            return map[key];
        }

        const TValue& operator[](const TKey& key) const {
            return map[key];
        }

        unsigned int Size() const { return (unsigned int)map.size(); }
        bool Empty() const { return map.empty(); }

        const std::unordered_map<TKey, TValue>& Map() const { return map; }

        std::unordered_map<TKey, TValue>& Map() { return map; }
    };
}
