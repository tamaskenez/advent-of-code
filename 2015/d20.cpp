#include "common.h"

int N = 1000000;

int main()
{
    {
        VI vs(N);
        FOR (elfnum, 1, < N) {
            for (int k = 1; k * elfnum < N; ++k) {
                vs[k * elfnum] += 10 * elfnum;
            }
        }
        FOR (i, 1, < N) {
            if (vs[i] >= 34000000) {
                printf("%d\n", i);
                break;
            }
        }
    }
    {
        VI vs(N);
        FOR (elfnum, 1, < N) {
            for (int k = 1; k <= 50 && k * elfnum < N; ++k) {
                vs[k * elfnum] += 11 * elfnum;
            }
        }
        FOR (i, 1, < N) {
            if (vs[i] >= 34000000) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
// 6 14