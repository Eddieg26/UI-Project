#pragma once

#include "../Core/RefCount.h"
#include <cassert>

namespace Pyro
{
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