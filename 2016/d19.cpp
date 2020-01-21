#include "common.h"

const int INPUT = 3014387;

struct Elf
{
    int num;
    int presents = 1;
};

int main()
{
    const int N = INPUT;
    // const int N = 5;
    {
        vector<Elf> elves(N);
        FOR (i, 0, < N) {
            elves[i].num = i + 1;
        }
        while (~elves > 1) {
            FOR (i, 0, < ~elves) {
                auto& ei = elves[i];
                if (ei.presents == 0) {
                    continue;
                }
                int j = (i + 1) % ~elves;
                auto& ej = elves[j];
                assert(ej.presents > 0);
                ei.presents += ej.presents;
                ej.presents = 0;
            }
            vector<Elf> elves2;
            for (auto& e : elves) {
                if (e.presents) {
                    elves2.PB(e);
                }
            }
            elves2.swap(elves);
        }
        printf("elf#%d presents %d\n", elves[0].num, elves[0].presents);
    }
    {
        vector<Elf> elves(N);
        FOR (i, 0, < N) {
            elves[i].num = i + 1;
        }
        vector<Elf> elves2;
        int elf_to_cont_num = 1;
        while (~elves > 1) {
            // printf("~elves %d\n", ~elves);
            int across_idx = -1;
            int elf_idx = -1;
            int next_increment = -1;
            FOR (i, 0, < ~elves) {
                if (elves[i].num == elf_to_cont_num) {
                    elf_idx = i;
                    break;
                }
            }
            assert(elf_idx >= 0);
            for (;; elf_idx = (elf_idx + 1) % ~elves) {
                auto& ei = elves[elf_idx];
                if (ei.presents == 0) {
                    for (;;) {
                        elf_idx = (elf_idx + 1) % ~elves;
                        if (elves[elf_idx].presents > 0) {
                            elf_to_cont_num = elves[elf_idx].num;
                            break;
                        }
                    }
                    break;
                }
                if (across_idx < 0) {
                    across_idx = (elf_idx + ~elves / 2) % ~elves;
                    next_increment = (~elves & 1) ? 2 : 1;
                } else {
                    across_idx = (across_idx + next_increment) % ~elves;
                    next_increment = 3 - next_increment;
                }
                auto& ej = elves[across_idx];
                assert(ej.presents > 0);
                // printf("%d steals from %d\n", ei.num, ej.num);
                ei.presents += ej.presents;
                ej.presents = 0;
            }
            elves2.reserve(~elves);
            elves2.clear();
            for (auto& e : elves) {
                if (e.presents) {
                    elves2.PB(e);
                }
            }
            elves2.swap(elves);
        }
        printf("part2 elf#%d presents %d\n", elves[0].num, elves[0].presents);
    }
    return 0;
}

// high 2008150