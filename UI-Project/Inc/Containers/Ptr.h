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

    /// Shared array pointer template class. Uses non-intrusive reference counting.
    template<typename T> class SharedArrayPtr {

    private:
        /// Pointer to the array.
        T* ptr;
        /// Pointer to the RefCount structure.
        RefCount* refCount;

    public:
        /// Construct
        SharedArrayPtr() : ptr(nullptr), refCount(nullptr) {}

        /// Copy-construct from another shared array pointer.
        SharedArrayPtr(const SharedArrayPtr<T>& rhs) :
            ptr(rhs.ptr),
            refCount(rhs.refCount) {
            AddRef();
        }

        /// Construct from a raw pointer.
        explicit SharedArrayPtr(T* ptr) :
            ptr(ptr),
            refCount(new RefCount()) {
            AddRef();
        }

        /// Destruct
        ~SharedArrayPtr() {
            ReleaseRef();
        }

        /// Assign from another shared array pointer.
        SharedArrayPtr<T>& operator =(const SharedArrayPtr<T>& rhs) {
            if (ptr == rhs.ptr)
                return *this;

            ReleaseRef();
            ptr = rhs.ptr;
            refCount = rhs.refCount;
            AddRef();

            return *this;
        }

        /// Assign from a raw pointer.
        SharedArrayPtr<T>& operator =(T* ptr) {
            if (this->ptr == ptr)
                return *this;

            ReleaseRef();

            if (ptr) {
                this->ptr = ptr;
                refCount = new RefCount();
                AddRef();
            }

            return *this;
        }

        /// Point to the array.
        T* operator ->() const {
            assert(ptr);
            return ptr;
        }

        /// Dereference the array.
        T& operator *() const {
            assert(ptr);
        }

        /// Subscript the array.
        T& operator [](const int index) {
            assert(ptr);
            return ptr[index];
        }

        /// Test for equality with another shared array pointer.
        bool operator ==(const SharedArrayPtr<T>& rhs) const { return ptr == rhs.ptr; }

        /// Test for inequality with another shared array pointer.
        bool operator !=(const SharedArrayPtr<T>& rhs) const { return ptr != rhs.ptr; }

        /// Test for less than with another array pointer.
        bool operator <(const SharedArrayPtr<T>& rhs) const { return ptr < rhs.ptr; }

        /// Convert to a raw pointer.
        operator T*() const { return ptr; }

        /// Reset to null and release the array reference.
        void Reset() { ReleaseRef(); }

        /// Perform a static cast from a shared array pointer of another type.
        template <class U> void StaticCast(const SharedArrayPtr<U>& rhs)
        {
            ReleaseRef();
            ptr = static_cast<T*>(rhs.Get());
            refCount = rhs.RefCountPtr();
            AddRef();
        }

        /// Perform a reinterpret cast from a shared array pointer of another type.
        template <class U> void ReinterpretCast(const SharedArrayPtr<U>& rhs)
        {
            ReleaseRef();
            ptr = reinterpret_cast<T*>(rhs.Get());
            refCount = rhs.RefCountPtr();
            AddRef();
        }

        /// Check if the pointer is null.
        bool Null() const { return ptr == nullptr; }

        /// Check if the ptr is not null
        bool NotNull() const { return ptr != nullptr; }

        /// Return the raw pointer.it
        T* Get() const { return ptr; }

        /// Return the array's reference count, or 0 if the pointer is null.
        int Refs() const { return refCount ? refCount->refs : 0; }

        /// Return pointer to the RefCount structure.
        RefCount* RefCountPtr() const { return refCount; }

        /// Return hash value for HashSet & HashMap.
        unsigned ToHash() const { return (unsigned)((size_t)ptr / sizeof(T)); }

    private:
        /// Prevent direct assignment from a shared array pointer of different type.
        template <class U> SharedArrayPtr<T>& operator =(const SharedArrayPtr<U>& rhs);

        void AddRef() {
            if (refCount) {
                assert(refCount->refs >= 0);
                ++(refCount->refs);
            }
        }

        /// Release the array reference and delete it and the RefCount structure if necessary.
        void ReleaseRef() {
            if (refCount) {
                assert(refCount->refs > 0);
                --(refCount->refs);
                if (!refCount->refs) {
                    refCount->refs = -1;
                    delete[] ptr;
                }

                if (refCount->refs < 0)
                    delete refCount;
            }

            ptr = nullptr;
            refCount = nullptr;
        }
    };

    /// Perform a static cast from one shared array pointer type to another.
    template <class T, class U> SharedArrayPtr<T> StaticCast(const SharedArrayPtr<U>& ptr)
    {
        SharedArrayPtr<T> ret;
        ret.StaticCast(ptr);
        return ret;
    }

    /// Perform a reinterpret cast from one shared array pointer type to another.
    template <class T, class U> SharedArrayPtr<T> ReinterpretCast(const SharedArrayPtr<U>& ptr)
    {
        SharedArrayPtr<T> ret;
        ret.ReinterpretCast(ptr);
        return ret;
    }
}
