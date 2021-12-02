#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d01_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    maybe<int> prev;
    int c = 0;
    vector<int> vs;
    for (auto l : lines) {
        l = trim(l);
        if (~l == 0) {
            continue;
        }
        int n = atoi(l.c_str());
        if (prev && n > *prev) {
            ++c;
        }
        prev = n;
        vs.PB(n);
    }
    printf("%d\n", c);
    int d = 0;
    for (int i = 1; i + 3 <= ~vs; ++i) {
        int prev = vs[i - 1] + vs[i] + vs[i + 1];
        int n = vs[i] + vs[i + 1] + vs[i + 2];
        if (prev < n) {
            ++d;
        }
    }
    printf("%d\n", d);
    return 0;
}
