#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d16_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, int> data;
    data["children"] = 3;
    data["cats"] = 7;
    data["samoyeds"] = 2;
    data["pomeranians"] = 3;
    data["akitas"] = 0;
    data["vizslas"] = 0;
    data["goldfish"] = 5;
    data["trees"] = 3;
    data["cars"] = 2;
    data["perfumes"] = 1;
    FOR (partnum, 1, <= 2) {
        for (auto& l : lines) {
            auto vs = split(l, " :,.");
            //"Sue 1: goldfish: 9, cars: 0, samoyeds: 9"
            assert(~vs == 8);
            auto suenum = stoi(vs[1]);
            int okcount = 0;
            FOR (i, 0, < 3) {
                auto obj = vs[2 + i * 2];
                auto objcount = stoi(vs[3 + i * 2]);
                if (partnum == 1) {
                    if (data.at(obj) == objcount) {
                        ++okcount;
                    }
                } else {
                    if (obj == "cats" || obj == "trees") {
                        if (data.at(obj) < objcount) {
                            ++okcount;
                        }
                    } else if (obj == "pomeranians" || obj == "goldfish") {
                        if (data.at(obj) > objcount) {
                            ++okcount;
                        }
                    } else {
                        if (data.at(obj) == objcount) {
                            ++okcount;
                        }
                    }
                }
            }
            if (okcount == 3) {
                printf("part%d,sue%d\n", partnum, suenum);
            }
        }
    }
    return 0;
}
// 6 54