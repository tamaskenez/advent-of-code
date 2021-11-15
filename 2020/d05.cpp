#include "common.h"

struct RC
{
    int r, c;
};

// FBFBBFFRLR

RC rc_from_bsp(string b)
{
    assert(~b == 7 + 3);
    int lo = 0, hi = 128;
    FOR (i, 0, < 7) {
        auto c = b[i];
        if (c == 'B') {
            lo += (hi - lo) / 2;
        } else {
            assert(c == 'F');
            hi -= (hi - lo) / 2;
        }
    }
    assert(lo + 1 == hi);
    int r = lo;
    lo = 0;
    hi = 8;
    FOR (i, 0, < 3) {
        auto c = b[7 + i];
        if (c == 'R') {
            lo += (hi - lo) / 2;
        } else {
            assert(c == 'L');
            hi -= (hi - lo) / 2;
        }
    }
    int c = lo;
    return RC{r, c};
}

int sid_from_rc(RC rc)
{
    return rc.r * 8 + rc.c;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d5_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int highestsid = -INT_MIN;
    map<int, RC> sids;
    FOR (r, 0, < 128) {
        FOR (c, 0, < 8) {
            auto rc = RC{r, c};
            sids.insert(make_pair(sid_from_rc(rc), rc));
        }
    }
    for (auto l : lines) {
        auto rc = rc_from_bsp(l);
        auto sid = sid_from_rc(rc);
        sids.erase(sid);
        if (sid > highestsid) {
            highestsid = sid;
        }
    }
    printf("P1: %d\n", highestsid);
    for (auto kv : sids) {
        printf("%d: %d, %d\n", kv.first, kv.second.r, kv.second.c);
    }
    return 0;
}

// 1226
// 1843
