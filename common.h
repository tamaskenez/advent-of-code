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
#define MKP make_pair

#define CALL(F) ([](auto&& x) { return F(forward<decltype(x)>(x)); })

#define PB push_back
#define EB emplace_back
#define PF printf
#define FST first
#define SND second

template <class T, typename = enable_if_t<is_invocable_v<decltype(std::size<T>), T>>>
int operator~(const T& v)
{
    return (int)size(v);
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

template <class T, class U, size_t N>
auto operator+(const array<T, N>& x, const array<U, N>& y)
{
    using R = decltype(x[0] + y[0]);
    array<R, N> result;
    FOR (i, (size_t)0, < N) {
        result[i] = x[i] + y[i];
    }
    return result;
}

template <class T, class U, size_t N>
auto operator-(const array<T, N>& x, const array<U, N>& y)
{
    using R = decltype(x[0] - y[0]);
    array<R, N> result;
    FOR (i, (size_t)0, < N) {
        result[i] = x[i] - y[i];
    }
    return result;
}

template <class T, size_t N, class U>
auto operator*(const array<T, N>& x, U y)
{
    using R = decltype(x[0] * y);
    array<R, N> r;
    FOR (i, (size_t)0, < N) {
        r[i] = x[i] * y;
    }
    return r;
}

template <class T, size_t N, class U>
auto operator/(const array<T, N>& x, U y)
{
    using R = decltype(x[0] / y);
    array<R, N> r;
    FOR (i, (size_t)0, < N) {
        r[i] = x[i] / y;
    }
    return r;
}

template <class T, class U, size_t N>
void operator+=(array<T, N>& x, const array<U, N>& y)
{
    FOR (i, (size_t)0, < N) {
        x[i] += y[i];
    }
}

template <class T, size_t N>
auto operator-(array<T, N>& x)
{
    array<T, N> result;
    FOR (i, (size_t)0, < N) {
        result[i] = -x[i];
    }
    return result;
}

template <class T, class U, size_t N>
void operator/=(array<T, N>& x, U y)
{
    FOR (i, (size_t)0, < N) {
        x[i] /= y;
    }
}

int as_int(int64_t x)
{
    assert(INT_MIN <= x && x <= INT_MAX);
    return (int)x;
}

template <class T, size_t N>
T manhattan(const array<T, N>& a, const array<T, N>& b)
{
    T s(0);
    FOR (i, (size_t)0, < N) {
        s += abs(a[i] - b[i]);
    }
    return s;
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

bool contains(const char* s, char c)
{
    return strchr(s, c) != nullptr;
}

bool contains(const string& s, char c)
{
    return s.find(c) != string::npos;
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

// Like RunningStat (remembering lower, upper of a number sequence) but also
// remembering a value for each number.
template <class T, class V>
struct RunningStatPair
{
    optional<pair<T, V>> lower, upper;
    int count = 0;
    int lower_count = 0, upper_count = 0;
    void add(T x, const V& v)
    {
        if (++count == 1) {
            lower = make_pair(x, v);
            upper = make_pair(x, v);
        } else {
            if (x < lower->FST) {
                lower = make_pair(x, v);
                lower_count = 1;
            } else {
                if (x == lower->FST) {
                    ++lower_count;
                }
                if (x == upper->FST) {
                    ++upper_count;
                } else if (upper->FST < x) {
                    upper = make_pair(x, v);
                    upper_count = 1;
                }
            }
        }
    }
};

template <class Iterator>
Iterator min_element_pair_second(Iterator b, Iterator e)
{
    if (b == e) {
        return e;
    }
    auto r = b;
    for (++b; b != e; ++b) {
        if (b->SND < r->SND) {
            r = b;
        }
    }
    return r;
}

template <class Iterator>
Iterator max_element_pair_second(Iterator b, Iterator e)
{
    if (b == e) {
        return e;
    }
    auto r = b;
    for (++b; b != e; ++b) {
        if (b->SND > r->SND) {
            r = b;
        }
    }
    return r;
}

template <class Iterator>
pair<Iterator, Iterator> minmax_element_pair_second(Iterator b, Iterator e)
{
    if (b == e) {
        return make_pair(e, e);
    }
    auto r = make_pair(b, b);
    for (++b; b != e; ++b) {
        if (b->SND < r.FST->SND) {
            r.FST = b;
        }
        if (b->SND > r.SND->SND) {
            r.SND = b;
        }
    }
    return r;
}

// map's value_type, which is pair, swapping first and second, into vector.
template <class M>
auto map_to_vector_swapped(const M& m)
{
    using swapped_value_type =
        pair<typename M::value_type::second_type, typename M::value_type::first_type>;
    vector<swapped_value_type> vs;
    vs.reserve(~m);
    for (auto& kv : m) {
        vs.emplace_back(kv.SND, kv.FST);
    }
    return vs;
}

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

#define UNREACHABLE assert(false)

template <class T>
void assert_between_cc(const T& x, T lo, T hi)
{
    (void)x;
    (void)lo;
    (void)hi;
    assert(lo <= x && x <= hi);
}

template <class T>
bool is_between_cc(const T& x, T lo, T hi)
{
    return lo <= x && x <= hi;
}

template <class T>
bool is_between_co(const T& x, T lo, T hi)
{
    return lo <= x && x < hi;
}

template <class T>
void assert_between_co(const T& x, T lo, T hi)
{
    (void)x;
    (void)lo;
    (void)hi;
    assert(lo <= x && x < hi);
}

const array<AI2, 4> DIRS4 = {
    AI2{1, 0},
    AI2{-1, 0},
    AI2{0, 1},
    AI2{0, -1},
};

template <class Ita, class Itb>
auto set_intersection(Ita abeg, Ita aend, Itb bbeg, Itb bend)
{
    using T = decay_t<decltype(*abeg)>;
    vector<T> vs;
    set_intersection(abeg, aend, bbeg, bend, back_inserter(vs));
    return vs;
}

template <class Ita, class Itb>
auto set_difference(Ita abeg, Ita aend, Itb bbeg, Itb bend)
{
    using T = decay_t<decltype(*abeg)>;
    vector<T> vs;
    set_difference(abeg, aend, bbeg, bend, back_inserter(vs));
    return vs;
}

template <class T>
set<T> vector2set(const vector<T>& vs)
{
    return set<T>(BE(vs));
}

template <class It, class Pr>
auto map_to_vec(It b, It e, Pr pr)
{
    using T = decay_t<decltype(pr(*b))>;
    vector<T> vs;
    for (; b != e; ++b) {
        vs.EB(pr(*b));
    }
    return vs;
}

template <class C, class Pr>
auto map_to_vec(const C& c, Pr pr)
{
    using T = decay_t<decltype(pr(*begin(c)))>;
    vector<T> vs;
    vs.reserve(size(c));
    for (auto& x : c) {
        vs.EB(pr(x));
    }
    return vs;
}
template <class T>
bool is_even(T t)
{
    return (t & 1) == 0;
}

template <class T, size_t N>
auto dot_product(const array<T, N>& a, const array<T, N>& b)
{
    return inner_product(BE(a), b.begin(), 0);
}

template <class T>
auto cross_product(const array<T, 3>& a, const array<T, 3>& b)
{
    return array<T, 3>{a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
                       a[0] * b[1] - a[1] * b[0]};
}

template <class T>
T sgn(T x)
{
    if (x < (T)0) {
        return -1;
    }
    if (x > (T)0) {
        return 1;
    }
    return 0;
}

template <class T, size_t N>
T sum(const array<T, N>& a)
{
    return accumulate(BE(a), 0);
}