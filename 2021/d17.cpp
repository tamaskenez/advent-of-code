#include "common.h"

struct Probe
{
    AI2 pos;
    AI2 vel;
};

auto input_min = AI2{143, -106};
auto input_max = AI2{177, -71};
// target area: x=143..177, y=-106..-71

Probe advance_probe(Probe p)
{
    p.pos += p.vel;
    switch (sgn(p.vel[0])) {
        case -1:
            ++p.vel[0];
            break;
        case 1:
            --p.vel[0];
            break;
        default:
            break;
    }
    --p.vel[1];
    return p;
}

bool is_within(int x, int lo, int hi)
{
    return lo <= x && x <= hi;
}

tuple<int,AI2> tryvel(int vx, int vy)
{
    Probe p{AI2{0, 0}, AI2{vx, vy}};
    int highest = 0;
    for (int step = 1;; ++step) {
        p = advance_probe(p);
        highest = std::max(highest, p.pos[1]);
        if (is_within(p.pos[0], input_min[0], input_max[0]) &&
            is_within(p.pos[1], input_min[1], input_max[1])) {
            return {highest,AI2{vx,vy}};
        }
        if(p.pos[1]<input_min[1]){
            return {INT_MIN,AI2{INT_MIN,INT_MIN}};
        }
    }
}

struct Result {
int highest;
set<AI2> vs;
bool operator==(const Result&y)const{
return highest==y.highest && vs.size()==y.vs.size();}
};

void update(Result&r,tuple<int,AI2> hv){
    auto [highest,v]=hv;
    if(highest==INT_MIN){return;}
    r.highest = std::max(r.highest,highest);
    r.vs.insert(v);
}

void P1()
{
    Result result;
    Result prev_result;
    for (int r = 1;; ++r) {
        for (int k = 0; k <= r; ++k) {
            update(result, tryvel(k, r));
            update(result, tryvel(k, -r));
        }
        for (int k = -r + 1; k <= r - 1; ++k) {
            update(result, tryvel(r, k));
        }
        if(!(prev_result==result)){
            prev_result=result;
            printf("r %d, highest %d, unique: %d\n",r,result.highest,~result.vs);
        }
    }
}

int main()
{
    P1();
    return 0;
}

//176 no
