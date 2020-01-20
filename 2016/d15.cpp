#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d15_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    struct Disc
    {
        int N;
        int p;
    };
    vector<Disc> discs;
    discs.resize(~lines);
    for (auto& l : lines) {
        auto vs = split(l, " #.");
        auto discnum = stoi(vs[1]) - 1;
        auto nposs = stoi(vs[3]);
        auto startpos = stoi(vs.back());
        discs[discnum] = Disc{nposs, startpos};
    }
    /*
    FOR (i, 0, < ~discs) {
        auto& d = discs[i];
        d.p = (d.p + 100 * d.N - 1 - i) % d.N;
    }*/

    for (auto part2 : {false, true}) {
        if(part2){
            discs.PB(Disc{11,0});
        }
        for (int i = 0;; ++i) {
            bool all_zero = true;
            FOR (j, 0, < ~discs) {
                auto& d = discs[j];
                auto pos = (d.p + i + j + 1) % d.N;
                if (pos != 0) {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero) {
                printf("p1 %d\n", i);
                break;
            }
        }
    }
    return 0;
}

// too high 288129