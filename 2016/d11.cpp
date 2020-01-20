#include "common.h"

//#define TEST
#define PART2
#ifdef TEST
enum Elements
{
    HY,
    LI,
    N_ELEMS
};
#else
enum Elements
{
    TH,
    RU,
    CO,
    PO,
    PR
#ifdef PART2
    ,
    EL,
    DI
#endif
    ,
    N_ELEMS
};
#endif

struct Floor
{
    bitset<N_ELEMS> ms, gs;
    bool has_other_generators(int ix) const
    {
        auto bs = gs;
        bs.reset(ix);
        return bs.any();
    }
    bool is_good() const
    {
        if (ms.none()) {
            return true;
        }
        if (gs.none()) {
            return true;
        }
        FOR (i, 0, < N_ELEMS) {
            if (ms[i] && !gs[i] && has_other_generators(i)) {
                return false;
            }
        }
        return true;
    }
    bool operator==(const Floor& y) const { return ms == y.ms && gs == y.gs; }
};

struct State
{
    int e = 1;
    array<Floor, 5> floors;

    bool operator<(const State& y) const
    {
        if (e < y.e) {
            return true;
        }
        if (e > y.e) {
            return false;
        }
        FOR (f, 1, <= 4) {
            auto& fl = floors[f];
            auto& fly = y.floors[f];
            if (fl.ms.to_ulong() < fly.ms.to_ulong()) {
                return true;
            }
            if (fl.ms.to_ulong() > fly.ms.to_ulong()) {
                return false;
            }
            if (fl.gs.to_ulong() < fly.gs.to_ulong()) {
                return true;
            }
            if (fl.gs.to_ulong() > fly.gs.to_ulong()) {
                return false;
            }
        }
        assert(*this == y);
        return false;
    }
    bool operator==(const State& y) const
    {
        return e == y.e && floors[1] == y.floors[1] && floors[2] == y.floors[2] &&
               floors[3] == y.floors[3] && floors[4] == y.floors[4];
    }
    bool is_good() const
    {
        assert_between_cc(e, 1, 4);
        FOR (floor_ix, 1, <= 4) {
            if (!floors[floor_ix].is_good()) {
                return false;
            }
        }
        return true;
    }
    void move_ms(int ix, int from, int to)
    {
        assert_between_co(ix, 0, (int)N_ELEMS);
        assert_between_cc(from, 1, 4);
        assert_between_cc(to, 1, 4);
        assert(from != to);
        assert(floors[from].ms[ix]);
        assert(!floors[to].ms[ix]);
        floors[from].ms.reset(ix);
        floors[to].ms.set(ix);
    }
    void move_gs(int ix, int from, int to)
    {
        assert_between_co(ix, 0, (int)N_ELEMS);
        assert_between_cc(from, 1, 4);
        assert_between_cc(to, 1, 4);
        assert(from != to);
        assert(floors[from].gs[ix]);
        assert(!floors[to].gs[ix]);
        floors[from].gs.reset(ix);
        floors[to].gs.set(ix);
    }
};

int main()
{
    vector<State> front, next_front;
    set<State> done;
    {
        State st;
#ifdef TEST
        auto& f1 = st.floors[1];
        auto& f2 = st.floors[2];
        auto& f3 = st.floors[3];
        f1.ms.set(HY);
        f1.ms.set(LI);
        f2.gs.set(HY);
        f3.gs.set(LI);
#else
        auto& f1 = st.floors[1];
        auto& f2 = st.floors[2];

        f1.ms.set(TH);
        f1.ms.set(RU);
        f1.ms.set(CO);

        f1.gs.set(PO);
        f1.gs.set(TH);
        f1.gs.set(PR);
        f1.gs.set(RU);
        f1.gs.set(CO);

        f2.ms.set(PO);
        f2.ms.set(PR);
#ifdef PART2
        f1.ms.set(EL);
        f1.ms.set(DI);
        f1.gs.set(EL);
        f1.gs.set(DI);
#endif
#endif
        front.PB(st);
    }
    assert(~front == 1);
    done.insert(front[0]);

    int steps = 0;
    bool part1_found = false;
    for (; !part1_found; ++steps) {
        for (const auto& st : front) {
            assert(!front.empty());
            assert(st.is_good());
            if (st.floors[4].ms.all() && st.floors[4].gs.all()) {
                printf("part1 %d\n", steps);
                part1_found = true;
                break;
            }
            // printf("steps %d %d\n", steps, ~front);
            // generate all steps from st
            const int this_floor_ix = st.e;
            const auto& this_floor = st.floors[this_floor_ix];
            FOR (target_floor_ix, max(1, this_floor_ix - 1), <= min(4, this_floor_ix + 1)) {
                if (this_floor_ix == target_floor_ix) {
                    continue;
                }
                FOR (ix1, 0, < N_ELEMS) {
                    if (this_floor.ms[ix1]) {
                        {
                            // m alone
                            auto st2 = st;
                            st2.e = target_floor_ix;
                            st2.move_ms(ix1, this_floor_ix, target_floor_ix);
                            if (st2.is_good() && done.count(st2) == 0) {
                                next_front.PB(st2);
                                done.insert(st2);
                            }
                        }
                        if (this_floor.gs[ix1]) {
                            // m with its g
                            auto st2 = st;
                            st2.e = target_floor_ix;
                            st2.move_ms(ix1, this_floor_ix, target_floor_ix);
                            st2.move_gs(ix1, this_floor_ix, target_floor_ix);
                            if (st2.is_good() && done.count(st2) == 0) {
                                next_front.PB(st2);
                                done.insert(st2);
                            }
                        }
                        // m1 with m2
                        FOR (ix2, ix1 + 1, < N_ELEMS) {
                            if (this_floor.ms[ix2]) {
                                {
                                    auto st2 = st;
                                    st2.e = target_floor_ix;
                                    st2.move_ms(ix1, this_floor_ix, target_floor_ix);
                                    st2.move_ms(ix2, this_floor_ix, target_floor_ix);
                                    if (st2.is_good() && done.count(st2) == 0) {
                                        next_front.PB(st2);
                                        done.insert(st2);
                                    }
                                }
                            }
                        }
                    }  // if ms ix1
                    if (this_floor.gs[ix1]) {
                        {
                            // g alone
                            auto st2 = st;
                            st2.e = target_floor_ix;
                            st2.move_gs(ix1, this_floor_ix, target_floor_ix);
                            if (st2.is_good() && done.count(st2) == 0) {
                                next_front.PB(st2);
                                done.insert(st2);
                            }
                        }
                        // g1 with g2
                        FOR (ix2, ix1 + 1, < N_ELEMS) {
                            if (this_floor.gs[ix2]) {
                                {
                                    auto st2 = st;
                                    st2.e = target_floor_ix;
                                    st2.move_gs(ix1, this_floor_ix, target_floor_ix);
                                    st2.move_gs(ix2, this_floor_ix, target_floor_ix);
                                    if (st2.is_good() && done.count(st2) == 0) {
                                        next_front.PB(st2);
                                        done.insert(st2);
                                    }
                                }
                            }
                        }
                    }  // if gs ix1
                }      // ix1
            }          // for floors
        }              // for fronts
        next_front.swap(front);
        next_front.clear();
        assert(!front.empty());
    }  // for ;;
    printf("exit1\n");

    return 0;
}
// high 3947771
// high 250342
// high 158162