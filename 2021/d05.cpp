#include "common.h"

AI2 min(AI2 a, AI2 b)
{
    return AI2{min(a[0], b[0]), min(a[1], b[1])};
}

AI2 max(AI2 a, AI2 b)
{
    return AI2{max(a[0], b[0]), max(a[1], b[1])};
}

struct M
{
    map<AI2, int> m;
    AI2 tl{INT_MAX, INT_MAX};
    AI2 br{INT_MIN, INT_MIN};
    void inc(AI2 rc)
    {
        m[rc]++;
        tl = min(tl, rc);
        br = max(br, rc);
    }
};

void P1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d05_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    M m;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        auto xs = split(l, ", ->");
        assert(~xs == 4);
        AI2 a{stoi(xs[0]), stoi(xs[1])};
        AI2 b{stoi(xs[2]), stoi(xs[3])};
        if (a[0] == b[0]) {
            auto lo = min(a[1], b[1]);
            auto hi = max(a[1], b[1]);
            FOR (i, lo, <= hi) {
                m.inc(AI2{a[0], i});
            }
        } else if (a[1] == b[1]) {
            auto lo = min(a[0], b[0]);
            auto hi = max(a[0], b[0]);
            FOR (i, lo, <= hi) {
                m.inc(AI2{i, a[1]});
            }
        }
    }
    int c = 0;
    for (auto& [k, v] : m.m) {
        if (v > 1) {
            ++c;
        }
    }
    printf("P1: %d\n", c);
}

void P2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d05_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    M m;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        auto xs = split(l, ", ->");
        assert(~xs == 4);
        AI2 a{stoi(xs[0]), stoi(xs[1])};
        AI2 b{stoi(xs[2]), stoi(xs[3])};
        auto d = b - a;
        assert(d[0] == 0 || d[1] == 0 || abs(d[0]) == abs(d[1]));
        assert(d[0] != 0 || d[1] != 0);
        d = over(d, sgn<int>);
        for (AI2 p = a;; p += d) {
            m.inc(p);
            if (p == b) {
                break;
            }
        }
    }
    int c = 0;
    for (auto& [k, v] : m.m) {
        if (v > 1) {
            ++c;
        }
    }
    printf("P2: %d\n", c);
}
int main()
{
    P1();
    P2();
    return 0;
}

// 11:27
