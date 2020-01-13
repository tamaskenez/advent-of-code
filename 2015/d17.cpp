#include "common.h"

const VI main_input = {33, 14, 18, 20, 45, 35, 16, 35, 1,  13,
                       18, 13, 50, 44, 48, 6,  24, 41, 30, 42};

int solve(const VI& xs)
{
    const int N = ~xs;
    int count = 0;
    FOR (i, 0, < (1 << N)) {
        int total = 0;
        FOR (j, 0, < N) {
            if (i & (1 << j)) {
                total += xs[j];
            }
            if (total > 150) {
                break;
            }
        }
        if (total == 150) {
            ++count;
        }
    }
    return count;
}

int solve2(const VI& xs)
{
    const int N = ~xs;
    int count = 0;
    int n_containers = INT_MAX;
    FOR (i, 0, < (1 << N)) {
        int total = 0;
        int nc = 0;
        FOR (j, 0, < N) {
            if (i & (1 << j)) {
                total += xs[j];
                ++nc;
            }
            if (total > 150) {
                break;
            }
        }
        if (total == 150) {
            if (nc < n_containers) {
                n_containers = nc;
                count = 1;
            } else if (nc == n_containers) {
                ++count;
            }
        }
    }
    return count;
}

int main()
{
    auto r = solve(main_input);
    printf("%d\n", r);
    r = solve2(main_input);
    printf("%d\n", r);
    return 0;
}
// 4 46
// 7 16