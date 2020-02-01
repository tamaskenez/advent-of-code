#include "common.h"

int calcsteps(int x0, int y0)
{
    auto x = abs(x0);
    auto y = abs(y0);
    auto steps1 = min(abs(x), abs(y));
    x -= steps1;
    y -= steps1;
    if (x == 0) {
        int r = 0;
        r += y / 2;
        y -= 2 * r;
        if (y == 0) {
            return r + steps1;
        }
        UNREACHABLE;
        return 0;
    } else if (y == 0) {
        int r = 0;
        r += x / 2;
        x -= 2 * r;
        if (x == 0) {
            return r + steps1;
        }
        UNREACHABLE;
        return 0;
    } else {
        UNREACHABLE;
        return 0;
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d11_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto ss = split(lines[0], ",");
    int x = 0;
    int y = 0;
    RunningStat<int> maxs;
    for (auto& s : ss) {
        if (s == "n") {
            y += 2;
        } else if (s == "ne") {
            ++y;
            ++x;
        } else if (s == "se") {
            --y;
            ++x;
        } else if (s == "s") {
            y -= 2;
        } else if (s == "sw") {
            --y;
            --x;
        } else if (s == "nw") {
            ++y;
            --x;
        } else {
            UNREACHABLE;
        }
        auto r = calcsteps(x, y);
        maxs.add(r);
    }
    auto r1 = calcsteps(x, y);
    printf("part1 %d\n", r1);
    printf("part2 %d\n", *maxs.upper);
    return 0;
}
