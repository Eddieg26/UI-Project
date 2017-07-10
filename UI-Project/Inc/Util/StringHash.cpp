#include "StringHash.h"
#include "../Containers/Str.h"
#include "../Containers/Hash.h"

#include <assert.h>
#include <cstdio>
#include <cctype>
#include <cstring>

namespace Pyro
{
    const StringHash StringHash::ZERO;

    StringHash::StringHash(const char* str) {
        hashValue = Calculate(str);
    }

    StringHash::StringHash(const String& str) {
        hashValue = Calculate(str.CString());
    }

    unsigned StringHash::Calculate(const char* str) {
        assert(str);
        return MakeHash(str);
    }

    String StringHash::ToString() const {
        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%08X", hashValue);
        return String(tempBuffer);
    }
}

