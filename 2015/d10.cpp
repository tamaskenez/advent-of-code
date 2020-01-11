#include "common.h"

const string main_input = "1113222113";

tuple<int, char> eat_some(int& i, const string& s)
{
    assert(i < ~s);
    auto ch = s[i++];
    int count = 1;
    while (i < ~s && s[i] == ch) {
        ++count;
        ++i;
    }
    assert(0 < count && count < 10);
    return make_tuple(count, ch);
}

string apply(const string& s)
{
    string t;
    int i = 0;
    while (i < ~s) {
        auto [count, ch] = eat_some(i, s);
        t += (char)('0' + count);
        t += ch;
    }
    return t;
}

int main()
{
    {
        auto s = main_input;
        FOR (i, 0, < 40) {
            s = apply(s);
        }
        printf("part1: %d\n", ~s);
    }
    {
        auto s = main_input;
        FOR (i, 0, < 50) {
            s = apply(s);
        }
        printf("part2: %d\n", ~s);
    }
    return 0;
}

// 1035
// 1104
