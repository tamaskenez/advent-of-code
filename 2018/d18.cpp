#include "common.h"

int H, W;

void count_around(const VS& board, int y, int x, int& nopen, int& ntrees, int& nlumber)
{
    nopen = ntrees = nlumber = 0;
    FOR (dy, -1, <= 1) {
        int yy = y + dy;
        if (!is_between_co(yy, 0, H)) {
            continue;
        }
        FOR (dx, -1, <= 1) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            int xx = x + dx;
            if (!is_between_co(xx, 0, W)) {
                continue;
            }
            switch (board[yy][xx]) {
                case '.':
                    ++nopen;
                    break;
                case '|':
                    ++ntrees;
                    break;
                case '#':
                    ++nlumber;
                    break;
                default:
                    UNREACHABLE;
            }
        }
    }
}
VS iterate(const VS& board)
{
    auto nb = board;
    FOR (y, 0, < ~board) {
        auto& row = board[y];
        auto& newrow = nb[y];
        FOR (x, 0, < ~row) {
            int ntrees, nlumber, nopen;
            count_around(board, y, x, nopen, ntrees, nlumber);
            switch (row[x]) {
                case '.':
                    if (ntrees >= 3) {
                        newrow[x] = '|';
                    }
                    break;
                case '|':
                    if (nlumber >= 3) {
                        newrow[x] = '#';
                    }
                    break;
                case '#':
                    if (nlumber >= 1 && ntrees >= 1) {
                        // remain
                    } else {
                        newrow[x] = '.';
                    }
                    break;
                default:
                    UNREACHABLE;
            }
        }
    }
    return nb;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d18_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    H = ~lines;
    W = ~lines[0];
    for (auto& l : lines) {
        assert(~l == W);
    }
    printf("HW %d %d\n", H, W);

    {
        auto board = lines;
        FOR (min, 0, < 10) {
            board = iterate(board);
        }
        map<char, int> counter;
        for (auto& r : board) {
            for (auto c : r) {
                ++counter[c];
            }
        }
        printf("value %d\n", counter['|'] * counter['#']);
    }

    auto value = [](const VS& board) {
        array<int, 255> counter;
        counter.fill(0);
        for (auto& r : board) {
            for (auto c : r) {
                ++counter[c];
            }
        }
        return counter['|'] * counter['#'];
    };

    {
        auto board = lines;
        map<VS, int> M;
        M[board] = 0;
        const int TOTAL = 1000000000;
        FOR (min, 0, < TOTAL) {
            board = iterate(board);

            int time_now = min + 1;
            auto it = M.find(board);
            if (it != M.end()) {
                int diff = time_now - it->second;
                printf("diff: %d\n", diff);
                int k = (TOTAL - time_now) / diff;
                min += k * diff;
            }

            M[board] = time_now;
        }
        printf("value %d\n", value(board));
    }
    return 0;
}
