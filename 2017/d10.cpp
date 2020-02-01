#include "common.h"
const VI INPUT = {129, 154, 49, 198, 200, 133, 97, 254, 41, 6, 2, 1, 255, 0, 191, 108};
const string INPUT2 = "129,154,49,198,200,133,97,254,41,6,2,1,255,0,191,108";
int main()
{
    {
        VI vs(256);
        iota(BE(vs), 0);
        int currpos = 0;
        int skipsize = 0;
        for (auto l : INPUT) {
            if (currpos != 0) {
                rotate(vs.begin(), vs.begin() + currpos, vs.end());
            }
            reverse(vs.begin(), vs.begin() + l);
            if (currpos != 0) {
                rotate(vs.begin(), vs.begin() + ~vs - currpos, vs.end());
            }
            currpos = (currpos + l + skipsize) % ~vs;
            ++skipsize;
        }
        printf("part1 %d\n", vs[0] * vs[1]);
    }
    {
        VI vs(256);
        iota(BE(vs), 0);
        int currpos = 0;
        int skipsize = 0;
        VI input;
        for (auto ch : INPUT2) {
            input.PB(ch);
        }
        for (auto i : {17, 31, 73, 47, 23}) {
            input.PB(i);
        }
        FOR (k, 0, < 64) {
            for (auto l : input) {
                if (currpos != 0) {
                    rotate(vs.begin(), vs.begin() + currpos, vs.end());
                }
                reverse(vs.begin(), vs.begin() + l);
                if (currpos != 0) {
                    rotate(vs.begin(), vs.begin() + ~vs - currpos, vs.end());
                }
                currpos = (currpos + l + skipsize) % ~vs;
                ++skipsize;
            }
        }
        VI densehash;
        FOR (i, 0, < 16) {
            int q = 0;
            FOR (j, 0, < 16) {
                q = q ^ vs[i * 16 + j];
            }
            densehash.PB(q);
        }
        string s;
        char buf[1000];
        buf[0] = 0;
        for (unsigned i : densehash) {
            sprintf(buf + strlen(buf), "%02x", i);
        }
        printf("%s\n", buf);
    }
    return 0;
}
