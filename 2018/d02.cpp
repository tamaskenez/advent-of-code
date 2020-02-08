#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d02_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int c2 = 0, c3 = 0;
    for (auto& l : lines) {
        map<char, int> m;
        for (auto c : l) {
            ++m[c];
        }
        bool b2 = false;
        bool b3 = false;
        for (auto& kv : m) {
            if (kv.second == 2) {
                b2 = true;
            }
            if (kv.second == 3) {
                b3 = true;
            }
        }
        if (b2) {
            ++c2;
        }
        if (b3) {
            ++c3;
        }
    }
    printf("%d\n", c2 * c3);
    FOR (i, 0, < ~lines - 1) {
        auto si = lines[i];
        FOR (j, i + 1, < ~lines) {
            auto sj = lines[j];
            assert(~si == ~sj);
            int d = 0;
            FOR (k, 0, < ~si) {
                if (si[k] != sj[k]) {
                    ++d;
                }
            }
            if (d == 1) {
                printf("%s\n%s\n", si.c_str(), sj.c_str());
                exit(0);
            }
        }
    }
    return 0;
}
