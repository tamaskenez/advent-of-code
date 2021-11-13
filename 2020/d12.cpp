#include "common.h"

struct Ship
{
    AI2 pos{0, 0};
    AI2 heading{1, 0};
};

struct Ship2
{
    AI2 pos{0, 0};
    AI2 heading{10, 1};
};

Ship next_pos(Ship s, string cmd)
{
    int num = atoi(cmd.c_str() + 1);
    switch (cmd[0]) {
        case 'N':
            s.pos[1] += num;
            break;
        case 'S':
            s.pos[1] -= num;
            break;
        case 'E':
            s.pos[0] += num;
            break;
        case 'W':
            s.pos[0] -= num;
            break;
        case 'L':
            switch (num) {
                case 90:
                    s.heading = AI2{-s.heading[1], s.heading[0]};
                    break;
                case 180:
                    s.heading = -s.heading;
                    break;
                case 270:
                    s.heading = AI2{s.heading[1], -s.heading[0]};
                    break;
                default:
                    assert(false);
            }
            break;
        case 'R':
            switch (num) {
                case 90:
                    s.heading = AI2{s.heading[1], -s.heading[0]};
                    break;
                case 180:
                    s.heading = -s.heading;
                    break;
                case 270:
                    s.heading = AI2{-s.heading[1], s.heading[0]};
                    break;
                default:
                    assert(false);
            }
            break;
        case 'F':
            s.pos += s.heading * num;
            break;
        default:
            assert(false);
    }
    return s;
}

Ship2 next_pos2(Ship2 s, string cmd)
{
    int num = atoi(cmd.c_str() + 1);
    switch (cmd[0]) {
        case 'N':
            s.heading[1] += num;
            break;
        case 'S':
            s.heading[1] -= num;
            break;
        case 'E':
            s.heading[0] += num;
            break;
        case 'W':
            s.heading[0] -= num;
            break;
        case 'L':
            switch (num) {
                case 90:
                    s.heading = AI2{-s.heading[1], s.heading[0]};
                    break;
                case 180:
                    s.heading = -s.heading;
                    break;
                case 270:
                    s.heading = AI2{s.heading[1], -s.heading[0]};
                    break;
                default:
                    assert(false);
            }
            break;
        case 'R':
            switch (num) {
                case 90:
                    s.heading = AI2{s.heading[1], -s.heading[0]};
                    break;
                case 180:
                    s.heading = -s.heading;
                    break;
                case 270:
                    s.heading = AI2{-s.heading[1], s.heading[0]};
                    break;
                default:
                    assert(false);
            }
            break;
        case 'F':
            s.pos += s.heading * num;
            break;
        default:
            assert(false);
    }
    return s;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    {
        Ship ship;
        for (auto l : lines) {
            ship = next_pos(ship, l);
        }
        auto p1 = abs(ship.pos[0]) + abs(ship.pos[1]);
        printf("p1: %d\n", p1);
    }
    {
        Ship2 ship;
        for (auto l : lines) {
            ship = next_pos2(ship, l);
        }
        auto p2 = abs(ship.pos[0]) + abs(ship.pos[1]);
        printf("p2: %d\n", p2);
    }
    return 0;
}
// 1526
