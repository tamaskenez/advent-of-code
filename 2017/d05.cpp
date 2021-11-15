#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d05_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    VI js0;
    for (auto& l : lines) {
        js0.PB(stoi(l));
    }
    {
        auto js = js0;
        int pc = 0;
        int steps = 0;
        for (;; ++steps) {
            if (pc < 0 || ~js <= pc) {
                break;
            }
            auto dpc = js[pc];
            int nextpc = pc + dpc;
            ++js[pc];
            pc = nextpc;
        }
        printf("steps %d\n", steps);
    }
    {
        auto js = js0;
        int pc = 0;
        int steps = 0;
        for (;; ++steps) {
            if (pc < 0 || ~js <= pc) {
                break;
            }
            auto dpc = js[pc];
            int nextpc = pc + dpc;
            if (dpc >= 3) {
                --js[pc];
            } else {
                ++js[pc];
            }
            pc = nextpc;
        }
        printf("steps %d\n", steps);
    }
    return 0;
}
// not 489
