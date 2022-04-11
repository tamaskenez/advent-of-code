#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
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
using AI4 = array<int, 4>;
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

template <class T, size_t N>
array<T, N> abs(const array<T, N>& a)
{
    array<T, N> b;
    FOR (i, (size_t)0, < N) {
        b[i] += abs(a[i]);
    }
    return b;
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

bool ends_with(const string& s, const char* t)
{
    auto l = (int)strlen(t);
    if (~s < l) {
        return false;
    }
    return s.substr(~s - l) == t;
}

string trim(string s)
{
    int i = 0;
    while (i < ~s && isspace(s[i])) {
        ++i;
    }
    int j = ~s;
    while (j <= ~s && i < j && isspace(s[j - 1])) {
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
int sgn(T x)
{
    if (x < (T)0) {
        return -1;
    }
    if (x > (T)0) {
        return 1;
    }
    return 0;
}

template <class T, size_t N, class F>
array<invoke_result_t<F, T>, N> over(const array<T, N>& xs, F&& f)
{
    array<invoke_result_t<F, T>, N> r;
    FOR (i, (size_t)0, < N) {
        r[i] = f(xs[i]);
    }
    return r;
}

template <class T>
struct ElemOfRhs
{
    const T& lhs;
    bool operator+=(initializer_list<T> rhs) const { return find(BE(rhs), lhs) != rhs.end(); }
};

template <class RHS>
struct ElemOfRhs2
{
    typename initializer_list<RHS>::const_iterator b, e;
};

struct LhsElemOfRhs
{
    template <class T>
    ElemOfRhs2<T> operator+=(initializer_list<T> rhs) const
    {
        return ElemOfRhs2<T>{BE(rhs)};
    }
};

template <class T>
bool operator+=(const T& lhs, ElemOfRhs2<T> rhs)
{
    return find(rhs.b, rhs.e, lhs) != rhs.e;
}

template <class T>
ElemOfRhs<T> operator,(const T& lhs, LhsElemOfRhs)
{
    return ElemOfRhs<T>{lhs};
}

#define ELEM_OF += LhsElemOfRhs{} +=

template <class T, size_t N>
T sum(const array<T, N>& a)
{
    return accumulate(BE(a), 0);
}

maybe<char> eat_any_char(string& s)
{
    if (s.empty()) {
        return nullopt;
    }
    auto c = s[0];
    s.erase(0, 1);
    return c;
}

bool eat_char(string& s, char c)
{
    if (s.empty() || s[0] != c) {
        return false;
    }
    s.erase(0, 1);
    return true;
}

bool eat_string(string& s, const string& t)
{
    if (starts_with(s, t)) {
        s = s.substr(~t);
        return true;
    }
    return false;
}

string eat_chars(string& s, const string& charset)
{
    int i = 0;
    while (i < ~s && charset.find(s[i]) != string::npos) {
        ++i;
    }
    auto result = s.substr(0, i);
    s = s.substr(i);
    return result;
}

void eat_wspace(string& s)
{
    int i = 0;
    while (i < ~s && isspace(s[i])) {
        ++i;
    }
    s = s.substr(i);
}

template <class T>
maybe<T> eat_integer(string& s, int base = 10)
{
    if (~s >= 1 && s[0] == '0') {
        s.erase(0, 1);
        return 0;
    }
    if (~s >= 2 && s[0] == '-' && s[1] == '0') {
        s.erase(0, 2);
        return 0;
    }
    T value;
    auto r = from_chars(s.c_str(), s.c_str() + ~s, value, base);
    if (r.ec != errc{}) {
        return nullopt;
    }
    s = s.substr(r.ptr - s.c_str());
    return value;
}

template <class T>
maybe<T> eat_integer(string_view& s, int base = 10)
{
    if (~s >= 1 && s[0] == '0') {
        s.remove_prefix(1);
        return 0;
    }
    if (~s >= 2 && s[0] == '-' && s[1] == '0') {
        s.remove_prefix(2);
        return 0;
    }
    T value;
    auto r = from_chars(s.data(), s.data() + ~s, value, base);
    if (r.ec != errc{}) {
        return nullopt;
    }
    s.remove_prefix(r.ptr - s.data());
    return value;
}

template <class T>
maybe<T> eat_floating(string& s);

template <>
maybe<float> eat_floating<float>(string& s)
{
    if (s.empty() || isspace(s[0])) {
        return nullopt;
    }
    if (~s >= 2 && s[0] == '0' && s[1] != '.') {
        s.erase(0, 1);
        return 0;
    }
    if (~s >= 3 && s[0] == '-' && s[1] == '0' && s[2] != '.') {
        s.erase(0, 2);
        return 0;
    }
    char* end = nullptr;
    auto r = strtof(s.c_str(), &end);
    if (end == s.c_str()) {
        return nullopt;
    }
    s = s.substr(end - s.c_str());
    return r;
}

template <>
maybe<double> eat_floating<double>(string& s)
{
    if (s.empty() || isspace(s[0])) {
        return nullopt;
    }
    if (s.empty() || isspace(s[0])) {
        return nullopt;
    }
    if (~s >= 2 && s[0] == '0' && s[1] != '.') {
        s.erase(0, 1);
        return 0;
    }
    if (~s >= 3 && s[0] == '-' && s[1] == '0' && s[2] != '.') {
        s.erase(0, 2);
        return 0;
    }
    char* end = nullptr;
    auto r = strtod(s.c_str(), &end);
    if (end == s.c_str()) {
        return nullopt;
    }
    s = s.substr(end - s.c_str());
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

    string s;
    assert(!eat_any_char(s) && ~s == 0);
    s = " ";
    assert(eat_any_char(s) == ' ' && ~s == 0);
    s = "abc";
    assert(eat_any_char(s) == 'a' && s == "bc");

    s = "";
    assert(!eat_char(s, 'a') && ~s == 0);
    s = "abc";
    assert(!eat_char(s, 'b') && s == "abc");
    s = "abc";
    assert(eat_char(s, 'a') && s == "bc");

    s = "";
    assert(eat_string(s, "") && ~s == 0);
    s = "";
    assert(!eat_string(s, "a") && ~s == 0);
    s = "abc";
    assert(!eat_string(s, "bb") && s == "abc");
    s = "abc";
    assert(eat_string(s, "ab") && s == "c");

    s = "";
    assert(eat_chars(s, "") == "" && s == "");
    s = "";
    assert(eat_chars(s, "a") == "" && s == "");
    s = "abc";
    assert(eat_chars(s, "bc") == "" && s == "abc");
    s = "abc";
    assert(eat_chars(s, "ba") == "ab" && s == "c");

    s = "";
    eat_wspace(s);
    assert(s == "");
    s = " \t \t";
    eat_wspace(s);
    assert(s == "");
    s = "a ";
    eat_wspace(s);
    assert(s == "a ");
    s = " a ";
    eat_wspace(s);
    assert(s == "a ");

    s = "";
    assert(!eat_integer<int>(s) && s == "");
    s = "a";
    assert(!eat_integer<int>(s) && s == "a");
    s = "a1";
    assert(!eat_integer<int>(s) && s == "a1");
    s = " 1";
    assert(!eat_integer<int>(s) && s == " 1");
    s = "1";
    assert(eat_integer<int>(s) == 1 && s == "");
    s = "0";
    assert(eat_integer<int>(s) == 0 && s == "");
    s = "00";
    assert(eat_integer<int>(s) == 0 && s == "0");
    s = "0123";
    assert(eat_integer<int>(s) == 0 && s == "123");
    s = "123";
    assert(eat_integer<int>(s) == 123 && s == "");
    s = "123a";
    assert(eat_integer<int>(s) == 123 && s == "a");

    s = "";
    assert(!eat_floating<double>(s) && s == "");
    s = "a";
    assert(!eat_floating<double>(s) && s == "a");
    s = "a1";
    assert(!eat_floating<double>(s) && s == "a1");
    s = " 1";
    assert(!eat_floating<double>(s) && s == " 1");
    s = "1";
    assert(eat_floating<double>(s) == 1 && s == "");
    s = "0";
    assert(eat_floating<double>(s) == 0 && s == "");
    s = "00";
    assert(eat_floating<double>(s) == 0 && s == "0");
    s = "0123";
    assert(eat_floating<double>(s) == 0 && s == "123");
    s = "123";
    assert(eat_floating<double>(s) == 123 && s == "");
    s = "123a";
    assert(eat_floating<double>(s) == 123 && s == "a");
    s = "123.456a";
    assert(fabs(eat_floating<double>(s).value() - 123.456) < 1e-12 && s == "a");
}

template <class T>
std::size_t hash_value(const T& v)
{
    return std::hash<std::decay_t<T>>{}(v);
}

template <class T>
void hash_combine(std::size_t& seed, const T& v)
{
    seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <class It>
std::size_t hash_range(It first, It last)
{
    std::size_t seed = 0;
    for (; first != last; ++first) {
        hash_combine(seed, *first);
    }
    return seed;
}

template <class It>
void hash_range(std::size_t& seed, It first, It last)
{
    for (; first != last; ++first) {
        hash_combine(seed, *first);
    }
}

template <class U, class V>
vector<pair<typename U::value_type, typename V::value_type>> zip(const U& u, const V& v)
{
    using UV = typename U::value_type;
    using VV = typename V::value_type;
    auto itu = u.begin();
    auto itv = v.begin();
    vector<pair<UV, VV>> r;
    for (; itu != u.end() && itv != v.end(); ++itu, ++itv) {
        r.emplace_back(*itu, *itv);
    }
    return r;
}

template <class U, class V>
map<U, V> to_map(const vector<pair<U, V>>& vs)
{
    map<U, V> m;
    for (auto& kv : vs) {
        m.insert(kv);
    }
    return m;
}

template <class U, class V, class VIT>
vector<V> vmap(const map<U, V>& m, VIT it, VIT e)
{
    vector<V> vs;
    for (; it != e; ++it) {
        vs.PB(m.at(*it));
    }
    return vs;
}

template <class T>
vector<T> sorted(vector<T> vs)
{
    sort(BE(vs));
    return move(vs);
}

string join(vector<char> vs, const string& sep)
{
    string r;
    if (!vs.empty()) {
        r.reserve(~vs + ((~vs - 1) * ~sep));
        r = vs[0];
        FOR (i, 1, < ~vs) {
            r += sep;
            r += vs[i];
        }
    }
    return r;
}

template <class IT, class V>
optional<int> index_of(IT b, IT e, const V& v)
{
    auto it = find(b, e, v);
    if (it == e) {
        return nullopt;
    }
    return it - b;
}

template <class K, class V>
vector<V> values(const map<K, V> m)
{
    vector<V> vs;
    vs.reserve(~m);
    for (auto& [_, v] : m) {
        vs.PB(v);
    }
    return vs;
}

template <class K, class V>
vector<K> keys(const map<K, V> m)
{
    vector<K> ks;
    ks.reserve(~m);
    for (auto& [k, _] : m) {
        ks.PB(k);
    }
    return ks;
}

string read_cin_line()
{
    string line;
    getline(cin, line);
    return line;
}

string repeat_string(string s, int n)
{
    string r;
    FOR (i, 0, < n) {
        r += s;
    }
    return r;
}

AI4 to_ai4(vector<string> vss)
{
    assert(~vss == 4);
    AI4 r;
    FOR (i, 0, < 4) {
        r[i] = stoi(vss[i]);
    }
    return r;
}
VI stoi(VS vss)
{
    VI vi;
    for (auto s : vss) {
        vi.push_back(stoi(s));
    }
    return vi;
}

VI64 to_vi64(VS vss)
{
    VI64 vi;
    for (auto s : vss) {
        vi.push_back(stoll(s));
    }
    return vi;
}

void printvi64(const VI64& as)
{
    FOR (i, 0, < ~as) {
        printf("%lld", as[i]);
        if (i < ~as - 1) {
            printf(" ");
        }
    }
    printf("\n");
    fflush(stdout);
}

// -----------------------------

namespace std {
template <>
struct hash<VI>
{
    std::size_t operator()(const VI& s) const noexcept { return hash_range(BE(s)); }
};

template <>
struct hash<vector<VI>>
{
    size_t operator()(const vector<VI>& s) const noexcept { return hash_range(BE(s)); }
};
}  // namespace std

unordered_map<int, unordered_map<vector<VI>, int>> cache;

int get_min_steps_without_cache(vector<VI> exercises);

int get_min_steps(vector<VI> exercises)
{
    if (exercises.empty()) {
        return 0;
    }

    int E = ~exercises;
    auto it = cache.find(E);
    if (it != cache.end()) {
        auto jt = it->second.find(exercises);
        if (jt != it->second.end()) {
            assert(jt->second >= 0);
            return jt->second;
        }
    }
    auto& result_ref = cache[E][exercises];
    result_ref = -1;
    result_ref = get_min_steps_without_cache(move(exercises));
    return result_ref;
}

int get_min_steps2_without_cache(const vector<VI>& exercises);

int get_min_steps_without_cache(vector<VI> exercises)
{
    int steps = 0;
    // Remove single steps and full spans
    int E = ~exercises;
    int W = ~(exercises[0]);
    VI min_by_weight(W, INT_MAX);
    FOR (i, 0, < E) {
        auto& e = exercises[i];
        FOR (j, 0, < ~e) {
            int prev = i == 0 ? 0 : exercises[i - 1][j];
            int& ej = e[j];
            int next = i == E - 1 ? 0 : exercises[i + 1][j];
            int singles = ej - max(prev, next);
            if (singles > 0) {
                e[j] -= singles;
                steps += 2 * singles;
            }
            min_by_weight[j] = min(min_by_weight[j], ej);
        }
    }

    for (auto m : min_by_weight) {
        steps += 2 * m;
    }

    bool nonzero_left = false;
    for (auto& e : exercises) {
        FOR (j, 0, < W) {
            auto& ej = e[j];
            ej -= min_by_weight[j];
            nonzero_left = nonzero_left || ej > 0;
        }
    }

    if (!nonzero_left) {
        return steps;
    }

    return steps + get_min_steps2_without_cache(exercises);
}

int get_min_steps2_without_cache(const vector<VI>& exercises)
{
    optional<int> best_steps;
    int E = ~exercises;
    FOR (i, 0, < E - 1) {
        auto& e = exercises[i];
        int W = ~e;
        // Look at spans starting here.
        FOR (j, 0, < W) {
            bool might_start_here = (i == 0 ? 0 : exercises[i - 1][j]) < e[j];
            if (might_start_here) {
                // Span: i..<k
                for (int k = i + 1; k <= E && exercises[k - 1][j] > 0; ++k) {
                    bool might_end_here;
                    if (k < E) {
                        might_end_here = exercises[k - 1][j] > exercises[k][j];
                    } else {
                        assert(k == E);
                        might_end_here = i > 0;
                    }
                    if (might_end_here) {
                        vector<VI> previous_exercises(exercises.begin(), exercises.begin() + i);
                        vector<VI> new_exercises(exercises.begin() + i, exercises.begin() + k);
                        vector<VI> subsequent_exercises(exercises.begin() + k, exercises.end());

                        int steps_here = get_min_steps(move(previous_exercises)) +
                                         get_min_steps(move(new_exercises)) +
                                         get_min_steps(move(subsequent_exercises));
                        if (!best_steps || steps_here < *best_steps) {
                            best_steps = steps_here;
                        }
                    }
                }
            }
        }
    }
    return best_steps.value();
}

int do_case(vector<VI> exercises)
{
    cache.clear();
    return get_min_steps(move(exercises));
}

int main()
{
    default_random_engine dre;
    constexpr bool testing = false;
    int T = testing ? 1000 : stoi(read_cin_line());
    FOR (t, 0, < T) {
        VI ew;
        if (testing) {
            int E = uniform_int_distribution<>(1, 10)(dre);
            int W = uniform_int_distribution<>(1, 100)(dre);
            ew = {E, W};
        } else {
            ew = stoi(split(read_cin_line(), " "));
        }
        assert(~ew == 2);
        auto E = ew[0];
        auto W = ew[1];
        vector<VI> exercises;
        exercises.reserve(E);
        FOR (e, 0, < E) {
            VI ws;
            if (testing) {
                ws.reserve(W);
                uniform_int_distribution<> uid(0, 100);
                for (;;) {
                    bool nonzero = false;
                    FOR (i, 0, < W) {
                        auto x = uid(dre);
                        ws.PB(x);
                        nonzero = nonzero || x > 0;
                    }
                    if (nonzero) {
                        break;
                    }
                    ws.clear();
                }
            } else {
                ws = stoi(split(read_cin_line(), " "));
            }
            assert(~ws == W);
            exercises.PB(move(ws));
        }
        auto r = do_case(move(exercises));
        printf("Case #%d: %d\n", t + 1, r);
    }

    return 0;
}
