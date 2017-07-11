#pragma once

#include "../Core/RefCounted.h"

namespace Pyro
{
    /// Shared pointer template class with intrusive reference counting.
    template<typename Type> class SharedPtr {

    private:
        /// Pointer to the object.
        Type* ptr;

    public:
        /// Construct a null shared pointer.
        SharedPtr() : ptr(nullptr) {}

        /// Copy-construct from another shared pointer.
        SharedPtr(const SharedPtr<Type>& rhs) : ptr(rhs.ptr) {
            AddRef();
        }

        /// Copy-construct from another shared pointer allowing implicit upcasting.
        template<typename U> SharedPtr(const SharedPtr<U>& rhs) : ptr(rhs.ptr) {
            AddRef();
        }

        /// Construct from a raw pointer.
        explicit SharedPtr(Type* _ptr) : ptr(_ptr) {
            AddRef();
        }

        /// Destruct. Release the object reference.
        ~SharedPtr() {
            ReleaseRef();
        }

        /// Assign from another shared pointer.
        SharedPtr<Type>& operator=(const SharedPtr<Type>& rhs) {
            if (ptr == rhs.ptr)
                return *this;

            ReleaseRef();
            ptr = rhs.ptr;
            AddRef();

            return *this;
        }

        /// Assign from another shared pointer allowing implicit upcasting.
        template<typename U> SharedPtr<Type>& operator=(SharedPtr<U>& rhs) {
            if (ptr == rhs.ptr)
                return *this;

            ReleaseRef();
            ptr = rhs.ptr;
            AddRef();

            return *this;
        }

        /// Assign from a raw pointer.
        SharedPtr<Type>& operator=(Type* ptr) {
            if (this->ptr == ptr)
                return *this;

            ReleaseRef();
            this->ptr = ptr;
            AddRef();

            return *this;
        }

        /// Point to the object.
        Type* operator ->() const {
            return ptr;
        }

        /// Dereference the object.
        Type& operator *() const {
            return *ptr;
        }

        /// Subscript the object if applicable.
        Type& operator[](const unsigned int index) {
            return ptr[index];
        }

        /// Test for less than with another shared pointer.
        template <typename U> bool operator <(const SharedPtr<U>& rhs) const { return ptr < rhs.ptr; }

        /// Test for equality with another shared pointer.
        template <typename U> bool operator ==(const SharedPtr<U>& rhs) const { return ptr == rhs.ptr; }

        /// Test for inequality with another shared pointer.
        template <typename U> bool operator !=(const SharedPtr<U>& rhs) const { return ptr != rhs.ptr; }

        /// Convert to a raw pointer.
        operator Type*() const { return ptr; }

        /// Reset to null and release the object reference.
        void Reset() { ReleaseRef(); }

        /// Perform a static cast from a shared pointer of another type.
        template<typename U> void StaticCast(const SharedPtr<U>& rhs) {
            ReleaseRef();
            ptr = static_cast<Type*>(rhs.Get());
            AddRef();
        }

        /// Perform a dynamic cast from a shared pointer of another type.
        template<typename U> void DynamicCast(const SharedPtr<U>& rhs) {
            ReleaseRef();
            ptr = dynamic_cast<Type*>(rhs.Get());
            AddRef();
        }

        /// Check if the pointer is null.
        bool Null() const { return ptr == nullptr; }

        /// Check if the pointer is not null.
        bool NotNull() const { return ptr != nullptr; }

        /// Return the raw pointer.
        Type* Get() const { return ptr; }

        /// Return the object's reference count, or 0 if the pointer is null.
        int Refs() const { return ptr ? ptr->Refs() : 0; }

        /// Return pointer to the RefCount structure.
        RefCount* RefCountPtr() const { return ptr ? ptr->RefCountPtr() : 0; }

        /// Return hash value for HashSet & HashMap.
        unsigned int ToHash() const { return (unsigned int)((size_t)(ptr) / sizeof(Type)); }

    private:
        template <typename U> friend class SharedPtr;

        /// Add a reference to the object pointed to.
        void AddRef() {
            if (ptr)
                ptr->AddRef();
        }

        /// Release the object reference and delete it if necessary.
        void ReleaseRef() {
            if (ptr) {
                ptr->ReleaseRef();
                ptr = nullptr;
            }
        }
    };

    /// Perform a static cast from one weak pointer type to another.
    template<typename T, typename U> SharedPtr<T> StaticCast(const SharedPtr<U>& ptr) {
        SharedPtr<T> ret;
        ret.StaticCast(ptr);
        return ret;
    }

    /// Perform a dynamic cast from one weak pointer type to another.
    template<typename T, typename U> SharedPtr<T> DynamicCast(const SharedPtr<U>& ptr) {
        SharedPtr<T> ret;
        ret.DynamicCast(ptr);
        return ret;
    }
}
