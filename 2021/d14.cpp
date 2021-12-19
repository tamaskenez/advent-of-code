#include "common.h"

void P2(string pol, map<string, string> m)
{
    map<string, int64_t> mm;
    pol = " " + pol + " ";
    FOR (i, 0, < ~pol - 1) {
        mm[pol.substr(i, 2)]++;
    }
    FOR (step, 0, < 40) {
        map<string, int64_t> newmm;
        for (auto [pr, count] : mm) {
            if (pr.find(' ') != string::npos) {
                newmm[pr]++;
                continue;
            }
            auto it = m.find(pr);
            assert(it != m.end());
            newmm[string(1, pr[0]) + it->second] += count;
            newmm[it->second + pr[1]] += count;
        }
        newmm.swap(mm);
    }

    map<char, int64_t> freq;
    for (auto [pr, count] : mm) {
        for (auto ch : pr) {
            if (ch != ' ') {
                freq[ch] += count;
            }
        }
    }
    vector<pair<int64_t, char>> v;
    for (auto [c, fr] : freq) {
        v.PB(make_pair(fr, c));
    }
    sort(BE(v));
    auto fr1 = v[0].first;
    auto fr2 = v.back().first;
    assert((fr1 & 1) == 0);
    assert((fr2 & 1) == 0);
    auto p2 = (fr2 - fr1) / 2;
    printf("P2: %lld\n", p2);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d14_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    auto pol = trim(lines[0]);
    auto pol0 = pol;
    assert(trim(lines[1]).empty());
    map<string, string> m;
    FOR (i, 2, < ~lines) {
        auto ll = split(trim(lines[i]), " -> ");
        m[ll[0]] = ll[1];
    }
    FOR (step, 0, < 10) {
        string newpol;
        FOR (i, 0, < ~pol - 1) {
            auto a = pol[i];
            newpol += a;
            auto b = pol[i + 1];
            auto ab = string(1, a) + b;
            auto it = m.find(ab);
            assert(it != m.end());
            auto c = it->second;
            newpol += c;
        }
        newpol += pol.back();
        newpol.swap(pol);
    }
    map<char, int> freq;
    for (auto c : pol) {
        freq[c]++;
    }
    vector<pair<int, char>> v;
    for (auto [c, fr] : freq) {
        v.PB(make_pair(fr, c));
    }
    sort(BE(v));
    auto fr1 = v[0].first;
    auto fr2 = v.back().first;
    auto p1 = fr2 - fr1;
    printf("P1: %d\n", p1);
    P2(pol0, m);
    return 0;
}
