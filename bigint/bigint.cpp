#include "bigint.hpp"

bigint::bigint() : s("0") {}

bigint::bigint(unsigned int n) {
    std::ostringstream oss;
    oss << n;
    s = oss.str();
}

bigint::bigint(const bigint& other) {
    s = other.s;
}

bigint &bigint::operator=(const bigint& other) {
    if(this != &other)
        s = other.s;
    return *this;
}

bigint::~bigint() {}

void bigint::normalize(std::string &s) {
    size_t pos = s.find_first_not_of("0");
    if(pos == std::string::npos)
        s = "0";
    else
        s = s.erase(0,pos);
}

bool bigint::operator==(const bigint& other) const{
    std::string a = s;
    std::string b = other.s;
    normalize(a);
    normalize(b);
    return a == b;
}

bool bigint::operator!=(const bigint& other)const {
    return !(*this == other);
}

bool bigint::operator>(const bigint& other) const{
    std::string a = s;
    std::string b = other.s;
    normalize(a);
    normalize(b);
    if(a.length() != b.length())
        return a.length() > b.length();
    return a > b;
}

bool bigint::operator<(const bigint& other) const{
    std::string a = s;
    std::string b = other.s;
    normalize(a);
    normalize(b);
    if(a.length() != b.length())
        return a.length() < b.length();
    return a < b;
}

bool bigint::operator>=(const bigint& other) const{
    return (*this > other || *this == other);
}

bool bigint::operator<=(const bigint& other) const{
    return (*this < other || *this == other);
}

bigint bigint::operator+(const bigint& other) const {
    std::string a = s;
    std::string b = other.s;
    while(a.length() < b.length())
        a = "0" + a; 
    while(b.length() < a.length())
        b = "0" + b;
    int carry = 0;
    std::string result;
    for(int i = a.length() - 1;i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result = char((sum % 10) + '0') + result;
        carry = sum / 10;
    }
    if (carry > 0)
        result = "1" + result;
    bigint res;
    normalize(result);
    res.s = result;
    return res;
}

bigint& bigint::operator+=(const bigint& other) {
   *this = *this + other;
   return *this;
}

bigint& bigint::operator++(void) {
    *this = *this + bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint tmp(*this);
    *this = *this + bigint(1);
    return tmp;
}

bigint bigint::operator<<(unsigned int n) const{
    bigint res(*this);
    for(unsigned int i = 0; i < n; i++)
        res.s = res.s + "0";
    normalize(res.s);
    return res;
}

bigint& bigint::operator<<=(unsigned int n){
    for(unsigned int i = 0; i < n; i++)
        s = s + "0";
    normalize(s);
    return *this;
}

bigint bigint::operator>>(const bigint& other) const {
    bigint res(*this);
    res >>= other;
    return res;
}

bigint &bigint::operator>>=(const bigint &other)
{
    std::string shift_str = other.s;
    normalize(shift_str);

    // Se la stringa dello shift ha più di 10 cifre supererà il valore 
    // massimo int/lunghezza stringa, quindi impostiamo a "0" per sicurezza
    if (shift_str.length() > 10) {
        s = "0";
        return *this;
    }

    // ➡️ OTTIMIZZAZIONE: Usato 'unsigned long' al posto di 'unsigned long long' per una compatibilità C++98 impeccabile
    unsigned long shift = 0;
    for (size_t i = 0; i < shift_str.length(); i++) {
        shift = shift * 10 + (shift_str[i] - '0');
    }

    if (shift >= s.length())
        s = "0";
    else
        s = s.substr(0, s.length() - shift);

    normalize(s);
    return *this;
}

std::string bigint::getValue() const{
    return s;
}

std::ostream& operator<<(std::ostream& oss, const bigint& other) {
    std::string value = other.getValue();
    bigint::normalize(value);
    oss << value;
    return oss;
}