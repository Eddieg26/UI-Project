#include "Str.h"

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cwchar>

namespace Pyro
{
    const String String::EMPTY;

    String::String() {
        m_uiLength = 0;
        m_pBuffer = nullptr;
        Reserve(MIN_CAPACITY);
        m_pBuffer[0] = ' ';
    }

    String::String(const String& str) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;
        *this = str;
    }

    String::String(const char* str) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;
        *this = str;
    }

    String::String(char* str) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;
        *this = (const char*)str;
    }

    String::String(const char* str, unsigned length) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        Resize(length);
        CopyChars(m_pBuffer, str, length);
    }

    String::String(const wchar_t* str) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        SetUTF8FromWChar(str);
    }

    String::String(wchar_t* str) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        SetUTF8FromWChar(str);
    }

    String::String(const WString& str) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        SetUTF8FromWChar(str.CString());
    }

    String::String(int value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%d", value);
        *this = tempBuffer;
    }

    String::String(short value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%d", value);
        *this = tempBuffer;
    }

    String::String(long value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%ld", value);
        *this = tempBuffer;
    }

    String::String(long long value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%lld", value);
        *this = tempBuffer;
    }

    String::String(unsigned value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%u", value);
        *this = tempBuffer;
    }

    String::String(unsigned short value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%u", value);
        *this = tempBuffer;
    }

    String::String(unsigned long value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%lu", value);
        *this = tempBuffer;
    }

    String::String(unsigned long long value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%llu", value);
        *this = tempBuffer;
    }

    String::String(float value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%g", value);
        *this = tempBuffer;
    }

    String::String(double value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        char tempBuffer[CONVERSION_BUFFER_LENGTH];
        sprintf_s(tempBuffer, "%.15g", value);
        *this = tempBuffer;
    }

    String::String(bool value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        if (value)
            *this = "true";
        else
            *this = "false";
    }

    String::String(char value) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        Resize(1);
        m_pBuffer[0] = value;
    }

    String::String(char value, unsigned length) {
        m_uiLength = 0;
        m_uiCapacity = 0;
        m_pBuffer = nullptr;

        Resize(length);
        for (unsigned i = 0; i < length; ++i) {
            m_pBuffer[i] = value;
        }
    }

    String::~String() {
        if (m_uiCapacity) {
            m_uiLength = 0;
            m_uiCapacity = 0;
            delete[] m_pBuffer;
        }
    }

    String& String::operator =(const String& str) {
        Resize(str.Length());
        CopyChars(m_pBuffer, str.CString(), str.Length());

        return *this;
    }

    String& String::operator =(const char* str) {
        unsigned strLength = CStringLength(str);
        Resize(strLength);
        CopyChars(m_pBuffer, str, strLength);

        return *this;
    }

    String& String::operator +=(const String& str) {
        unsigned oldLength = m_uiLength;
        Resize(m_uiLength + str.Length());
        CopyChars(m_pBuffer + oldLength, str.CString(), str.Length());

        return *this;
    }

    String& String::operator +=(const char* str) {
        unsigned rhsLength = CStringLength(str);
        unsigned oldLength = m_uiLength;
        Resize(m_uiLength + rhsLength);
        CopyChars(m_pBuffer + oldLength, str, rhsLength);

        return *this;
    }

    String& String::operator +=(char c) {
        unsigned oldLength = m_uiLength;
        Resize(m_uiLength + 1);
        m_pBuffer[oldLength] = c;

        return *this;
    }

    String& String::operator +=(int value) {
        return *this += String(value);
    }

    String& String::operator +=(short value) {
        return *this += String(value);
    }

    String& String::operator +=(long value) {
        return *this += String(value);
    }

    String& String::operator +=(long long value) {
        return *this += String(value);
    }

    String& String::operator +=(unsigned value) {
        return *this += String(value);
    }

    String& String::operator +=(unsigned short value) {
        return *this += String(value);
    }

    String& String::operator +=(unsigned long value) {
        return *this += String(value);
    }

    String& String::operator +=(unsigned long long value) {
        return *this += String(value);
    }

    String& String::operator +=(float value) {
        return *this += String(value);
    }

    String& String::operator +=(double value) {
        return *this += String(value);
    }

    String& String::operator +=(bool value) {
        return *this += String(value);
    }

    String String::operator +(const String& str) const {
        String ret;
        ret.Resize(m_uiLength + str.Length());
        CopyChars(ret.m_pBuffer, m_pBuffer, m_uiLength);
        CopyChars(ret.m_pBuffer + m_uiLength, str.CString(), str.Length());

        return ret;
    }

    String String::operator +(const char* str) const {
        unsigned rhsLength = CStringLength(str);
        String ret;
        ret.Resize(m_uiLength + rhsLength);
        CopyChars(ret.m_pBuffer, m_pBuffer, m_uiLength);
        CopyChars(ret.m_pBuffer + m_uiLength, str, rhsLength);

        return ret;
    }

    bool String::operator ==(const String& str) const {
        return strcmp(CString(), str.CString()) == 0;
    }

    bool String::operator !=(const String& str) const {
        return strcmp(CString(), str.CString()) != 0;
    }

    bool String::operator <(const String& str) const {
        return strcmp(CString(), str.CString()) < 0;
    }

    bool String::operator >(const String& str) const {
        return strcmp(CString(), str.CString()) > 0;
    }

    bool String::operator ==(const char* str) const {
        return strcmp(CString(), str) == 0;
    }

    bool String::operator !=(const char* str) const {
        return strcmp(CString(), str) != 0;
    }

    bool String::operator <(const char* str) const {
        return strcmp(CString(), str) < 0;
    }

    bool String::operator >(const char* str) const {
        return strcmp(CString(), str) > 0;
    }

    char& String::operator [](unsigned index) {
        return m_pBuffer[index];
    }

    const char& String::operator [](unsigned index) const {
        return m_pBuffer[index];
    }

    char& String::At(unsigned index) {
        return m_pBuffer[index];
    }

    const char& String::At(unsigned index) const {
        return m_pBuffer[index];
    }

    void String::Replace(char replaceThis, char replaceWith, bool caseSensitive) {
        if (caseSensitive) {
            for (unsigned i = 0; i < m_uiLength; ++i) {
                if (m_pBuffer[i] == replaceThis)
                    m_pBuffer[i] = replaceWith;
            }
        }
        else {
            replaceThis = (char)tolower(replaceThis);
            for (unsigned i = 0; i < m_uiLength; ++i) {
                if (tolower(m_pBuffer[i]) == replaceThis)
                    m_pBuffer[i] = replaceWith;
            }
        }
    }

    void String::Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive) {
        unsigned nextPos = 0;

        while (nextPos < m_uiLength) {
            unsigned pos = Find(replaceThis, nextPos, caseSensitive);
            if (pos == NPOS)
                break;
            Replace(pos, replaceThis.Length(), replaceWith);
            nextPos = pos + replaceWith.Length();
        }
    }

    void String::Replace(unsigned pos, unsigned length, const String& replaceWith) {
        if (pos + length > m_uiLength)
            return;

        Replace(pos, length, replaceWith.m_pBuffer, replaceWith.Length());
    }

    void String::Replace(unsigned pos, unsigned length, const char* replaceWith) {
        if (pos + length > m_uiLength)
            return;

        Replace(pos, length, replaceWith, CStringLength(replaceWith));
    }

    String String::Replaced(char replaceThis, char replaceWith, bool caseSensitive) const {
        String ret(*this);
        ret.Replace(replaceThis, replaceWith, caseSensitive);
        return ret;
    }

    String String::Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive) const {
        String ret(*this);
        ret.Replace(replaceThis, replaceWith, caseSensitive);
        return ret;
    }

    String& String::Append(const String& str) {
        return *this += str;
    }

    String& String::Append(const char* str) {
        return *this += str;
    }

    String& String::Append(char c) {
        return *this += c;
    }

    String& String::Append(const char* str, unsigned length) {
        if (str) {
            unsigned oldLength = m_uiLength;
            Resize(oldLength + length);
            CopyChars(m_pBuffer + oldLength, str, length);
        }

        return *this;
    }

    void String::Insert(unsigned pos, const String& str) {
        if (pos > m_uiLength)
            pos = m_uiLength;

        if (pos == m_uiLength)
            (*this) += str;
        else
            Replace(pos, 0, str);
    }

    void String::Insert(unsigned pos, const char* str, unsigned length) {
        if (pos > m_uiLength)
            pos = m_uiLength;

        if (pos == m_uiLength)
            (*this) += str;
        else
            Replace(pos, 0, str, length);
    }

    void String::Insert(unsigned pos, char c) {
        if (pos > m_uiLength)
            pos = m_uiLength;

        if (pos == m_uiLength)
            (*this) += c;
        else {
            unsigned oldLength = m_uiLength;
            Resize(m_uiLength + 1);
            MoveRange(pos + 1, pos, oldLength);
            m_pBuffer[pos] = c;
        }
    }

    void String::Erase(unsigned pos, unsigned length) {
        Replace(pos, length, String::EMPTY);
    }

    void String::Resize(unsigned newLength) {
        if (!m_uiCapacity) {
            if (!newLength)
                return;

            m_uiCapacity = newLength + 1;
            if (m_uiCapacity < MIN_CAPACITY)
                m_uiCapacity = MIN_CAPACITY;

            m_pBuffer = new char[m_uiCapacity];
        }
        else {
            if (newLength && m_uiCapacity < newLength + 1) {
                while (m_uiCapacity < newLength + 1)
                    m_uiCapacity += (m_uiCapacity + 1) >> 1;

                char* newBuffer = new char[m_uiCapacity];

                if (m_uiLength)
                    CopyChars(newBuffer, m_pBuffer, m_uiLength);
                delete[] m_pBuffer;

                m_pBuffer = newBuffer;
            }
        }

        m_pBuffer[newLength] = '\0';
        m_uiLength = newLength;
    }

    void String::Reserve(unsigned newCapacity) {
        if (!m_pBuffer) {
            m_uiCapacity = newCapacity;
            m_pBuffer = new char[m_uiCapacity];
            for (unsigned i = 0; i < m_uiCapacity; ++i)
                m_pBuffer[i] = '\0';

            return;
        }

        if (newCapacity < m_uiLength)
            newCapacity = m_uiLength + 1;
        if (newCapacity == m_uiCapacity)
            return;

        char* newBuffer = new char[newCapacity];
        CopyChars(newBuffer, m_pBuffer, m_uiLength + 1);

        if (m_uiCapacity)
            delete[] m_pBuffer;

        m_uiCapacity = newCapacity;
        m_pBuffer = newBuffer;
    }

    void String::Compact() {
        if (m_uiCapacity)
            Reserve(m_uiLength + 1);
    }

    void String::Clear() {
        m_uiLength = 0;
    }

    char String::Front() const {
        return m_pBuffer ? m_pBuffer[0] : 0;
    }

    char String::Back() const {
        return m_pBuffer ? m_pBuffer[m_uiLength - 1] : 0;
    }

    String String::SubString(unsigned pos) const {
        if (pos < m_uiLength) {
            String ret;
            ret.Resize(m_uiLength - pos);
            CopyChars(ret.m_pBuffer, m_pBuffer + pos, ret.Length());
            return ret;
        }

        return String::EMPTY;
    }

    String String::SubString(unsigned pos, unsigned length) const {
        if (pos < m_uiLength) {
            String ret;
            if (pos + length > m_uiLength)
                length = length - pos;
            ret.Resize(length);
            CopyChars(ret.m_pBuffer, m_pBuffer + pos, ret.Length());
            return ret;
        }

        return String::EMPTY;
    }

    String String::Trimmed() const {
        unsigned trimStart = 0;
        unsigned trimEnd = m_uiLength;

        while (trimStart < trimEnd) {
            char c = m_pBuffer[trimStart];
            if (c != ' ' && c != 9)
                break;

            ++trimStart;
        }
        while (trimEnd > trimStart) {
            char c = m_pBuffer[trimEnd];
            if (c != ' ' && c != 9)
                break;

            --trimEnd;
        }

        return SubString(trimStart, trimEnd - trimStart);
    }

    String String::ToUpper() const {
        String ret(*this);
        for (unsigned i = 0; i < m_uiLength; ++i)
            ret[i] = toupper(m_pBuffer[i]);

        return ret;
    }

    String String::ToLower() const {
        String ret(*this);
        for (unsigned i = 0; i < m_uiLength; ++i)
            ret[i] = tolower(m_pBuffer[i]);

        return ret;
    }

    StringVector String::Split(char seperator, bool keepEmptyStrings) const {
        return Split(CString(), seperator, keepEmptyStrings);
    }

    void String::Join(const StringVector& subStrings, const String& glue) {
        *this = Joined(subStrings, glue);
    }

    unsigned String::Find(char c, unsigned startPos, bool caseSensitive) const {
        if (caseSensitive) {
            for (unsigned i = startPos; i < m_uiLength; ++i) {
                if (m_pBuffer[i] == c)
                    return i;
            }
        }
        else {
            c = (char)tolower(c);
            for (unsigned i = startPos; i < m_uiLength; ++i) {
                if (tolower(m_pBuffer[i] == c))
                    return i;
            }
        }

        return NPOS;
    }

    unsigned String::Find(const String& str, unsigned startPos, bool caseSensitive) const {
        if (!str.Length() || str.Length() > m_uiLength)
            return NPOS;

        char first = str.m_pBuffer[0];
        if (!caseSensitive)
            first = (char)tolower(first);

        for (unsigned i = startPos; i <= m_uiLength - str.m_uiLength; ++i) {
            char c = m_pBuffer[i];
            if (!caseSensitive)
                c = (char)tolower(c);

            if (c == first) {
                unsigned skip = NPOS;
                bool found = true;

                for (unsigned j = 1; j < str.m_uiLength; ++j) {
                    c = m_pBuffer[i + j];
                    char d = str.m_pBuffer[j];

                    if (!caseSensitive) {
                        c = (char)tolower(c);
                        d = (char)tolower(d);
                    }

                    if (skip == NPOS && c == first)
                        skip = i + j - 1;

                    if (c != d) {
                        found = false;
                        if (skip != NPOS)
                            i = skip;
                        break;
                    }
                }

                if (found)
                    return i;
            }
        }

        return NPOS;
    }

    unsigned String::FindLast(char c, unsigned startPos, bool caseSensitive) const {
        if (startPos >= m_uiLength)
            startPos = m_uiLength - 1;

        if (caseSensitive) {
            for (unsigned i = 0; i < m_uiLength; ++i) {
                if (m_pBuffer[i] == c)
                    return i;
            }
        }
        else {
            c = (char)tolower(c);
            for (unsigned i = 0; i < m_uiLength; ++i) {
                if (tolower(m_pBuffer[i]) == c)
                    return i;
            }
        }

        return NPOS;
    }

    unsigned String::FindLast(const String& str, unsigned startPos, bool caseSensitive) const {
        if (startPos >= m_uiLength)
            startPos = m_uiLength - 1;

        if (!str.m_uiLength || str.m_uiLength > m_uiLength)
            return NPOS;

        if (startPos > m_uiLength - str.m_uiLength)
            startPos = m_uiLength - str.m_uiLength;

        char first = str.m_pBuffer[0];
        if (!caseSensitive)
            first = (char)tolower(first);

        for (unsigned i = startPos; i < m_uiLength; --i) {
            char c = m_pBuffer[i];
            if (!caseSensitive)
                c = (char)tolower(c);

            if (c == first) {
                bool found = true;
                for (unsigned j = 1; j < str.m_uiLength; ++j) {
                    c = m_pBuffer[i + j];
                    char d = str.m_pBuffer[j];

                    if (!caseSensitive) {
                        c = (char)tolower(c);
                        d = (char)tolower(d);
                    }

                    if (c != d) {
                        found = false;
                        break;
                    }
                }

                if (found)
                    return i;
            }
        }

        return NPOS;
    }

    bool String::StartsWith(const String& str, bool caseSensitive) const {
        if (!str.m_uiLength || str.m_uiLength > m_uiLength)
            return false;

        for (unsigned i = 0; i < str.m_uiLength; ++i) {
            char c = str.m_pBuffer[i];
            char d = m_pBuffer[i];

            if (!caseSensitive) {
                c = (char)tolower(c);
                d = (char)tolower(d);
            }

            if (c != d)
                return false;
        }

        return true;
    }

    bool String::EndsWith(const String& str, bool caseSensitive) const {
        unsigned pos = FindLast(str, Length() - 1, caseSensitive);
        return pos != NPOS && pos == Length() - str.Length();
    }

    const char* String::CString() const { return m_pBuffer; }
    unsigned String::Length() const { return m_uiLength; }
    unsigned String::Capacity() const { return m_uiCapacity; }
    bool String::Empty() const { return m_uiLength == 0; }

    unsigned String::ToHash() const {
        unsigned hash = 0;
        unsigned i = 0;
        while (i < m_uiLength) {
            hash = m_pBuffer[i] + (hash << 6) + (hash << 16) - hash;
            ++i;
        }

        return hash;
    }

    int String::Compare(const String& str, bool caseSensitve) const {
        return Compare(CString(), str.CString(), caseSensitve);
    }

    int String::Compare(const char* str, bool caseSensitive) const {
        return Compare(CString(), str, caseSensitive);
    }

    bool String::Contains(const String& str, bool caseSensive) const {
        return Find(str, 0, caseSensive) != NPOS;
    }

    bool String::Contains(char c, bool caseSensitive) const {
        return Find(c, 0, caseSensitive) != NPOS;
    }

    void String::SetUTF8FromLatin1(const char* str) {
        if (!str)
            return;

        char temp[7];
        while (str) {
            char* dest = temp;
            EncodeUTF8(dest, (unsigned)*str++);
            *dest = 0;
            Append(temp);
        }
    }

    void String::SetUTF8FromWChar(const wchar_t* str) {
        if (!str)
            return;

        Clear();

        char temp[7];

#ifdef _WIN32
        uint size = (uint)std::wcslen(str) + 1;
        while (size) {
            unsigned unicodeChar = DecodeUTF16(str);
            char* dest = temp;
            EncodeUTF8(dest, unicodeChar);
            *dest = 0;
            Append(temp);
            --size;
        }
#endif
    }

    unsigned String::LengthUTF8() const {
        unsigned ret = 0;

        const char* src = m_pBuffer;
        if (!src)
            return ret;

        const char* end = m_pBuffer + m_uiLength;

        while (src < end) {
            DecodeUTF8(src);
            ++ret;
        }
        return ret;
    }

    unsigned String::ByteOffsetUTF8(unsigned index) const {
        unsigned byteOffset = 0;
        unsigned utfPos = 0;

        while (utfPos < index && byteOffset < m_uiLength) {
            NextUTF8Char(byteOffset);
            ++utfPos;
        }

        return byteOffset;
    }

    unsigned String::NextUTF8Char(unsigned& byteOffset) const {
        if (!m_pBuffer)
            return 0;

        const char* src = m_pBuffer + byteOffset;
        unsigned ret = DecodeUTF8(src);
        byteOffset = (unsigned)(src - m_pBuffer);

        return ret;
    }

    unsigned String::AtUTF8(unsigned index) const {
        unsigned byteOffset = ByteOffsetUTF8(index);
        return NextUTF8Char(byteOffset);
    }

    void String::ReplaceUTF8(unsigned index, unsigned unicodeChar) {
        unsigned byteOffset = 0;
        unsigned utfPos = 0;

        while (utfPos < index && byteOffset < m_uiLength) {
            NextUTF8Char(byteOffset);
            ++utfPos;
        }

        if (utfPos < index)
            return;

        unsigned beginCharPos = byteOffset;
        NextUTF8Char(byteOffset);

        char temp[7];
        char* dest = temp;
        EncodeUTF8(dest, unicodeChar);
        *dest = 0;

        Replace(beginCharPos, byteOffset - beginCharPos, temp, (unsigned)(dest - temp));
    }

    String& String::AppendUTF8(unsigned unicodeChar) {
        char temp[7];
        char* dest = temp;
        EncodeUTF8(dest, unicodeChar);
        *dest = 0;
        return Append(temp);
    }

    String String::SubstringUTF8(unsigned pos) const {
        unsigned utf8Length = LengthUTF8();
        unsigned byteOffset = ByteOffsetUTF8(pos);
        String ret;

        while (pos < utf8Length) {
            ret.AppendUTF8(NextUTF8Char(byteOffset));
            ++pos;
        }

        return ret;
    }

    String String::SubstringUTF8(unsigned pos, unsigned length) const {
        unsigned utf8Length = LengthUTF8();
        unsigned byteOffset = ByteOffsetUTF8(pos);
        unsigned endPos = pos + length;
        String ret;

        while (pos < endPos && pos < utf8Length) {
            ret.AppendUTF8(NextUTF8Char(byteOffset));
            ++pos;
        }

        return ret;
    }

    String& String::AppendWithFormat(const char* formatString, ...) {
        va_list args;
        va_start(args, formatString);
        AppendWithFormatArgs(formatString, args);
        va_end(args);
        return *this;
    }

    String& String::AppendWithFormatArgs(const char* formatString, va_list args) {
        int pos = 0, lastPos = 0;
        int length = (int)strlen(formatString);

        while (true) {
            // Scan the format string and find %a argument where a is one of d, f, s ...
            while (pos < length && formatString[pos] != '%') ++pos;
            Append(formatString + lastPos, (unsigned)(pos - lastPos));
            if (pos >= length)
                return *this;

            char format = formatString[pos + 1];
            pos += 2;
            lastPos = pos;
            switch (format) {
                // Integar
            case 'd':
            case 'i':
            {
                int arg = va_arg(args, int);
                Append(String(arg));
                break;
            }
            // Unsigned
            case 'u':
            {
                unsigned arg = va_arg(args, unsigned);
                Append(String(arg));
                break;
            }

            // Unsigned long
            case 'l':
            {
                unsigned long arg = va_arg(args, unsigned long);
                Append(String(arg));
                break;
            }

            // Real
            case 'f':
            {
                double arg = va_arg(args, double);
                Append(String(arg));
                break;
            }

            // Character
            case 'c':
            {
                int arg = va_arg(args, int);
                Append(String(arg));
                break;
            }

            // C string
            case 's':
            {
                char* arg = va_arg(args, char*);
                Append(arg);
                break;
            }

            // Hex
            case 'x':
            {
                char buff[CONVERSION_BUFFER_LENGTH];
                int arg = va_arg(args, int);
                int argLength = ::sprintf_s(buff, "%x", arg);
                Append(buff, (unsigned)argLength);
                break;
            }

            // Pointer
            case 'p':
            {
                char buff[CONVERSION_BUFFER_LENGTH];
                int arg = va_arg(args, int);
                int argLength = ::sprintf_s(buff, "%p", reinterpret_cast<void*>(arg));
                Append(buff, (unsigned)argLength);
                break;
            }

            case '%':
            {
                Append("%", 1);
                break;
            }
            default:
                break;
            }
        }
    }

    /*static*/ StringVector String::Split(const char* str, char separator, bool keepEmptyStrings) {
        StringVector ret;
        const char* strEnd = str + String::CStringLength(str);

        for (const char* splitEnd = str; splitEnd != strEnd; ++splitEnd) {
            if (*splitEnd == separator) {
                const ptrdiff_t splitLen = splitEnd - str;

                if (splitLen > 0 || keepEmptyStrings)
                    ret.Add(String(str, splitLen));

                str = splitEnd + 1;
            }
        }

        return ret;
    }

    /*static*/ String String::Joined(const Vector<String>& subStrings, const String& glue) {
        if (subStrings.Empty())
            return String::EMPTY;

        String joinedString(subStrings[0]);
        for (unsigned i = 1; i < subStrings.Size(); ++i)
            joinedString.Append(glue).Append(subStrings[i]);

        return joinedString;
    }

    /*static*/ void String::EncodeUTF8(char*& dest, unsigned unicodeChar) {
        if (unicodeChar < 0x80)
            *dest++ = unicodeChar;
        else if (unicodeChar < 0x800)
        {
            dest[0] = (char)(0xc0 | ((unicodeChar >> 6) & 0x1f));
            dest[1] = (char)(0x80 | (unicodeChar & 0x3f));
            dest += 2;
        }
        else if (unicodeChar < 0x10000)
        {
            dest[0] = (char)(0xe0 | ((unicodeChar >> 12) & 0xf));
            dest[1] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
            dest[2] = (char)(0x80 | (unicodeChar & 0x3f));
            dest += 3;
        }
        else if (unicodeChar < 0x200000)
        {
            dest[0] = (char)(0xf0 | ((unicodeChar >> 18) & 0x7));
            dest[1] = (char)(0x80 | ((unicodeChar >> 12) & 0x3f));
            dest[2] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
            dest[3] = (char)(0x80 | (unicodeChar & 0x3f));
            dest += 4;
        }
        else if (unicodeChar < 0x4000000)
        {
            dest[0] = (char)(0xf8 | ((unicodeChar >> 24) & 0x3));
            dest[1] = (char)(0x80 | ((unicodeChar >> 18) & 0x3f));
            dest[2] = (char)(0x80 | ((unicodeChar >> 12) & 0x3f));
            dest[3] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
            dest[4] = (char)(0x80 | (unicodeChar & 0x3f));
            dest += 5;
        }
        else
        {
            dest[0] = (char)(0xfc | ((unicodeChar >> 30) & 0x1));
            dest[1] = (char)(0x80 | ((unicodeChar >> 24) & 0x3f));
            dest[2] = (char)(0x80 | ((unicodeChar >> 18) & 0x3f));
            dest[3] = (char)(0x80 | ((unicodeChar >> 12) & 0x3f));
            dest[4] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
            dest[5] = (char)(0x80 | (unicodeChar & 0x3f));
            dest += 6;
        }
    }

#define GET_NEXT_CONTINUATION_BYTE(ptr) *ptr; if ((unsigned char)*ptr < 0x80 || (unsigned char)*ptr >= 0xc0) return '?'; else ++ptr;

    /*static*/ unsigned String::DecodeUTF8(const char*& src) {
        if (src == 0)
            return 0;

        unsigned char char1 = *src++;

        // Check if we are in the middle of a UTF8 character
        if (char1 >= 0x80 && char1 < 0xc0)
        {
            while ((unsigned char)*src >= 0x80 && (unsigned char)*src < 0xc0)
                ++src;
            return '?';
        }

        if (char1 < 0x80)
            return char1;
        else if (char1 < 0xe0)
        {
            unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
            return (unsigned)((char2 & 0x3f) | ((char1 & 0x1f) << 6));
        }
        else if (char1 < 0xf0)
        {
            unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
            return (unsigned)((char3 & 0x3f) | ((char2 & 0x3f) << 6) | ((char1 & 0xf) << 12));
        }
        else if (char1 < 0xf8)
        {
            unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
            return (unsigned)((char4 & 0x3f) | ((char3 & 0x3f) << 6) | ((char2 & 0x3f) << 12) | ((char1 & 0x7) << 18));
        }
        else if (char1 < 0xfc)
        {
            unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
            return (unsigned)((char5 & 0x3f) | ((char4 & 0x3f) << 6) | ((char3 & 0x3f) << 12) | ((char2 & 0x3f) << 18) |
                ((char1 & 0x3) << 24));
        }
        else
        {
            unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
            unsigned char char6 = GET_NEXT_CONTINUATION_BYTE(src);
            return (unsigned)((char6 & 0x3f) | ((char5 & 0x3f) << 6) | ((char4 & 0x3f) << 12) | ((char3 & 0x3f) << 18) |
                ((char2 & 0x3f) << 24) | ((char1 & 0x1) << 30));
        }
    }

#ifdef _WIN32
    /*static*/ void String::EncodeUTF16(wchar_t*& dest, unsigned unicodeChar) {
        if (unicodeChar < 0x10000)
            *dest++ = unicodeChar;
        else
        {
            unicodeChar -= 0x10000;
            *dest++ = 0xd800 | ((unicodeChar >> 10) & 0x3ff);
            *dest++ = 0xdc00 | (unicodeChar & 0x3ff);
        }
    }

    /*static*/ unsigned String::DecodeUTF16(const wchar_t*& src) {
        if (src == 0)
            return 0;

        unsigned short word1 = *src;

        // Check if we are at a low surrogate
        word1 = *src++;
        if (word1 >= 0xdc00 && word1 < 0xe000)
        {
            while (*src >= 0xdc00 && *src < 0xe000)
                ++src;
            return '?';
        }

        if (word1 < 0xd800 || word1 >= 0xe000)
            return word1;
        else
        {
            unsigned short word2 = *src++;
            if (word2 < 0xdc00 || word2 >= 0xe000)
            {
                --src;
                return '?';
            }
            else
                return (((word1 & 0x3ff) << 10) | (word2 & 0x3ff)) + 0x10000;
        }
    }
#endif

    /*static*/ unsigned String::CStringLength(const char* str) {
        return (str ? (unsigned)strlen(str) : 0);
    }

    /*static*/ int String::Compare(const char* lhs, const char* rhs, bool caseSensitive) {
        if (!lhs || !rhs)
            return lhs ? 1 : (rhs ? -1 : 0);

        if (caseSensitive)
            return strcmp(lhs, rhs);
        else
        {
            for (;;)
            {
                char l = (char)tolower(*lhs);
                char r = (char)tolower(*rhs);
                if (!l || !r)
                    return l ? 1 : (r ? -1 : 0);
                if (l < r)
                    return -1;
                if (l > r)
                    return 1;

                ++lhs;
                ++rhs;
            }
        }
    }

    /*static*/ void String::CopyChars(char* dest, const char* src, unsigned count) {
#ifdef _MSC_VER
        if (count)
            memcpy(dest, src, count);
#else
        char* end = dest + count;
        while (dest != end)
        {
            *dest = *src;
            ++dest;
            ++src;
        }
#endif
    }

    void String::MoveRange(unsigned dest, unsigned src, unsigned count) {
        if (count)
            memmove(m_pBuffer + dest, m_pBuffer + src, count);
    }

    void String::Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength) {
        int delta = (int)srcLength - (int)length;

        if (pos + length < m_uiLength)
        {
            if (delta < 0)
            {
                MoveRange(pos + srcLength, pos + length, m_uiLength - pos - length);
                Resize(m_uiLength + delta);
            }
            if (delta > 0)
            {
                Resize(m_uiLength + delta);
                MoveRange(pos + srcLength, pos + length, m_uiLength - pos - length - delta);
            }
        }
        else
            Resize(m_uiLength + delta);

        CopyChars(m_pBuffer + pos, srcStart, srcLength);
    }

    WString::WString() {
        m_uiLength = 0;
        m_pBuffer = nullptr;
    }

    WString::WString(const String& str) {
        m_uiLength = 0;
        m_pBuffer = nullptr;

#ifdef _WIN32
        unsigned neededSize = 0;
        wchar_t temp[3];

        unsigned byteOffset = 0;
        while (byteOffset < str.Length()) {
            wchar_t* dest = temp;
            String::EncodeUTF16(dest, str.NextUTF8Char(byteOffset));
            neededSize += dest - temp;
        }

        Resize(neededSize);

        byteOffset = 0;
        wchar_t* dest = m_pBuffer;
        while (byteOffset < str.Length())
            String::EncodeUTF16(dest, str.NextUTF8Char(byteOffset));
#else
        Resize(str.LengthUTF8());

        unsigned byteOffset = 0;
        wchar_t* dest = m_pBuffer;
        while (byteOffset < str.Length())
            *dest++ = (wchar_t)str.NextUTF8Char(byteOffset);
#endif
    }

    WString::~WString() {
        delete[] m_pBuffer;
    }

    wchar_t& WString::operator [](unsigned index) {
        return m_pBuffer[index];
    }

    const wchar_t& WString::operator [](unsigned index) const {
        return m_pBuffer[index];
    }

    wchar_t& WString::At(unsigned index) {
        return m_pBuffer[index];
    }

    const wchar_t& WString::At(unsigned index) const {
        return m_pBuffer[index];
    }

    void WString::Resize(unsigned newLength) {
        if (!newLength) {
            delete[] m_pBuffer;
            m_pBuffer = nullptr;
            m_uiLength = 0;
        }
        else {
            wchar_t* newBuffer = new wchar_t[newLength + 1];
            if (m_pBuffer) {
                unsigned copyLength = m_uiLength < newLength ? m_uiLength : newLength;
                memcpy(newBuffer, m_pBuffer, copyLength * sizeof(wchar_t));
                m_pBuffer = nullptr;
            }
            newBuffer[newLength] = 0;
            m_pBuffer = newBuffer;
            m_uiLength = newLength;
        }
    }

    bool WString::Empty() const {
        return m_uiLength == 0;
    }

    unsigned WString::Length() const {
        return m_uiLength;
    }

    const wchar_t* WString::CString() const {
        return m_pBuffer;
    }
    void WString::CopyChars(wchar_t * dest, const wchar_t * src, unsigned count) {
        if (count)
            memcpy(dest, src, count);
    }
}
