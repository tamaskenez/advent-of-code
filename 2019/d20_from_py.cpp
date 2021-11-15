// https://github.com/penteract/adventofcode/blob/master/20/sol.py
#include "common.h"

map<AI2, char> mkmap(const VS& lines)
{
    map<AI2, char> m;
    assert(!lines.empty());
    int H = ~lines;
    int W = ~lines[0];
    FOR (r, 0, < H) {
        auto& l = lines[r];
        assert(~l == W);
        FOR (c, 0, < W) {
            m[AI2{c, r}] = l[c];
        }
    }
    return m;
}

vector<AI2> neighbs(AI2 xy)
{
    auto [x, y] = xy;
    vector<AI2> v = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
    return v;
}

using XYL = pair<AI2, int>;
vector<XYL> available(XYL p, const map<AI2, char>& m, const map<AI2, XYL>& tp)
{
    vector<XYL> r;
    for (auto x : neighbs(p.FST)) {
        if (m.at(x) == '.') {
            r.emplace_back(x, p.SND);
        }
    }
    if (findable(tp, p.FST)) {
        r.emplace_back(tp.at(p.FST).FST, tp.at(p.FST).SND + p.SND);
    }
    return r;
}

bool isouter(AI2 p)
{
    return p[0] < 10 || p[1] < 10 || max(p[0], p[1]) > 110;
}

void print(const map<AI2, XYL>& tp)
{
    for (auto& kv : tp) {
        printf("(%d,%d) -> ((%d,%d),%d)\n", kv.FST[0], kv.FST[1], kv.SND.FST[0], kv.SND.FST[1],
               kv.SND.SND);
    }
}

void solve()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    printf("START\n");
    for (auto& l : lines) {
        printf("%s\n", l.c_str());
    }
    printf("END\n");
    auto m = mkmap(lines);
    map<AI2, XYL> tp;
    map<string, AI2> ls;
    for (auto& kv : m) {
        auto k = kv.FST;
        if (kv.SND != '.') {
            continue;
        }
        for (auto x : neighbs(k)) {
            if (!isupper(m[x])) {
                continue;
            }
            auto dx = x[0] - k[0];
            auto dy = x[1] - k[1];
            auto t = string{m[x], m[AI2{x[0] + dx, x[1] + dy}]};
            if (dx + dy < 0) {
                swap(t[0], t[1]);
            }
            if (findable(ls, t)) {
                auto o = isouter(k) ? -1 : 1;
                tp[k] = XYL{ls[t], o};
                tp[ls[t]] = XYL{k, -o};
            } else {
                ls[t] = k;
            }
        }
    }

    print(tp);
    auto pos = ls["AA"];
    auto fr = map<int, vector<XYL>>{};
    fr[0].PB(XYL{pos, 0});
    auto seen = set<XYL>{};

    while (!fr.empty()) {
        auto bit = fr.begin();
        auto& bv = bit->second;
        assert(!bv.empty());
        auto [d, nxp] = make_tuple(bit->first, bv.back());
        bv.pop_back();
        if (bv.empty()) {
            fr.erase(bit);
        }
        for (auto k : available(nxp, m, tp)) {
            if (!findable(seen, k) && k.SND >= 0) {
                seen.insert(k);
                fr[d + 1].PB(k);
            }
        }
        if (nxp == XYL{ls["ZZ"], 0}) {
            printf("done %d ((%d,%d),%d)\n", d, nxp.FST[0], nxp.FST[1], nxp.SND);
            break;
        }
    }
}

int main()
{
    solve();
    return 0;
}
