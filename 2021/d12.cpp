#include "common.h"

#include <list>

struct TravelState
{
    vector<string> path;
    set<string> small_caves_visited;
    string single_small_cave;
};

bool is_big_cave(const string& s)
{
    assert(!s.empty());
    return isupper(s[0]);
}

void P2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, set<string>> paths;
    set<string> small_caves;
    for (auto l : lines) {
        auto rr = split(trim(l), "-");
        paths[rr[0]].insert(rr[1]);
        paths[rr[1]].insert(rr[0]);
        if (!is_big_cave(rr[0]) && rr[0] != "start" && rr[0] != "end") {
            small_caves.insert(rr[0]);
        }
        if (!is_big_cave(rr[1]) && rr[1] != "start" && rr[1] != "end") {
            small_caves.insert(rr[1]);
        }
    }
    vector<TravelState> tss, dones;
    tss.PB(TravelState{vector<string>({"start"}), set<string>(), ""});

    while (!tss.empty()) {
        vector<TravelState> next_tss;
        for (const auto& ts : tss) {
            assert(!ts.path.empty());
            auto& from = ts.path.back();
            auto& tos = paths.at(from);
            for (const auto& to : tos) {
                if (to == "start") {
                    continue;
                }
                if (to == "end") {
                    auto new_ts = ts;
                    new_ts.path.PB("end");
                    dones.PB(move(new_ts));
                } else {
                    assert(to != "start" && to != "end");
                    if (is_big_cave(to) ||
                        (ts.small_caves_visited.count(to) == 0 || ts.single_small_cave.empty())) {
                        auto new_ts = ts;
                        new_ts.path.PB(to);
                        if (!is_big_cave(to)) {
                            if (ts.small_caves_visited.count(to) > 0) {
                                assert(ts.single_small_cave.empty());
                                new_ts.single_small_cave = to;
                            }
                            new_ts.small_caves_visited.insert(to);
                        }
                        next_tss.PB(move(new_ts));
                    }
                }
            }
        }
        tss.swap(next_tss);
    }
    printf("P2: %d\n", ~dones);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, set<string>> paths;
    set<string> small_caves;
    for (auto l : lines) {
        auto rr = split(trim(l), "-");
        paths[rr[0]].insert(rr[1]);
        paths[rr[1]].insert(rr[0]);
        if (!is_big_cave(rr[0]) && rr[0] != "start" && rr[0] != "end") {
            small_caves.insert(rr[0]);
        }
        if (!is_big_cave(rr[1]) && rr[1] != "start" && rr[1] != "end") {
            small_caves.insert(rr[1]);
        }
    }
    vector<TravelState> tss, dones;
    tss.PB(TravelState{vector<string>({"start"}), set<string>(), ""});

    while (!tss.empty()) {
        vector<TravelState> next_tss;
        for (const auto& ts : tss) {
            assert(!ts.path.empty());
            auto& from = ts.path.back();
            auto& tos = paths.at(from);
            for (const auto& to : tos) {
                if (to == "start") {
                    continue;
                }
                if (to == "end") {
                    auto new_ts = ts;
                    new_ts.path.PB("end");
                    dones.PB(move(new_ts));
                } else {
                    assert(to != "start" && to != "end");
                    if (is_big_cave(to) || ts.small_caves_visited.count(to) == 0) {
                        auto new_ts = ts;
                        new_ts.path.PB(to);
                        if (!is_big_cave(to)) {
                            new_ts.small_caves_visited.insert(to);
                        }
                        next_tss.PB(move(new_ts));
                    }
                }
            }
        }
        tss.swap(next_tss);
    }
    printf("P1: %d\n", ~dones);
    P2();
    return 0;
}
