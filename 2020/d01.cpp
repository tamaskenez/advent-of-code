#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d1_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<long> xs;
    for (auto l : lines) {
        xs.PB(atol(l.c_str()));
    }
    FOR (i, 0, < ~xs - 1) {
        if (xs[i] > 2020) {
            continue;
        }
        FOR (j, i + 1, < ~xs) {
            if (xs[i] + xs[j] == 2020) {
                printf("sum of two %ld  \n", xs[i] * xs[j]);
            }
        }
    }
    FOR (i, 0, < ~xs - 2) {
        if (xs[i] > 2020) {
            continue;
        }
        FOR (j, i + 1, < ~xs - 1) {
            if (xs[i] + xs[j] > 2020) {
                continue;
            }
            FOR (k, 0, < ~xs) {
                if (xs[i] + xs[j] + xs[k] == 2020) {
                    printf("sum of three %ld\n", xs[i] * xs[j] * xs[k]);
                }
            }
        }
    }
    return 0;
}
