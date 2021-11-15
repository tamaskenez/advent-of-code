#include "common.h"

bool is_wall(AI2 xy)
{
    const int SEED = 1362;
    auto x = xy[0];
    auto y = xy[1];
    auto sn = x * x + 3 * x + 2 * x * y + y + y * y + SEED;
    uint count = 0;
    assert(sn >= 0);
    uint n = (uint)sn;
    while (n != 0) {
        if (n & 1) {
            ++count;
        }
        n = n >> 1;
    }
    return (count & 1) == 1;
}

const array<AI2, 4> DIRS = {AI2{-1, 0}, AI2{1, 0}, AI2{0, -1}, AI2{0, 1}};
int main()
{
    AI2 start{1, 1};
    AI2 target{31, 39};
    set<AI2> visited;
    vector<AI2> front, next_front;
    bool done = false;
    front.PB(start);
    visited.insert(start);
    int steps = 0;
    for (; !done; ++steps) {
        if (steps == 50) {
            printf("at steps = 50, ~visited = %d\n", ~visited);
        }
        assert(!front.empty());
        next_front.clear();
        for (auto x : front) {
            if (x == target) {
                printf("part1 %d steps\n", steps);
                done = true;
                break;
            }
            for (auto d : DIRS) {
                auto next_loc = x + d;
                if (next_loc[0] >= 0 && next_loc[1] >= 0 && !contains(visited, next_loc) &&
                    !is_wall(next_loc)) {
                    next_front.PB(next_loc);
                    visited.insert(next_loc);
                }
            }
        }
        front.swap(next_front);
    }
    printf("---");
    return 0;
}
