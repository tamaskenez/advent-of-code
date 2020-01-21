#include "common.h"

struct Node
{
    AI2 loc;
    int size, used, avail, perc;
};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<AI2, Node> nodes;
    FOR (i, 2, < ~lines) {
        auto& l = lines[i];
        auto vs = split(l, " T%");
        assert(~vs == 5);
        auto ws = split(vs[0], "-xy");
        assert(~ws == 3);
        auto x = stoi(ws[1]);
        auto y = stoi(ws[2]);
        auto size = stoi(vs[1]);
        auto used = stoi(vs[2]);
        auto avail = stoi(vs[3]);
        auto perc = stoi(vs[4]);
        auto xy = AI2{x, y};
        nodes[xy] = Node{xy, size, used, avail, perc};
        printf("");
    }
    int viable = 0;
    RunningStat<int> xr, yr;
    map<int, int> usedstat, sizestat;
    AI2 init_empty_loc;
    int init_empty_loc_counter = 0;
    for (auto& i : nodes) {
        auto& n = i.SND;
        ++usedstat[n.used];
        ++sizestat[n.size];
        if (n.used == 0) {
            assert(init_empty_loc_counter == 0);
            ++init_empty_loc_counter;
            init_empty_loc = i.FST;
        }
        xr.add(i.FST[0]);
        yr.add(i.FST[1]);
        for (auto& j : nodes) {
            if (i.SND.used > 0 && i.FST != j.FST && i.SND.used <= j.SND.avail) {
                ++viable;
            }
        }
    }
    printf("viable: %d\n", viable);
    printf("xr %d..%d\n", *xr.lower, *xr.upper);
    printf("yr %d..%d\n", *yr.lower, *yr.upper);
    printf("~nodes %d\n", ~nodes);

    const int W = *xr.upper + 1;
    const int H = *yr.upper + 1;
    AI2 init_data_loc{W - 1, 0};
    AI2 ORIGIN{0, 0};

    FOR (y, 0, < H) {
        FOR (x, 0, < W) {
            auto loc = AI2{x, y};
            auto& node = nodes.at(loc);
            printf("%3d/%3d ", node.used, node.size);
        }
        printf("\n");
    }
    printf("usedstat\n");
    for (auto& kv : usedstat) {
        printf("%d: %d\n", kv.first, kv.second);
    }
    printf("sizestat\n");
    for (auto& kv : sizestat) {
        printf("%d: %d\n", kv.first, kv.second);
    }
    FOR (y, 0, < H) {
        FOR (x, 0, < W) {
            auto loc = AI2{x, y};
            auto& node = nodes.at(loc);
            char c;
            if (node.used == 0) {
                c = '_';
            } else if (node.size < 100) {
                c = '.';
            } else {
                c = '#';
            }
            printf("%c ", c);
        }
        printf("\n");
    }
    // try BFS
    struct State
    {
        AI2 data_loc, empty_loc;
        bool operator<(const State& b) const
        {
            if (data_loc < b.data_loc) {
                return true;
            }
            if (data_loc > b.data_loc) {
                return false;
            }
            return empty_loc < b.empty_loc;
        }
    };
    State st0{init_data_loc, init_empty_loc};
    vector<State> front, next_front;
    set<State> visited;
    front.PB(st0);
    visited.insert(st0);
    int steps = 0;
    bool done = false;
    for (; !done && !front.empty(); steps++) {
        next_front.clear();
        for (const auto& st : front) {
            if (st.data_loc == ORIGIN) {
                printf("part2 steps %d\n", steps);
                done = true;
                break;
            }
            for (auto dir : {AI2{0, 1}, AI2{0, -1}, AI2{1, 0}, AI2{-1, 0}}) {
                auto next_empty_loc = st.empty_loc + dir;
                if (!is_between_co(next_empty_loc[0], 0, W) ||
                    !is_between_co(next_empty_loc[1], 0, H)) {
                    continue;
                }
                if (nodes.at(next_empty_loc).size >= 100) {
                    continue;
                }
                State next_state;
                if (next_empty_loc == st.data_loc) {
                    next_state = State{st.empty_loc, st.data_loc};
                } else {
                    next_state = State{st.data_loc, next_empty_loc};
                }
                if (!contains(visited, next_state)) {
                    next_front.PB(next_state);
                    visited.insert(next_state);
                }
            }
        }
        next_front.swap(front);
    }
    printf("done\n");
    return 0;
}
// 21:00 : could be calculated by hand