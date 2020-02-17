#include "common.h"

#if 1
const int depth = 4845;
const AI2 target = AI2{6, 770};
#else
const int depth = 510;
const AI2 target = AI2{10, 10};
#endif

map<AI2, int> gidcs;
int geoindex(AI2 xy);

int erosion_level(AI2 xy)
{
    return (geoindex(xy) + depth) % 20183;
}

int geoindex(AI2 xy)
{
    if (xy == AI2{0, 0} || xy == target) {
        return 0;
    }
    auto [x, y] = xy;
    if (y == 0) {
        return xy[0] * 16807;
    }
    if (x == 0) {
        return xy[1] * 48271;
    }
    int gix;
    auto it = gidcs.find(xy);
    if (it == gidcs.end()) {
        gix = erosion_level(AI2{x - 1, y}) * erosion_level(AI2{x, y - 1});
        gidcs[xy] = gix;
    } else {
        gix = it->second;
    }
    return gix;
}

char regtype(AI2 xy)
{
    auto el = erosion_level(xy);
    const char* const types = "rwn";
    return types[el % 3];
}

int risk_level(AI2 xy)
{
    return erosion_level(xy) % 3;
}

enum Tool
{
    NOTOOL,
    TORCH,
    CLIMB
};

struct State
{
    AI2 xy;
    Tool tool;
    bool operator<(const State& b) const
    {
        if (xy < b.xy) {
            return true;
        }
        if (xy > b.xy) {
            return false;
        }
        return tool < b.tool;
    }
};

auto INIT_STATE = State{AI2{0, 0}, TORCH};

bool is_tool_ok(char regtype, Tool tool)
{
    switch (regtype) {
        case 'r':
            return tool == CLIMB || tool == TORCH;
        case 'w':
            return tool == CLIMB || tool == NOTOOL;
        case 'n':
            return tool == TORCH || tool == NOTOOL;
        default:
            UNREACHABLE;
    }
    UNREACHABLE;
    return false;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    auto [tx, ty] = target;
    int trl = 0;
    FOR (x, 0, <= tx) {
        FOR (y, 0, <= ty) {
            trl += risk_level(AI2{x, y});
        }
    }
    printf("%d\n", trl);

    map<int, vector<State>> front;
    front.insert(MKP(0, vector<State>{INIT_STATE}));

    set<State> settled;
    bool found = false;
    int prev_front = -1;
    map<State, int> best_tentative;
    while (!front.empty()) {
        auto it = front.begin();
        if (it->first != prev_front) {
            prev_front = it->first;
            printf("front %d, count: %d\n", prev_front, ~it->second);
        }
        if (it->second.empty()) {
            front.erase(it);
            continue;
        }
        auto state_time = it->first;
        auto state = it->second.back();
        it->second.pop_back();
        settled.insert(state);

        if (state.xy == target && state.tool == TORCH) {
            printf("mins: %d\n", state_time);
            found = true;
            break;
        }
        // try to move
        for (auto d : DIRS4) {
            auto nxy = state.xy + d;
            auto [x, y] = nxy;
            if (x < 0 || y < 0) {
                continue;
            }
            if (is_tool_ok(regtype(nxy), state.tool)) {
                auto ns = State{nxy, state.tool};
                auto nt = state_time + 1;
                if (!contains(settled, ns)) {
                    auto jt = best_tentative.find(ns);
                    if (jt == best_tentative.end() || nt < jt->second) {
                        front[nt].PB(ns);
                        best_tentative[ns]=nt;
                    }
                }
            }
        }
        auto this_regtype = regtype(state.xy);
        assert(is_tool_ok(this_regtype, state.tool));
        for (auto newtool : {NOTOOL, TORCH, CLIMB}) {
            if (newtool != state.tool && is_tool_ok(this_regtype, newtool)) {
                auto ns = State{state.xy, newtool};
                auto nt = state_time + 7;
                if (!contains(settled, ns)) {
                    auto jt = best_tentative.find(ns);
                    if (jt == best_tentative.end() || nt < jt->second) {
                        front[nt].PB(ns);
                        best_tentative[ns]=nt;
                    }
                }
            }
        }
    }
    if (!found) {
        printf("not found\n");
    }
    return 0;
}
