#include "RefCounted.h"

#include <assert.h>

namespace Pyro
{
    RefCounted::RefCounted() : refCount(new RefCount) {}

    RefCounted::~RefCounted() {
        assert(refCount && refCount->refs == 0);

        refCount->refs = -1;
    }

    void RefCounted::AddRef() {
        assert(refCount && refCount->refs >= 0);
        ++refCount->refs;
    }

    void RefCounted::ReleaseRef() {
        assert(refCount->refs > 0);
        --refCount->refs;

        if (!refCount->refs)
            delete this;
    }
}

