#include "common.h"

// 1 1 2 2
// 3 3 4 4
const int INPUT = 361527;
const array<AI2, 4> DIRS = {AI2{1, 0}, AI2{0, 1}, AI2{-1, 0}, AI2{0, -1}};
int main()
{
    AI2 loc{0, 0};
    int cdi = 0;
    int steps_to_next_dir = 2;
    int x = 1;
    int counter = 3;
    map<AI2, int> mem;
    bool done1 = false;
    bool done2 = false;
    mem[AI2{0, 0}] = 1;
    for (; !done1 || !done2;) {
        if (x == INPUT) {
            int d = manhattan(loc, AI2{0, 0});
            printf("part1 %d\n", d);
            done1 = true;
        }
        if (mem.count(loc) == 0) {
            int s = 0;
            FOR (dx, -1, <= 1) {
                FOR (dy, -1, <= 1) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    auto it = mem.find(loc + AI2{dx, dy});
                    if (it != mem.end()) {
                        s += it->second;
                    }
                }
            }
            mem[loc] = s;
            if (!done2 && s > INPUT) {
                printf("part2 %d\n", s);
                done2 = true;
            }
        }
        if (--steps_to_next_dir == 0) {
            cdi = (cdi + 1) % 4;
            steps_to_next_dir = (counter++) / 2;
        }
        loc += DIRS[cdi];
        ++x;
    }
    return 0;
}
