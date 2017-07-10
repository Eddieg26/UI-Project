#pragma once

#include <list>
#include "../Util/types.h"

namespace Pyro
{
    /// Doubly-linked list template class
    template<typename T> class List {

    private:
        std::list<type> mData;

    public:
        /// Construct empty
        List() {}

        /// Construct from another list
        List(const List<T>& rhs) {
            *this = rhs;
        }

        /// Destruct
        ~List() {
            Clear();
        }

        /// Assign from another list
        List& operator=(const List<T>& rhs) {
            if (this != &rhs) {
                Clear();
                mData = rhs.mData;
            }

            return *this;
        }

        /// Add-assign an element
        List& operator+=(const T& value) {
            Push(value);
            return *this;
        }

        List& operator+=(const List<T>& rhs) {
            uint oldSize = mData.size();
            mData.resize(mData.size() + rhs.Size());
            std::copy(rhs.mData.begin(), rhs.mData.end(), mData.begin() + oldSize);
        }

        /// Test for equality with another list
        bool operator==(const List<T>& rhs) {
            return mData == rhs.mData;
        }

        bool operator!=(const List<T>& rhs) {
            return !(*this == rhs);
        }

        /// Return element at index
        T& operator[](uint index) {
            return *(mData.begin() + index);
        }

        const T& operator[](uint index) const {
            return *(mData.cbegin() + index);
        }

        /// Insert an element to the end.
        void Push(const T& value) {
            mData.push_back(value);
        }

        /// Insert an element to the beginning.
        void PushHead(const T& value) {
            mData.push_front(value);
        }

        /// Insert an element at index
        void Insert(uint index, const T& value) {
            mData.insert(mData.begin() + index, value);
        }

        /// Insert elements at index
        void Insert(uint index, const T* items, uint count) {
            mData.insert(mData.begin() + index, items, items + count);
        }

        void RemoveAt(uint index) {
            if (index < mData.size())
                mData.erase(mData.begin() + index);
        }

        /// Erase the last element.
        void Pop() {
            mData.pop_back();
        }

        /// Erase the first element.
        void PopFront() {
            mData.pop_front();
        }

        /// Clear the list
        void Clear() {
            mData.clear();
        }

        /// Resize the list by removing or adding items at the end.
        void Resize(uint newSize) {
            mData.resize(newSize);
        }

        /// Return index to value, or to size if not found.
        uint Find(const T& value) const {
            auto iter = mData.begin();
            uint index = 0;
            while (iter != mData.end()) {
                if ((*iter) == value)
                    break;

                ++iter;
                ++index;
            }

            return index;
        }

        /// Return whether contains a specific value.
        bool Contains(const T& value) const {
            return Find(value) != mData.size();;
        }

        /// Return first element.
        T& Front() { *mData.begin(); }

        /// Return const first element.
        const T& Front() const { return *mData.cbegin(); }

        /// Return last element
        T& Back() { return *(mData.begin() + (mData.size() - 1)); }

        /// Return const last element
        const T& Back() const { return *(mData.cbegin() + (mData.size() - 1)); }

        /// Return size
        uint Size() const { return mData.size(); }

        /// Return whether list is empty.
        bool Empty() const { return mData.empty(); }
    };
}
