
#pragma once

#include "Hash.h"

namespace Pyro
{
    template<typename T, typename U>
    class Pair {

    private:
        T m_tFirst;
        U m_uSecond;

    public:
        Pair() = default;
        Pair(const T& first, const U& second);
        Pair(const Pair<T, U>& pair);
        Pair<T, U>& operator=(const Pair<T, U>& pair);

        bool operator ==(const Pair<T, U>& rhs) const;
        bool operator !=(const Pair<T, U>& rhs) const;
        bool operator <(const Pair<T, U>& rhs) const;
        bool operator >(const Pair<T, U>& rhs) const;

        const T& First() const;
        const U& Second() const;

        T& First();
        U& Second();

        unsigned int ToHash() const;
    };


    template<typename T, typename U>
    Pair<T, U>::Pair(const T& first, const U& second) {
        m_tFirst = first;
        m_uSecond = second;
    }

    template<typename T, typename U>
    Pair<T, U>::Pair(const Pair<T, U>& pair) {
        m_tFirst = pair.m_tFirst;
        m_uSecond = pair.m_uSecond;
    }

    template<typename T, typename U>
    Pair<T, U>& Pair<T, U>::operator=(const Pair<T, U>& pair) {
        if (this != &pair) {
            m_tFirst = pair.m_tFirst;
            m_uSecond = pair.m_uSecond;
        }

        return *this;
    }

    template<typename T, typename U>
    bool Pair<T, U>::operator ==(const Pair<T, U>& rhs) const { return m_tFirst == rhs.m_tFirst && m_uSecond == rhs.m_uSecond; }

    template<typename T, typename U>
    bool Pair<T, U>::operator !=(const Pair<T, U>& rhs) const { return m_tFirst != rhs.m_tFirst || m_uSecond != rhs.m_uSecond; }

    template<typename T, typename U>
    bool Pair<T, U>::operator <(const Pair<T, U>& rhs) const {
        if (m_tFirst < rhs.m_tFirst)
            return true;
        if (m_tFirst != rhs.m_tFirst)
            return false;
        return m_uSecond < rhs.m_uSecond;
    }

    template<typename T, typename U>
    bool Pair<T, U>::operator >(const Pair<T, U>& rhs) const {
        if (m_tFirst > rhs.m_tFirst)
            return true;
        if (m_tFirst != rhs.m_tFirst)
            return false;
        return m_uSecond > rhs.m_uSecond;
    }

    template<typename T, typename U>
    const T& Pair<T, U>::First() const { return m_tFirst; }

    template<typename T, typename U>
    const U& Pair<T, U>::Second() const { return m_uSecond; }

    template<typename T, typename U>
    T& Pair<T, U>::First() { return m_tFirst; }

    template<typename T, typename U>
    U& Pair<T, U>::Second() { return m_uSecond; }

    template<typename T, typename U>
    unsigned Pair<T, U>::ToHash() const { return (MakeHash(m_tFirst) & 0xffff) | (MakeHash(m_uSecond) << 16); }


    // Construct a pair.
    template <typename T, typename U>
    Pair<T, U> MakePair(const T& first, const U& second) {
        return Pair<T, U>(first, second);
    }
}
