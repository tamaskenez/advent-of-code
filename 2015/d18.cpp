#include "common.h"

using Board = VS;

void corners_on(Board& b)
{
    b[0][0] = '#';
    b[99][0] = '#';
    b[0][99] = '#';
    b[99][99] = '#';
}

int count_nbs(const Board& b, int r, int c)
{
    int count = 0;
    FOR (dr, -1, <= 1) {
        FOR (dc, -1, <= 1) {
            if (dr == 0 && dc == 0) {
                continue;
            }
            auto rr = r + dr;
            auto cc = c + dc;
            if (0 <= rr && rr < 100 && 0 <= cc && cc < 100) {
                auto ch = b[rr][cc];
                if (ch == '#') {
                    ++count;
                } else {
                    assert(ch == '.');
                }
            }
        }
    }
    return count;
}

Board iterate(const Board& b, int part)
{
    auto nb = b;
    FOR (r, 0, < 100) {
        FOR (c, 0, < 100) {
            int nbs = count_nbs(b, r, c);
            auto ch = b[r][c];
            if (ch == '#') {
                if (nbs == 2 || nbs == 3) {
                } else {
                    nb[r][c] = '.';
                }
            } else {
                assert(ch == '.');
                if (nbs == 3) {
                    nb[r][c] = '#';
                }
            }
        }
    }
    if (part == 2) {
        corners_on(nb);
    }
    return nb;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d18_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    FOR (part, 1, <= 2) {
        Board board(100);
        assert(~lines == 100);
        int r = 0;
        for (auto& l : lines) {
            assert(~l == 100);
            board[r++] = l;
        }
        if (part == 2) {
            corners_on(board);
        }
        FOR (i, 0, < 100) {
            board = iterate(board, part);
        }
        int count = 0;
        for (auto& row : board) {
            for (auto c : row) {
                if (c == '#') {
                    ++count;
                } else {
                    assert(c == '.');
                }
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
// 9 15