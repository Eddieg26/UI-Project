#include "RefCounted.h"

#include <assert.h>

namespace Pyro
{
    RefCounted::RefCounted() : refs(0) {}

    RefCounted::~RefCounted() {
        assert(refs == 0);

        refs = -1;
    }

    void RefCounted::AddRef() {
        assert(refs >= 0);
        ++refs;
    }

    void RefCounted::ReleaseRef() {
        assert(refs > 0);
        --refs;

        if (!refs)
            delete this;
    }
}

