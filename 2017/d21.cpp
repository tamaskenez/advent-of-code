#include "common.h"

const VS INPUT = {".#.", "..#", "###"};

bool is_samex(const VS& board, int r, int c, int N, const VS& pattern, int rotcode)
{
    FOR (i, 0, < N) {
        FOR (j, 0, < N) {
            auto c1 = board[r + i][c + j];
            int a = i, b = j;
            if (rotcode & 4) {
                a = N - i - 1;
            }
            switch (rotcode & 3) {
                case 0:
                    break;
                case 1:
                    tie(a, b) = make_tuple(b, N - a - 1);
                    break;
                case 2:
                    tie(a, b) = make_tuple(N - a - 1, N - b - 1);
                    break;
                case 3:
                    tie(a, b) = make_tuple(N - b - 1, a);
                    break;
                default:
                    UNREACHABLE;
            }
            auto c2 = pattern[a][b];
            if (c1 != c2) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    map<VS, VS> patterns2;
    map<VS, VS> patterns3;
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d21_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    for (auto& l : lines) {
        auto xs = split(l, "=> \t");
        assert(~xs == 2);
        auto s0 = split(xs[0], "/");
        auto s1 = split(xs[1], "/");
        assert(~s0 + 1 == ~s1);
        if (~s0 == 2) {
            patterns2[s0] = s1;
        } else {
            assert(~s0 == 3);
            patterns3[s0] = s1;
        }
    }
    auto board = INPUT;
    FOR (iter, 0, < 18) {
        const int S = ~board;
        if (S % 2 == 0) {
            VS nextboard(S / 2 * 3, string(S / 2 * 3, ' '));
            for (int r = 0; r < S; r += 2) {
                for (int c = 0; c < S; c += 2) {
                    vector<VS> rhss;
                    for (auto& kv : patterns2) {
                        FOR (rotcode, 0, < 8) {
                            if (is_samex(board, r, c, 2, kv.first, rotcode)) {
                                rhss.PB(kv.second);
                                break;
                            }
                        }
                    }
                    assert(~rhss == 1);
                    int r3 = r / 2 * 3;
                    int c3 = c / 2 * 3;
                    auto& rhs = rhss[0];
                    assert(~rhs == 3 && ~(rhs[0]) == 3);
                    FOR (i, 0, < 3) {
                        FOR (j, 0, < 3) {
                            nextboard[r3 + i][c3 + j] = rhs[i][j];
                        }
                    }
                }
            }
            board.swap(nextboard);
        } else {
            assert(S % 3 == 0);
            VS nextboard(S / 3 * 4, string(S / 3 * 4, ' '));
            for (int r = 0; r < S; r += 3) {
                for (int c = 0; c < S; c += 3) {
                    vector<VS> rhss;
                    for (auto& kv : patterns3) {
                        FOR (rotcode, 0, < 8) {
                            if (is_samex(board, r, c, 3, kv.first, rotcode)) {
                                rhss.PB(kv.second);
                                break;
                            }
                        }
                    }
                    assert(~rhss == 1);
                    int r3 = r / 3 * 4;
                    int c3 = c / 3 * 4;
                    auto& rhs = rhss[0];
                    assert(~rhs == 4 && ~(rhs[0]) == 4);
                    FOR (i, 0, < 4) {
                        FOR (j, 0, < 4) {
                            nextboard[r3 + i][c3 + j] = rhs[i][j];
                        }
                    }
                }
            }
            board.swap(nextboard);
        }
        printf("--- AFTER %d ---\n", iter + 1);
        int count = 0;
        FOR (i, 0, < ~board) {
            auto& row = board[i];
            assert(~board == ~row);
            FOR (j, 0, < ~row) {
                auto ch = row[j];
                if (ch == '#') {
                    ++count;
                }
                printf("%c", ch);
            }
            printf("\n");
        }
        printf("count: %d\n", count);
    }
    return 0;
}

// not 57