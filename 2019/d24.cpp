#include "common.h"

// clang-format off
const VS main_input ={
    "#..#.",
    "#.#.#",
    "...#.",
    "....#",
    "#.#.#"
};

const VS test_input={
"....#",
"#..#.",
"#..##",
"..#..",
"#...."
};
// clang-format on

const int H = 5;
const int W = 5;
bool within(AI2 x)
{
    return 0 <= x[0] && x[0] < H && 0 <= x[1] && x[1] < W;
}

vector<AI2> nbs(AI2 x)
{
    vector<AI2> r;
    auto a = AI2{x[0] - 1, x[1]};
    if (within(a)) {
        r.PB(a);
    }
    a = AI2{x[0] + 1, x[1]};
    if (within(a)) {
        r.PB(a);
    }
    a = AI2{x[0], x[1] - 1};
    if (within(a)) {
        r.PB(a);
    }
    a = AI2{x[0], x[1] + 1};
    if (within(a)) {
        r.PB(a);
    }
    return r;
}

vector<AI3> nbs(AI3 a)
{
    assert(!(a[0] == 2 && a[1] == 2));
    vector<AI3> result;
    auto [r, c, l] = a;
    for (int d : {-1, 1}) {
        auto b = AI3{r + d, c, l};
        if (b[0] == 2 && b[1] == 2) {
            FOR (i, 0, < 5) {
                result.PB(AI3{d == -1 ? 4 : 0, i, l + 1});
            }
        } else if (b[0] == -1 || b[0] == 5) {
            result.PB(AI3{d == -1 ? 1 : 3, 2, l - 1});
        } else {
            assert(within(AI2{b[0], b[1]}));
            result.PB(b);
        }
        b = AI3{r, c + d, l};
        if (b[0] == 2 && b[1] == 2) {
            FOR (i, 0, < 5) {
                result.PB(AI3{i, d == -1 ? 4 : 0, l + 1});
            }
        } else if (b[1] == -1 || b[1] == 5) {
            result.PB(AI3{2, d == -1 ? 1 : 3, l - 1});
        } else {
            assert(within(AI2{b[0], b[1]}));
            result.PB(b);
        }
    }
    return result;
}

char& at(VS& x, AI2 rc)
{
    assert(within(rc));
    assert(~x == H);
    auto& row = x[rc[0]];
    assert(~row == W);
    return row[rc[1]];
}

char at(const VS& x, AI2 rc)
{
    assert(within(rc));
    assert(~x == H);
    auto& row = x[rc[0]];
    assert(~row == W);
    return row[rc[1]];
}

VS next_phase(const VS& x)
{
    assert(~x == H && ~x[0] == W);
    VS next(H, string(W, '.'));
    FOR (r, 0, < H) {
        FOR (c, 0, < W) {
            int nb_bugs = 0;
            for (auto nb : nbs(AI2{r, c})) {
                auto ch = at(x, nb);
                if (ch == '.') {
                } else {
                    assert(ch == '#');
                    nb_bugs++;
                }
            }
            auto ch = at(x, AI2{r, c});
            if (ch == '.') {
                if (nb_bugs == 1 || nb_bugs == 2) {
                    at(next, AI2{r, c}) = '#';
                } else {
                    at(next, AI2{r, c}) = '.';
                }
            } else {
                assert(ch == '#');
                if (nb_bugs != 1) {
                    at(next, AI2{r, c}) = '.';
                } else {
                    at(next, AI2{r, c}) = '#';
                }
            }
        }
    }
    return next;
}

tuple<int, int> min_max_level(const set<AI3>& bugs)
{
    int min_level = 0;
    int max_level = 0;
    for (auto a : bugs) {
        assert(within(AI2{a[0], a[1]}));
        min_level = min(min_level, a[2]);
        max_level = max(max_level, a[2]);
    }
    return {min_level, max_level};
}

set<AI3> next_phase(const set<AI3>& bugs)
{
    set<AI3> next = bugs;
    set<AI3> locs;
    if (true) {
        for (auto& a : bugs) {
            auto v = nbs(a);
            locs.insert(BE(v));
            locs.insert(a);
        }
    } else {
        auto [mil, mal] = min_max_level(bugs);
        FOR (l, mil - 1, <= mal + 1) {
            FOR (r, 0, < 5) {
                FOR (c, 0, < 5) {
                    if (r == 2 && c == 2) {
                        continue;
                    }
                    locs.insert(AI3{r, c, l});
                }
            }
        }
    }
    for (auto& a : locs) {
        assert(within(AI2{a[0], a[1]}));
        int nb_bugs = 0;
        for (auto nb : nbs(a)) {
            if (bugs.count(nb) > 0) {
                nb_bugs++;
            }
        }
        if (bugs.count(a) == 0) {
            if (nb_bugs == 1 || nb_bugs == 2) {
                next.insert(a);
            }
        } else {
            if (nb_bugs != 1) {
                next.erase(a);
            }
        }
    }
    return next;
}

int biodiv(const VS& x)
{
    int result = 0;
    FOR (r, 0, < H) {
        FOR (c, 0, < W) {
            auto k = c + H * r;
            if (x[r][c] == '#') {
                result |= (1 << k);
            }
        }
    }
    return result;
}

void solve()
{
    set<VS> happened;
    auto eris = main_input;

    happened.insert(eris);
    for (;;) {
        auto next_eris = next_phase(eris);
        if (happened.count(next_eris) > 0) {
            printf("biodiv: %d\n", biodiv(next_eris));
            break;
        } else {
            happened.insert(next_eris);
        }
        eris = next_eris;
    };
}

void print(const set<AI3>& bugs)
{
    auto [min_level, max_level] = min_max_level(bugs);
    FOR (level, min_level, <= max_level) {
        printf("\nDepth: %d\n", level);
        FOR (r, 0, < H) {
            FOR (c, 0, < W) {
                if (bugs.count(AI3{r, c, level}) > 0) {
                    assert(!(r == 2 && c == 2));
                    printf("#");
                } else {
                    printf(r == 2 && c == 2 ? "?" : ".");
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}

void solve2()
{
    set<AI3> bugs;
    VS input;
    int N;
    if (false) {
        input = test_input;
        N = 10;
    } else {
        input = main_input;
        N = 200;
    }
    FOR (r, 0, < H) {
        FOR (c, 0, < W) {
            auto ch = input[r][c];
            if (ch == '#') {
                assert(r != 2 || c != 2);
                bugs.insert(AI3{r, c, 0});
            } else {
                assert(ch == '.');
            }
        }
    }

    printf("initial\n");
    print(bugs);
    FOR (i, 0, < N) {
        auto next_bugs = next_phase(bugs);
        bugs.swap(next_bugs);
    };
    printf("after %d steps\n", N);
    print(bugs);
    printf("bugs count after %d steps: %d", N, ~bugs);
}

int main()
{
    /*
    for (bool b : {false, true}) {
        FOR (r, 0, < 5) {
            FOR (c, 0, < 5) {
                if (r == 2 && c == 2) {
                    printf("[   ?   ] ");
                    continue;
                }
                auto v = nbs(AI3{r, c, 0});
                int n = ~v;
                sort(BE(v));
                v.erase(unique(BE(v)), v.end());
                assert(n == ~v);
                // printf("%d ", n);
                printf("[");
                for (auto x : v) {
                    if ((b && x[2] == 0) || (!b && x[2] != 0)) {
                        printf("%d,%d,%d ", x[0], x[1], x[2]);
                    }
                }
                printf("]");
            }
            printf("\n");
        }
        printf("\n");
    }
     */
    solve();
    solve2();
    return 0;
}