#pragma once
#include <cstdarg>

#include "Vector.h"

namespace Pyro
{
    static const int CONVERSION_BUFFER_LENGTH = 128;
    static const int MAXTRIX_CONVERSION_LENGTH = 256;

    class String;
    class WString;

    typedef Vector<String> StringVector;

    class String {

    private:
        /// String length
        unsigned m_uiLength;
        /// String capacity
        unsigned m_uiCapacity;
        /// String buffer, null if not allocated
        char* m_pBuffer;

        /// Initial dynamic allocation size.
        static const unsigned MIN_CAPACITY = 8;

    public:
        /// Position for "not found."
        static const unsigned NPOS = 0xffffffff;
        /// Empty string.
        static const String EMPTY;

    public:

        /// Construct Empty
        String();

        /// Construct from another String
        String(const String& str);

        /// Construct from a C String
        String(const char* str);

        /// Construct from a C String
        String(char* str);

        /// Construct from a char array and length
        String(const char* str, unsigned length);

        /// Construct from a null terminated wide character array
        String(const wchar_t* str);

        /// Construct from a null terminated wide character array
        String(wchar_t* str);

        /// Construct froma wide character string
        String(const WString& str);

        /// Construct from an integar
        explicit String(int value);
        /// Construct from a short
        explicit String(short value);
        /// Construct from a long
        explicit String(long value);
        /// Construct from a long long
        explicit String(long long value);
        /// Construct from an unsignedegar
        explicit String(unsigned value);
        /// Construct from an unsigned short
        explicit String(unsigned short value);
        /// Construct from an unsigned long
        explicit String(unsigned long value);
        /// Construct from an unsigned long long
        explicit String(unsigned long long value);
        /// Construct from a float
        explicit String(float value);
        /// Construct from a double
        explicit String(double value);
        /// Construct from a bool
        explicit String(bool value);
        /// Construct from a char
        explicit String(char value);
        /// Construct from a char and fill length
        explicit String(char value, unsigned length);

        /// Destruct
        ~String();

        /// Assign a String
        String& operator =(const String& str);

        /// Assign a C String
        String& operator =(const char* str);

        /// Add-assign a String
        String& operator +=(const String& str);

        /// Add-assign a C String
        String& operator +=(const char* str);

        /// Add-assign a char
        String& operator +=(char c);

        /// Add-assign (concatenate as a string) an integar
        String& operator +=(int value);
        /// Add-assign (concatenate as a string) an short
        String& operator +=(short value);
        /// Add-assign (concatenate as a string) an long
        String& operator +=(long value);
        /// Add-assign (concatenate as a string) an long long
        String& operator +=(long long value);
        /// Add-assign (concatenate as a string) an unsignedegar
        String& operator +=(unsigned value);
        /// Add-assign (concatenate as a string) an unsigned short
        String& operator +=(unsigned short value);
        /// Add-assign (concatenate as a string) an unsigned long
        String& operator +=(unsigned long value);
        /// Add-assign (concatenate as a string) an unsigned long long
        String& operator +=(unsigned long long value);
        /// Add-assign (concatenate as a string) a float
        String& operator +=(float value);
        /// Add-assign (concatenate as a string) a double
        String& operator +=(double value);
        /// Add-assign (concatenate as a string) a bool
        String& operator +=(bool value);

        /// Add a String
        String operator +(const String& str) const;

        /// Add a C String
        String operator +(const char* str) const;

        /// Test for equality with another string
        bool operator ==(const String& str) const;

        /// Test for inequality with another string
        bool operator !=(const String& str) const;

        /// Test if less than another string
        bool operator <(const String& str) const;

        /// Test if greater than another string
        bool operator >(const String& str) const;

        /// Test for equality with a C String
        bool operator ==(const char* str) const;

        /// Test for inequality with a C String
        bool operator !=(const char* str) const;

        /// Test if less than a C String
        bool operator <(const char* str) const;

        /// Test if greater than a C String
        bool operator >(const char* str) const;

        /// Return char at index
        char& operator [](unsigned index);

        /// Return const char at index
        const char& operator [](unsigned index) const;

        /// Return char at index
        char& At(unsigned index);

        /// Return const char at index
        const char& At(unsigned index) const;

        /// Replace all occurrences of a character
        void Replace(char replaceThis, char replaceWith, bool caseSensitive = true);
        /// Replace all occurrences of a string
        void Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive = true);
        /// Replace a sub-string with a string
        void Replace(unsigned pos, unsigned length, const String& replaceWith);
        /// Replace a sub-string with a C String
        void Replace(unsigned pos, unsigned length, const char* replaceWith);
        /// Return a string with all occurences of a character replaced
        String Replaced(char replaceThis, char replaceWith, bool caseSensitive = true) const;
        /// Return a string with all occurrences of a string replaced
        String Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive = true) const;
        /// Append a string
        String& Append(const String& str);
        /// Append a C String
        String& Append(const char* str);
        /// Append a char
        String& Append(char c);
        /// Append characters
        String& Append(const char* c, unsigned length);
        /// Insert a string
        void Insert(unsigned pos, const String& str);
        /// Insert a C string
        void Insert(unsigned pos, const char* str, unsigned length);
        /// Insert a char
        void Insert(unsigned pos, char c);
        /// Erase a sub-string
        void Erase(unsigned pos, unsigned length = 1);
        /// Resize the string
        void Resize(unsigned newLength);
        /// Set new Capacity
        void Reserve(unsigned newCapacity);
        /// Reallocate so no extra memory is used
        void Compact();
        /// Clear the string
        void Clear();

        /// Return first char or zero if empty
        char Front() const;

        /// Return last char or zero if empty
        char Back() const;

        /// Return a sub-string from position to end
        String SubString(unsigned pos) const;
        /// Return a sub-string with length from position
        String SubString(unsigned pos, unsigned length) const;
        /// Return a string with whitespace trimmed from beginning and end
        String Trimmed() const;
        /// Return a string in uppercase
        String ToUpper() const;
        /// Return a string in lowercase
        String ToLower() const;
        /// Return substrings split by a separator char. By default don't return empty strings
        StringVector Split(char seperator, bool keepEmptyStrings = false) const;
        /// Join substrings with a 'glue' string
        void Join(const StringVector& subStrings, const String& glue);
        /// Return the index to the first occurrence of a char or NPOS if not found
        unsigned Find(char c, unsigned startPos = 0, bool caseSensitive = true) const;
        /// Return the index to the first occurrence of a string or NPOS if not found
        unsigned Find(const String& str, unsigned startPos = 0, bool caseSensitive = true) const;
        /// Returnt the index of the last occurrence of a char or NPOS if not found
        unsigned FindLast(char c, unsigned startPos = NPOS, bool caseSensitive = true) const;
        /// Return the index of the last occurrence of a string or NPOS if not found
        unsigned FindLast(const String& str, unsigned startPos = NPOS, bool caseSensitive = true) const;
        /// Returns whehter starts with a string
        bool StartsWith(const String& str, bool caseSensitive = true) const;
        /// Returns whether ends with a string
        bool EndsWith(const String& str, bool caseSensitive = true) const;

        /// Returns the C String
        const char* CString() const;
        /// Returns the length
        unsigned Length() const;
        /// Returns the capacity
        unsigned Capacity() const;

        /// Returns whether the string is empty
        bool Empty() const;

        /// Return hash value
        unsigned ToHash() const;

        /// Returns the comparison result with a string
        int Compare(const String& str, bool caseSensitve = true) const;
        /// Returns the comparison result with a C string
        int Compare(const char* str, bool caseSensitive = true) const;

        /// Returns whether contains a specific occurrence of a string
        bool Contains(const String& str, bool caseSensive = true) const;
        /// Returns whether contains a specific char
        bool Contains(char c, bool caseSensitive = true) const;

        /// Construct UTF8 content from Latin1.
        void SetUTF8FromLatin1(const char* str);
        /// Construct UTF8 content from wide characters.
        void SetUTF8FromWChar(const wchar_t* str);
        /// Calculate number of characters in UTF8 content.
        unsigned LengthUTF8() const;
        /// Return byte offset to char in UTF8 content.
        unsigned ByteOffsetUTF8(unsigned index) const;
        /// Return next Unicode character from UTF8 content and increase byte offset.
        unsigned NextUTF8Char(unsigned& byteOffset) const;
        /// Return Unicode character at index from UTF8 content.
        unsigned AtUTF8(unsigned index) const;
        /// Replace Unicode character at index from UTF8 content.
        void ReplaceUTF8(unsigned index, unsigned unicodeChar);
        /// Append Unicode character at the end as UTF8.
        String& AppendUTF8(unsigned unicodeChar);
        /// Return a UTF8 substring from position to end.
        String SubstringUTF8(unsigned pos) const;
        /// Return a UTF8 substring with length from position.
        String SubstringUTF8(unsigned pos, unsigned length) const;

        /// Append to string using formatting.
        String& AppendWithFormat(const char* formatString, ...);
        /// Append to string using variable arguments.
        String& AppendWithFormatArgs(const char* formatString, va_list args);

        /// Return substrings split by a separator char. By default don't return empty strings.
        static StringVector Split(const char* str, char separator, bool keepEmptyStrings = false);
        /// Return a string by joining substrings with a 'glue' string.
        static String Joined(const Vector<String>& subStrings, const String& glue);

        /// Encode Unicode character to UTF8. Pointer will be incremented.
        static void EncodeUTF8(char*& dest, unsigned unicodeChar);
        /// Decode Unicode character from UTF8. Pointer will be incremented.
        static unsigned DecodeUTF8(const char*& src);
#ifdef _WIN32
        /// Encode Unicode character to UTF16. Pointer will be incremented.
        static void EncodeUTF16(wchar_t*& dest, unsigned unicodeChar);
        /// Decode Unicode character from UTF16. Pointer will be incremented.
        static unsigned DecodeUTF16(const wchar_t*& src);
#endif

        /// Return length of a C string.
        static unsigned CStringLength(const char* str);

        /// Compare two C strings.
        static int Compare(const char* lhs, const char* rhs, bool caseSensitive);

    private:
        /// Move a range of characters within the string.
        void MoveRange(unsigned dest, unsigned src, unsigned count);

        /// Copy chars from one buffer to another.
        static void CopyChars(char* dest, const char* src, unsigned count);

        /// Replace a substring with another substring.
        void Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength);
    };

    inline String operator +(const char* lhs, const String& rhs) {
        String ret(lhs);
        ret += rhs;
        return ret;
    }

    inline String operator +(const wchar_t* lhs, const String& rhs) {
        String ret(lhs);
        ret += rhs;
        return ret;
    }

    /// Wide character string. Only meant for converting from String and passing to the operating system where necessary
    class WString {

    private:
        /// String length
        unsigned m_uiLength;
        /// String buffer, null if not allocated
        wchar_t* m_pBuffer;

    public:
        /// Construct Empty
        WString();

        /// Construct with string
        WString(const String& str);

        /// Destruct
        ~WString();

        /// Return char at index
        wchar_t& operator [](unsigned index);

        /// Return const char at index
        const wchar_t& operator [](unsigned index) const;

        /// Return char at index
        wchar_t& At(unsigned index);

        /// Return const char at index
        const wchar_t& At(unsigned index) const;

        /// Resize the string
        void Resize(unsigned newLength);

        /// Return whether string is empty
        bool Empty() const;

        /// Return string length
        unsigned Length() const;

        /// Return C string
        const wchar_t* CString() const;

    private:
        /// Copy wide chars from one buffer to another.
        static void CopyChars(wchar_t* dest, const wchar_t* src, unsigned count);
    };
}
