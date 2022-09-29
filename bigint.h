#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <limits>
#include <iostream>

class bigint {
    using byte = uint8_t;
    using dbyte = uint16_t;
    private:
        size_t capacity;
        byte* array;
        bool is_negative;

        void grow();
        void trim();
        size_t num_bytes() const;
    public:
        static const bigint zero;

        bigint();
        bigint(char);
        bigint(short);
        bigint(int);
        bigint(long);
        bigint(long long);
        bigint(signed char);
        bigint(unsigned char);
        bigint(unsigned short);
        bigint(unsigned int);
        bigint(unsigned long);
        bigint(unsigned long long);

        bigint(const bigint&);
        bigint(bigint&&);
        ~bigint();
        bigint& operator=(const bigint&);
        bigint& operator=(bigint&&);

        operator bool() const;
        operator char() const;
        operator short() const;
        operator int() const;
        operator long() const;
        operator long long() const;
        operator signed char() const;
        operator unsigned char() const;
        operator unsigned short() const;
        operator unsigned int() const;
        operator unsigned long() const;
        operator unsigned long long() const;

        bigint operator+() const;
        bigint operator-() const;
        bigint& operator++();
        bigint& operator--();
        bigint operator++(int);
        bigint operator--(int);

        bool operator==(const bigint&) const;
        bool operator!=(const bigint&) const;
        bool operator>(const bigint&) const;
        bool operator<(const bigint&) const;
        bool operator>=(const bigint&) const;
        bool operator<=(const bigint&) const;
        template<typename T> bool operator==(T rhs) const {return this->operator==(static_cast<bigint>(rhs));}
        template<typename T> bool operator!=(T rhs) const {return this->operator!=(static_cast<bigint>(rhs));}
        template<typename T> bool operator<(T rhs) const {return this->operator<(static_cast<bigint>(rhs));}
        template<typename T> bool operator>(T rhs) const {return this->operator>(static_cast<bigint>(rhs));}
        template<typename T> bool operator<=(T rhs) const {return this->operator<=(static_cast<bigint>(rhs));}
        template<typename T> bool operator>=(T rhs) const {return this->operator>=(static_cast<bigint>(rhs));}

        bigint operator+(const bigint&) const;
        bigint operator-(const bigint&) const;
        bigint operator*(const bigint&) const;
        bigint operator/(const bigint&) const;
        bigint operator%(const bigint&) const;
        template<typename T> bool operator+(T rhs) const {return this->operator+(static_cast<bigint>(rhs));}
        template<typename T> bool operator-(T rhs) const {return this->operator-(static_cast<bigint>(rhs));}
        template<typename T> bool operator*(T rhs) const {return this->operator*(static_cast<bigint>(rhs));}
        template<typename T> bool operator/(T rhs) const {return this->operator/(static_cast<bigint>(rhs));}
        template<typename T> bool operator%(T rhs) const {return this->operator%(static_cast<bigint>(rhs));}

        bigint& operator+=(const bigint&);
        bigint& operator-=(const bigint&);
        bigint& operator*=(const bigint&);
        bigint& operator/=(const bigint&);
        bigint& operator%=(const bigint&);

        bigint operator&(const bigint&) const;
        bigint operator|(const bigint&) const;
        bigint operator^(const bigint&) const;
        bigint operator<<(size_t) const;
        bigint operator>>(size_t) const;
        template<typename T> bool operator&(T rhs) const {return this->operator&(static_cast<bigint>(rhs));}
        template<typename T> bool operator|(T rhs) const {return this->operator|(static_cast<bigint>(rhs));}
        template<typename T> bool operator^(T rhs) const {return this->operator^(static_cast<bigint>(rhs));}

        bigint& operator&=(const bigint&);
        bigint& operator|=(const bigint&);
        bigint& operator^=(const bigint&);
        bigint& operator<<=(size_t);
        bigint& operator>>=(size_t);

        std::string to_string() const;
        std::string to_hex(bool = false) const;
        std::string to_bin(bool = false) const;

        static bigint pow(const bigint&, const bigint&);
        static bigint factorial(const bigint&);
};

template<typename T> bool operator==(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) == rhs;}
template<typename T> bool operator!=(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) != rhs;}
template<typename T> bool operator<(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) < rhs;}
template<typename T> bool operator>(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) > rhs;}
template<typename T> bool operator<=(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) <= rhs;}
template<typename T> bool operator>=(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) >= rhs;}

template<typename T> bool operator+(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) + rhs;}
template<typename T> bool operator-(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) - rhs;}
template<typename T> bool operator*(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) * rhs;}
template<typename T> bool operator/(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) / rhs;}
template<typename T> bool operator%(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) % rhs;}

template<typename T> bool operator&(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) & rhs;}
template<typename T> bool operator|(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) | rhs;}
template<typename T> bool operator^(T lhs, const bigint& rhs) {return static_cast<bigint>(lhs) ^ rhs;}

std::ostream& operator<<(std::ostream&, const bigint&);
std::istream& operator>>(std::istream&, bigint&);

bigint stobi(const std::string&, size_t* = nullptr, int = 10);

#endif