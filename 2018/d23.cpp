#include "common.h"

using I64 = int64_t;
using AL3 = array<I64, 3>;

struct Bot
{
    AL3 pos;
    I64 r;
};

bool in_range(const Bot& a, const Bot& b)
{
    return manhattan(a.pos, b.pos) <= a.r + b.r;
}

int points_in_range_on_edge(const Bot& a, const Bot& b)
{
    if (!in_range(a, b)) {
        return {};
    }
    AL3 mins, maxs;
    FOR (i, 0, < 3) {
        mins[i] = max(a.pos[i] - a.r, b.pos[i] - b.r);
        maxs[i] = min(a.pos[i] + a.r, b.pos[i] + b.r);
        if (maxs[i] < mins[i]) {
            return {};
        }
    }
    assert(in_range(a, b));
    int result = 0;
    FOR (x, mins[0], <= maxs[0]) {
        auto a_left = a.r - abs(x - a.pos[0]);
        auto b_left = b.r - abs(x - b.pos[0]);
        assert(a_left >= 0 && b_left >= 0);
        auto miny = max(a.pos[1] - a_left, b.pos[1] - b_left);
        auto maxy = min(a.pos[1] + a_left, b.pos[1] + b_left);
        miny = max(miny, mins[1]);
        maxy = min(maxy, maxs[1]);
        FOR (y, miny, <= maxy) {
            a_left = a.r - abs(x - a.pos[0]) - abs(y - a.pos[1]);
            b_left = b.r - abs(x - b.pos[0]) - abs(y - b.pos[1]);
            assert(a_left >= 0 && b_left >= 0);
            auto minz = max(a.pos[2] - a_left, b.pos[2] - b_left);
            auto maxz = min(a.pos[2] + a_left, b.pos[2] + b_left);
            minz = max(minz, mins[2]);
            maxz = min(maxz, maxs[2]);
            if (minz <= maxz) {
                bool b1 = manhattan(AL3{x, y, minz}, a.pos) == a.r;
                bool b2 = manhattan(AL3{x, y, minz}, b.pos) == b.r;
                if (b1 || b2) {
                    // result.PB(AL3{x, y, minz});
                    ++result;
                }
                if (minz < maxz) {
                    bool b3 = manhattan(AL3{x, y, maxz}, a.pos) == a.r;
                    bool b4 = manhattan(AL3{x, y, maxz}, b.pos) == b.r;
                    if (b3 || b4) {
                        // result.PB(AL3{x, y, maxz});
                        ++result;
                    }
                }
            }
        }
    }
    return result;
}

AL3 sign_vector(int i)
{
    return AL3{(i & 1) ? 1 : -1, (i & 2) ? 1 : -1, (i & 4) ? 1 : -1};
}

I64 get_plane(AL3 pos, I64 r, AL3 s)
{
    return s[0] * (pos[0] + s[0] * r) + s[1] * pos[1] + s[2] * pos[2];
}

int count_bots_in_range(const vector<Bot>& bots, AL3 p)
{
    int c = 0;
    for (auto& b : bots) {
        if (manhattan(b.pos, p) <= b.r) {
            ++c;
        }
    }
    return c;
};

const AL3 origin{0, 0, 0};

void iterate_from(const vector<Bot>& bots, AL3 p)
{
    int bestn = count_bots_in_range(bots, p);
    auto bestd = manhattan(origin, p);
    auto bestp = p;
    printf("starting iteration with count %d d %lld\n", bestn, bestd);
    for (;;) {
        bool changed = false;
        p = bestp;
        FOR (i, 0, < 3 * 3 * 3) {
            auto dx = (i % 3 - 1);
            auto dy = ((i / 3) % 3 - 1);
            auto dz = ((i / 9) % 3 - 1);
            auto q = AL3{p[0] + dx, p[1] + dy, p[2] + dz};
            int n = count_bots_in_range(bots, q);
            auto d = manhattan(origin, q);
            if (n > bestn || (n == bestn && d < bestd)) {
                bestn = n;
                bestd = d;
                bestp = q;
                printf("better count %d, d %lld (%lld %lld %lld\n", bestn, bestd, bestp[0],
                       bestp[1], bestp[2]);
                changed = true;
            }
        }
        if (!changed) {
            printf("Done iteration.\n");
            break;
        }
    }
}

void analyze(const vector<Bot>& bots, AL3 p)
{
    vector<AL3> closer(3, p);
    auto dp = manhattan(p, origin);
    FOR (i, 0, < 3) {
        closer[i][i] += -sgn(closer[i][i]);
        auto dq = manhattan(closer[i], origin);
    }
    FOR (i, 0, < ~bots - 1) {
        auto& bi = bots[i];
        auto ri = manhattan(bi.pos, p) - bi.r;
        FOR (j, i + 1, < ~bots) {
            auto& bj = bots[j];
            auto rj = manhattan(bj.pos, p) - bj.r;
            if ((ri == 0 && rj == 0) || (ri == -1 && rj == 0) || (ri == 0 && rj == -1)) {
                int close_both_in_count = 0;
                assert(manhattan(bi.pos, p) <= bi.r);
                assert(manhattan(bj.pos, p) <= bj.r);
                for (auto c : closer) {
                    bool in1 = manhattan(bi.pos, c) <= bi.r;
                    bool in2 = manhattan(bj.pos, c) <= bj.r;
                    if (in1 && in2) {
                        ++close_both_in_count;
                    }
                }
                if (close_both_in_count == 0) {
                    printf("%d and %d (rij %lld %lld)\n", i, j, ri, rj);
                }
            }
        }
    }
}

pair<I64, I64> tau_limits(AL3 p0, AL3 normal, AL3 center, I64 r)
{
    printf("%lld %lld %lld\n", p0[0] - center[0], p0[1] - center[1], p0[2] - center[2]);
    // p0 + normal * tau is a line
    // we need lo <= tau <= hi where manhattan(p0 + normal * tau, center) == r
    bool found_zero = false;
    int zero_coord;
    FOR (i, 0, < 3) {
        if (normal[i] == 0) {
            assert(!found_zero);
            zero_coord = i;
            found_zero = true;
        }
    }
    // lhs = SUM abs(p0[c] + tau * normal[c] - center[c])
    int nc1 = (zero_coord + 1) % 3;
    int nc2 = (zero_coord + 2) % 3;
    auto tau1 = -(p0[nc1] - center[nc1]) / normal[nc1];
    auto tau2 = -(p0[nc2] - center[nc2]) / normal[nc2];
    if (tau1 > tau2) {
        swap(tau1, tau2);
    }
    auto eval_at = [p0, normal, center](I64 tau) { return manhattan(p0 + normal * tau, center); };
    assert(eval_at(tau1) == r);
    if (tau1 != tau2) {
        assert(eval_at(tau1 + 1) == r);
        assert(eval_at(tau2 - 1) == r);
        assert(eval_at(tau2) == r);
    }
    return pair<I64, I64>{tau1, tau2};
}

array<AL3, 3> get_vertices(AL3 pos, I64 r, AL3 sv)
{
    array<AL3, 3> vs;
    vs.fill(pos);
    FOR (i, 0, < 3) {
        vs[i][i] += sv[i] * r;
    }
    return vs;
}

maybe<AL3> get_intersection(AL3 a0, AL3 a1, AL3 b0, AL3 b1)
{
    auto va = a1 - a0;
    auto vb = b1 - b0;
    auto ma = abs(va[0]);
    auto mb = abs(vb[0]);
    FOR (i, 1, < 3) {
        ma = max(ma, abs(va[i]));
        mb = max(mb, abs(vb[i]));
    }
    assert(ma != 0);
    assert(mb != 0);
    int za = 0, zb = 0;
    FOR (i, 0, < 3) {
        if (va[i] == 0) {
            ++za;
        } else {
            assert(abs(va[i]) == ma);
            va[i] /= ma;
        }
        if (vb[i] == 0) {
            ++zb;
        } else {
            assert(abs(vb[i]) == mb);
            vb[i] /= mb;
        }
    }
    assert(za == 1 && zb == 1);
    if (va == vb || va == -vb) {
        return {};
    }
    auto C1 = b0[0] - a0[0];
    auto C2 = b0[1] - a0[1];
    auto D1 = -vb[1] * C1 + vb[0] * C2;
    auto D2 = -va[1] * C1 + va[0] * C2;
    auto det_denom = -va[0] * vb[1] + vb[0] * va[1];
    if (abs(det_denom) == 1) {
        auto tau1 = D1 / det_denom;
        auto tau2 = D2 / det_denom;
        auto check1 = va * tau1 + a0;
        auto check2 = vb * tau2 + b0;
        assert(check1 == check2);
        if (is_between_cc(tau1, 0LL, ma) && is_between_cc(tau2, 0LL, mb)) {
            return check1;
        } else {
            return {};
        }
    } else {
        int a = 3;
    }
    return {};
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d23_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    // pos=<222387066,65494240,34682491>, r=65410023
    vector<Bot> bots_loading;
    RunningStat<I64> rr;
    for (auto& l : lines) {
        auto xs = split(l, "pos=<>, \tr");
        assert(~xs == 4);
        auto ys = map_to_vec(xs, CALL(stoll));
        auto pos = AL3{ys[0], ys[1], ys[2]};
        auto r = ys[3];
        rr.add(r);
        bots_loading.PB(Bot{pos, r});
    }
    const auto& bots = bots_loading;
    printf("total %d bots\n", ~bots);
    {
        RunningStatPair<I64, Bot> stat;
        // Find strongest.
        for (auto& b : bots) {
            stat.add(b.r, b);
        }
        assert(stat.upper_count == 1);
        auto sp = stat.upper->SND.pos;
        auto sr = stat.upper->SND.r;
        printf("strongest (%lld %lld %lld r %lld)\n", sp[0], sp[1], sp[2], sr);
        int count = 0;
        for (auto& b : bots) {
            if (manhattan(b.pos, sp) <= sr) {
                ++count;
            }
        }
        printf("in strongest range: count %d\n", count);
    }

    if (0) {
        vector<AL3> points;
        FOR (i, 0, < ~bots - 1) {
            auto& bi = bots[i];
            FOR (j, i + 1, < ~bots) {
                auto& bj = bots[j];
                if (!in_range(bi, bj)) {
                    continue;
                }
                bool bi_even = is_even(sum(bi.pos) + bi.r);
                bool bj_even = is_even(sum(bj.pos) + bj.r);
                vector<pair<I64, I64>> radii;
                if (bi_even == bj_even) {
                    radii.emplace_back(bi.r, bj.r);
                } else {
                    radii.emplace_back(bi.r, bj.r - 1);
                    radii.emplace_back(bi.r - 1, bj.r);
                }
                for (auto rii : radii) {
                    FOR (k, 0, < 8) {
                        auto sv = sign_vector(k);
                        for (auto sign2 : {-1, 1}) {
                            auto pi = get_plane(bi.pos, rii.first, sv);
                            auto pj = get_plane(bj.pos, rii.second, sv * sign2);
                            if (pi == pj * sign2) {
                                printf("coplanar %d %d\n", i, j);
                                // need 3 edges
                                auto edgesi = get_vertices(bi.pos, rii.first, sv);
                                auto edgesj = get_vertices(bj.pos, rii.second, sv * sign2);
                                FOR (vi, 0, < 3) {
                                    FOR (vj, 0, < 3) {
                                        auto m_is =
                                            get_intersection(edgesi[vi], edgesi[(vi + 1) % 3],
                                                             edgesj[vj], edgesj[(vj + 1) % 3]);
                                        if (m_is) {
                                            points.PB(*m_is);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        int bestn = -1;
        I64 bestd = INT64_MAX;
        for (auto p : points) {
            auto n = count_bots_in_range(bots, p);
            auto d = manhattan(p, origin);
            if (n > bestn || (n == bestn && d < bestd)) {
                bestn = n;
                bestd = d;
                printf("bestn %d bestd %lld (%lld,%lld,%lld)\n", bestn, bestd, p[0], p[1], p[2]);
            }
        }
        exit(0);
    }
    if (0) {
        auto p = AL3{59182453, 49186430, 10819933};
        analyze(bots, p);
        iterate_from(bots, p);
        exit(0);
    }
    vector<AL3> points;
    auto add_points = [&points](I64 xtoy, I64 betay, I64 xtoz, I64 betaz, AL3 lower, AL3 upper,
                                const Bot& /* bi*/, const Bot& /* bj*/) {
        bool yok = true;
        bool zok = true;
        if (xtoy > 0) {
            lower[0] = max(lower[0], (lower[1] - betay) / xtoy);
            upper[0] = min(upper[0], (upper[1] - betay) / xtoy);
        } else if (xtoy < 0) {
            lower[0] = max(lower[0], (upper[1] - betay) / xtoy);
            upper[0] = min(upper[0], (lower[1] - betay) / xtoy);
        } else {
            yok = is_between_cc(betay, lower[1], upper[1]);
        }
        if (xtoz > 0) {
            lower[0] = max(lower[0], (lower[2] - betaz) / xtoz);
            upper[0] = min(upper[0], (upper[2] - betaz) / xtoz);
        } else if (xtoz < 0) {
            lower[0] = max(lower[0], (upper[2] - betaz) / xtoz);
            upper[0] = min(upper[0], (lower[2] - betaz) / xtoz);
        } else {
            zok = is_between_cc(betaz, lower[2], upper[2]);
        }
        bool xok = lower[0] <= upper[0];
        if (xok && yok && zok) {
            auto x = lower[0];
            auto y = xtoy * x + betay;
            auto z = xtoz * x + betaz;
            points.PB(AL3{x, y, z});
            x = upper[0];
            y = xtoy * x + betay;
            z = xtoz * x + betaz;
            points.PB(AL3{x, y, z});
            x = (upper[0] + lower[0]) / 2;
            y = xtoy * x + betay;
            z = xtoz * x + betaz;
            points.PB(AL3{x, y, z});
        }
    };
    int best_nbots_int_range = -1;
    I64 best_dist = INT_MAX;
    FOR (i, 0, < ~bots - 1) {
        i = 165;
        auto bi = bots[i];
        FOR (j, i + 1, < ~bots) {
            j = 200;
            auto bj = bots[j];
            // bi = Bot{AL3{-5, 0, 0}, 5};
            // bj = Bot{AL3{5, 0, 0}, 5};
            if (!in_range(bi, bj)) {
                continue;
            }
            points.clear();
            bool bi_even = is_even(sum(bi.pos) + bi.r);
            bool bj_even = is_even(sum(bj.pos) + bj.r);
            vector<pair<I64, I64>> radii;
            if (bi_even == bj_even) {
                radii.emplace_back(bi.r, bj.r);
            } else {
                radii.emplace_back(bi.r, bj.r - 1);
                radii.emplace_back(bi.r - 1, bj.r);
            }
            for (auto rii : radii) {
                FOR (ie, 0, < 8) {
                    auto sa = sign_vector(ie);
                    int a = 3;
                    FOR (je, 0, < 8) {
                        auto sb = sign_vector(je);
                        {
                            auto dp = dot_product(sa, sb);
                            if (dp == 3 || dp == -3) {
                                continue;
                            }
                        }
                        AL3 lower, upper;
                        bool notgood = false;

                        FOR (c, 0, < 3) {
                            lower[c] = max(bi.pos[c] - (sa[c] < 0 ? rii.FST : 0),
                                           bj.pos[c] - (sb[c] < 0 ? rii.SND : 0));
                            upper[c] = min(bi.pos[c] + (sa[c] > 0 ? rii.FST : 0),
                                           bj.pos[c] + (sb[c] > 0 ? rii.SND : 0));
                            if (upper[c] < lower[c]) {
                                notgood = true;
                                break;
                            }
                        }
                        if (notgood) {
                            continue;
                        }

                        auto normal = cross_product(sa, sb);
                        array<I64, 3> allowed_values = {-2, 0, 2};
                        FOR (i, 0, < 3) {
                            assert(contains(BE(allowed_values), normal[i]));
                        }
                        normal /= 2;
                        assert(dot_product(normal, sa) == 0);
                        assert(dot_product(normal, sb) == 0);

                        AL3 p0;
                        auto det_denom_x = sa[1] * sb[2] - sa[2] * sb[1];
                        if (det_denom_x == 0) {
                            // swap x and y
                            p0[1] = 0;
                            auto det_denom_y = sa[0] * sb[2] - sa[2] * sb[0];
                            assert(det_denom_y != 0);
                            auto pa = get_plane(bi.pos, rii.FST, sa);
                            auto pb = get_plane(bj.pos, rii.SND, sb);
                            auto betax = sb[2] * pa - sa[2] * pb;
                            auto betaz = -sb[0] * pa + sa[0] * pb;
                            assert(is_even(betax) && is_even(betaz));
                            p0[0] = betax / det_denom_y;
                            p0[2] = betaz / det_denom_y;
                        } else {
                            p0[0] = 0;
                            auto pa = get_plane(bi.pos, rii.FST, sa);
                            auto pb = get_plane(bj.pos, rii.SND, sb);
                            auto betay = sb[2] * pa - sa[2] * pb;
                            auto betaz = -sb[1] * pa + sa[1] * pb;
                            assert(is_even(betay) && is_even(betaz));
                            p0[1] = betay / det_denom_x;
                            p0[2] = betaz / det_denom_x;
                        }
                        if (sa == AL3{-1, 1, 1} && sb == AL3{-1, -1, -1}) {
                            auto tt1 = tau_limits(p0, normal, bi.pos, rii.FST);
                            auto tt2 = tau_limits(p0, normal, bj.pos, rii.SND);
                            auto lotau = max(tt1.FST, tt2.FST);
                            auto hitau = min(tt1.SND, tt2.SND);
                            if (lotau > hitau) {
                                continue;
                            }
                            for (auto c : {AL3{59182453, 49186430, 10819933}, p0 + normal * lotau,
                                           p0 + normal * hitau}) {
                                auto ra = manhattan(c, bi.pos) - bi.r;
                                auto rb = manhattan(c, bj.pos) - bj.r;
                                auto d = manhattan(c, origin);
                                auto n = count_bots_in_range(bots, c);
                                int a = 3;
                            }
                        }
                        /*
                         */
                        // line: p0 + normal * tau
                        /*
                        auto xtoy = (-sb[2] * sa[0] + sa[2] * sb[0]) / det_denom;
                        auto xtoz = (sb[1] * sa[0] - sa[1] * sb[0]) / det_denom;
                        auto pa = get_plane(bi.pos, bi.r, sa);
                        auto pb = get_plane(bj.pos, bj.r, sb);
                        auto pam = get_plane(bi.pos, bi.r - 1, sa);
                        auto pbm = get_plane(bj.pos, bj.r - 1, sb);
                        auto betay = sb[2] * pa - sa[2] * pb;
                        auto betaz = -sb[1] * pa + sa[1] * pb;
                        assert((betay & 1) == (betaz & 1));
                        if (betay & 1) {
                            auto betayam = sb[2] * pam - sa[2] * pb;
                            auto betazam = -sb[1] * pam + sa[1] * pb;
                            auto betaybm = sb[2] * pa - sa[2] * pbm;
                            auto betazbm = -sb[1] * pa + sa[1] * pbm;
                            assert(is_even(betayam));
                            assert(is_even(betazam));
                            assert(is_even(betaybm));
                            assert(is_even(betazbm));
                            betayam /= det_denom;
                            betazam /= det_denom;
                            betaybm /= det_denom;
                            betazbm /= det_denom;
                            add_points(xtoy, betayam, xtoz, betazam, lower, upper, bi, bj);
                            add_points(xtoy, betaybm, xtoz, betazbm, lower, upper, bi, bj);
                        } else {
                            betay /= det_denom;
                            betaz /= det_denom;
                            auto c1 = ~points;
                            add_points(xtoy, betay, xtoz, betaz, lower, upper, bi, bj);
                            auto c2 = ~points;
                            if (false && c1 != c2) {
                                auto p = points.back();
                                auto x = p[0];
                                auto y = xtoy * x + betay;
                                auto z = xtoz * x + betaz;
                                auto should_be_a = sa[0] * x + sa[1] * y + sa[2] * z;
                                auto should_be_b = sb[0] * x + sb[1] * y + sb[2] * z;
                                auto r = manhattan(AL3{x, y, z}, bi.pos);
                                auto also_should_be_a =
                                    bi.pos[0] + sa[0] * bi.r + bi.pos[1] + bi.pos[2];
                                int a = 3;
                            }
                        }*/
                    }
                }
            }
            sort_unique_trunc(points);
            for (auto p : points) {
                auto dra = bi.r - manhattan(bi.pos, p);
                auto drb = bj.r - manhattan(bj.pos, p);
                auto d = manhattan(p, origin);
                auto c = count_bots_in_range(bots, p);
                if (c > best_nbots_int_range || (c == best_nbots_int_range && d < best_dist)) {
                    best_nbots_int_range = c;
                    best_dist = d;
                    printf("%d bots %lld (%lld %lld %lld)\n", best_nbots_int_range, best_dist, p[0],
                           p[1], p[2]);
                }
            }
        }
    }

    return 0;
}

// 956 bots 120282120 (59729105 49186430 11366585)
// 956 bots 119213862 (59194976 49186430 10832456)
// too high 132256348 (883)
// too high 120232633 (928)
// too high 122010228 (949)
// ? better count 980, d 119188816 (59182453 49186430 10819933
// not correct better count 956, d 119213860 (59194975 49186430 10832455