#include "common.h"

int processgroup(const VS& gl)
{
    set<char> yeses;
    for (auto l : gl) {
        for (auto c : l) {
            yeses.insert(c);
        }
    }
    return ~yeses;
}

int processgroup2(const VS& gl)
{
    set<char> yeses;
    FOR (c, 'a', <= 'z') {
        yeses.insert(c);
    }
    for (auto l : gl) {
        set<char> y;
        for (auto c : l) {
            y.insert(c);
        }
        FOR (c, 'a', <= 'z') {
            if (y.count(c) == 0) {
                yeses.erase(c);
            }
        }
    }
    return ~yeses;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d6_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    VS grouplines;
    int totalyc = 0;
    int totalyc2 = 0;
    for (auto l : lines) {
        auto tl = trim(l);
        if (tl.empty()) {
            if (!grouplines.empty()) {
                totalyc += processgroup(grouplines);
                totalyc2 += processgroup2(grouplines);
                grouplines.clear();
            }
        } else {
            grouplines.PB(tl);
        }
    }
    if (!grouplines.empty()) {
        totalyc += processgroup(grouplines);
        totalyc2 += processgroup2(grouplines);
    }

    printf("p1: %d\n", totalyc);
    printf("p2: %d\n", totalyc2);
    return 0;
}

// 7:40
