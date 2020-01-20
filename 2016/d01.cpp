#include "common.h"

// enum DIR = {NORTH, WEST, SOUTH, EAST};

const array<AI2, 4> DIR_VECTORS = {AI2{0, 1}, AI2{-1, 0}, AI2{0, -1}, AI2{1, 0}};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d01_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto line = lines[0];
    //line = "R8, R4, R4, R8";
    auto vs = split(line, " ,");
    int dir = 0;
    AI2 here{0, 0};
    set<AI2> beenhere;
    beenhere.insert(here);
    bool part2ok = false;
    auto check = [&]() {
        if (!part2ok) {
            auto it = beenhere.find(here);
            if (it != beenhere.end()) {
                printf("part2 %d\n", manhattan(AI2{}, here));
                part2ok = true;
            } else {
                beenhere.insert(here);
            }
        }
    };
    for (auto& v : vs) {
        auto c = v[0];
        if (c == 'L') {
            dir = (dir + 3) % 4;
        } else if (c == 'R') {
            dir = (dir + 1) % 4;
        } else {
            assert(false);
        }
        auto num = stoi(v.substr(1));
        auto dv = DIR_VECTORS[dir];
        FOR (i, 0, < num) {
            here[0] += dv[0];
            here[1] += dv[1];
            check();
        }
    }
    printf("%d\n", manhattan(AI2{}, here));
    return 0;
}
// 7 33