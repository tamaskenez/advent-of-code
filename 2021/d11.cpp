#include "common.h"

int w = 0, h = 0;

vector<AI2> get_nbs(int r, int c)
{
    vector<AI2> nbs;
    FOR (dr, -1, <= 1) {
        FOR (dc, -1, <= 1) {
            if (dr == 0 && dc == 0) {
                continue;
            }
            auto nr = r + dr;
            auto nc = c + dc;
            if (nr < 0 || h <= nr) {
                continue;
            }
            if (nc < 0 || w <= nc) {
                continue;
            }
            nbs.push_back(AI2{nr, nc});
        }
    }
    return nbs;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d11_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    h = ~lines;
    w = ~(lines[0]);

    int64_t flash_count = 0;
    for (int step = 1;; ++step) {
        FOR (r, 0, < h) {
            FOR (c, 0, < w) {
                lines[r][c]++;
            }
        }
        set<AI2> flashed_now;
        for (;;) {
            set<AI2> flashing;
            FOR (r, 0, < h) {
                FOR (c, 0, < w) {
                    if (lines[r][c] > '9') {
                        flashing.insert(AI2{r, c});
                        flashed_now.insert(AI2{r, c});
                        lines[r][c] = '0';
                        flash_count++;
                    }
                }
            }
            if (flashing.empty()) {
                break;
            }
            for (auto f : flashing) {
                auto nbs = get_nbs(f[0], f[1]);
                for (auto nb : nbs) {
                    if (flashed_now.count(AI2{nb[0], nb[1]}) == 0) {
                        lines[nb[0]][nb[1]]++;
                    }
                }
            }
        }
        if (step == 100) {
            printf("P1: %lld\n", flash_count);
        }
        if (~flashed_now == w * h) {
            printf("P2: %d\n", step);
            break;
        }
        /*
        printf("After step %d\n",step);
        FOR (r, 0, < h) {
            printf("%s\n",lines[r].c_str());
        }
        printf("\n");*/
    }

    return 0;
}

// 20 22
