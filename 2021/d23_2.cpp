#include "common.h"

// const string input = "BCBDDCBADBACADCA";
const string input = "DACDDCBADBACCABB";

constexpr int ROW = 0;
constexpr int COL = 1;
constexpr int EMPTY = -1;
constexpr int AM_COUNT = 4;

// space {0, 0..10}, {1, 0..3}, {2, 0..3}, {3, 0..3}, {4, 0..3}
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
    array<array<AI2, AM_COUNT>, 4> ams;
    bool deleted = false;
    bool operator<(const GS& y) const { return min_full_cost() < y.min_full_cost(); }
    auto get_array() const
    {
        array<char, 27> a;
        a.fill('.');
        FOR (am, 0, < 4) {
            FOR (si, 0, < AM_COUNT) {
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
                    case 3:
                        a[19 + p[COL]] = ch;
                        break;
                    case 4:
                        a[23 + p[COL]] = ch;
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
    assert(0 <= p[ROW] && p[ROW] <= AM_COUNT);
    if (p[0] == 0) {
        assert(0 <= p[COL] && p[COL] <= 10);
    } else {
        assert(0 <= p[1] && p[1] <= 3);
    }
}

using Bor = array<array<int, 11>, AM_COUNT + 1>;
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
            // bor[1..to[ROW]][to[COL] must be empty
            FOR (r, 1, <= to[ROW]) {
                if (bor[r][to[COL]] != EMPTY) {
                    return false;
                }
            }
            return abs(ep - from[COL]) + to[ROW];
        };
        case 1:
        case 2:
        case 3:
        case 4: {
            int ep = entrance_pos(from[COL]);
            // bor[1..from[ROW]-1][from[COL]] must be empty
            FOR (r, 1, < from[ROW] - 1) {
                if (bor[r][from[COL]] != EMPTY) {
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

int min_remaining_cost(array<array<AI2, AM_COUNT>, 4> ams, bool debug = false)
{
    static const auto bor = get_empty_bor();
    int cost = 0;
    array<array<AI2, AM_COUNT>, 4> am_to;
    FOR (am, 0, < 4) {
        set<int> remaining_rows = {1, 2, 3, 4};
        FOR (si, 0, < AM_COUNT) {
            auto p = ams[am][si];
            if (p[ROW] != 0 && p[COL] == am) {
                auto c = remaining_rows.erase(p[ROW]);
                assert(c == 1);
            }
        }
        FOR (si, 0, < AM_COUNT) {
            auto p = ams[am][si];
            if (p[ROW] == 0 || p[COL] != am) {
                auto it = remaining_rows.begin();
                auto row = *it;
                remaining_rows.erase(it);
                am_to[am][si] = AI2{row, am};
            } else {
                am_to[am][si] = p;
            }
            assert_valid_pos(am_to[am][si]);
        }
    }
    FOR (am, 0, < 4) {
        FOR (si, 0, < AM_COUNT) {
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
    return cost>0?1:0;
}

auto get_painted_bor(const GS& gs)
{
    auto bor = get_empty_bor();
    FOR (am, 0, < 4) {
        FOR (si, 0, < AM_COUNT) {
            auto p = gs.ams[am][si];
            bor[p[ROW]][p[COL]] = am;
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
        FOR (si, 0, < AM_COUNT) {
            auto from = gs.ams[am][si];
            switch (from[ROW]) {
                case 0: {
                    // top row
                    // if A's column must be at least one empty then same
                    // otherwise can't go
                    int r = 0;
                    assert(bor[0][entrance_pos(am)] == EMPTY);
                    for (;;) {
                        if (r < AM_COUNT && bor[r + 1][am] == EMPTY) {
                            ++r;
                        } else {
                            break;
                        }
                    }

                    if (r == 0) {
                        continue;
                    }
                    int last_empty_row = r;
                    for (;;) {
                        if (r < AM_COUNT && bor[r + 1][am] == am) {
                            ++r;
                        } else {
                            break;
                        }
                    }
                    // r is the last am or last empty
                    if (r != AM_COUNT) {
                        continue;
                    }

                    auto to = AI2{last_empty_row, am};

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
                case 1:
                case 2:
                case 3:
                case 4: {
                    if (from[COL] == am) {
                        // in its column
                        // must be 0 non-am below
                        bool found_non_am = false;
                        FOR (r, from[ROW] + 1, <= AM_COUNT) {
                            if (bor[r][am] != am) {
                                found_non_am = true;
                                break;
                            }
                        }
                        if (!found_non_am) {
                            continue;
                        }
                    }
                    // 0 or more empty above
                    bool do_continue = false;
                    FOR (r, 1, < from[ROW]) {
                        if (bor[r][from[COL]] != EMPTY) {
                            do_continue = true;
                            break;
                        }
                    }
                    if (do_continue) {
                        continue;
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

    FOR (r, 1, <= AM_COUNT) {
        printf(r == 1 ? "###" : "  #");
        FOR (am, 0, < 4) {
            printf("%c#", boritem_to_char(bor[r][am]));
        }
        printf(r == 1 ? "##\n" : "\n");
    }
    printf("  #########\n");
}

void P2()
{
    GS initial;
    array<int, 4> next_am_si;
    next_am_si.fill(0);
    FOR (i, 0, < ~input) {
        auto c = input[i];
        int am = c - 'A';
        int si = next_am_si[am]++;
        assert(0 <= si && si < AM_COUNT);
        initial.ams[am][si] = AI2{i / 4 + 1, i % 4};
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

        auto it = added.find(key);
        assert(it->second == &dq.front());

        dq.pop_front();
        added.erase(it);

        if (next.min_remaining_cost == 0) {
            printf("P1: %d\n", next.cost_so_far);
            break;
        }

        //                        0123456789a0123012301230123
        if (next.get_string() == "..........DBCB.DCBADBACADCA") {
            print(next);
            printf("");
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
    P2();
    return 0;
}
