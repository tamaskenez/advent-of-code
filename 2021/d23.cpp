#include "common.h"

// const string input = "BCBDADCA";
const string input = "DACDCABB";

constexpr int ROW = 0;
constexpr int COL = 1;
constexpr int EMPTY = -1;

// space {0,0..10}, {1,0..3}, {2,0..3}
char boritem_to_char(int a)
{
    if (a == EMPTY) {
        return '.';
    } else {
        return (char)a + 'A';
    }
}
struct GS
{
    int cost_so_far = 0;
    int min_remaining_cost = 0;
    int min_full_cost() const { return cost_so_far + min_remaining_cost; }
    array<array<AI2, 2>, 4> ams;
    bool deleted = false;
    bool operator<(const GS& y) const { return min_full_cost() < y.min_full_cost(); }
    auto get_array() const
    {
        array<char, 19> a;
        a.fill('.');
        FOR (am, 0, < 4) {
            FOR (si, 0, < 2) {
                auto p = ams[am][si];
                auto ch = boritem_to_char(am);
                switch (p[ROW]) {
                    case 0:
                        a[p[COL]] = ch;
                        break;
                    case 1:
                        a[11 + p[COL]] = ch;
                        break;
                    case 2:
                        a[15 + p[COL]] = ch;
                        break;
                    default:
                        assert(false);
                }
            }
        }
        return a;
    }
    string get_string() const
    {
        auto a = get_array();
        return string(BE(a));
    }
};

// 0123456789a
// ...........
// ..0.1.2.3..
int entrance_pos(int am)
{
    assert(0 <= am && am < 4);
    const int ep[4] = {2, 4, 6, 8};
    return ep[am];
}

int am_cost(int am)
{
    assert(0 <= am && am < 4);
    const int ep[4] = {1, 10, 100, 1000};
    return ep[am];
}

void assert_valid_pos(AI2 p)
{
    assert(0 <= p[0] && p[0] <= 2);
    if (p[0] == 0) {
        assert(0 <= p[1] && p[1] <= 10);
    } else {
        assert(0 <= p[1] && p[1] <= 3);
    }
}

using Bor = array<array<int, 11>, 3>;
auto get_empty_bor()
{
    Bor bor;
    for (auto& a : bor) {
        for (auto& b : a) {
            b = EMPTY;
        }
    }
    return bor;
}

optional<int> get_dist(const Bor& bor, AI2 from, AI2 to)
{
    assert_valid_pos(from);
    assert_valid_pos(to);
    assert(from != to);

    if (from[ROW] != 0 && to[ROW] != 0) {
        auto dir = sgn(to[COL] - from[COL]);
        int stopover = entrance_pos(from[COL]) + dir;
        return get_dist(bor, from, AI2{0, stopover}).value() +
               get_dist(bor, AI2{0, stopover}, to).value();
    }

    switch (from[ROW]) {
        case 0: {
            // top row
            int ep = entrance_pos(to[COL]);
            assert(from[COL] != ep);
            auto dir = sgn(ep - from[COL]);
            for (auto col = from[COL] + dir; col != ep + dir; col += dir) {
                if (bor[0][col] != EMPTY) {
                    return nullopt;
                }
            }
            if (bor[1][to[1]] != EMPTY) {
                return nullopt;
            }
            if (to[ROW] == 2) {
                if (bor[2][to[COL]] != EMPTY) {
                    return nullopt;
                }
            }
            return abs(ep - from[COL]) + to[ROW];
        };
        case 1:
        case 2: {
            int ep = entrance_pos(from[COL]);
            if (from[ROW] == 2) {
                if (bor[1][from[COL]] != EMPTY) {
                    return nullopt;
                }
            }
            auto dir = sgn(to[COL] - ep);
            assert(dir != 0);
            for (auto col = ep; col != to[COL] + dir; col += dir) {
                if (bor[0][col] != EMPTY) {
                    return nullopt;
                }
            }
            return abs(to[COL] - ep) + from[ROW];
        } break;
        default:
            assert(false);
    }
}

int min_remaining_cost(array<array<AI2, 2>, 4> ams, bool debug = false)
{
    static const auto bor = get_empty_bor();
    int cost = 0;
    array<array<AI2, 2>, 4> am_to;
    FOR (am, 0, < 4) {
        auto p0 = ams[am][0];
        auto p1 = ams[am][1];
        if (p0[ROW] > 0 && p0[COL] == am) {
            am_to[am][0] = p0;
            if (p1[ROW] > 0 && p1[COL] == am) {
                am_to[am][1] = p1;
            } else {
                am_to[am][1] = AI2{3 - p0[ROW], am};
            }
        } else {
            if (p1[ROW] > 0 && p1[COL] == am) {
                am_to[am][1] = p1;
                am_to[am][0] = AI2{3 - p1[ROW], am};
            } else {
                am_to[am][0] = AI2{1, am};
                am_to[am][1] = AI2{2, am};
            }
        }
        assert_valid_pos(am_to[am][0]);
        assert_valid_pos(am_to[am][1]);
    }
    FOR (am, 0, < 4) {
        FOR (si, 0, < 2) {
            auto from = ams[am][si];
            auto to = am_to[am][si];
            if (from == to) {
                continue;
            }
            auto dist = get_dist(bor, from, to).value();
            if (debug) {
                printf("%c: %d %d -> %d %d: %d\n", boritem_to_char(am), from[0], from[1], to[0],
                       to[1], dist);
            }
            cost += am_cost(am) * dist;
        }
    }
    return cost;
}

auto get_painted_bor(const GS& gs)
{
    auto bor = get_empty_bor();
    FOR (am, 0, < 4) {
        FOR (si, 0, < 2) {
            auto p = gs.ams[am][si];
            bor[p[0]][p[1]] = am;
        }
    }
    return bor;
}

void print(const GS& gs);

vector<GS> generate_next_steps(const GS& gs)
{
    auto bor = get_painted_bor(gs);
    vector<GS> nexts;
    FOR (am, 0, < 4) {
        FOR (si, 0, < 2) {
            auto from = gs.ams[am][si];
            switch (from[ROW]) {
                case 0: {
                    // top row
                    // if A's cell is like
                    // .. go to bottom
                    // .A go to top
                    // otherwise can't go
                    if (bor[1][am] != EMPTY) {
                        continue;
                    }
                    AI2 to;
                    if (bor[2][am] == EMPTY) {
                        to = AI2{2, am};
                    } else if (bor[2][am] == am) {
                        to = AI2{1, am};
                    } else {
                        continue;
                    }
                    auto dist = get_dist(bor, from, to);
                    if (!dist) {
                        continue;
                    }
                    GS next = gs;
                    next.cost_so_far += am_cost(am) * *dist;
                    next.ams[am][si] = to;
                    next.min_remaining_cost = min_remaining_cost(next.ams);
                    nexts.PB(next);
                } break;
                case 1: {
                    if (from[COL] == am) {
                        if (bor[2][am] == am) {
                            // own room AA -> no next step
                            continue;
                        }  // else own room AX -> go up
                    }      // else different room -> go up

                    assert(bor[2][from[COL]] != EMPTY);
                    // Must go up first
                    for (auto col : {0, 1, 3, 5, 7, 9, 10}) {
                        auto to = AI2{0, col};
                        auto dist = get_dist(bor, from, to);
                        if (dist) {
                            auto next = gs;
                            next.ams[am][si] = to;
                            next.cost_so_far += *dist * am_cost(am);
                            next.min_remaining_cost = min_remaining_cost(next.ams);
                            nexts.PB(next);
                        }
                    }
                } break;
                case 2: {
                    if (from[COL] == am) {
                        // Don't go anywhere.
                        continue;
                    } else {
                        // different room -> go up
                        if (bor[1][from[COL]] != EMPTY) {
                            continue;
                        }
                    }

                    // Must go up first
                    for (auto col : {0, 1, 3, 5, 7, 9, 10}) {
                        auto to = AI2{0, col};
                        auto dist = get_dist(bor, from, to);
                        if (dist) {
                            auto next = gs;
                            next.ams[am][si] = to;
                            next.cost_so_far += *dist * am_cost(am);
                            next.min_remaining_cost = min_remaining_cost(next.ams);
                            nexts.PB(next);
                        }
                    }
                } break;
                default:
                    assert(false);
            }
        }
    }
    for (auto& n : nexts) {
        if (n.min_full_cost() < gs.min_full_cost()) {
            print(gs);
            print(n);
            auto mrc0 = min_remaining_cost(gs.ams, true);
            auto mrc1 = min_remaining_cost(n.ams, true);
            printf("");
        }
        assert(n.min_full_cost() >= gs.min_full_cost());
    }
    return nexts;
}

void print(const GS& gs)
{
    printf("cfr: %d mrc: %d\n", gs.cost_so_far, gs.min_remaining_cost);
    auto bor = get_painted_bor(gs);
    printf("#############\n");
    printf("#");
    for (auto am : bor[0]) {
        printf("%c", boritem_to_char(am));
    }
    printf("#\n");

    FOR (r, 1, <= 2) {
        printf("###");
        FOR (am, 0, < 4) {
            printf("%c#", boritem_to_char(bor[r][am]));
        }
        printf("##\n");
    }
    printf("#########\n");
}

void P1()
{
    GS initial;
    set<int> am_done;
    FOR (i, 0, < ~input) {
        auto c = input[i];
        int am = c - 'A';
        int si = 0;
        if (am_done.count(am) > 0) {
            si = 1;
        }
        am_done.insert(am);
        initial.ams[am][si] = AI2{i < 4 ? 1 : 2, i % 4};
    }
    initial.min_remaining_cost = min_remaining_cost(initial.ams);
    print(initial);
    printf("%s\n", initial.get_string().c_str());

    int step = 0;
    map<int, deque<GS>> nexts;
    unordered_map<string, int> done;
    unordered_map<string, GS*> added;

    auto& dq = nexts[initial.min_full_cost()];
    dq.PB(initial);
    added.insert(make_pair(initial.get_string(), &dq.back()));

    while (!nexts.empty()) {
        auto it_begin = nexts.begin();

        if (it_begin->second.empty()) {
            nexts.erase(it_begin);
            continue;
        }

        auto& dq = it_begin->second;

        auto next = dq.front();

        if (next.deleted) {
            dq.pop_front();
            continue;
        }

        auto key = next.get_string();
        //          0123456789a01230123
        if (key == "...B.C.....B..DADCA") {
            print(next);
            printf("");
        }
        auto it = added.find(key);
        assert(it->second == &dq.front());

        dq.pop_front();
        added.erase(it);

        if (next.min_remaining_cost == 0) {
            printf("P1: %d\n", next.cost_so_far);
            break;
        }

        auto itb = done.insert(make_pair(next.get_string(), next.cost_so_far));
        assert(itb.second);

        printf("step %d, mfc %d (%d+%d) ~nexts %d\n", step++, next.min_full_cost(),
               next.cost_so_far, next.min_remaining_cost, ~nexts);
        auto further_nexts = generate_next_steps(next);

        for (auto& n : further_nexts) {
            auto key = n.get_string();
            {
                auto it = done.find(key);
                if (it != done.end()) {
                    assert(it->second <= n.cost_so_far);
                    continue;
                }
            }
            auto it = added.find(key);
            if (it == added.end()) {
                auto& dqq = nexts[n.min_full_cost()];
                dqq.PB(n);
                added.insert(make_pair(move(key), &dqq.back()));
            } else {
                assert(!it->second->deleted);
                if (n.cost_so_far < it->second->cost_so_far) {
                    it->second->deleted = true;
                    auto& dqq = nexts[n.min_full_cost()];
                    dqq.PB(n);
                    it->second = &dqq.back();
                }
            }
        }
    }
    printf("Done.\n");
}

int main()
{
    P1();
    return 0;
}
