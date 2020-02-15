#include "common.h"

const AI2 DOWN{0, 1};
const AI2 UP{0, -1};
const AI2 LEFT{-1, 0};
const AI2 RIGHT{1, 0};

void print(const map<AI2, char>& M)
{
    RunningStat<int> rx, ry;
    for (auto& kv : M) {
        auto [xy, c] = kv;
        rx.add(xy[0]);
        ry.add(xy[1]);
    }
    FOR (y, *ry.lower, <= *ry.upper) {
        FOR (x, *rx.lower, <= *rx.upper) {
            auto it = M.find(AI2{x, y});
            if (it != M.end()) {
                printf("%c", it->second);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("-------------\n");
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d17_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    // y=1369, x=409..419
    // x=413, y=698..701
    map<AI2, char> M;
    RunningStat<int> rx, ry;
    for (auto& l : lines) {
        auto xs = split(l, "=, \t.");
        assert(~xs == 5);
        if (xs[0] == "x") {
            assert(xs[2] == "y");
            auto x = stoi(xs[1]);
            auto y0 = stoi(xs[3]);
            auto y1 = stoi(xs[4]);
            rx.add(x);
            ry.add(y0);
            ry.add(y1);
            assert(y0 <= y1);
            FOR (y, y0, <= y1) {
                M[AI2{x, y}] = '#';
            }
        } else if (xs[0] == "y") {
            assert(xs[2] == "x");
            auto y = stoi(xs[1]);
            auto x0 = stoi(xs[3]);
            auto x1 = stoi(xs[4]);
            assert(x0 <= x1);
            ry.add(y);
            rx.add(x0);
            rx.add(x1);
            FOR (x, x0, <= x1) {
                M[AI2{x, y}] = '#';
            }
        } else {
            UNREACHABLE;
        }
    }
    printf("x %d..%d\n", *rx.lower, *rx.upper);
    printf("y %d..%d\n", *ry.lower, *ry.upper);
    set<AI2> work;
    work.insert(AI2{500, 1});
    M[AI2{500, 0}] = '+';
    auto at = [&M](AI2 xy) {
        auto it = M.find(xy);
        if (it == M.end()) {
            return '.';
        } else {
            return it->second;
        }
    };
    set<AI2> nw;
    // print(M);
    set<AI2> check_settling;
    for (;;) {
        bool changed = false;
        nw.clear();
        // printf("~work: %d\n", ~work);
        for (auto w : work) {
            if (!is_between_cc(w[1], 1, *ry.upper)) {
                continue;
            }
            char ch = at(w);
            if (ch == '#' || ch == '~') {
                continue;
            }
            switch (ch) {
                case '|':
                    break;
                case '.': {
                    bool inserted = false;
                    if (at(w + UP) == '+' || at(w + UP) == '|') {
                        M[w] = '|';
                        nw.insert(w + LEFT);
                        nw.insert(w + RIGHT);
                        nw.insert(w + DOWN);
                        inserted = true;
                    } else {
                        auto l = at(w + LEFT);
                        auto ld = at(w + LEFT + DOWN);
                        auto r = at(w + RIGHT);
                        auto rd = at(w + RIGHT + DOWN);
                        if ((l == '|' && (ld == '#' || ld == '~')) ||
                            (r == '|' && (rd == '#' || rd == '~'))) {
                            M[w] = '|';
                            nw.insert(w + LEFT);
                            nw.insert(w + RIGHT);
                            nw.insert(w + DOWN);
                        }
                        inserted = true;
                    }
                    if (inserted) {
                        changed = true;
                        check_settling.insert(w);
                    }
                } break;
                default:
                    UNREACHABLE;
            }
            while (!check_settling.empty()) {
                auto w = *check_settling.begin();
                check_settling.erase(w);
                if (at(w) != '|') {
                    continue;
                }
                for (;;) {
                    if (at(w + LEFT) == '|') {
                        w = w + LEFT;
                        check_settling.erase(w);
                    } else {
                        break;
                    }
                }
                if (at(w + LEFT) == '#') {
                    auto x0 = w[0];
                    for (;; w += RIGHT) {
                        auto c_here = at(w);
                        auto c_down = at(w + DOWN);
                        if (c_here == '|' && (c_down == '~' || c_down == '#')) {
                            continue;
                        }
                        if (c_here == '#') {
                            FOR (x, x0, < w[0]) {
                                M[AI2{x, w[1]}] = '~';
                                check_settling.insert(AI2{x, w[1] - 1});
                                check_settling.insert(AI2{x - 1, w[1] - 1});
                                check_settling.insert(AI2{x + 1, w[1] - 1});
                                nw.insert(AI2{x, w[1] - 1});
                                nw.insert(AI2{x - 1, w[1] - 1});
                                nw.insert(AI2{x + 1, w[1] - 1});
                            }
                        }
                        break;
                    }
                }
            }
        }
        nw.swap(work);
        if (!changed) {
            break;
        }
    }
    print(M);
    int count = 0;
    int count2=0;
    for (auto& kv : M) {
        if ((kv.second == '|' || kv.second == '~') && kv.first[1] >= *ry.lower) {
            ++count;
        }
        if (kv.second == '~') {
            ++count2;
        }
    }
    printf("count %d\n", count);
    printf("count2 %d\n", count2);
    return 0;
}

// 31864 high