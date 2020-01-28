#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d02_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int total = 0, total2 = 0;
    for (auto& l : lines) {
        auto vs = split(l, " \t");
        VI xs;
        for (auto v : vs) {
            xs.PB(stoi(v));
        }
        auto mm = minmax_element(BE(xs));
        auto d = *mm.second - *mm.first;
        total += d;
        bool done = false;
        FOR (i, 0, < ~xs - 1) {
            FOR (j, i + 1, < ~xs) {
                auto mi = min(xs[i], xs[j]);
                auto ma = max(xs[i], xs[j]);
                if (ma % mi == 0) {
                    done = true;
                    total2 += ma / mi;
                    break;
                }
            }
            if (done) {
                break;
            }
        }
    }
    printf("%d\n", total);
    printf("%d\n", total2);
    return 0;
}
