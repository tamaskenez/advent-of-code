#include "common.h"

int count_trees(VS lines, AI2 slope)
{
    AI2 pos{0, 0};
    int W = ~lines[0];
    int c = 0;
    while (pos[0] < ~lines) {
        assert(~lines[pos[0]] == W);
        if (lines[pos[0]][pos[1]] == '#') {
            c++;
        }
        pos = AI2{pos[0] + slope[0], (pos[1] + slope[1]) % W};
    }
    return c;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d3_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int r = count_trees(lines, AI2{1, 3});
    printf("P1: %d\n", r);
    int64_t p = 1;
    for (auto slope : {AI2{1, 1}, AI2{1, 3}, AI2{1, 5}, AI2{1, 7}, AI2{2, 1}}) {
        p *= count_trees(lines, slope);
    }
    printf("P2: %lld\n", p);
    return 0;
}
// 7:42
