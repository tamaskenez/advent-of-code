#include "common.h"

using Token = int;

enum TT
{
    Open = -1,
    Close = -2,
    Comma = -3,
    Number = -4
};

TT get_type(Token t)
{
    switch (t) {
        case Open:
        case Close:
        case Comma:
            return (TT)t;
        default:
            assert(t >= 0);
            return Number;
    }
}

optional<vector<Token>> try_explode(vector<Token> ts)
{
    int level = 0;
    FOR (i, 0, < ~ts) {
        auto t = ts[i];
        if (t == Open) {
            ++level;
        } else if (t == Close) {
            --level;
        }
        if (level == 5) {
            assert(get_type(ts[i + 1]) == Number);
            assert(get_type(ts[i + 2]) == Comma);
            assert(get_type(ts[i + 3]) == Number);
            assert(get_type(ts[i + 4]) == Close);
            for (int j = i - 1; j >= 0; --j) {
                if (get_type(ts[j]) == Number) {
                    ts[j] += ts[i + 1];
                    break;
                }
            }
            for (int j = i + 4; j < ~ts; ++j) {
                if (get_type(ts[j]) == Number) {
                    ts[j] += ts[i + 3];
                    break;
                }
            }
            auto new_ts = vector<Token>(ts.begin(), ts.begin() + i);
            new_ts.PB(0);
            new_ts.insert(new_ts.end(), ts.begin() + i + 5, ts.end());
            return new_ts;
        }
    }
    return nullopt;
}

optional<vector<Token>> try_split(const vector<Token>& ts)
{
    FOR (i, 0, < ~ts) {
        if (get_type(ts[i]) == Number && ts[i] >= 10) {
            auto new_ts = vector<Token>(ts.begin(), ts.begin() + i);
            new_ts.PB(Open);
            new_ts.PB(ts[i] / 2);
            new_ts.PB(Comma);
            new_ts.PB((ts[i] + 1) / 2);
            new_ts.PB(Close);
            new_ts.insert(new_ts.end(), ts.begin() + i + 1, ts.end());
            return new_ts;
        }
    }
    return nullopt;
}

optional<vector<Token>> reduce1(const vector<Token>& ts)
{
    auto r = try_explode(ts);
    if (r)
        return *r;
    return try_split(ts);
}

vector<Token> reduce(vector<Token> ts)
{
    for (;;) {
        auto r = reduce1(ts);
        if (!r) {
            return ts;
        }
        ts = *r;
    }
}

vector<Token> add(const vector<Token>& a, const vector<Token>& b)
{
    vector<Token> new_ts;
    new_ts.PB(Open);
    new_ts.insert(new_ts.end(), BE(a));
    new_ts.PB(Comma);
    new_ts.insert(new_ts.end(), BE(b));
    new_ts.PB(Close);
    return new_ts;
}

using token_view = basic_string_view<Token>;

string sprint(const vector<Token>& ts)
{
    string s;
    for (auto t : ts) {
        switch (get_type(t)) {
            case Open:
                s += '[';
                break;
            case Comma:
                s += ',';
                break;
            case Close:
                s += ']';
                break;
            case Number:
                s += to_string(t);
                break;
            default:
                assert(false);
                break;
        }
    }
    return s;
}

void print(const vector<Token>& ts)
{
    printf("%s\n", sprint(ts).c_str());
}

string sprint(token_view tv)
{
    return sprint(vector<Token>(BE(tv)));
}

int magnitude(token_view& tv)
{
    auto before = sprint(tv);
    assert(!tv.empty());
    if (get_type(tv[0]) == Open) {
        tv.remove_prefix(1);
        auto m0 = magnitude(tv);
        assert(!tv.empty() && get_type(tv[0]) == Comma);
        tv.remove_prefix(1);
        auto m1 = magnitude(tv);
        assert(!tv.empty() && get_type(tv[0]) == Close);
        tv.remove_prefix(1);
        return 3 * m0 + 2 * m1;
    }
    assert(get_type(tv[0]) == Number);
    auto r = tv[0];
    tv.remove_prefix(1);
    return r;
}

int magnitude(const vector<Token>& ts)
{
    auto tv = token_view(ts.data(), ~ts);
    auto r = magnitude(tv);
    assert(tv.empty());
    return r;
}

int P1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d18_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<vector<Token>> itss;
    for (auto l : lines) {
        auto sv = string_view(l);
        vector<Token> tokens;
        while (!sv.empty()) {
            switch (sv[0]) {
                case '[':
                    tokens.PB(Open);
                    sv.remove_prefix(1);
                    break;
                case ']':
                    tokens.PB(Close);
                    sv.remove_prefix(1);
                    break;
                case ',':
                    tokens.PB(Comma);
                    sv.remove_prefix(1);
                    break;
                default: {
                    auto i = eat_integer<int>(sv);
                    assert(i);
                    tokens.PB(*i);
                } break;
            }
        }
        itss.PB(tokens);
        if (~itss == 2) {
            assert(~itss == 2);
            auto s = reduce(add(itss[0], itss[1]));
            itss.assign(1, s);
        }
    }
    assert(~itss == 1);
    print(itss[0]);
    auto r = magnitude(itss[0]);
    printf("P1: %d\n", r);
    return 0;
}

int P2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d18_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<vector<Token>> itss;
    for (auto l : lines) {
        auto sv = string_view(l);
        vector<Token> tokens;
        while (!sv.empty()) {
            switch (sv[0]) {
                case '[':
                    tokens.PB(Open);
                    sv.remove_prefix(1);
                    break;
                case ']':
                    tokens.PB(Close);
                    sv.remove_prefix(1);
                    break;
                case ',':
                    tokens.PB(Comma);
                    sv.remove_prefix(1);
                    break;
                default: {
                    auto i = eat_integer<int>(sv);
                    assert(i);
                    tokens.PB(*i);
                } break;
            }
        }
        itss.PB(tokens);
    }
    auto highest = 0;
    FOR (i, 0, < ~itss) {
        FOR (j, 0, < ~itss) {
            if (i == j) {
                continue;
            }
            highest = std::max(highest, magnitude(reduce(add(itss[i], itss[j]))));
        }
    }
    printf("P2: %d\n", highest);
    return 0;
}
int main()
{
    P1();
    P2();
}
