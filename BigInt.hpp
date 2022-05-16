#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <numeric>
#include <limits>
#include <algorithm>

template<typename T>
class BigDecimalInt {
    // base/radix: 10
    
    using lli = long long int;
    using uint = unsigned int;

private:
    static constexpr uint N = std::numeric_limits<T>().digits10 - 1;
    static constexpr lli ipow(uint base, uint expo) {
        return expo == 0 ? 1 : base * ipow(base, expo - 1);
    }
    static constexpr lli MOD = ipow(10, N);
    std::vector<T> data;

    BigDecimalInt(std::vector<T> data_) : data(data_) {}
public:
    BigDecimalInt() : data({0}) {}

    BigDecimalInt(lli a) {
        if (a == 0) {
            data.push_back(0);
        } else {
            bool negative = a < 0;
            a = std::abs(a);
            while (a != 0) {
                data.push_back(a % MOD);
                a /= MOD;
            }
            if (negative) {
                *this = -(*this);
            }
        }
    }

    BigDecimalInt(std::string s) {
        bool negative = false;
        if (s.at(0) == '-') {
            s.erase(0, 1);
            negative = true;
        }
        while (s.length() > N) {
            auto val = s.substr(s.length() - N);
            data.push_back(std::stoi(val));
            s.erase(s.length() - N, N);
        }
        data.push_back(std::stoi(s));
        if (negative) (*this) = -(*this);
    }

    BigDecimalInt(const BigDecimalInt & i) : data(i.data) {}

    BigDecimalInt(BigDecimalInt && i) : data(std::move(i.data)) { i.data = {0}; }
    
    BigDecimalInt & operator=(const BigDecimalInt & i) {
        this->data = i.data;
        return *this;
    }

    BigDecimalInt & operator=(BigDecimalInt && i) {
        this->data = std::move(i.data);
        i.data = {0};
        return *this;
    }

    bool operator<(BigDecimalInt const & other) const {
        auto x = rbegin(this->data);
        auto y = rbegin(other.data);
        if (this->data.size() == other.data.size()) {
            while (x != rend(this->data) && y != rend(other.data)) {
                if (*x != *y) return (*x) < (*y);
                ++x;
                ++y;
            }
            return false;
        } else {
            bool same_sign = (*x) * (*y) > 0;
            if (same_sign) {
                return this->data.size() < other.data.size();
            } else {
                return (*x) < (*y);
            }
        }
    }

    bool operator>=(BigDecimalInt const & other) const {
        return !(*this < other);
    }

    bool operator==(BigDecimalInt const & other) const {
        auto x = rbegin(this->data);
        auto y = rbegin(other.data);
        if (this->data.size() == other.data.size()) {
            while (x != rend(this->data) && y != rend(other.data)) {
                if (*x != *y) return false;
                ++x;
                ++y;
            }
            return true;
        } else { return false; }
    }

    bool operator>(BigDecimalInt const & other) const {
        return !((*this) == other) && !((*this) < other);
    }

    BigDecimalInt & operator+=(BigDecimalInt const & other) {
        auto v = BigDecimalInt(*this) + other;
        *this = std::move(v);
        return *this;
    }

    BigDecimalInt & operator-=(BigDecimalInt const & other) {
        auto v = BigDecimalInt(*this) - other;
        *this = std::move(v);
        return *this;
    }

    BigDecimalInt operator+(BigDecimalInt const & other) const {
        auto x = begin(this->data);
        auto y = begin(other.data);
        std::vector<T> new_data;
        lli carry = 0;
        while (x != end(this->data) || y != end(other.data)) {
            auto t = carry;
            if (x != end(this->data)) { t += *x; ++x; }
            if (y != end(other.data)) { t += *y; ++y; }
            new_data.push_back(t % MOD);
            carry = t / MOD;
        }
        if (carry > 0) new_data.push_back(carry);
        while (new_data.size() > 1 && *(rbegin(new_data)) == 0) new_data.pop_back();
        return {new_data};
    }

    BigDecimalInt operator-(BigDecimalInt const & other) const {
        return BigDecimalInt(*this) + (-other);
    }

    BigDecimalInt operator-() const {
        std::vector<T> new_data;
        T carry = 0;
        T t = 0;
        for (auto i = begin(data); i != end(data); ++i) {
            t = (MOD - *i + carry);
            t %= MOD;
            new_data.push_back(t);
            carry = -1;
        }
        while (new_data.size() > 1 && *(rbegin(new_data)) == 0) new_data.pop_back();
        if (t != 0) new_data.push_back(-1); // from positive to negative
        return {new_data};
    }

    BigDecimalInt operator*(long long int val) const {
        // bool same_sign = ((val < 0) == ((*this) < 0));
        if ((*this) < 0) {
            return val < 0 ? (-(*this)) * - val : - ((-(*this)) * val);
        } else {
            if (val < 0) {
                return -((*this) * (-val));
            } else { // val > 0, this > 0
                std::vector<T> new_data;
                lli carry = 0;
                for (auto i : this->data) {
                    carry += static_cast<lli>(i) * val;
                    new_data.push_back(carry % MOD);
                    carry /= MOD;
                }
                while (carry > 0) {
                    new_data.push_back(carry % MOD);
                    carry /= MOD;
                }
                return {new_data};
            }
        }
    }

    BigDecimalInt operator*=(int val) {
        auto t = BigDecimalInt(*this) * val;
        *this = std::move(t);
        return *this;
    }

    BigDecimalInt operator/(int val) const {
        if ((*this) < 0) {
            return val < 0 ? (-(*this)) / - val : - ((-(*this)) / val);
        } else {
            if (val < 0) {
                return -((*this) / (-val));
            } else { // val > 0, this > 0
                std::vector<T> new_data;
                auto i = rbegin(this->data);
                lli t = 0;
                while (i != rend(this->data)) {
                    t *= MOD;
                    t += *i;
                    new_data.push_back(t/val);
                    t %= val;
                    i++;
                }
                auto p = new_data.begin();
                while (*p == 0) ++p;
                
                std::reverse(p, new_data.end());
                return {std::vector<T>(p, new_data.end())};
            }
        }
    }
    
    friend std::string to_string(BigDecimalInt const& i) {
        std::string s;
        BigDecimalInt a;
        if (i < 0) {
            s.push_back('-');
            a = -i;
        } else {
            a = i;
        }
        s.append(std::to_string(*rbegin(a.data)));
        return std::accumulate(rbegin(a.data) + 1, rend(a.data), s,
            [](std::string & t, T val) {
                auto part = std::to_string(val);
                part.insert(begin(part), N-part.length(), '0');
                return std::move(t) + part;
        });
    }

    friend std::ostream & operator<< (std::ostream & os, BigDecimalInt const& a) {
        os << to_string(a); return os;
    }

    friend std::istream & operator>> (std::istream & is, BigDecimalInt & a) {
        std::string s;
        is >> s;
        a = BigDecimalInt(s);
        return is;
    }

    auto size() { return data.size(); }
    auto shrink() { data.shrink_to_fit(); }
    auto mem() { return data.capacity() * (std::numeric_limits<T>().digits / 8); } // Bytes
};

using MyInt = BigDecimalInt<int>;
