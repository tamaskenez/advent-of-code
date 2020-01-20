#include "common.h"

bool is_abba(const string& s)
{
    assert(~s == 4);
    return s[0] != s[1] && s[0] == s[3] && s[1] == s[2];
}

bool has_abba(const string& w)
{
    FOR (i, 0, <= ~w - 4) {
        if (is_abba(w.substr(i, 4))) {
            return true;
        }
    }
    return false;
}

void collect_babs(set<string>& babs, const string& w)
{
    FOR (i, 0, <= ~w - 3) {
        auto s = w.substr(i, 3);
        if (s[0] == s[2] && s[0] != s[1]) {
            babs.insert(s);
        }
    }
}

bool has_common(const set<string>& abas, const set<string>& babs)
{
    for (auto& aba : abas) {
        string bab = {aba[1], aba[0], aba[1]};
        if (babs.count(bab) > 0) {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d07_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int total = 0;
    int total2 = 0;
    for (auto l : lines) {
        // l = "abba[mnop]qrst";
        assert(l[0] != '[');
        auto vs = split(l, "[]");
        bool has_abba_outside = false;
        bool has_abba_inside = false;
        bool inside_brackets = false;
        set<string> abas;
        set<string> babs;
        for (auto w : vs) {
            bool habba = has_abba(w);
            if (inside_brackets) {
                if (habba) {
                    has_abba_inside = true;
                }
                collect_babs(babs, w);
            } else {
                if (habba) {
                    has_abba_outside = true;
                }
                collect_babs(abas, w);
            }
            inside_brackets = !inside_brackets;
        }
        if (!has_abba_inside && has_abba_outside) {
            ++total;
        }
        if (has_common(abas, babs)) {
            ++total2;
        }
    }
    printf("part1 %d\n", total);
    printf("part2 %d\n", total2);
    return 0;
}
// 11 43