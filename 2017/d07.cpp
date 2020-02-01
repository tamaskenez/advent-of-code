#include "common.h"

int get_total_weight(const string& n,
                     const map<string, VS>& M,
                     const map<string, int>& N,
                     map<string, int>& TW)
{
    auto it = M.find(n);
    if (it == M.end() || it->second.empty()) {
        // no children
        return N.at(n);
    }
    int tw = 0;
    // it->second map get_total_weight($, M, N, TW) =>> sum
    for (auto& ch : it->second) {
        tw += get_total_weight(ch, M, N, TW);
    }
    return tw + N.at(n);
}

bool do_something_with_children(const string& n,
                                const map<string, VS>& M,
                                const map<string, int>& N,
                                map<string, int>& TW)
{
    auto it = M.find(n);
    if (it == M.end() || it->second.empty()) {
        return false;
    }
    auto& chs = it->second;

    VI ws;
    for (auto& ch : chs) {
        ws.PB(TW.at(ch));
        if (do_something_with_children(ch, M, N, TW)) {
            return true;
        }
    }

    auto zs = ws;
    sort_unique_trunc(zs);
    if (~zs <= 1) {
        return false;
    }
    assert(~zs == 2);
    zs = ws;
    sort(BE(zs));
    assert(~zs != 2);
    int okw = zs[~zs / 2];
    bool found = false;
    FOR (i, 0, < ~chs) {
        if (ws[i] == okw) {
            continue;
        }
        auto& ch = chs[i];
        printf("%s is %d in itself, could be %d\n", ch.c_str(), N.at(ch), N.at(ch) - ws[i] + okw);
        found = true;
    }
    assert(found);
    return true;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d07_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, VS> M;
    map<string, int> N;
    for (auto& l : lines) {
        auto vs = split(l, " ->,\t");
        // ehsqyyb (174) -> xtcdt, tujcuy, wiqohmb, cxdwmu
        auto lhs = vs[0];
        auto lhsnum = stoi(vs[1].substr(1, ~(vs[1]) - 2));
        VS chs;
        FOR (i, 2, < ~vs) {
            auto n = vs[i];
            chs.PB(n);
        }
        M[lhs] = chs;
        N[lhs] = lhsnum;
    }
    string root;
    {
        set<string> a;
        for (auto& kv : N) {
            a.insert(kv.first);
        }
        for (auto& kv : M) {
            for (auto& b : kv.second) {
                a.erase(b);
            }
        }
        for (auto& b : a) {
            printf("%s\n", b.c_str());
        }
        assert(~a == 1);
        root = *a.begin();
    }

    map<string, int> TW;
    for (auto& kv : N) {
        if (!contains(TW, kv.first)) {
            TW[kv.first] = get_total_weight(kv.first, M, N, TW);
        }
    }

    do_something_with_children(root, M, N, TW);
    return 0;
}
