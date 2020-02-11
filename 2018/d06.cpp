#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d06_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<AI2> ps;
    RunningStat<int> rsx, rsy;
    for (auto& l : lines) {
        auto xs = split(l, ", \t");
        auto p = AI2{stoi(xs[0]), stoi(xs[1])};
        ps.PB(p);
        rsx.add(p[0]);
        rsy.add(p[1]);
    }
    int dx = *rsx.upper - *rsx.lower;
    int dy = *rsy.upper - *rsy.lower;
    int d = max(dx, dy) / 2;
    VI ldixs;
    VI counts(~ps);
    set<int> edgeps;
    int t10000=0;
    FOR (y, *rsy.lower - d, <= *rsy.upper + d) {
        FOR (x, *rsx.lower - d, <= *rsx.upper + d) {
            int ld = INT_MAX;
            ldixs.clear();
            int suma=0;
            FOR (i, 0, < ~ps) {
                auto md = manhattan(ps[i], AI2{x, y});
                suma+=md;
                if (md < ld) {
                    ld = md;
                    ldixs.assign(1, i);
                } else if (md == ld) {
                    ldixs.PB(i);
                }
            }
            bool onedge = (x == *rsx.lower - d || x == *rsx.upper + d) ||
                          (y == *rsy.lower - d || y == *rsy.upper + d);
            if(suma<10000){
                ++t10000;
                if(onedge){
                    printf("not good\n");
                    exit(-1);
                }
            }
            if (~ldixs == 1) {
                ++counts[ldixs[0]];
                if (onedge) {
                    edgeps.insert(ldixs[0]);
                }
            }
        }
    }
    int bc = -1;
    int bi = 999;
    FOR (i, 0, < ~counts) {
        if (counts[i] > bc && !contains(edgeps, i)) {
            bc = counts[i];
            bi = i;
        }
    }
    printf("%d %c\n", bc, bi + 'A');
    printf("%d\n", t10000);

    return 0;
}
// high 128619
// high 456397
// high 58650