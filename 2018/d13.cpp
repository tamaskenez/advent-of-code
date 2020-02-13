#include "common.h"

enum Turn
{
    T_LEFT,
    T_STRAIGHT,
    T_RIGHT
};

struct Car
{
    AI2 rc, dir;
    Turn next_turn;
    bool crashed = false;
    bool operator<(const Car& b) const { return rc < b.rc; }
};

void print(map<AI2, char>& board, vector<Car> cars)
{
    RunningStat<int> mr, mc;
    for (auto& kv : board) {
        auto rc = kv.first;
        mr.add(rc[0]);
        mc.add(rc[1]);
    }
    auto H = *mr.upper + 1;
    auto W = *mc.upper + 1;

    vector<vector<char>> M(H, vector<char>(W, ' '));
    for (auto& kv : board) {
        auto rc = kv.first;
        M[rc[0]][rc[1]] = kv.second;
    }
    for (auto& c : cars) {
        auto rc = c.rc;
        char cd;
        if (c.dir == AI2{1, 0}) {
            cd = 'v';
        } else if (c.dir == AI2{-1, 0}) {
            cd = '^';
        } else if (c.dir == AI2{0, 1}) {
            cd = '>';
        } else if (c.dir == AI2{0, -1}) {
            cd = '<';
        } else {
            UNREACHABLE;
        }
        M[rc[0]][rc[1]] = cd;
    }
    printf("----------------\n");
    FOR (rix, 0, < H) {
        FOR (cix, 0, < W) {
            printf("%c", M[rix][cix]);
        }
        printf("\n");
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d13_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<AI2, char> board;
    vector<Car> cars;
    FOR (rix, 0, < ~lines) {
        auto& l = lines[rix];
        FOR (cix, 0, < ~l) {
            auto rc = AI2{rix, cix};
            auto ch = l[cix];
            switch (ch) {
                case '<':
                    cars.PB(Car{rc, AI2{0, -1}, T_LEFT});
                    break;
                case '>':
                    cars.PB(Car{rc, AI2{0, 1}, T_LEFT});
                    break;
                case '^':
                    cars.PB(Car{rc, AI2{-1, 0}, T_LEFT});
                    break;
                case 'v':
                    cars.PB(Car{rc, AI2{1, 0}, T_LEFT});
                    break;
            }
            if (ch == '<' || ch == '>') {
                ch = '-';
            } else if (ch == '^' || ch == 'v') {
                ch = '|';
            }
            assert(strchr("|-/\\ +", ch) != nullptr);
            if (ch != ' ') {
                board[rc] = ch;
            }
        }
    }
    auto cars_here = [&cars](AI2 rc) {
        VI cs;
        FOR (i, 0, < ~cars) {
            if (!cars[i].crashed && cars[i].rc == rc) {
                cs.PB(i);
            }
        }
        return cs;
    };
    print(board, cars);
    for (;;) {
        sort(BE(cars));
        for (auto& car : cars) {
            if (car.crashed) {
                continue;
            }
            auto it = board.find(car.rc);
            assert(it != board.end());
            auto ch = it->second;
            switch (ch) {
                case '|':
                    assert((car.dir == AI2{1, 0} || car.dir == AI2{-1, 0}));
                    car.rc += car.dir;
                    break;
                case '-':
                    assert((car.dir == AI2{0, 1} || car.dir == AI2{0, -1}));
                    car.rc += car.dir;
                    break;
                case '/':
                    car.dir = AI2{-car.dir[1], -car.dir[0]};
                    car.rc += car.dir;
                    break;
                case '\\':
                    car.dir = AI2{car.dir[1], car.dir[0]};
                    car.rc += car.dir;
                    break;
                case '+':
                    switch (car.next_turn) {
                        case T_LEFT:
                            car.dir = AI2{-car.dir[1], car.dir[0]};
                            break;
                        case T_STRAIGHT:
                            break;
                        case T_RIGHT:
                            car.dir = AI2{car.dir[1], -car.dir[0]};
                            break;
                        default:
                            UNREACHABLE;
                    }
                    car.next_turn = (Turn)((car.next_turn + 1) % 3);
                    car.rc += car.dir;
                    break;
                default:
                    UNREACHABLE;
            }
            auto caridcs = cars_here(car.rc);
            if (~caridcs > 1) {
                printf("crash %d,%d\n", car.rc[1], car.rc[0]);
                assert(~caridcs == 2);
                cars[caridcs[0]].crashed = true;
                cars[caridcs[1]].crashed = true;
            }
            // print(board, cars);
        }
        int nchars = 0;
        for (auto& c : cars) {
            if (!c.crashed) {
                ++nchars;
            }
        }
        if(nchars==1){
            for (auto& c : cars) {
                if (!c.crashed) {
                    printf("last char %d,%d\n",c.rc[1],c.rc[0]);
                    exit(0);
                }
            }
        }
    }
    return 0;
}
