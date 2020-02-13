#include "common.h"

const int INPUT = 5177;
// const int INPUT = 18;

int power_level(int x, int y)
{
    int rackID = x + 10;
    int pl = rackID * y;
    pl += INPUT;
    pl *= rackID;
    pl = (pl / 100) % 10;
    pl -= 5;
    return pl;
}
using AI4 = array<int, 4>;
map<AI4, int> pls;

int big_power_level(int x, int y, int sx, int sy)
{
    auto it = pls.find(AI4{x, y, sx, sy});
    if (it != pls.end()) {
        return it->second;
    }
    int pl = 0;
    assert(0 <= x && x + sx <= 300);
    assert(0 <= y && y + sy <= 300);
    if (sx == 1 && sy == 1) {
        pl = power_level(x, y);
    } else {
        int sxa = (sx + 1) / 2;
        int sxb = sx - sxa;
        int sya = (sy + 1) / 2;
        int syb = sy - sya;
        assert(sxa != 0 && sya != 0);
        pl = big_power_level(x, y, sxa, sya);
        if (sxb > 0) {
            pl += big_power_level(x + sxa, y, sxb, sya);
        }
        if (syb > 0) {
            pl += big_power_level(x, y + sya, sxa, syb);
        }
        if (sxb > 0 && syb > 0) {
            pl += big_power_level(x + sxa, y + sya, sxb, syb);
        }
    }
    pls[AI4{x, y, sx, sy}] = pl;
    return pl;
}

int main()
{
    int bestpl = INT_MIN;
    AI3 bestxys{-1, -1, -1};
    FOR (s, 1, <= 300) {
        printf("s %d\n", s);
        FOR (y, 0, <= 300 - s) {
            FOR (x, 0, < 300 - s) {
                int pl = big_power_level(x, y, s, s);
                if (pl > bestpl) {
                    bestpl = pl;
                    bestxys = AI3{x, y, s};
                }
            }
        }
    }
    printf("%d,%d,%d\n", bestxys[0], bestxys[1], bestxys[2]);
    return 0;
}
