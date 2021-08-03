#include "BigInt.hpp"

auto factorial_sum(int n) {
    MyInt result = 1, a = 1;
    for (int i = 2; i <= n; i++) {
        a *= i;
        result += a;
    }
    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << factorial_sum(n);
}
