#include "vect2.hpp"


vect2::vect2() : x(0), y(0) {}


vect2::vect2(int a,int b) : x(a), y(b) {}


vect2::~vect2() {}


vect2::vect2(const vect2& other) {
    x = other.x;
    y = other.y;
}


vect2 &vect2::operator=(const vect2& other) {
    if(this != &other){
        x = other.x;
        y = other.y;
    }
    return *this;
}


int vect2::get_x() const {
    return x;
}


int vect2::get_y() const {
    return y;
}


int& vect2::operator[](int a) {
    return (a == 0) ? x : y;
}


const int& vect2::operator[](int a) const{
    return (a == 0) ? x : y;
}


bool vect2::operator==(const vect2& other) const{
    return (x == other.x && y == other.y);
}
       
bool vect2::operator!=(const vect2& other) const{
    return (!(*this == other));
}


vect2 vect2::operator+(const vect2& other) const{
    return vect2(x + other.x, y + other.y);
}


vect2 vect2::operator-(const vect2& other) const{
    return vect2(x - other.x, y - other.y);
}


vect2 vect2::operator*(int scalar) const{
    return vect2(x * scalar, y * scalar);
}


vect2& vect2::operator+=(const vect2& other) {
    x = x + other.x;
    y = y + other.y;
    return *this;
}
  
vect2& vect2::operator-=(const vect2& other) {
    x = x - other.x;
    y = y - other.y;
    return *this;
}


vect2& vect2::operator*=(int scalar){
    x = x * scalar;
    y = y * scalar;
    return *this;
}


vect2& vect2::operator++(void) {
    x += 1;
    y += 1;
    return *this; 
}


vect2 vect2::operator++(int) {
    vect2 tmp(*this);
    x += 1;
    y += 1;
    return tmp; 
}


vect2 vect2::operator--(int) {
    vect2 tmp(*this);
    x -= 1;
    y -= 1;
    return tmp;
}


vect2& vect2::operator--(void) {
    x -= 1;
    y -= 1;
    return *this;
}


vect2 vect2::operator-() const {
    return vect2(-x,-y);
}


std::ostream& operator<<(std::ostream& oss, const vect2& v) {
    oss << "{" << v.get_x() << ", " << v.get_y() << "}";
    return oss;
}


vect2 operator*(int scalar,const vect2& v) {
    return vect2(v.get_x() * scalar, v.get_y() * scalar);
}
