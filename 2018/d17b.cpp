#include <algorithm>
#include <string>
#include <thread>
#include <vector>

#include "common.h"

void print(const map<AI2, char>& M)
{
    printf("--------------\n");
    RunningStat<int> rx, ry;
    for (auto& kv : M) {
        auto [xy, c] = kv;
        rx.add(xy[0]);
        ry.add(xy[1]);
    }
    FOR (y, *ry.lower, <= *ry.upper) {
        FOR (x, *rx.lower, <= *rx.upper) {
            auto it = M.find(AI2{x, y});
            if (it == M.end()) {
                printf(".");
            } else {
                printf("%c", it->second);
            }
        }
        printf("\n");
    }
}

const AI2 DOWN{0, 1};
const AI2 UP{0, -1};
const AI2 LEFT{-1, 0};
const AI2 RIGHT{1, 0};

char bat(const map<AI2, char>& M, AI2 xy)
{
    auto it = M.find(xy);
    return it == M.end() ? '.' : it->second;
}

void drop(map<AI2, char>& M, AI2 from, int maxy)
{
    for (;;) {
        auto xy = from;
        auto ch = bat(M, xy);
        assert(contains("|+", ch));

        // go down until ~ or #
        for (auto next = xy + DOWN;; tie(xy, next) = MKP(next, next + DOWN)) {
            if (next[1] > maxy) {
                return;
            }
            ch = bat(M, next);
            if (contains("~#", ch)) {
                break;
            }
            if (ch == '.') {
                M[next] = '|';
            } else {
                assert(ch == '|');
            }
        }

        // go horizontally from xy
        assert(contains("~#", bat(M, xy + DOWN)));

        maybe<AI2> left_wall, right_wall;
        for (int dir : {-1, 1}) {
            auto loc = xy;
            for (;;) {
                auto next_loc = loc + AI2{dir, 0};
                auto l = bat(M, next_loc);
                if (l == '#') {
                    if (dir == -1) {
                        left_wall = next_loc;
                    } else {
                        right_wall = next_loc;
                    }
                    break;
                }
                if (l == '.') {
                    M[next_loc] = '|';
                } else {
                    assert(l == '|');
                }
                auto d = bat(M, next_loc + DOWN);
                if (d == '.') {
                    drop(M, next_loc, maxy);
                }
                d = bat(M, next_loc + DOWN);
                if (d == '|') {
                    break;
                }
                assert(contains("~#", d));
                loc = next_loc;
            }
        }
        bool again = false;
        if (left_wall && right_wall) {
            FOR (x, (*left_wall)[0] + 1, < (*right_wall)[0]) {
                auto loc = AI2{x, xy[1]};
                assert(bat(M, loc) == '|');
                M[loc] = '~';
            }
            again = from[1] + 1 < xy[1];
        }
        if (!again) {
            break;
        }
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d17_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<AI2, char> M;
    RunningStat<int> rx, ry;
    for (auto& l : lines) {
        // x=399, y=626..636
        // x=511, y=1234..1250
        auto a = split(l, "=, xy.\t");
        auto b = split(l, "=, .\t");
        auto ai = map_to_vec(a, CALL(stoi));
        assert(~ai == 3);
        if (b[0] == "x") {
            assert(b[2] == "y");
            auto x = ai[0];
            auto y0 = ai[1];
            auto y1 = ai[2];
            assert(y0 <= y1);
            FOR (y, y0, <= y1) {
                M[AI2{x, y}] = '#';
                rx.add(x);
                ry.add(y);
            }
        } else if (b[0] == "y") {
            assert(b[2] == "x");
            auto y = ai[0];
            auto x0 = ai[1];
            auto x1 = ai[2];
            assert(x0 <= x1);
            FOR (x, x0, <= x1) {
                M[AI2{x, y}] = '#';
                rx.add(x);
                ry.add(y);
            }
        } else {
            UNREACHABLE;
        }
    }
    M[AI2{500, 0}] = '+';

    drop(M, AI2{500, 0}, *ry.upper);

    print(M);

    int count = 0;
    for (auto& kv : M) {
        auto [xy, c] = kv;
        if (contains("|~", c) && is_between_cc(xy[1], *ry.lower, *ry.upper)) {
            ++count;
        }
    }
    printf("count %d\n", count);
    return 0;
}
