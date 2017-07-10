#pragma once

namespace Pyro
{
    typedef unsigned int HashType;

    class String;

    /// 32-bit hash value for a string.
    class StringHash
    {
    public:
        /// Construct with zero value.
        StringHash() :
            hashValue(0) {}

        /// Copy-construct from another hash.
        StringHash(const StringHash& rhs) :
            hashValue(rhs.hashValue) {}

        /// Construct with an initial value.
        explicit StringHash(const HashType& value) :
            hashValue(value) {}

        /// Construct from a C string case-insensitively.
        StringHash(const char* str);
        /// Construct from a string case-insensitively.
        StringHash(const String& str);

        /// Assign from another hash.
        StringHash& operator =(const StringHash& rhs) {
            hashValue = rhs.hashValue;
            return *this;
        }

        StringHash& operator=(const HashType& rhs) {
            hashValue = rhs;
            return *this;
        }

        /// Add a hash.
        StringHash operator +(const StringHash& rhs) const {
            StringHash ret;
            ret.hashValue = hashValue + rhs.hashValue;
            return ret;
        }

        /// Add-assign a hash.
        StringHash& operator +=(const StringHash& rhs) {
            hashValue += rhs.hashValue;
            return *this;
        }

        /// Test for equality with another hash.
        bool operator ==(const StringHash& rhs) const { return hashValue == rhs.hashValue; }

        /// Test for inequality with another hash.
        bool operator !=(const StringHash& rhs) const { return hashValue != rhs.hashValue; }

        /// Test if less than another hash.
        bool operator <(const StringHash& rhs) const { return hashValue < rhs.hashValue; }

        /// Test if greater than another hash.
        bool operator >(const StringHash& rhs) const { return hashValue > rhs.hashValue; }

        /// Return true if nonzero hash value.
        operator bool() const { return hashValue != 0; }

        /// Return hash value.
        HashType Value() const { return hashValue; }

        /// Return as string.
        String ToString() const;

        /// Return hash value for HashSet & HashMap.
        HashType ToHash() const { return hashValue; }

        /// Calculate hash value case-insensitively from a C string.
        static HashType Calculate(const char* str);

        /// Zero hash.
        static const StringHash ZERO;

    private:
        /// Hash value.
        HashType hashValue;
    };
}