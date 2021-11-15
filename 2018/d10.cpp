#include "common.h"

struct PV
{
    AI2 p, v;
};

void iterate(vector<PV>& pvs)
{
    for (auto& pv : pvs) {
        pv.p += pv.v;
    }
}

void print(const vector<PV>& pvs)
{
    printf("------------------------\n");
    set<AI2> s;
    RunningStat<int> rx, ry;
    for (auto& pv : pvs) {
        s.insert(pv.p);
        rx.add(pv.p[0]);
        ry.add(pv.p[1]);
    }
    FOR (y, (*ry.lower), <= (*ry.upper)) {
        FOR (x, (*rx.lower), <= (*rx.upper)) {
            if (contains(s, AI2{x, y})) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d10_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    // position=<-19843, -49909> velocity=< 2,  5>
    vector<PV> pvs;
    for (auto& l : lines) {
        auto xs = split(l, "=<, \t>");
        PV pv;
        pv.p = AI2{stoi(xs[1]), stoi(xs[2])};
        pv.v = AI2{stoi(xs[4]), stoi(xs[5])};
        pvs.PB(pv);
    }
    int prev_dx = INT_MAX;
    int prev_dy = INT_MAX;
    bool dx_increase = false;
    bool dy_increase = false;
    FOR (i, 0, < 100000) {
        iterate(pvs);
        RunningStat<int> x, y;
        for (auto& pv : pvs) {
            x.add(pv.p[0]);
            y.add(pv.p[1]);
        }
        auto dx = *x.upper - *x.lower;
        auto dy = *y.upper - *y.lower;
        if (10007 <= i && i <= 10011) {
            print(pvs);
        }
        if (prev_dx < dx) {
            printf("X!\n");
            printf("%d: %d %d\n", i, dx, dy);
            dx_increase = true;
        }
        if (prev_dy < dy) {
            printf("Y!\n");
            printf("%d: %d %d\n", i, dx, dy);
            dy_increase = true;
        }
        prev_dx = dx;
        prev_dy = dy;
        if (dx_increase && dy_increase) {
            break;
        }
    }
    return 0;
}
