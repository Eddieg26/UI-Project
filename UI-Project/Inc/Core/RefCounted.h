#pragma once

namespace Pyro
{
    typedef const void* ClassID;

    struct RefCount {
        /// Reference count. If below zero, the object has been destroyed.
        int refs;

        /// Construct
        RefCount() : refs(0) {}
        /// Destruct
        ~RefCount() {
            refs = 0;
        }
    };

#define REFCOUNTED(typeName) \
	public: \
		virtual ClassID GetClassID() const { return GetClassIDStatic(); } \
		static ClassID GetClassIDStatic() { static const int typeID = 0; return (ClassID)&typeID; }

    /// Base class for intrusively reference-counted objects. These are noncopyable and non-assignable.
    class RefCounted {

    private:
        /// Reference count. If below zero the object has been destroyed
        RefCount* refCount;

    public:
        /// Construct. Allocate the reference count structure and set an initial self weak reference.
        RefCounted();

        /// Destruct. Mark as expired and also delete the reference count structure if no outside weak references exist.
        virtual ~RefCounted();

        /// Increment reference count
        void AddRef();
        /// Decrement reference count and delete self in no more references.
        void ReleaseRef();
        /// Return reference count
        int Refs() const { return refCount ? refCount->refs : 0; }
        /// Return reference count structure
        RefCount* RefCountPtr() { return refCount; }
        /// Return reference count structure
        const RefCount* RefCountPtr() const { return refCount; }

        /// Returns whether is object or not
        virtual bool IsObject() const { return false; }

        virtual ClassID GetClassID() const = 0;
        static ClassID GetClassIDStatic() { static const int typeID = 0; return (ClassID)&typeID; }

    private:
        /// Prevent copy construction
        RefCounted(const RefCounted& rhs) = delete;
        /// Prevent assignment
        RefCounted& operator=(const RefCounted& rhs) = delete;
    };
}
