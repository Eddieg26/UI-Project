#pragma once

#include <iostream>
#include <cstddef>
#include "Str.h"
#include "Pair.h"
#include "../Util/StringHash.h"
#include "../Util/types.h"

namespace Pyro
{
    /// Pointer hash function.
    template <class T> uint MakeHash(T* value) {
        return (uint)((size_t)value / sizeof(T));
    }

    /// Const pointer hash function.
    template <class T> uint MakeHash(const T* value) {
        return (uint)((size_t)value / sizeof(T));
    }

    /// Generic hash function.
    template <class T> uint MakeHash(const T& value) {
        return value.ToHash();
    }

    /// Void pointer hash function.
    template <> inline uint MakeHash(void* value) {
        return (uint)reinterpret_cast<size_t>(value);
    }

    /// Const void pointer hash function.
    template <> inline uint MakeHash(const void* value) {
        return (uint)reinterpret_cast<size_t>(value);
    }

    /// Long long hash function.
    template <> inline uint MakeHash(const long long& value) {
        return (uint)((value >> 32) | (value & 0xffffffff));
    }

    /// uint long long hash function.
    template <> inline uint MakeHash(const uint64& value) {
        return (uint)((value >> 32) | (value & 0xffffffff));
    }

    /// Int hash function.
    template <> inline uint MakeHash(const int& value) {
        return (uint)value;
    }

    /// uint hash function.
    template <> inline uint MakeHash(const uint& value) {
        return value;
    }

    /// Short hash function.
    template <> inline uint MakeHash(const short& value) {
        return (uint)value;
    }

    /// uint short hash function.
    template <> inline uint MakeHash(const uint16& value) {
        return value;
    }

    /// Char hash function.
    template <> inline uint MakeHash(const char& value) {
        return (uint)value;
    }

    /// uint char hash function.
    template <> inline uint MakeHash(const uint8& value) {
        return value;
    }

    template <> inline uint MakeHash(const char* value) {
        uint hash = 0;
        uint i = 0;
        uint length = (uint)strlen(value);
        while (i < length) {
            hash = value[i] + (hash << 6) + (hash << 16) - hash;
            ++i;
        }

        return hash;
    }
}


namespace std
{
    template<>
    struct hash<Pyro::StringHash> {
        size_t operator()(const Pyro::StringHash& value) const {
            return value.ToHash();
        }
    };

    template<>
    struct hash<Pyro::String> {
        size_t operator()(const Pyro::String& value) const {
            return value.ToHash();
        }
    };

    template<>
    struct hash<Pyro::Pair<Pyro::StringHash, Pyro::StringHash>> {
        size_t operator()(const Pyro::Pair<Pyro::StringHash, Pyro::StringHash>& value) const {
            return value.ToHash();
        }
    };
}

