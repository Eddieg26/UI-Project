#pragma once

#include <unordered_set>

namespace Pyro
{

    template <typename Type>
    class HashSet {

    private:
        std::unordered_set<Type> set;

    public:
        /// Construct
        HashSet() {}

        /// Copy-construct
        HashSet(const HashSet<Type>& rhs) {
            set = rhs.set;
        }

        /// Assignement-operator
        HashSet<Type>& operator=(const HashSet<Type>& rhs) {
            if (this != &rhs) {
                set = rhs.set;
            }

            return *this;
        }

        /// Destruct
        ~HashSet() {
            set.clear();
        }

        bool Add(Type& value) {
            unsigned prevSize = (unsigned)set.size();
            set.emplace(value);
            return prevSize != set.size();
        }

        void Remove(const Type& value) {
            auto i = set.find(value);
            if (i != set.end())
                i = set.erase(i);
        }

        void Clear() {
            set.clear();
        }

        bool Contains(const Type& value) const {
            auto i = set.find(value);
            return i != set.end();
        }

        unsigned Size() const { return (unsigned)set.size(); }

        bool Empty() const { return set.empty(); }

        const std::unordered_set<Type>& Set() const { return set; }

        std::unordered_set<Type>& Set() { return set; }
    };

}