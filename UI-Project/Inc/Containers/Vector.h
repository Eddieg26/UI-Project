#pragma once

#include <vector>
#include "../Util/types.h"

namespace Pyro
{
    template<typename Type>
    class Vector {

    private:
        std::vector<Type> mData;

    public:
        Vector();
        explicit Vector(uint capacity);
        Vector(Type* data, uint size);
        Vector(const Vector<Type>& list);
        Vector<Type>& operator=(const Vector<Type>& list);
        ~Vector();

        void Add(const Type& item);
        void AddRange(const Type* item, uint count);
        void AddRange(const Vector<Type>& list);
        void Insert(uint index, const Type& item);
        void InsertRange(uint startIndex, const Type* list, uint count);
        void InsertRange(uint startIndex, const Vector<Type> list);
        bool Remove(const Type& item);
        void RemoveAll(const Type& item);
        void RemoveRange(uint start, uint count);
        void RemoveAt(uint index);
        void Clear();

        void Reverse();
        void Reverse(uint start, uint count);

        // Reallocate so that no extra memory is used.
        void Compact();
        void Reserve(uint newCapacity);

        bool Contains(const Type& item) const;
        bool Empty() const { return mData.empty(); }

        Vector<Type> GetRange(uint start, uint count) const;
        Vector<Type> GetAll(const Type& item) const;

        Type& operator[](uint index);
        const Type& operator[](const uint index) const;

        bool operator ==(const Vector<Type>& rhs) const;
        bool operator !=(const Vector<Type>& rhs) const;

        uint Size() const { return (uint)mData.size(); }
        uint Capcity() const { return (uint)mData.capacity(); }
        const Type* Data() const { return mData.data(); }

        const std::vector<Type>& Vec() const { return mData; }

        std::vector<Type>& Vec() { return mData; }

    private:
        void Swap(Type& a, Type& b);
    };

    template<typename Type>
    Vector<Type>::Vector() {
    }

    template<typename Type>
    Vector<Type>::Vector(uint capacity) {
        Reserve(1);
    }

    template<typename Type>
    Vector<Type>::Vector(Type* data, uint size) {
        AddRange(data, size);
    }

    template<typename Type>
    Vector<Type>::Vector(const Vector<Type>& list) {
        AddRange(list);
    }

    template<typename Type>
    Vector<Type>& Vector<Type>::operator=(const Vector<Type>& list) {
        if (this != &list) {
            Clear();
            mData = list.mData;
        }

        return *this;
    }

    template<typename Type>
    Vector<Type>::~Vector() {
        mData.clear();
    }

    template<typename Type>
    void Vector<Type>::Add(const Type& item) {
        mData.push_back(item);
    }

    template<typename Type>
    void Vector<Type>::AddRange(const Type* items, uint count) {
        uint oldSize = (uint)mData.size();
        mData.resize(mData.size() + count);
        std::copy(items, items + count, mData.begin() + oldSize);
    }

    template<typename Type>
    void Vector<Type>::AddRange(const Vector<Type>& list) {
        AddRange(list.mData.data(), list.Size());
    }

    template<typename Type>
    void AddRange(const Vector<Type>& list) {
        AddRange(list.mData.data(), list.Size());
    }

    template<typename Type>
    void Vector<Type>::Insert(uint index, const Type& item) {
        if (index < mData.size())
            mData.insert(mData.begin() + index, item);
        else
            mData.push_back(item);
    }

    template<typename Type>
    void Vector<Type>::InsertRange(uint startIndex, const Type* list, uint count) {
        mData.insert(mData.begin() + startIndex, list, list + count);
    }

    template<typename Type>
    void Vector<Type>::InsertRange(uint startIndex, const Vector<Type> list) {
        InsertRange(startIndex, list.mData, list.Size());
    }

    template<typename Type>
    bool Vector<Type>::Remove(const Type& item) {
        bool removed = false;
        for (uint i = 0; i < mData.size(); ++i) {
            if (mData[i] == item) {
                mData.erase(mData.begin() + i);
                removed = true;
                break;
            }
        }

        return removed;
    }

    template<typename Type>
    void Vector<Type>::RemoveAll(const Type& item) {
        while (Remove(item));
    }

    template<typename Type>
    void Vector<Type>::RemoveAt(uint index) {
        uint count = mData.size() - index;
        memcpy(&mData[index], &mData[index + 1], count * sizeof(Type));

        --mData.size();
    }

    template<typename Type>
    void Vector<Type>::RemoveRange(uint start, uint count) {
        if (start >= mData.size())
            return;

        uint index = start;
        while (index < count && index < mData.size()) {
            mData.erase(mData.begin() + index);
            ++count;
        }
    }

    template<typename Type>
    void Vector<Type>::Clear() {
        mData.clear();
    }

    template<typename Type>
    void Vector<Type>::Reverse() {
        if (mData.size() < 2) return;

        uint start, end;

        for (start = 0, end = mData.size() - 1; start <= end && start != end; ++start, --end) {
            Swap(mData[start], mData[end]);
        }
    }

    template<typename Type>
    void Vector<Type>::Reverse(uint start, uint count) {

        if (start >= mData.size()) return;

        if (start + count >= mData.size())
            count = mData.size() - start;

        uint begin, end;

        for (begin = start, end = start + count - 1; begin <= end && begin != end; ++begin, --end) {
            Swap(mData[begin], mData[end]);
        }
    }

    template<typename Type>
    void Vector<Type>::Compact() {
        Type* data = mData.data();
        uint size = mData.size();
        mData.clear();
        AddRange(data, size);
    }

    template<typename Type>
    void Vector<Type>::Reserve(uint capacity) {
        mData.reserve(capacity);
    }

    template<typename Type>
    bool Vector<Type>::Contains(const Type& item) const {
        for (uint i = 0; i < mData.size(); ++i) {
            if (mData[i] == item)
                return true;
        }

        return false;
    }

    template<typename Type>
    Vector<Type> Vector<Type>::GetRange(uint start, uint count) const {
        Vector<Type> ret;

        if (start + count < mData.size()) {
            ret.AddRange(&mData[start], count);
        }
        else {
            if (start < mData.size()) {
                ret.AddRange(&mData[start], mData.size() - start);
            }
        }

        return ret;
    }

    template<typename Type>
    Vector<Type> Vector<Type>::GetAll(const Type& item) const {
        Vector<Type> ret;

        for (uint i = 0; i < mData.size(); ++i) {
            if (mData[i] == item)
                ret.Add(item);
        }

        return ret;
    }

    template<typename Type>
    Type& Vector<Type>::operator[](uint index) {
        return mData[index];
    }

    template<typename Type>
    const Type& Vector<Type>::operator[](const uint index) const {
        return mData[index];
    }

    template<typename Type>
    bool Vector<Type>::operator ==(const Vector<Type>& rhs) const {
        if (Size() != rhs.Size())
            return false;

        for (uint i = 0; i < mData.size(); ++i) {
            if (mData[i] != rhs.mData[i])
                return false;
        }

        return true;
    }

    template<typename Type>
    bool Vector<Type>::operator !=(const Vector<Type>& rhs) const {
        return !(*this == rhs);
    }

    template<typename Type>
    void Vector<Type>::Swap(Type& a, Type& b) {
        Type temp = a;
        a = b;
        b = temp;
    }

}

