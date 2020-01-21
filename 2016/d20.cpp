#include "common.h"

using UL = unsigned long;
using PUL = pair<UL, UL>;  // SND exclusive

bool is_ok(const vector<PUL>& ivs, UL cand)
{
    auto it = upper_bound(BE(ivs), cand, [](auto a, auto b) { return a < b.FST; });
    if (it == ivs.begin()) {
        return true;
    }
    --it;
    for (;;) {
        assert(it->first <= cand);
        if (cand < it->second) {
            return false;
        }
        ++it;
        if (it == ivs.end()) {
            return true;
        }
        if (cand < it->second) {
            return true;
        }
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<PUL> ivs;
    for (auto& l : lines) {
        auto vs = split(l, "-");
        assert(~vs == 2);
        auto i0 = stoul(vs[0]);
        auto i1 = stoul(vs[1]);
        assert(to_string(i0) == vs[0]);
        assert(to_string(i1) == vs[1]);
        ivs.EB(i0, i1 + 1);
    }
    map<UL, pair<set<int>, set<int>>> m;
    FOR (i, 0, < ~ivs) {
        auto& iv = ivs[i];
        m[iv.FST].FST.insert(i);  // here m[..] begins interval#i
        m[iv.SND].SND.insert(i);  // here m[..] ends interval#i
    }
    map<UL, set<int>> n;
    set<int> active_iv_idcs;
    for (auto& kv : m) {
        auto& ip = kv.FST;
        auto& pp = kv.SND;
        auto& begin_set = pp.FST;
        auto& end_set = pp.SND;
        for (auto i : begin_set) {
            active_iv_idcs.insert(i);
        }
        for (auto i : end_set) {
            active_iv_idcs.erase(i);
        }
        n[ip] = active_iv_idcs;
    }
    for (auto& kv : n) {
        if (kv.second.empty()) {
            printf("%lu\n", kv.FST);
            break;
        }
    }
    printf("done\n");
    UL total = 0;
    for (auto it = n.begin();; ++it) {
        auto jt = it;
        ++jt;
        if (jt == n.end()) {
            assert(it->second.empty());
            total += (UINT32_MAX - it->first) + 1;
            break;
        }
        if (it->second.empty()) {
            total += jt->first - it->first;
        }
    }
    printf("total %lu\n", total);
    return 0;
}
// too low 906616