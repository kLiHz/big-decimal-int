#include "BigInt.hpp"
#include <unordered_map>

class QueryFactorials {
    std::unordered_map<int, MyInt> nums;
    int last_n = 0;

public:
    QueryFactorials() {
        nums[0] = 1;
        nums[1] = 1;
    }
    auto get_fact_of(int n) {
        if (n > last_n) {
            auto a = nums[last_n];
            for (int i = last_n + 1; i <= n; i++) {
                a *= i;
                nums[i] = a;
            }
            last_n = n;
            return a;
        } else {
            return nums[n];
        }
    }
};

int main() {
    int t, n;
    QueryFactorials inst;
    std::cin >> t;
    while (t > 0) {
        std::cin >> n;
        auto v = inst.get_fact_of(n);
        std::cout << v << std::endl;
        std::cout << v.mem() << "Bytes.\n";
        std::cout << "Size: " << v.size() << "\n";
        v.shrink();
        std::cout << v.mem() << "Bytes.\n";
        std::cout << "Size: " << v.size() << "\n";
        --t;
    }
}

auto fact(int n) {
    MyInt a = 1;
    for (int i = 1; i <= n; i++) {
        a *= i;
    }
    return a;
}
