#include "common.h"

const int GSN = 5177;

int power_level(int x, int y)
{
    int rid = x + 10;
    int pl = rid * y;
    pl += GSN;
    pl *= rid;
    pl = (pl / 100) % 10;
    return pl - 5;
}

using AI4 = array<int, 4>;
map<AI4, int> pls;

int sum_power_level(int x, int y, int sx, int sy)
{
    auto it = pls.find(AI4{x, y, sx, sy});
    if (it != pls.end()) {
        return it->second;
    }
    int pl = 0;
    int sxa = (sx + 1) / 2;
    int sxb = sx - sxa;
    int sya = (sy + 1) / 2;
    int syb = sy - sya;

    if (sxb == 0 && syb == 0) {
        assert(sxa == 1 && sya == 1);
        pl = power_level(x, y);
    } else {
        assert(sxa > 0 && sya > 0);
        pl = sum_power_level(x, y, sxa, sya);
        if (sxb > 0) {
            pl += sum_power_level(x + sxa, y, sxb, sya);
        }
        if (syb > 0) {
            pl += sum_power_level(x, y + sya, sxa, syb);
        }
        if (sxb > 0 && syb > 0) {
            pl += sum_power_level(x + sxa, y + sya, sxb, syb);
        }
    }

    pls[AI4{x, y, sx, sy}] = pl;
    return pl;
}

int main()
{
    AI3 bxys{-1, -1, -1};
    int bs = INT_MIN;
    FOR (sz, 1, <= 300) {
        printf("sz %d\n", sz);
        FOR (x, 1, <= 300 - sz) {
            FOR (y, 1, <= 300 - sz) {
                int s = sum_power_level(x, y, sz, sz);
                if (s > bs) {
                    bs = s;
                    bxys = AI3{x, y, sz};
                }
            }
        }
    }
    printf("%d,%d,%d\n", bxys[0], bxys[1], bxys[2]);
    return 0;
}

// 6:47
