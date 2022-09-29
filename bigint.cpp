#include "bigint.h"

// MARK: Static Data Members

const bigint bigint::zero;

// MARK: Private Helper Functions

void bigint::grow() {
    if (capacity == 0) {
        capacity = 1;
        array = new byte[1] {0};
    } else {
        byte* new_array = new byte[capacity + capacity] {0};
        for (size_t i = 0; i < capacity; i++) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        capacity += capacity;
    }
}

void bigint::trim() {
    size_t i = num_bytes();
    while (capacity && capacity >= (i << 1)) {
        capacity >>= 1;
    }
    byte* new_array = nullptr;
    if (capacity) {
        new_array = new byte[capacity] {0};
        for (size_t i = 0; i < capacity; i++) {
            new_array[i] = array[i];
        }
    }
    delete[] array;
    array = new_array;
    if (!capacity) is_negative = false;
}

size_t bigint::num_bytes() const {
    int i = capacity;
    while (i > 0 && !array[i - 1]) --i;
    return i;
}

// MARK: Constructors

bigint::bigint()
    :capacity(0), array(nullptr), is_negative(false) {}

bigint::bigint(char num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(num < 0) {
    if (is_negative) num = -num;
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(short num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(num < 0) {
    if (is_negative) num = -num;
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(int num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(num < 0) {
    if (is_negative) num = -num;
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(long num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(num < 0) {
    if (is_negative) num = -num;
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(long long num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(num < 0) {
    if (is_negative) num = -num;
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(signed char num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(num < 0) {
    if (is_negative) num = -num;
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(unsigned char num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(false) {
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(unsigned short num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(false) {
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(unsigned int num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(false) {
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(unsigned long num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(false) {
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

bigint::bigint(unsigned long long num)
    :capacity(sizeof(num)), array(new byte[sizeof(num)]), is_negative(false) {
    for (size_t i = 0; i < capacity; i++) {
        array[i] = (num >> (i << 3)) & 0xFF;
    }
}

// MARK: Rule of 5

bigint::bigint(const bigint& other)
    :capacity(other.capacity), array(other.capacity ? new byte[other.capacity] : nullptr), is_negative(other.is_negative) {
    if (capacity) {
        for (size_t i = 0; i < capacity; i++) {
            array[i] = other.array[i];
        }
    };
}

bigint::bigint(bigint&& other)
    :capacity(other.capacity), array(other.array), is_negative(other.is_negative) {
    other.capacity = 0;
    other.array = nullptr;
}

bigint::~bigint() {
    delete[] array;
}

bigint& bigint::operator = (const bigint& other) {
    if (&other == this) return *this;

    delete[] array;
    capacity = other.capacity;
    if (capacity) {
        array = new byte[capacity];
        for (size_t i = 0; i < capacity; i++) {
            array[i] = other.array[i];
        }
    } else array = nullptr;
    is_negative = other.is_negative;

    return *this;
}

bigint& bigint::operator = (bigint&& other) {
    if (&other == this) return *this;

    delete[] array;
    capacity = other.capacity;
    array = other.array;
    is_negative = other.is_negative;

    other.capacity = 0;
    other.array = nullptr;
    
    return *this;
}

// MARK: Conversion Operators

bigint::operator bool() const {
    return this->operator!=(zero);
}

bigint::operator char() const {
    if (std::numeric_limits<char>().min() == 0) return this->operator unsigned char();
    else return this->operator signed char();
}

bigint::operator short() const {
    using T = short;
    using U = unsigned short;

    U result_u = is_negative ? -*this : *this;
    if (is_negative) --result_u;
    if (result_u > std::numeric_limits<U>().max() / 2) throw std::overflow_error("Conversion to signed type failed: bigint is too large.");
    T result = result_u;
    if (is_negative) result = -result - 1;
    return result;
}

bigint::operator int() const {
    using T = int;
    using U = unsigned int;

    U result_u = is_negative ? -*this : *this;
    if (is_negative) --result_u;
    if (result_u > std::numeric_limits<U>().max() / 2) throw std::overflow_error("Conversion to signed type failed: bigint is too large.");
    T result = result_u;
    if (is_negative) result = -result - 1;
    return result;
}

bigint::operator long() const {
    using T = long;
    using U = unsigned long;

    U result_u = is_negative ? -*this : *this;
    if (is_negative) --result_u;
    if (result_u > std::numeric_limits<U>().max() / 2) throw std::overflow_error("Conversion to signed type failed: bigint is too large.");
    T result = result_u;
    if (is_negative) result = -result - 1;
    return result;
}

bigint::operator long long() const {
    using T = long long;
    using U = unsigned long long;

    U result_u = is_negative ? -*this : *this;
    if (is_negative) --result_u;
    if (result_u > std::numeric_limits<U>().max() / 2) throw std::overflow_error("Conversion to signed type failed: bigint is too large.");
    T result = result_u;
    if (is_negative) result = -result - 1;
    return result;
}

bigint::operator signed char() const {
    using T = signed char;
    using U = unsigned char;

    U result_u = is_negative ? -*this : *this;
    if (is_negative) --result_u;
    if (result_u > std::numeric_limits<U>().max() / 2) throw std::overflow_error("Conversion to signed type failed: bigint is too large.");
    T result = result_u;
    if (is_negative) result = -result - 1;
    return result;
}

bigint::operator unsigned char() const {
    using T = unsigned char;

    const size_t max = sizeof(T);
    T result = 0;
    if (is_negative) {
        for (size_t i = 0; i < capacity; i++) {
            if (array[i]) throw std::overflow_error("Conversion to unsigned type failed: bigint is negative.");
        }
    } else {
        size_t i = num_bytes();
        if (i > max) throw std::overflow_error("Conversion failed: bigint is too large");
        while (i-- > 0) {
            result <<= 8;
            result |= array[i];
        }
    }
    return result;
}

bigint::operator unsigned short() const {
    using T = unsigned short;

    const size_t max = sizeof(T);
    T result = 0;
    if (is_negative) {
        for (size_t i = 0; i < capacity; i++) {
            if (array[i]) throw std::overflow_error("Conversion to unsigned type failed: bigint is negative.");
        }
    } else {
        size_t i = num_bytes();
        if (i > max) throw std::overflow_error("Conversion failed: bigint is too large");
        while (i-- > 0) {
            result <<= 8;
            result |= array[i];
        }
    }
    return result;
}

bigint::operator unsigned int() const {
    using T = unsigned int;

    const size_t max = sizeof(T);
    T result = 0;
    if (is_negative) {
        for (size_t i = 0; i < capacity; i++) {
            if (array[i]) throw std::overflow_error("Conversion to unsigned type failed: bigint is negative.");
        }
    } else {
        size_t i = num_bytes();
        if (i > max) throw std::overflow_error("Conversion failed: bigint is too large");
        while (i-- > 0) {
            result <<= 8;
            result |= array[i];
        }
    }
    return result;
}

bigint::operator unsigned long() const {
    using T = unsigned long;

    const size_t max = sizeof(T);
    T result = 0;
    if (is_negative) {
        for (size_t i = 0; i < capacity; i++) {
            if (array[i]) throw std::overflow_error("Conversion to unsigned type failed: bigint is negative.");
        }
    } else {
        size_t i = num_bytes();
        if (i > max) throw std::overflow_error("Conversion failed: bigint is too large");
        while (i-- > 0) {
            result <<= 8;
            result |= array[i];
        }
    }
    return result;
}

bigint::operator unsigned long long() const {
    using T = unsigned long long;

    const size_t max = sizeof(T);
    T result = 0;
    if (is_negative) {
        for (size_t i = 0; i < capacity; i++) {
            if (array[i]) throw std::overflow_error("Conversion to unsigned type failed: bigint is negative.");
        }
    } else {
        size_t i = num_bytes();
        if (i > max) throw std::overflow_error("Conversion failed: bigint is too large");
        while (i-- > 0) {
            result <<= 8;
            result |= array[i];
        }
    }
    return result;
}

// MARK: Unary Operators

bigint bigint::operator + () const {
    bigint result = *this;
    return result;
}

bigint bigint::operator - () const {
    bigint result = *this;
    result.is_negative = !result.is_negative;
    return result;
}

bigint& bigint::operator ++ () {
    if (is_negative) {
        is_negative = !is_negative;
        this->operator--();
        is_negative = !is_negative;
        return *this;
    }

    size_t i = 0;
    do {
        if (i == capacity) grow();
        ++array[i];
    } while (!array[i++]);

    return *this;
}

bigint& bigint::operator -- () {
    if (is_negative) {
        is_negative = !is_negative;
        this->operator++();
        is_negative = !is_negative;
        return *this;
    }

    size_t i = 0;
    if (!capacity) grow();
    while (i < capacity) {
        if (array[i]) break;
        ++i;
    }
    if (i < capacity) {
        do {
            --array[i];
        } while (i-- > 0);
    } else {
        array[0] = 0x01;
        is_negative = true;
    }

    return *this;
}

bigint bigint::operator ++ (int) {
    bigint result = *this;
    this->operator++();
    return result;
}

bigint bigint::operator -- (int) {
    bigint result = *this;
    this->operator--();
    return result;
}

// MARK: Relational Operators

bool bigint::operator == (const bigint& rhs) const {
    const bigint& lhs = *this;

    bool both_zero = true;
    size_t i = 0;
    while (i < lhs.capacity || i < rhs.capacity) {
        const byte lbyte = (i < lhs.capacity) ? lhs.array[i] : 0;
        const byte rbyte = (i < rhs.capacity) ? rhs.array[i] : 0;
        if (lbyte != rbyte) return false;
        else if (lbyte) both_zero = false;
        ++i;
    }
    if (!both_zero && (lhs.is_negative != rhs.is_negative)) return false;
    
    return true;
}

bool bigint::operator != (const bigint& rhs) const {
    return !this->operator==(rhs);
}

bool bigint::operator < (const bigint& rhs) const {
    const bigint& lhs = *this;

    if (lhs.is_negative) {
        return -lhs > -rhs;
    }

    if (rhs.is_negative) return false;

    size_t i = (lhs.capacity > rhs.capacity) ? lhs.capacity : rhs.capacity;
    while (i-- > 0) {
        const byte lbyte = (i < lhs.capacity) ? lhs.array[i] : 0;
        const byte rbyte = (i < rhs.capacity) ? rhs.array[i] : 0;
        if (lbyte < rbyte) return true;
        else if (lbyte > rbyte) return false;
    }
    return false;
}

bool bigint::operator > (const bigint& rhs) const {
    const bigint& lhs = *this;

    if (lhs.is_negative) {
        return -lhs < -rhs;
    }

    size_t i = (lhs.capacity > rhs.capacity) ? lhs.capacity : rhs.capacity;
    while (i-- > 0) {
        const byte lbyte = (i < lhs.capacity) ? lhs.array[i] : 0;
        const byte rbyte = (i < rhs.capacity) ? rhs.array[i] : 0;
        if (rhs.is_negative) {
            if (lbyte || rbyte) return true;
        } else {
            if (lbyte > rbyte) return true;
            else if (lbyte < rbyte) return false;
        }
    }
    return false;
}

bool bigint::operator <= (const bigint& rhs) const {
    return !this->operator>(rhs);
}

bool bigint::operator >= (const bigint& rhs) const {
    return !this->operator<(rhs);
}

// MARK: Binary Arithmetic Operators

bigint bigint::operator + (const bigint& rhs) const {
    const bigint& lhs = *this;

    if (lhs.is_negative != rhs.is_negative) {
        return lhs - (-rhs);
    }

    bigint result;
    result.is_negative = lhs.is_negative;

    bool carry = false;
    size_t i = 0;
    while (i < lhs.capacity || i < rhs.capacity) {
        const byte lbyte = (i < lhs.capacity) ? lhs.array[i] : 0;
        const byte rbyte = (i < rhs.capacity) ? rhs.array[i] : 0;
        if (i == result.capacity) result.grow();
        result.array[i] = lbyte + rbyte + (carry ? 1 : 0);
        carry = (!carry && lbyte > (rbyte ^ 0xFF)) || (carry && lbyte >= (rbyte ^ 0xFF));
        ++i;
    }
    if (carry) {
        if (i == result.capacity) result.grow();
        result.array[i] = 0x01;
    }

    return result;
}

bigint bigint::operator - (const bigint& rhs) const {
    const bigint& lhs = *this;

    if (lhs.is_negative != rhs.is_negative) {
        return lhs + (-rhs);
    }

    bool right_greater = (rhs > lhs);
    bool right_larger = right_greater != rhs.is_negative;
    const bigint& larger = right_larger ? rhs : lhs;
    const bigint& smaller = right_larger ? lhs : rhs;

    bigint result;
    result.is_negative = right_greater;

    size_t i = 0;
    bool borrow = false;
    while (i < larger.capacity || i < smaller.capacity) {
        const byte lbyte = (i < larger.capacity) ? larger.array[i] : 0;
        const byte sbyte = (i < smaller.capacity) ? smaller.array[i] : 0;
        if (i == result.capacity) result.grow();
        result.array[i] = lbyte - sbyte - (borrow ? 1 : 0);
        borrow = (!borrow && sbyte > lbyte) || (borrow && sbyte >= lbyte);
        ++i;
    }

    return result;
}

bigint bigint::operator * (const bigint& rhs) const {
    const bigint& lhs = *this;

    bigint result;
    for (size_t i = 0; i < lhs.capacity; i++) {
        bigint line;
        while (line.capacity < i) line.grow();
        dbyte lbyte = lhs.array[i];
        dbyte carry = 0;  // carry & lbyte are really only bytes, but this avoids unnecessary conversions
        for (size_t j = 0; j < rhs.capacity; j++) {
            dbyte prod = lbyte * static_cast<dbyte>(rhs.array[j]) + carry;
            if (line.capacity == i + j) line.grow();
            line.array[i + j] = prod & 0xFF;
            carry = prod >> 8;
        }
        if (carry) {
            if (line.capacity == i + rhs.capacity) line.grow();
            line.array[i + rhs.capacity] = carry;
        }
        result += line;
    }
    result.is_negative = lhs.is_negative != rhs.is_negative;
    result.trim();
    return result;
}

bigint bigint::operator / (const bigint& rhs) const {
    const bigint& lhs = *this;
    bigint rhs_trim = rhs;
    rhs_trim.trim();

    if (!rhs_trim.capacity) throw std::invalid_argument("Divide by zero error.");

    bigint result;
    size_t nb = lhs.num_bytes();
    while(result.capacity < nb) result.grow();

    bigint diff;
    for (size_t i = nb; i-- > 0; ) {
        diff <<= 8;
        diff |= lhs.array[i];
        byte count = 0;
        while (diff >= rhs_trim) {
            diff -= rhs_trim;
            ++count;
        }
        result.array[i] = count;
    }
    result.is_negative = lhs.is_negative != rhs.is_negative;
    return result;
}

bigint bigint::operator % (const bigint& rhs) const {
    const bigint& lhs = *this;
    bigint rhs_trim = rhs;
    rhs_trim.trim();

    if (!rhs_trim.capacity) throw std::invalid_argument("Divide by zero error.");

    bigint result;
    size_t nb = lhs.num_bytes();

    for (size_t i = nb; i-- > 0; ) {
        result <<= 8;
        result |= lhs.array[i];
        while (result >= rhs_trim) {
            result -= rhs_trim;
        }
    }
    result.is_negative = lhs.is_negative;
    result.trim();
    return result;
}

// MARK: Arithmetic Assignment Operators

bigint& bigint::operator += (const bigint& other) {
    if (is_negative != other.is_negative) {
        this->operator-=(-other);
        return *this;
    }

    bool carry = false;
    size_t i = 0;
    while (i < capacity || i < other.capacity) {
        const byte tbyte = (i < capacity) ? array[i] : 0;
        const byte obyte = (i < other.capacity) ? other.array[i] : 0;
        if (i == capacity) grow();
        array[i] = tbyte + obyte + (carry ? 1 : 0);
        carry = (!carry && tbyte > (obyte ^ 0xFF)) || (carry && tbyte >= (obyte ^ 0xFF));
        ++i;
    }
    if (carry) {
        if (i == capacity) grow();
        array[i] = 0x01;
    }

    return *this;
}

bigint& bigint::operator -= (const bigint& other) {
    if (is_negative != other.is_negative) {
        return this->operator+=(-other);
    }

    bool right_greater = (other > *this);
    bool right_larger = right_greater != other.is_negative;
    const bigint& larger = right_larger ? other : *this;
    const bigint& smaller = right_larger ? *this : other;

    is_negative = right_greater;

    size_t i = 0;
    bool borrow = false;
    while (i < larger.capacity || i < smaller.capacity) {
        const byte lbyte = (i < larger.capacity) ? larger.array[i] : 0;
        const byte sbyte = (i < smaller.capacity) ? smaller.array[i] : 0;
        if (i == capacity) grow();
        array[i] = lbyte - sbyte - (borrow ? 1 : 0);
        borrow = (!borrow && sbyte > lbyte) || (borrow && sbyte >= lbyte);
        ++i;
    }

    return *this;
}

bigint& bigint::operator *= (const bigint& other) {
    return this->operator=(std::move(this->operator*(other)));
}

bigint& bigint::operator /= (const bigint& other) {
    return this->operator=(std::move(this->operator/(other)));
}

bigint& bigint::operator %= (const bigint& other) {
    return this->operator=(std::move(this->operator%(other)));
}

// MARK: Binary Bitwise Operators

bigint bigint::operator & (const bigint& rhs) const {
    const bigint& lhs = *this;

    bigint result;
    size_t i = 0;
    while (i < lhs.capacity && i < rhs.capacity) {
        if (i == result.capacity) result.grow();
        result.array[i] = lhs.array[i] & rhs.array[i];
        ++i;
    }
    return result;
}

bigint bigint::operator | (const bigint& rhs) const {
    const bigint& lhs = *this;

    bigint result;
    size_t i = 0;
    while (i < lhs.capacity || i < rhs.capacity) {
        const byte lbyte = (i < lhs.capacity) ? lhs.array[i] : 0;
        const byte rbyte = (i < rhs.capacity) ? rhs.array[i] : 0;
        if (i == result.capacity) result.grow();
        result.array[i] = lbyte | rbyte;
        ++i;
    }
    return result;
}

bigint bigint::operator ^ (const bigint& rhs) const {
    const bigint& lhs = *this;

    bigint result;
    size_t i = 0;
    while (i < lhs.capacity || i < rhs.capacity) {
        const byte lbyte = (i < lhs.capacity) ? lhs.array[i] : 0;
        const byte rbyte = (i < rhs.capacity) ? rhs.array[i] : 0;
        if (i == result.capacity) result.grow();
        result.array[i] = lbyte ^ rbyte;
        ++i;
    }
    return result;
}

bigint bigint::operator << (size_t rhs) const {
    const bigint& lhs = *this;

    size_t nb = lhs.num_bytes();
    if (nb == 0) return zero;

    bigint result;    
    byte shamt = rhs % 8;
    size_t offset = rhs / 8;
    byte extra = lhs.array[nb - 1] >> (8 - shamt);

    while (result.capacity < nb + offset + (extra ? 1 : 0)) {
        if (result.capacity > std::numeric_limits<size_t>().max() / 2) throw std::overflow_error("Logical shift error: shift too large.");
        else result.grow();
    }

    for (size_t i = nb; i-- > 0; ) {
        if (lhs.array[i] >> (8 - shamt)) result.array[i + offset + 1] |= lhs.array[i] >> (8 - shamt);
        result.array[i + offset] |= lhs.array[i] << shamt;
    }

    return result;
}

bigint bigint::operator >> (size_t rhs) const {
    const bigint & lhs = *this;
    
    size_t nb = lhs.num_bytes();
    byte shamt = rhs % 8;
    size_t offset = rhs / 8;
    if (offset > nb) return zero;

    bigint result;
    byte extra = lhs.array[nb - 1] >> shamt;

    while (result.capacity < nb - offset - (extra ? 0 : 1)) result.grow();
    
    for (size_t i = offset; i < nb; i++) {
        if (lhs.array[i] >> shamt) result.array[i - offset] |= lhs.array[i] >> shamt;
        if (i < nb - 1) result.array[i - offset] |= lhs.array[i + 1] << (8 - shamt);
    }

    return result;
}

// MARK: Bitwise Assignment Operators

bigint& bigint::operator &= (const bigint& other) {
    size_t i = 0;
    while (i < capacity && i < other.capacity) {
        array[i] = array[i] & other.array[i];
        ++i;
    }
    while (i < capacity) {
        array[i] = 0;
        ++i;
    }
    return *this;
}

bigint& bigint::operator |= (const bigint& other) {
    size_t i = 0;
    while (i < capacity || i < other.capacity) {
        const byte lbyte = (i < capacity) ? array[i] : 0;
        const byte rbyte = (i < other.capacity) ? other.array[i] : 0;
        if (i == capacity) grow();
        array[i] = lbyte | rbyte;
        ++i;
    }
    return *this;
}

bigint& bigint::operator ^= (const bigint& other) {
    size_t i = 0;
    while (i < capacity || i < other.capacity) {
        const byte lbyte = (i < capacity) ? array[i] : 0;
        const byte rbyte = (i < other.capacity) ? other.array[i] : 0;
        if (i == capacity) grow();
        array[i] = lbyte ^ rbyte;
        ++i;
    }
    return *this;
}

bigint& bigint::operator <<= (size_t other) {
    return this->operator=(std::move(this->operator<<(other)));
}

bigint& bigint::operator >>= (size_t other) {
    return this->operator=(std::move(this->operator>>(other)));
}

// MARK: std::string Conversion

std::string bigint::to_string() const {
    bigint cpy = *this;
    cpy.is_negative = false;

    std::string result_rev;
    const bigint base = 10;
    do {
        char digit = cpy % base;
        digit += 48;
        result_rev.push_back(digit);
        cpy /= base;
    } while (cpy != zero);
    if (is_negative && cpy != zero) result_rev.push_back('-');

    std::string result;
    for (auto it = result_rev.end(); it-- != result_rev.begin(); ) {
        result.push_back(*it);
    }
    return result;
}

std::string bigint::to_hex(bool print_leading_zeros) const {
    std::string result = is_negative ? "-0x" : "0x";
    const char hex_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    bool started = false;
    for (size_t i = capacity; i-- > 0; ) {
        if (array[i] >> 4) started = true;
        if (started || print_leading_zeros) result.push_back(hex_table[array[i] >> 4]);
        if (array[i] & 0xF) started = true;
        if (started || print_leading_zeros) result.push_back(hex_table[array[i] & 0xF]);
    }
    if (result.back() == 'x') result.push_back('0');

    return result;
}

std::string bigint::to_bin(bool print_leading_zeros) const {
    std::string result = is_negative ? "-" : "";

    bool started = false;
    for (size_t i = capacity; i-- > 0; ) {
        for (unsigned int j = 8; j-- > 0; ) {
            bool is_on = (array[i] >> j) & 0x1;
            if (is_on) started = true;
            if (started || print_leading_zeros) result.push_back(is_on ? '1' : '0');
        }
    }

    if (result.empty() || result.back() == '-') result.push_back('0');
    return result;
}

// MARK: Static Functions

bigint bigint::pow(const bigint& base, const bigint& exp) {
    if (exp < 0) return zero;

    bigint b = base;
    bigint e = exp;
    bigint result = 1;
    while (e > 0) {
        unsigned char byte = e & bigint(0xFFu);
        for (int i = 0; i < 8; i++) {
            bool is_on = byte & (1 << i);
            if (is_on) result *= b;
            b *= b;
        }
        e >>= 8;
    }
    return result;
}

bigint bigint::factorial(const bigint& n) {
    if (n < 0) throw std::invalid_argument("Cannot take factorial of negative number.");

    bigint result = 1;
    for (bigint i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// MARK: Non-Class Functions

std::ostream& operator << (std::ostream& os, const bigint& num) {
    return os << num.to_string();
}

std::istream& operator >> (std::istream& is, bigint& num) {
    std::string input;
    is >> input;
    try {
        num = stobi(input, nullptr, 10);
    } catch (const std::invalid_argument& err) {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}

bigint stobi(const std::string& str, size_t* pos, int base) {
    auto it = str.begin();
    while (it != str.end() && std::isspace(*it)) ++it;

    bigint result;
    bool negative = false;
    if (it != str.end() && *it == '-') {
        negative = true;
        ++it;
    } else if (it != str.end() && *it == '+') {
        ++it;
    }

    bool number = false;

    while (it != str.end()) {
        int digit;
        if (*it == '0') {
            if (!number) {
                number = true;
                ++it;
                if (it != str.end()) {
                    if (*it == 'x') {
                        if (base == 0) base = 16;
                        if (base == 16) {
                            ++it;
                            continue;
                        } else break;
                    } else {
                        if (base == 0) base = 8;
                        continue;
                    }
                } else break;
            } else digit = 0;
        } else if (*it >= '1' && *it <= '9') digit = *it - '0';
        else if (*it >= 'A' && *it <= 'Z') digit = *it - 'A' + 10;
        else if (*it >= 'a' && *it <= 'z') digit = *it - 'a' + 10;
        else break;
        if (digit >= base) break;

        if (!number) {
            if (base == 0) base = 10;
            number = true;
        }
        result *= base;
        result += digit;
        ++it;
    }
    if (!number) throw std::invalid_argument("std::string did not contain a number.");
    if (pos) *pos = it - str.begin();
    if (negative) result = -result;
    return result;
}