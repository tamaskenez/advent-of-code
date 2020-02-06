#include "common.h"

using ALI3 = array<int64_t, 3>;

struct Part
{
    ALI3 p, v, a;
};

void operator+=(ALI3& x, ALI3 y)
{
    x[0] += y[0];
    x[1] += y[1];
    x[2] += y[2];
}

void solve1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<Part> parts;
    for (auto& l : lines) {
        // p=<-11104,1791,5208>, v=<-6,36,-84>, a=<19,-5,-4>
        auto xs = split(l, "p=<, \tva>");
        assert(~xs == 9);
        auto p = ALI3{stoi(xs[0]), stoi(xs[1]), stoi(xs[2])};
        auto v = ALI3{stoi(xs[3]), stoi(xs[4]), stoi(xs[5])};
        auto a = ALI3{stoi(xs[6]), stoi(xs[7]), stoi(xs[8])};
        parts.PB(Part{p, v, a});
    }
    int prev_closest = -1;
    for (;;) {
        int closest_idx = -1;
        int64_t closest_man = INT_MAX;
        FOR (idx, 0, < ~parts) {
            auto& part = parts[idx];
            auto pp = part.p;
            auto md = abs(pp[0]) + abs(pp[1]) + abs(pp[2]);
            if (md < closest_man) {
                closest_man = md;
                closest_idx = idx;
            }
        }
        for (auto& part : parts) {
            part.v += part.a;
            part.p += part.v;
        }
        if (prev_closest != closest_idx) {
            prev_closest = closest_idx;
            auto pp = parts[closest_idx].p;
            printf("new closest#%d, (%lld %lld %lld)\n", closest_idx, pp[0], pp[1], pp[2]);
        }
    }
}
// 650 high

void solve2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<Part> parts;
    for (auto& l : lines) {
        auto xs = split(l, "p=<, \tva>");
        assert(~xs == 9);
        auto p = ALI3{stoi(xs[0]), stoi(xs[1]), stoi(xs[2])};
        auto v = ALI3{stoi(xs[3]), stoi(xs[4]), stoi(xs[5])};
        auto a = ALI3{stoi(xs[6]), stoi(xs[7]), stoi(xs[8])};
        parts.PB(Part{p, v, a});
    }

    map<ALI3,int> s;
    VI torem;
    int prev_count=~parts;
    for (;;) {
        s.clear();
        FOR (i, 0, < ~parts) {
            ++s[parts[i].p];
        }
        torem.clear();
        FOR (i, 0, < ~parts) {
            if(s[parts[i].p]>1){
                torem.PB(i);
            }
        }
        FORBACK(i,~torem-1,>=0){
            parts.erase(parts.begin() + torem[i]);
        }
        if(~parts!=prev_count){
            prev_count=~parts;
            printf("new count: %d\n", prev_count);
        }
        for (auto& part : parts) {
            part.v += part.a;
            part.p += part.v;
        }
    }
}

int main()
{
    //solve1();
    solve2();
}
