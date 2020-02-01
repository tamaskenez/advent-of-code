#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<int, VI> pipes;
    set<int> nodes;
    for (auto& l : lines) {
        auto xs = split(l, "<-> \t,");
        auto a0 = stoi(xs[0]);
        nodes.insert(a0);
        FOR (i, 1, < ~xs) {
            auto a = stoi(xs[i]);
            pipes[a0].PB(a);
            pipes[a].PB(a0);
            nodes.insert(a);
        }
    }
    set<int> visited;
    int total = 0;
    for (; !nodes.empty();) {
        VI wl;
        auto n0 = *nodes.begin();
        wl.push_back(n0);
        set<int> ing;
        ing.insert(n0);
        while (!wl.empty()) {
            auto q = wl.back();
            wl.pop_back();
            auto& vs = pipes[q];
            for (auto v : vs) {
                if (!contains(visited, v)) {
                    wl.PB(v);
                    ing.insert(v);
                    visited.insert(v);
                }
            }
        }
        printf("node#%d: %d\n", n0, ~ing);
        for (auto n : ing) {
            nodes.erase(n);
        }
        ++total;
    }
    printf("total %d\n", total);
    return 0;
}
