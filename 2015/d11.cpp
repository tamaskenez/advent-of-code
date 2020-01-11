#include "common.h"

const string main_input = "hepxcrrq";

void next_it(string& s)
{
    if (s.empty()) {
        return;
    }
    for (int i = ~s - 1; i >= 0;) {
        auto& si = s[i];
        assert('a' <= si && si <= 'z');
        ++si;
        if (si == 'i' || si == 'o' || si == 'l') {
            continue;
        }
        if (si <= 'z') {
            return;
        }
        si = 'a';
        --i;
    }
}

bool firstr(const string& s)
{
    FOR (i, 0, <= ~s - 3) {
        if (s[i] + 1 == s[i + 1] && s[i + 1] + 1 == s[i + 2]) {
            return true;
        }
    }
    return false;
}

bool secondr(const string& s)
{
    int pc = 0;
    for (int i = 0; i <= ~s - 2; ++i) {
        if (s[i] == s[i + 1]) {
            if (++pc == 2) {
                return true;
            }
            ++i;
        }
    }
    return false;
}

int main()
{
    auto s = main_input;
    for (;;) {
        next_it(s);
        if (firstr(s) && secondr(s)) {
            break;
        }
    }
    printf("part1: %s\n", s.c_str());

    s = "hepxxyzz";
    for (;;) {
        next_it(s);
        if (firstr(s) && secondr(s)) {
            break;
        }
    }
    printf("part2: %s\n", s.c_str());
    return 0;
}
