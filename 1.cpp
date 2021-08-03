#include "BigInt.hpp"


int main() {
    // MyInt a = 1237590876123467LL, b = 9;
    // std::cout << a << " " << b << "\n";
    // b = a;
    // std::cout << a << " " << b << "\n";
    // MyInt c;
    // c = std::move(a);
    // std::cout << a << " " << b << " " << c;

    // MyInt a = 10, b = -10, c = 0;
    // MyInt a = 761295, b = -761295, c; 
    MyInt a = 1230000000000000LL, b = -3467LL, c = 0;

    std::cout << a << ", " << b << ", " << c << std::endl;
    std::cout << -a << ", " << -b << std::endl;

    std::cout << std::boolalpha;
    // std::cout << "a < b " << (a < b) << "\n";
    // std::cout << "b < a " << (b < a) << "\n";
    // std::cout << "a < c " << (a < c) << "\n";
    // std::cout << "c < a " << (c < a) << "\n";
    // std::cout << "b < c " << (b < c) << "\n";
    // std::cout << "c < b " << (c < b) << "\n";
    std::cout << "a == -(-a) " << (a == -(-a)) << "\n";

    std::cout << a + b << "\t" << a - b << "\n";
    std::cout << b + a << "\t" << b - a << "\n";
    std::cout << MyInt(6666666666) * 333 << "\n"; 
    std::cout << a * 3 << " " << b * 3 << "\n";
    std::cout << a * -3 << " " << b * -3 << "\n";
    std::cout << MyInt(6666666666) / 333 << "\n"; 
    std::cout << a / 3 << " " << b / 3 << "\n";
}
