#include <iostream>

#include "common.h"

const int x = 0;
#if 0
int tid = 939;
vector<int> buses = {7, 13, x, x, 59, x, 31, 19};

#else
int tid = 1015292;
vector<int> buses = {19,  x, x, x, x, x, x, x, x, 41, x,  x, x,   x,  x,  x, x, x, x,
                     743, x, x, x, x, x, x, x, x, x,  x,  x, x,   13, 17, x, x, x, x,
                     x,   x, x, x, x, x, x, x, x, x,  29, x, 643, x,  x,  x, x, x, 37,
                     x,   x, x, x, x, x, x, x, x, x,  x,  x, x,   x,  x,  x, 23};

#endif
struct Best
{
    int busid;
    int earliest;
};

int main()
{
    maybe<Best> best;
    for (auto b : buses) {
        if (b == 0) {
            continue;
        }
        int r = tid % b;
        int earliest;
        if (r == 0) {
            earliest = tid;
        } else {
            earliest = (b - r) + tid;
            assert(earliest % b == 0);
        }
        if (!best || best->earliest > earliest) {
            best = Best{b, earliest};
        }
    }
    assert(best);
    auto p1 = best->busid * (best->earliest - tid);
    printf("P1: %d\n", p1);

    int64_t t = 0;
    int64_t step = 0;
    FOR (i, 0, < ~buses) {
        auto b = buses[i];
        if (b == 0) {
            continue;
        }
        auto r = b - i;
        printf("divisor %d rem %d\n", b, i == 0 ? 0 : r);
        if (i == 0) {
            step = b;
            t = 0;
        } else {
            int64_t k = 0;
            int64_t j = 0;
            for (;;) {
                auto lhs = k * step + (t + (i % b));
                auto rhs = j * b;
                if (lhs < rhs) {
                    auto needed = rhs - lhs;
                    auto increase = max<int64_t>(1, needed / step);
                    assert(increase != 0);
                    k += increase;
                } else if (lhs > rhs) {
                    auto needed = lhs - rhs;
                    auto increase = max<int64_t>(1, needed / b);
                    assert(increase != 0);
                    j += increase;
                } else {
                    break;
                }
            }
            t += k * step;
            step *= b;
        }
    }

    cout << "P2: " << t << endl;

    return 0;
}

// 11 00
