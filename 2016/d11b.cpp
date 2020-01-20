#include "common.h"

/*
1. POG, THG THM PRG RUG, RUM COG COM
2. POM PRM
*/

//#define TEST
#ifdef TEST
enum Elems
{
    HY,
    LI,
    N_ELEMS
};
const char* ELEM_NAMES[] = {"HY", "LI"};
#else
enum Elems
{
    PO,
    TH,
    PR,
    RU,
    CO,
    N_ELEMS
};
const char* ELEM_NAMES[] = {"PO","TH","PR","RU","CO"};
#endif

const int N_FLOORS = 4;
struct Floor
{
    bitset<N_ELEMS> ms, gs;

    bool is_good() const
    {
        if (ms.none() || gs.none()) {
            return true;
        }
        FOR (i, 0, < N_ELEMS) {
            if (ms[i] && !gs[i]) {
                return false;
            }
        }
        return true;
    }
    string hash_string() const { return to_string(ms.to_ulong()) + "," + to_string(gs.to_ulong()); }
};

struct State
{
    int elev = 0;
    array<Floor, N_FLOORS> floors;
    bool is_good() const
    {
        assert_between_co(elev, 0, N_FLOORS);
        int total = 0;
        for (auto& fl : floors) {
            total += fl.ms.count() + fl.gs.count();
            if (!fl.is_good()) {
                return false;
            }
        }
        assert(total == 2 * N_ELEMS);
        return true;
    }
    string hash_string() const
    {
        string r = to_string(elev);
        for (auto& fl : floors) {
            r += ";";
            r += fl.hash_string();
        }
        return r;
    }
    void move_m(int elem_ix, int from_floor, int to_floor)
    {
        assert_between_co(elem_ix, 0, (int)N_ELEMS);
        assert_between_co(from_floor, 0, N_FLOORS);
        assert_between_co(to_floor, 0, N_FLOORS);
        assert(floors[from_floor].ms[elem_ix]);
        assert(!floors[to_floor].ms[elem_ix]);
        floors[from_floor].ms.reset(elem_ix);
        floors[to_floor].ms.set(elem_ix);
    }
    void move_g(int elem_ix, int from_floor, int to_floor)
    {
        assert_between_co(elem_ix, 0, (int)N_ELEMS);
        assert_between_co(from_floor, 0, N_FLOORS);
        assert_between_co(to_floor, 0, N_FLOORS);
        assert(floors[from_floor].gs[elem_ix]);
        assert(!floors[to_floor].gs[elem_ix]);
        floors[from_floor].gs.reset(elem_ix);
        floors[to_floor].gs.set(elem_ix);
    }
};

State get_initial_state()
{
    State st;
    auto& fl1 = st.floors[0];
    auto& fl2 = st.floors[1];

#ifdef TEST
    auto& fl3 = st.floors[2];

    fl1.ms.set(HY);
    fl1.ms.set(LI);
    fl2.gs.set(HY);
    fl3.gs.set(LI);
#else
    // 1. POG THG PRG RUG COG
    // 1. THM RUM COM
    for (auto e : {PO, TH, PR, RU, CO}) {
        fl1.gs.set(e);
    }
    for (auto e : {TH, RU, CO}) {
        fl1.ms.set(e);
    }

    fl2.ms.set(PO);
    fl2.ms.set(PR);
#endif
    return st;
}

int main()
{
    vector<State> front, next_front;
    front.PB(get_initial_state());
    bool done = false;
    int steps = 0;
    unordered_set<string> visited;
    assert(~front == 1);
    visited.insert(front[0].hash_string());
    for (; !done; ++steps) {
        if (front.empty()) {
            printf("No solution\n");
            break;
        }
        next_front.clear();
        printf("next possible %d. steps:\n", steps + 1);
        for (const auto& st : front) {
            assert(st.is_good());
            if (st.floors.back().ms.all() && st.floors.back().gs.all()) {
                printf("part1 %d\n", steps);
                done = true;
                break;
            }
            const int this_fix = st.elev;
            auto& this_fl = st.floors[this_fix];
            FOR (target_fix, max(0, this_fix - 1), <= min(N_FLOORS - 1, this_fix + 1)) {
                if (this_fix == target_fix) {
                    continue;
                }
                // try to bring every combination from this_fix to target_fix
                auto try_move = [&st, this_fix, target_fix, &next_front, &visited](
                                    initializer_list<int> mss, initializer_list<int> gss) {
                    assert_between_cc(~mss + ~gss, 1, 2);
                    assert(abs(this_fix - target_fix) == 1);
                    auto st_next = st;
                    st_next.elev = target_fix;
                    for (auto i : mss) {
                        st_next.move_m(i, this_fix, target_fix);
                    }
                    for (auto i : gss) {
                        st_next.move_g(i, this_fix, target_fix);
                    }
                    if (st_next.is_good()) {
                        auto hs = st_next.hash_string();
                        if (!contains(visited, hs)) {
                            next_front.PB(st_next);
                            visited.emplace(move(hs));
                            string s;
                            for (auto i : mss) {
                                s += string(ELEM_NAMES[i]) + "M ";
                            }
                            for (auto i : gss) {
                                s += string(ELEM_NAMES[i]) + "G ";
                            }
                            printf("floor %d -> %d, taking %s\n", this_fix + 1, target_fix + 1,
                                   s.c_str());
                        }
                    }
                };
                FOR (ix, 0, < N_ELEMS) {
                    if (this_fl.ms[ix]) {
                        try_move({ix}, {});
                        FOR (jx, ix + 1, < N_ELEMS) {
                            if (this_fl.ms[jx]) {
                                try_move({ix, jx}, {});
                            }
                        }
                        if (this_fl.gs[ix]) {
                            try_move({ix}, {ix});
                        }
                    }
                    if (this_fl.gs[ix]) {
                        try_move({}, {ix});
                        FOR (jx, ix + 1, < N_ELEMS) {
                            if (this_fl.gs[jx]) {
                                try_move({}, {ix, jx});
                            }
                        }
                    }
                }
            }
        }
        front.swap(next_front);
    }
    return 0;
}
