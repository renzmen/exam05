#ifndef VECT2_HPP
#define VECT2_HPP


#include <string>
#include <iostream>


class vect2 {
    private :
        int x;
        int y;
    public:
        vect2();
        vect2(int a,int b);
        ~vect2();
        vect2(const vect2& other);
        vect2 &operator=(const vect2& other);


        int& operator[](int a);
        const int& operator[](int a) const;
        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const;


        vect2 operator+(const vect2& other) const;
        vect2 operator-(const vect2& other) const;
        vect2 operator*(int scalar) const;
        vect2& operator+=(const vect2& other);
        vect2& operator-=(const vect2& other);
        vect2& operator*=(int scalar);


        vect2 &operator++(void);
        vect2 operator++(int);
        vect2 &operator--(void);
        vect2 operator--(int);


        vect2 operator-() const;


        int get_x() const;
        int get_y() const;
};


std::ostream& operator<<(std::ostream& oss, const vect2& v);


vect2 operator*(int scalar,const vect2& v);




#endif
