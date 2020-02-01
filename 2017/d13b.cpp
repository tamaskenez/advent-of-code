#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d13_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<int, int> ranges;
    for (auto& l : lines) {
        auto xs = split(l, " :");
        assert(~xs == 2);
        ranges[stoi(xs[0])] = stoi(xs[1]);
    }
    int totsev = 0;
    for (auto& kv : ranges) {
        int depth = kv.FST;
        int range = kv.SND;
        int picosec = depth;
        assert(range > 1);
        int pos = picosec % (2 * range - 2);
        if (pos == 0) {
            totsev += depth * range;
        }
    }
    printf("%d\n", totsev);
    for (int delay = 0;; ++delay) {
        bool caught = false;
        for (auto& kv : ranges) {
            int depth = kv.FST;
            int range = kv.SND;
            int picosec = depth + delay;
            assert(range > 1);
            int pos = picosec % (2 * range - 2);
            if (pos == 0) {
                caught = true;
                break;
            }
        }
        if (!caught) {
            printf("delay: %d\n", delay);
            break;
        }
    }
    return 0;
}
