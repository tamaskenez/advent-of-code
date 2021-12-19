#include "common.h"

// Scanner having a rotation means the scanner's x axis corresponds to f, y to u, z to r;
struct Rot
{
    AI3 f, u, r;
    bool operator<(const Rot& y) const
    {
        if (f < y.f) {
            return true;
        }
        if (f > y.f) {
            return false;
        }
        if (u < y.u) {
            return true;
        }
        if (u > y.u) {
            return false;
        }
        return r < y.r;
    }
};

struct Trans
{
    Rot rot;
    AI3 xlat;
    bool operator<(const Trans& y) const
    {
        if (rot < y.rot) {
            return true;
        }
        if (y.rot < rot) {
            return false;
        }
        return xlat < y.xlat;
    }
};

struct Mapping
{
    int other_scanner_no;
    Trans trans;
};

struct Scanner
{
    vector<AI3> ps;
    vector<int> closestd;
    vector<vector<AI3>> closestp;
    vector<Mapping> mappings_to, mappings_from;

    void prepare()
    {
        closestd.resize(~ps);
        closestp.resize(~ps);
        FOR (i, 0, < ~ps) {
            int c = INT_MAX;
            vector<AI3> pp;
            FOR (j, 0, < ~ps) {
                if (i == j) {
                    continue;
                }
                auto m = manhattan(ps[i], ps[j]);
                if (m < c) {
                    c = m;
                    pp.assign(1, ps[j]);
                } else if (m == c) {
                    pp.PB(ps[j]);
                }
            }
            closestd[i] = c;
            closestp[i] = pp;
        }
    }
};

using VSCS = vector<Scanner>;

vector<Rot> generate_rotations()
{
    vector<Rot> rots;
    for (int fno : {0, 1, 2}) {
        for (bool neg : {false, true}) {
            auto f = AI3{0, 0, 0};
            f[fno] = neg ? -1 : 1;
            for (auto uno : {0, 1, 2}) {
                if (uno == fno) {
                    continue;
                }
                for (bool uneg : {false, true}) {
                    auto u = AI3{0, 0, 0};
                    u[uno] = uneg ? -1 : 1;
                    auto r = cross_product(f, u);
                    rots.PB(Rot{f, u, r});
                }
            }
        }
    }
    return rots;
}

AI3 apply_rot(const Rot& r, AI3 p)
{
    return AI3{dot_product(r.f, p), dot_product(r.u, p), dot_product(r.r, p)};
}

AI3 apply_reverse_rot(const Rot& r, AI3 p)
{
    AI3 y;
    FOR (i, 0, < 3) {
        y[i] = dot_product(AI3{r.f[i], r.u[i], r.r[i]}, p);
    }
    return y;
}

bool same_abs_numbers(AI3 a, AI3 b)
{
    a = abs(a);
    b = abs(b);
    sort(BE(a));
    sort(BE(b));
    return a == b;
}

bool is_equal_enough(vector<AI3> a, vector<AI3> b)
{
    sort(BE(a));
    sort(BE(b));
    return ~set_intersection(BE(a), BE(b)) >= 12;
}

void P1(VSCS scs)
{
    for (auto& sc : scs) {
        sc.prepare();
    }
    auto rots = generate_rotations();
    set<int> aligned = {0};
    set<int> unaligned;
    FOR (i, 1, < ~scs) {
        unaligned.insert(i);
    }

    while (!unaligned.empty()) {
        bool found = false;
        for (auto ua : unaligned) {
            for (auto al : aligned) {
                // Try to align ua to al
                map<int, pair<VI, VI>> m;  // map distance to points in al and ua
                auto& sal = scs[al];
                auto& sua = scs[ua];
                FOR (i, 0, < ~sal.ps) {
                    m[sal.closestd[i]].first.PB(i);
                }
                FOR (i, 0, < ~sua.ps) {
                    m[sua.closestd[i]].second.PB(i);
                }
                set<Trans> good_transs;
                for (auto& [d, pvivi] : m) {
                    if (pvivi.FST.empty() || pvivi.SND.empty()) {
                        continue;
                    }
                    for (auto p : pvivi.FST) {
                        for (auto q : pvivi.SND) {
                            for (auto po : sal.closestp[p]) {
                                for (auto qo : sua.closestp[q]) {
                                    // We have two pairs
                                    // sal.ps[p] -> sal.ps[po]
                                    // sua.ps[q] -> sua.ps[qo]
                                    // Find the rotation
                                    auto psp = sal.ps[p];
                                    auto psq = sua.ps[q];
                                    auto pd = po - psp;
                                    auto qd = qo - psq;
                                    // Which takes pd to qd
                                    if (same_abs_numbers(pd, qd)) {
                                        continue;
                                    }
                                    for (auto& r : rots) {
                                        if (qd == apply_rot(r, pd)) {
                                            auto xlat = sua.ps[q] - apply_rot(r, sal.ps[p]);
                                            good_transs.insert(Trans{r, xlat});
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                int counter = 0;
                for (auto& tr : good_transs) {
                    vector<AI3> transformed_al;
                    for (auto p : sal.ps) {
                        auto q = apply_rot(tr.rot, p) + tr.xlat;
                        transformed_al.PB(q);
                    }
                    if (is_equal_enough(transformed_al, sua.ps)) {
                        scs[al].mappings_to.PB(Mapping{ua, tr});
                        scs[ua].mappings_from.PB(Mapping{al, tr});
                        ++counter;
                    }
                }
                assert(counter <= 1);
                if (counter == 1) {
                    found = true;
                    unaligned.erase(ua);
                    aligned.insert(ua);
                    break;
                }
            }  // for aligned
            if (found) {
                break;
            }
        }  // for unaligned
    }      // while not empty

    set<AI3> ps;
    vector<AI3> origins;
    FOR (i, 0, < ~scs) {
        auto& sc = scs[i];
        if (i == 0) {
            ps.insert(BE(sc.ps));
            origins.PB(AI3{0, 0, 0});
            continue;
        }
        auto forward = i;
        auto ps_to_trans = scs[i].ps;
        AI3 origin{0, 0, 0};
        do {
            assert(~scs[forward].mappings_from == 1);
            auto& mapping_from = scs[forward].mappings_from[0];
            auto trans = mapping_from.trans;
            for (auto& p : ps_to_trans) {
                p = apply_reverse_rot(trans.rot, p - trans.xlat);
            }
            origin = apply_reverse_rot(trans.rot, origin - trans.xlat);
            forward = mapping_from.other_scanner_no;
        } while (forward != 0);
        ps.insert(BE(ps_to_trans));
        origins.PB(origin);
    }

    printf("P1: %d\n", ~ps);
    int maxd = 0;
    FOR (i, 0, < ~origins - 1) {
        FOR (j, i + 1, < ~origins) {
            maxd = std::max(maxd, manhattan(origins[i], origins[j]));
        }
    }
    printf("P2: %d\n", maxd);
}

// 13122 high

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d19_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    optional<int> sno;
    VSCS scs;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        if (starts_with(l, "---")) {
            assert(l[11] == ' ');
            sno = stoi(l.substr(12));
            continue;
        }
        assert(sno);
        if (~scs <= *sno) {
            scs.resize(*sno + 1);
        }
        auto ns = split(l, ",");
        assert(~ns == 3);
        auto p = AI3{stoi(ns[0]), stoi(ns[1]), stoi(ns[2])};
        scs[*sno].ps.PB(p);
    }
    P1(scs);
    return 0;
}

// 1:44:00
