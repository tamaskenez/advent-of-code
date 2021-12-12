#include "common.h"

struct Entry
{
    vector<string> patterns;
    vector<string> digits;
};

// 0: 6
// 1: 2
// 2: 5
// 3: 5
// 4: 4
// 5: 5
// 6: 6
// 7: 3
// 8: 7
// 9: 6

// 1: 2

// 7: 3

// 4: 4

// 8: 7

// 2: 5
// 3: 5
// 5: 5

// 0: 6
// 6: 6
// 9: 6

set<char> intersection(const set<char> a, const string& b)
{
    set<char> r;
    for (auto c : b) {
        if (a.count(c) > 0) {
            r.insert(c);
        }
    }
    return r;
}

set<char> subtract(const set<char> a, const string& b)
{
    set<char> r = a;
    for (auto c : b) {
        r.erase(c);
    }
    return r;
}

set<char> to_set(const std::string& s)
{
    set<char> r(BE(s));
    return r;
}

set<char> subtract(set<char> a, const set<char>& b)
{
    for (auto c : b) {
        a.erase(c);
    }
    return a;
}

string subtract(const string& a, const string& b, int count = -1)
{
    set<char> r(BE(a));
    auto rr = subtract(r, b);
    if (count >= 0) {
        assert(~rr == count);
    }
    return string(BE(rr));
}

char subtract1(const string& a, const string& b)
{
    auto set_b = to_set(b);
    auto set_a = to_set(a);
    for (auto c : set_b) {
        set_a.erase(c);
    }
    assert(~set_a == 1);
    return *set_a.begin();
}

vector<string> orig_digits = {"abcefg", "cf",     "acdeg", "acdfg",   "bcdf",
                              "abdfg",  "abdefg", "acf",   "abcdefg", "abcdfg"};

char map_to_orig(const string& m, char c)
{
    auto pos = m.find(c);
    assert(pos != string::npos);
    return char('a' + pos);
}

string map_to_orig(const string& m, string cc)
{
    string result;
    for (auto c : cc) {
        result.PB(map_to_orig(m, c));
    }
    return result;
}

bool is_valid_orig_segments(const string& s)
{
    return find(BE(orig_digits), s) != orig_digits.end();
}

bool check_patterns_with_map(string m, vector<string> ps)
{
    for (auto p : ps) {
        for (auto& c : p) {
            c = map_to_orig(m, c);
        }
        sort(BE(p));
        if (!is_valid_orig_segments(p)) {
            return false;
        }
    }
    return true;
}

int solve_entry(const Entry& entry)
{
    std::string s = "abcdefg";
    bool found = false;
    do {
        if (check_patterns_with_map(s, entry.patterns)) {
            found = true;
            break;
        }
    } while (std::next_permutation(s.begin(), s.end()));
    int total = 0;
    for (auto d : entry.digits) {
        auto orig = map_to_orig(s, d);
        sort(BE(orig));
        auto it = find(BE(orig_digits), orig);
        assert(it != orig_digits.end());
        int number = it - orig_digits.begin();
        total = 10 * total + number;
    }
    return total;
}

int solve_entry2(const Entry& entry)
{
    // Decode
    map<int, vector<string>> patterns;
    for (auto& p : entry.patterns) {
        patterns[~p].PB(p);
    }

    assert(~patterns[2] == 1);
    auto cf = patterns[2][0];
    assert(~cf == 2);

    assert(~patterns[3] == 1);
    auto acf = patterns[3][0];
    assert(~acf == 3);

    assert(~patterns[4] == 1);
    auto bcdf = patterns[4][0];
    assert(~bcdf == 4);

    string cde;
    assert(~patterns[6] == 3);
    for (auto some6 : patterns.at(6)) {
        auto missing = subtract("abcdefg", some6);
        assert(~missing == 1);
        cde.PB(missing[0]);
    }
    assert(~to_set(cde) == 3);

    set<char> set_bcef;
    for (auto some5 : patterns.at(5)) {
        auto missing = subtract("abcdefg", some5);
        assert(~missing == 2);
        set_bcef.insert(BE(missing));
    }
    assert(~set_bcef == 4);
    auto bcef = string(BE(set_bcef));

    auto a = subtract1(acf, cf);
    auto bd = subtract(bcdf, acf, 2);
    auto b = subtract1(bd, cde);
    auto d = subtract1(bd, string(1, b));
    auto f = subtract1(cf, cde);
    auto c = subtract1(cf, string(1, f));
    auto e = subtract1(subtract(cde, string(1, c), 2), string(1, d));
    auto g = subtract1("abcdefg", string({a, b, c, d, e, f}));

    auto sm = string({a, b, c, d, e, f, g});

    int final_number = 0;
    for (auto digit : entry.digits) {
        string k;
        for (auto d : digit) {
            auto p = sm.find(d);
            assert(p != string::npos);
            auto origc = char('a' + p);
            k.PB(origc);
        }
        sort(BE(k));
        auto it = find(BE(orig_digits), k);
        assert(it != orig_digits.end());
        int number = it - orig_digits.begin();
        final_number = 10 * final_number + number;
    }
    return final_number;
}

void TheP1(vector<string> lines)
{
    int counter = 0;
    for (auto l : lines) {
        auto lr = split(l, "|");
        for (auto s : split(lr[1], " ")) {
            if (~s ELEM_OF{2, 3, 4, 7}) {
                ++counter;
            }
        }
    }
    printf("P1: %d\n", counter);
}

void TheP2(VS lines)
{
    VS d09 = {"abcefg", "cf",     "acdeg", "acdfg",   "bcdf",
              "abdfg",  "abdefg", "acf",   "abcdefg", "abcdfg"};
    set<string> req(BE(d09));
    int64_t t = 0;
    for (auto k : lines) {
        auto ab = split(k, "|");
        auto [a, b] = MKP(ab[0], ab[1]);
        string x = "abcdefg";
        do {
            auto m = to_map(zip(x, string("abcdefg")));
            set<string> r;
            for (auto w : split(a, " ")) {
                r.insert(join(sorted(vmap(m, BE(w))), ""));
            }
            if (r == req) {
                VS vb;
                for (auto w : split(b, " ")) {
                    vb.PB(join(sorted(vmap(m, BE(w))), ""));
                }
                int s = 0;
                for (auto i : vb) {
                    s = 10 * s + index_of(BE(d09), i).value();
                }
                t += s;
            }
        } while (next_permutation(BE(x)));
    }
    printf("P2: %lld\n", t);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d08_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<Entry> entries;
    TheP1(lines);
    TheP2(lines);
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        auto pp = l.find('|');
        assert(pp != string::npos);
        auto sa = l.substr(0, pp);
        auto sb = l.substr(pp + 1);
        auto xsa = split(sa, " ");
        auto xsb = split(sb, " ");
        assert(~xsa == 10);
        assert(~xsb == 4);
        entries.PB(Entry{xsa, xsb});
    }
    int counter = 0;
    for (auto& e : entries) {
        for (auto& s : e.digits) {
            switch (~s) {
                case 2:
                case 3:
                case 4:
                case 7:
                    ++counter;
                default:
                    break;
            }
        }
    }
    printf("P1: %d\n", counter);

    int64_t p2 = 0;
    for (auto& e : entries) {
        p2 += solve_entry(e);
    }
    printf("P2: %lld\n", p2);
    return 0;
}
// 17:00
