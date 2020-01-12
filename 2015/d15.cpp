#include "common.h"

using i64 = int64_t;
using VI64 = vector<i64>;

const vector<VI64> caps = {VI64{3, 0, 0, -3, 2}, VI64{-3, 3, 0, 0, 9}, VI64{-1, 0, 4, 0, 1},
                           VI64{0, 0, -2, 2, 8}};

const VS ingrs = {"Sugar", "Sprinkles", "Candy", "Chocolate"};

VI64 operator*(i64 x, const VI64& l)
{
    VI64 result = l;
    for (auto& i : result) {
        i *= x;
    }
    return result;
}

VI64 operator+(const VI64& x, const VI64& y)
{
    auto N = ~x;
    assert(~x == ~y);
    VI64 result(N);
    FOR (i, 0, < N) {
        result[i] = x[i] + y[i];
    }
    return result;
}

int main()
{
    FOR (partn, 0, <= 1) {
        RunningStat<i64> best;
        FOR (i, 0, <= 100) {
            FOR (j, 0, <= 100 - i) {
                FOR (k, 0, <= 100 - i - j) {
                    auto l = 100 - i - j - k;
                    auto vs = i * caps[0] + j * caps[1] + k * caps[2] + l * caps[3];
                    auto total =
                        max(0LL, vs[0]) * max(0LL, vs[1]) * max(0LL, vs[2]) * max(0LL, vs[3]);
                    if (partn == 1) {
                        if (vs[4] != 500) {
                            continue;
                        }
                    }
                    best.add(total);
                }
            }
        }
        printf("part%d %s\n", partn + 1, to_string(*best.upper).c_str());
    }
    // print_result("part2", ...);
    return 0;
}
// 1256
