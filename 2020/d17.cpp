#include "common.h"

template <int N>
using Grid = set<array<int,N>>;

vector<AI3> neighbors(AI3 p)
{
    vector<AI3> nbs;
    FOR (r, -1, <= 1) {
        FOR (c, -1, <= 1) {
            FOR (d, -1, <= 1) {
                if (r == 0 && c == 0 && d == 0) {
                    continue;
                }
                nbs.PB(AI3{p[0] + r, p[1] + c, p[2] + d});
            }
        }
    }
    return nbs;
}

vector<AI4> neighbors(AI4 p)
{
    vector<AI4> nbs;
    FOR (r, -1, <= 1) {
        FOR (c, -1, <= 1) {
            FOR (d, -1, <= 1) {
                FOR (e, -1, <= 1) {
                    if (r == 0 && c == 0 && d == 0 && e == 0) {
                        continue;
                    }
                    nbs.PB(AI4{p[0] + r, p[1] + c, p[2] + d, p[3] + e});
                }
            }
        }
    }
    return nbs;
}

int n_active_nbs(const Grid<3>& g, AI3 p)
{
    int result = 0;
    FOR (r, -1, <= 1) {
        FOR (c, -1, <= 1) {
            FOR (d, -1, <= 1) {
                if (r == 0 && c == 0 && d == 0) {
                    continue;
                }
                if (g.count(AI3{p[0] + r, p[1] + c, p[2] + d})) {
                    ++result;
                }
            }
        }
    }
    return result;
}

int n_active_nbs(const Grid<4>& g, AI4 p)
{
    int result = 0;
    FOR (r, -1, <= 1) {
        FOR (c, -1, <= 1) {
            FOR (d, -1, <= 1) {
                FOR (e, -1, <= 1) {
                    if (r == 0 && c == 0 && d == 0 && e == 0) {
                        continue;
                    }
                    if (g.count(AI4{p[0] + r, p[1] + c, p[2] + d, p[3] + e})) {
                        ++result;
                    }
                }
            }
        }
    }
    return result;
}

template <int N>
Grid<N> sim(const Grid<N>& g)
{
    Grid<N> h;
    set<array<int,N>> ss;
    for (auto a : g) {
        auto nbs = neighbors(a);
        ss.insert(BE(nbs));
    }
    for (auto s : ss) {
        auto n = n_active_nbs(g, s);
        if (g.count(s)) {
            if (n == 2 || n == 3) {
                h.insert(s);
            }
        } else {
            if (n == 3) {
                h.insert(s);
            }
        }
    }
    return h;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d17_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(!lines.empty());

    {
        int r = 0;
        Grid<3> g;
        for (auto& l : lines) {
            FOR (c, 0, < ~l) {
                if (l[c] == '#') {
                    g.insert(AI3{r, c, 0});
                }
            }
            ++r;
        }
        FOR (cycle, 0, < 6) {
            g = sim<3>(g);
        }
        printf("P1: %d\n", ~g);
    }
    {
        int r = 0;
        Grid<4> g;
        for (auto& l : lines) {
            FOR (c, 0, < ~l) {
                if (l[c] == '#') {
                    g.insert(AI4{r, c, 0, 0});
                }
            }
            ++r;
        }
        FOR (cycle, 0, < 6) {
            g = sim<4>(g);
        }
        printf("P2: %d\n", ~g);
    }
    return 0;
}

// 23.58
