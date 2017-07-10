#pragma once

#include "../Core/RefCounted.h"

namespace Pyro
{
    /// Shared pointer template class with intrusive reference counting.
    template<typename Type> class SharedPtr {

    private:
        Type* ptr;

    public:
        SharedPtr() : ptr(nullptr) {}

        SharedPtr(const SharedPtr<Type>& rhs) : ptr(rhs.ptr) {
            AddRef();
        }

        template<typename U> SharedPtr(const SharedPtr<U>& rhs) : ptr(rhs.ptr) {
            AddRef();
        }

        explicit SharedPtr(Type* _ptr) : ptr(_ptr) {
            AddRef();
        }

        ~SharedPtr() {
            ReleaseRef();
        }

        SharedPtr<Type>& operator=(const SharedPtr<Type>& rhs) {
            if (ptr == rhs.ptr)
                return *this;

            ReleaseRef();
            ptr = rhs.ptr;
            AddRef();

            return *this;
        }

        template<typename U> SharedPtr<Type>& operator=(SharedPtr<U>& rhs) {
            if (ptr == rhs.ptr)
                return *this;

            ReleaseRef();
            ptr = rhs.ptr;
            AddRef();

            return *this;
        }

        SharedPtr<Type>& operator=(Type* ptr) {
            if (this->ptr == ptr)
                return *this;

            ReleaseRef();
            this->ptr = ptr;
            AddRef();

            return *this;
        }

        Type* operator ->() const {
            return ptr;
        }

        Type& operator *() const {
            return *ptr;
        }

        Type& operator[](const unsigned int index) {
            return ptr[index];
        }

        template <typename U> bool operator <(const SharedPtr<U>& rhs) const { return ptr < rhs.ptr; }

        template <typename U> bool operator ==(const SharedPtr<U>& rhs) const { return ptr == rhs.ptr; }

        template <typename U> bool operator !=(const SharedPtr<U>& rhs) const { return ptr != rhs.ptr; }

        operator Type*() const { return ptr; }

        void Reset() { ReleaseRef(); }

        template<typename U> void StaticCast(const SharedPtr<U>& rhs) {
            ReleaseRef();
            ptr = static_cast<Type*>(rhs.Get());
            AddRef();
        }

        template<typename U> void DynamicCast(const SharedPtr<U>& rhs) {
            ReleaseRef();
            ptr = dynamic_cast<Type*>(rhs.Get());
            AddRef();
        }

        bool Null() const { return ptr == nullptr; }

        bool NotNull() const { return ptr != nullptr; }

        Type* Get() const { return ptr; }

        int Refs() const { return ptr ? ptr->Refs() : 0; }

        unsigned int ToHash() const { return (unsigned int)((size_t)(ptr) / sizeof(Type)); }

    private:
        template <typename U> friend class SharedPtr;

        void AddRef() {
            if (ptr)
                ptr->AddRef();
        }

        void ReleaseRef() {
            if (ptr) {
                ptr->ReleaseRef();
                ptr = nullptr;
            }
        }
    };

    template<typename T, typename U>
    SharedPtr<T> StaticCast(const SharedPtr<U>& ptr) {
        SharedPtr<T> ret;
        ret.StaticCast(ptr);
        return ret;
    }

    template<typename T, typename U>
    SharedPtr<T> DynamicCast(const SharedPtr<U>& ptr) {
        SharedPtr<T> ret;
        ret.DynamicCast(ptr);
        return ret;
    }
}
