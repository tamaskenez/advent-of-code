#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d03_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<AI2, int> m;
    for (auto& l : lines) {
        auto xs = split(l, "# @,:\tx");
        //#1304 @ 775,937: 15x17
        assert(~xs == 5);
        auto id = xs[0];
        auto lt = AI2{stoi(xs[1]), stoi(xs[2])};
        auto wh = AI2{stoi(xs[3]), stoi(xs[4])};
        FOR (x, lt[0], < lt[0] + wh[0]) {
            FOR (y, lt[1], < lt[1] + wh[1]) {
                ++m[AI2{x, y}];
            }
        }
    }
    int c = 0;
    for (auto& kv : m) {
        if (kv.second > 1) {
            ++c;
        }
    }
    printf("%d\n", c);

    for (auto& l : lines) {
        auto xs = split(l, "# @,:\tx");
        //#1304 @ 775,937: 15x17
        assert(~xs == 5);
        auto id = xs[0];
        auto lt = AI2{stoi(xs[1]), stoi(xs[2])};
        auto wh = AI2{stoi(xs[3]), stoi(xs[4])};
        bool ok = true;
        FOR (x, lt[0], < lt[0] + wh[0]) {
            FOR (y, lt[1], < lt[1] + wh[1]) {
                if (m[AI2{x, y}] > 1) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
        if (ok) {
            printf("%s\n", id.c_str());
        }
    }
    return 0;
}
