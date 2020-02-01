#include "common.h"

optional<int> mystep(int& myloc, const map<int, int>& theirlocs)
{
    ++myloc;
    auto it = theirlocs.find(myloc);
    if (it == theirlocs.end()) {
        return {};
    }
    if (it->second == 0) {
        return it->first;
    }
    return {};
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d13_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<int, int> ls;
    RunningStat<int> depths;
    for (auto& l : lines) {
        auto xs = split(l, " \t:");
        assert(~xs == 2);
        auto a = stoi(xs[0]);
        auto b = stoi(xs[1]);
        ls[a] = b;
        depths.add(a);
    }

    int q = 1;
    for (auto& kv : ls) {
        int r = kv.second;
        if (r > 1) {
            q = lcm(q, r * 2 - 2);
        }
    }
    printf("q: %d\n", q);

    for (int delay = 0;; ++delay) {
        int totsev = 0;
        bool caught = false;
        for (auto& kv : ls) {
            int depth = kv.first;
            int range = kv.second;
            int time_when_enter = delay + depth;
            int pos = time_when_enter % (2 * range - 2);
            if (pos == 0) {
                totsev += depth * range;
                caught = true;
            }
        }
        if (delay == 0 || !caught) {
            printf("delay: %d, totsev: %d\n", delay, totsev);
        }
        if (!caught) {
            break;
        }
    }
    return 0;
}
// 1624 low