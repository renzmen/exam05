#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <sstream>

class bigint {
    public:
    bigint();
    bigint(unsigned int n);
    ~bigint();
    bigint(const bigint& other);
    bigint &operator=(const bigint& other);

    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>=(const bigint& other) const;
    bool operator<=(const bigint& other) const;

    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);
    bigint& operator++(void);
    bigint operator++(int);
    bigint operator<<(unsigned int n) const;
    bigint& operator>>=(const bigint& other);
    bigint& operator<<=(unsigned int n);

    std::string getValue() const;
    static void normalize(std::string &s);

    private:
        std::string s;
};

std::ostream& operator<<(std::ostream& oss, const bigint& other);

#endif
