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
using VS = vector<string>;
using VB = vector<bool>;
using AI2 = array<int, 2>;
using AI3 = array<int, 3>;

AI2 operator+(AI2 x, AI2 y)
{
    return AI2{x[0] + y[0], x[1] + y[1]};
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
void operator+=(AI2& x, AI2 y)
{
    x[0] += y[0];
    x[1] += y[1];
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

template <class T, class U>
bool findable(const T& m, const U& v)
{
    return m.find(v) != m.end();
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