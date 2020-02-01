#include "common.h"
const string INPUT = "wenycdww";

VI knothash(const string strinput)
{
    VI vs(256);
    iota(BE(vs), 0);
    int currpos = 0;
    int skipsize = 0;
    VI input;
    for (auto ch : strinput) {
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
    return densehash;
}

vector<AI2> get_nbs_from(AI2 xy, set<AI2>& toproc)
{
    vector<AI2> wl(1, xy);
    toproc.erase(xy);
    vector<AI2> result;
    result.PB(xy);
    while (!wl.empty()) {
        auto q = wl.back();
        wl.pop_back();
        for (auto dir : DIRS4) {
            auto nb = q + dir;
            if (contains(toproc, nb)) {
                toproc.erase(nb);
                wl.PB(nb);
                result.PB(nb);
            }
        }
    }
    return result;
}

using b128 = bitset<128>;
int main()
{
    vector<b128> bs(128);
    int setcount = 0;
    FOR (rix, 0, < 128) {
        auto s = INPUT + "-" + to_string(rix);
        auto z = knothash(s);
        assert(~z == 16);
        int col = 0;
        bitset<128> row;
        FOR (i, 0, < 16) {
            FORBACK (j, 7, >= 0) {
                if ((z[i] >> j) & 1) {
                    row[col++] = true;
                    ++setcount;
                } else {
                    ++col;
                }
            }
        }
        assert(col == 128);
        bs[rix] = row;
    }
    printf("%d\n", setcount);

    set<AI2> toproc;
    FOR (i, 0, < 128) {
        FOR (j, 0, < 128) {
            if (bs[i][j]) {
                toproc.insert(AI2{i, j});
            }
        }
    }

    int gc = 0;
    while (!toproc.empty()) {
        auto xy = *toproc.begin();
        toproc.erase(xy);
        auto nbs = get_nbs_from(xy, toproc);
        ++gc;
    }

    printf("gc %d\n", gc);

    return 0;
}

// not 8226