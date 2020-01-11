#include "common.h"

bool is_vowel(char c)
{
    const string vs = "aeiou";
    if (vs.find(c) != string::npos) {
        return true;
    }
    return false;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d5_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int nice = 0;
    const vector<string> notss = {"ab", "cd", "pq", "xy"};
    for (auto l : lines) {
        int vowels = 0;
        for (auto c : l) {
            if (is_vowel(c)) {
                ++vowels;
            }
        }
        int twice = 0;
        FOR (i, 0, < ~l - 1) {
            if (l[i] == l[i + 1]) {
                ++twice;
            }
        }
        bool has_nots = false;
        for (auto& nots : notss) {
            if (l.find(nots) != string::npos) {
                has_nots = true;
                break;
            }
        }
        if (vowels >= 3 && !has_nots && twice > 0) {
            ++nice;
        }
    }
    printf("nice: %d\n", nice);

    nice = 0;
    for (auto l : lines) {
        bool ok1 = false;
        FOR (i, 0, <= ~l - 4) {
            auto s = l.substr(i, 2);
            if (l.substr(i + 2).find(s) != string::npos) {
                ok1 = true;
                break;
            }
        }
        bool ok2 = false;
        FOR (i, 0, < ~l - 2) {
            if (l[i] == l[i + 2]) {
                ok2 = true;
                break;
            }
        }
        if (ok1 && ok2) {
            ++nice;
        }
    }
    printf("nice2: %d\n", nice);

    return 0;
}

// 6 16
// not 67
