#include "common.h"

const string INPUT =
    "4	1	15	12	0	9	9	5	5	8	7	3	"
    "14	5	12	3";
int main()
{
    auto sbs0 = split(INPUT, " \t");
    VI bs0;
    for (auto s : sbs0) {
        bs0.PB(stoi(s));
    }
    {
        auto bs = bs0;
        int steps = 1;
        set<VI> encd;
        encd.insert(bs);
        for (;; ++steps) {
            auto maix = max_element(BE(bs)) - bs.begin();
            auto blhere = bs[maix];
            bs[maix] = 0;
            for (; blhere > 0;) {
                maix = (maix + 1) % ~bs;
                ++bs[maix];
                --blhere;
            }
            if (contains(encd, bs)) {
                break;
            }
            encd.insert(bs);
        }
        printf("%d\n", steps);
    }
    {
        auto bs = bs0;
        int steps = 1;
        map<VI, int> encd;
        encd.insert(make_pair(bs, 0));
        for (;; ++steps) {
            auto maix = max_element(BE(bs)) - bs.begin();
            auto blhere = bs[maix];
            bs[maix] = 0;
            for (; blhere > 0;) {
                maix = (maix + 1) % ~bs;
                ++bs[maix];
                --blhere;
            }
            auto it = encd.find(bs);
            if (it != encd.end()) {
                printf("steps %d diff %d \n", steps, steps - it->second);
                break;
            }
            encd.insert(make_pair(bs, steps));
        }
    }
    return 0;
}
