#include "BigInt.hpp"

void factorial()
{
    MyInt result, a = 1;
    for (int i = 1; i <= 20; i++) {
        a *= i;
        std::cout << i << "! = " << a << std::endl;
        result += a;
    }
    std::cout << "Their sum is " << result;
}

int main() {
    factorial();
}
