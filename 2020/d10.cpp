#include <iostream>

#include "common.h"

map<int, int64_t> cache;

int64_t countt(const int ix, const VI& xs)
{
    if (ix + 1 == ~xs) {
        return 1;
    }
    auto it = cache.find(ix);
    if (it != cache.end()) {
        return it->second;
    }
    assert(ix < ~xs);
    int64_t r = 0;
    auto x = xs[ix];
    FOR (iy, ix + 1, < ~xs) {
        auto y = xs[iy];
        if (y - x > 3) {
            break;
        }
        r += countt(iy, xs);
    }
    cache[ix] = r;
    return r;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d10_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    VI vs;
    for (auto l : lines) {
        vs.PB(atoi(l.c_str()));
    }
    vs.PB(0);
    auto highest = *max_element(BE(vs));
    vs.PB(highest + 3);
    sort(BE(vs));
    map<int, int> ds;
    FOR (i, 1, < ~vs) {
        int d = vs[i] - vs[i - 1];
        ds[d]++;
    }
    auto p1 = ds[1] * ds[3];
    printf("P1: %d\n", p1);

    auto p2 = countt(0, vs);
    cout << "P2: " << p2 << endl;

    return 0;
}

// 1792 low
// 8 52
