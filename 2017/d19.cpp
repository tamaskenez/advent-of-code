#include "common.h"

// D R U L
const array<AI2, 4> DIRS = {
    AI2{1, 0},
    AI2{0, 1},
    AI2{-1, 0},
    AI2{0, -1},
};

AI2 left(AI2 d)
{
    return AI2{-d[1], d[0]};
}

AI2 right(AI2 d)
{
    return AI2{d[1], -d[0]};
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d19_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(!lines.empty());
    const int W = ~(lines[0]);
    const int H = ~lines;
    for (auto& l : lines) {
        assert(~l == W);
    }
    printf("HW %d %d\n", H, W);
    auto dir = AI2{1, 0};
    auto pos = AI2{0, (int)lines[0].find('|')};
    printf("start %d %d\n", pos[0], pos[1]);
    auto at = [&lines](AI2 a) {
        auto r = a[0];
        auto c = a[1];
        if (r < 0 || r >= ~lines) {
            return ' ';
        }
        auto& line = lines[r];
        if (c < 0 || c == ~line) {
            return ' ';
        }
        return line[c];
    };
    string enc;
    int steps_went = 0;
    for (;;) {
        auto ch = at(pos);
        printf("at %d %d\n", pos[0], pos[1]);
        if (ch == '|' || ch == '-') {
            pos += dir;
        } else if (isalpha(ch)) {
            printf("found %c\n", ch);
            enc += ch;
            pos += dir;
        } else if (ch == '+') {
            auto pos2 = pos + dir;
            if (at(pos2) == '|' || at(pos2) == '-') {
                pos += dir;
            } else {
                auto dirleft = left(dir);
                auto dirright = right(dir);
                auto cleft = at(pos + dirleft);
                auto cright = at(pos + dirright);
                if (cleft == ' ') {
                    assert(cright == '|' || cright == '-');
                    dir = dirright;
                    pos += dir;
                } else if (cright == ' ') {
                    assert(cleft == '|' || cleft == '-');
                    dir = dirleft;
                    pos += dir;
                } else {
                    UNREACHABLE;
                }
            }
        } else {
            UNREACHABLE;
        }
        ++steps_went;
    }
    return 0;
}
