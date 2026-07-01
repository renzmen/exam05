#include "bigint.hpp"
#include <iostream>


int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);


    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;


    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;


    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;


    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;


    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;


    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;

  // Test overflow dello shift (creiamo un numero gigante tramite lo shift)
    bigint enorme(10);
    bigint shift_gigante(9999);
    shift_gigante <<= 20; // Ora shift_gigante è un numero enorme con tantissimi zeri!
    
    std::cout << "Test shift estremo: " << (enorme >> shift_gigante) << std::endl;
}
