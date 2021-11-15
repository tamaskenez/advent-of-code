#include "common.h"

AI2 right(AI2 dir)
{
    return AI2{dir[1], -dir[0]};
}

AI2 left(AI2 dir)
{
    return AI2{-dir[1], dir[0]};
}

void solve1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

#if 0
    lines.resize(3);
    lines[0] = "..#";
    lines[1] = "#..";
    lines[2] = "...";
#endif
    set<AI2> board;
    int row = 0;
    const int H = ~lines;
    const int W = ~lines[0];
    for (auto& l : lines) {
        assert(~l == W);
        int col = 0;
        for (auto c : l) {
            if (c == '#') {
                board.insert(AI2{row, col});
            }
            ++col;
        }
        ++row;
    }
    assert(W & 1);
    assert(H & 1);

    AI2 carrier{W / 2, H / 2};
    AI2 dir{-1, 0};
    int bc = 0;
    FOR (i, 0, < 10000) {
        if (contains(board, carrier)) {
            dir = right(dir);
            board.erase(carrier);
        } else {
            dir = left(dir);
            board.insert(carrier);
            ++bc;
        }
        carrier += dir;
    }
    printf("~board %d\n", ~board);
    printf("bc %d\n", bc);
}

void solve2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

#if 0
    lines.resize(3);
    lines[0] = "..#";
    lines[1] = "#..";
    lines[2] = "...";
#endif
    map<AI2, char> board;
    int row = 0;
    const int H = ~lines;
    const int W = ~lines[0];
    for (auto& l : lines) {
        assert(~l == W);
        int col = 0;
        for (auto c : l) {
            if (c == '#') {
                board[AI2{row, col}] = 'I';
            }
            ++col;
        }
        ++row;
    }
    assert(W & 1);
    assert(H & 1);

    AI2 carrier{W / 2, H / 2};
    AI2 dir{-1, 0};
    int bc = 0;
    FOR (i, 0, < 10000000) {
        auto it = board.find(carrier);
        if (it != board.end()) {
            switch (it->second) {
                case 'W':
                    // no turn
                    it->second = 'I';
                    ++bc;
                    break;
                case 'I':
                    dir = right(dir);
                    it->second = 'F';
                    break;
                case 'F':
                    dir = AI2{-dir[0], -dir[1]};
                    board.erase(carrier);
                    break;
                default:
                    UNREACHABLE;
            }
        } else {
            dir = left(dir);
            board[carrier] = 'W';
        }
        carrier += dir;
    }
    printf("bc %d\n", bc);
}

int main()
{
    // solve1();
    solve2();
}
// 810 not