#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define BE(X) std::begin(X), std::end(X)
#define FOR(VAR, FROM, OP_TO) for (auto VAR = (FROM); VAR OP_TO; ++(VAR))
#define FORBACK(VAR, FROM, OP_TO) for (auto VAR = (FROM); VAR OP_TO; --(VAR))
#define FORBE(VAR, X) for (auto VAR = begin(X); (VAR) != end(X); ++(VAR))
#define PB push_back
#define EB emplace_back
#define PF printf
#define FST first
#define SND second

template <class T>
int operator~(const T& x)
{
    return (int)x.size();
}
template <class C>
void sort_unique_trunc(C& x)
{
    sort(BE(x));
    x.erase(unique(BE(x)), x.end());
}

using PII = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VF = vector<float>;
using VS = vector<string>;
using VB = vector<bool>;
using AI2 = array<int, 2>;
using AI3 = array<int, 3>;
template <class T>
using maybe = optional<T>;

AI2 operator+(AI2 x, AI2 y)
{
    return AI2{x[0] + y[0], x[1] + y[1]};
}
void operator+=(AI2& x, AI2 y)
{
    x[0] += y[0];
    x[1] += y[1];
}

int as_int(int64_t x)
{
    assert(INT_MIN <= x && x <= INT_MAX);
    return (int)x;
}
int manhattan(AI2 a, AI2 b)
{
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

using VI64 = vector<int64_t>;
using i64 = int64_t;

VI64 to_vi64(const string& s)
{
    VI64 r;
    for (auto c : s) {
        r.push_back(c);
    }
    return r;
}

string to_string(const VI64& x)
{
    string s;
    for (auto i : x) {
        s += (char)i;
    }
    return s;
}

int diff(pair<int, int> pp)
{
    return pp.second - pp.first;
}

void print(const VI64 outputs)
{
    for (auto c : outputs) {
        printf("%c", (char)c);
    }
}

VS read_lines(ifstream& f)
{
    VS lines;
    for (string line; getline(f, line);) {
        lines.emplace_back(move(line));
    }
    if (!lines.empty() && lines.back().empty()) {
        lines.pop_back();
    }
    return lines;
}

// findable containers (maps): find != end
template <class T, class U>
bool contains(const T& m, const U& v)
{
    return m.find(v) != m.end();
}

// linear find between iterators: find != last
template <class T, class U>
bool contains(T first, T last, const U& v)
{
    return find(first, last, v) != last;
}

template <class T, class U>
auto try_find_v(const T& m, const U& v) -> maybe<const typename T::mapped_type&>
{
    auto it = m.find(v);
    if (it != m.end()) {
        return it->second;
    }
    return {};
}

template <class T, class U>
auto try_find_v(T& m, const U& v) -> maybe<typename T::mapped_type&>
{
    auto it = m.find(v);
    if (it != m.end()) {
        return it->second;
    }
    return {};
}

template <class T, class U>
void must_insert(T& m, U&& value)
{
    auto itb = m.insert(forward<U>(value));
    assert(itb.second);
}

map<int64_t, int> prime_factors(int64_t p)
{
    map<int64_t, int> factors;
    for (int64_t k = 2; k * k <= p; ++k) {
        for (;;) {
            auto d = p / k;
            if (d * k == p) {
                ++factors[k];
                printf("F %lld\n", k);
                p /= k;
            } else {
                break;
            }
        }
    }
    if (p != 1) {
        printf("F %lld\n", p);
        ++factors[p];
    }
    return factors;
}

bool starts_with(const string& s, const string& t)
{
    if (~s < ~t) {
        return false;
    }
    FOR (i, 0, < ~t) {
        if (s[i] != t[i]) {
            return false;
        }
    }
    return true;
}

bool starts_with(const string& s, const char* t)
{
    auto ls = ~s;
    for (int i = 0;; ++i) {
        auto tc = t[i];
        if (tc == 0) {
            return true;
        }
        if (i >= ls || s[i] != tc) {
            return false;
        }
    }
}

string trim(string s)
{
    int i = 0;
    while (i < ~s && iswspace(s[i])) {
        ++i;
    }
    int j = ~s;
    while (j <= ~s && i < j && iswspace(s[j - 1])) {
        --j;
    }
    return s.substr(i, j - i);
}

// Multiple seperators count as one.
// In other words, doesn't return empty tokens.
VS split(const string& s, const char* separators)
{
    vector<char> input(~s + 1);
    copy(BE(s), input.begin());
    input[~s] = 0;
    char* token = std::strtok(input.data(), separators);
    VS r;
    while (token) {
        r.push_back(token);
        token = std::strtok(nullptr, separators);
    }
    return r;
}

void common_test()
{
    FOR (i, 0, < 4) {
        FOR (j, 0, < 4) {
            FOR (k, 0, < 4) {
                auto si = string(i, ' ');
                auto sj = string(j, 'a');
                auto sk = string(k, ' ');
                assert(trim(si + sj + sk) == sj);
            }
        }
    }
}

template <class T>
struct RunningStat
{
    optional<T> lower, upper;
    int count = 0;
    void add(T x)
    {
        if (++count == 1) {
            lower = x;
            upper = x;
        } else {
            if (x < *lower) {
                lower = x;
            } else if (*upper < x) {
                upper = x;
            }
        }
    }
};

template <class Iterator>
auto sum(Iterator b, Iterator e)
{
    using value_t = decay_t<decltype(*b)>;
    return accumulate(b, e, (value_t)0);
}

template <class Iterator>
auto product(Iterator b, Iterator e)
{
    using value_t = decay_t<decltype(*b)>;
    return accumulate(b, e, (value_t)1, multiplies<value_t>());
}

template <class Iterator>
auto diff(Iterator b, Iterator e)
{
    assert(b != e);
    auto bb = b;
    ++bb;
    assert(bb != e);
    using value_t = decay_t<decltype(*b)>;
    vector<value_t> r;
    r.reserve(max<ptrdiff_t>(e - b, 0));
    for (; bb != e; ++b, ++bb) {
        r.PB(*bb - *b);
    }
    return r;
}

template <class Iterator>
string to_string(Iterator b, Iterator e)
{
    string s;
    bool first = true;
    for (; b != e; ++b) {
        if (first) {
            first = false;
        } else {
            s += ' ';
        }
        s += to_string(*b);
    }
    return s;
}