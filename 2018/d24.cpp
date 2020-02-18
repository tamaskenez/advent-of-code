#include "common.h"

struct Group
{
    int id;
    int count;
    int hp;
    VS weakto, immto;
    int dmgq;
    string dmgtype;
    int initiative;

    int effective_power() const
    {
        assert(count > 0);
        return dmgq * count;
    }
};

void print(const Group& g)
{
    printf("Group#%d, %d x %d hp, %d %s damage\n", g.id, g.count, g.hp, g.dmgq, g.dmgtype.c_str());
    printf("\tweak (%d):", ~g.weakto);
    for (auto& w : g.weakto) {
        printf(" %s", w.c_str());
    }
    printf("\n");
    printf("\timmune (%d):", ~g.immto);
    for (auto& w : g.immto) {
        printf(" %s", w.c_str());
    }
    printf("\n");
}

using Player = vector<Group>;

int get_possible_dmg(const Group& a, const Group& b)
{
    bool weak = contains(BE(b.weakto), a.dmgtype);
    bool immun = contains(BE(b.immto), a.dmgtype);
    assert(!(weak && immun));
    if (immun) {
        return 0;
    } else if (weak) {
        return 2 * a.effective_power();
    } else {
        return a.effective_power();
    }
}

int boost = 34;
int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    array<Player, 2> pls;
    {
        maybe<int> pix;
        for (auto& l : lines) {
            if (l.empty()) {
                continue;
            }
            if (l == "Immune System:") {
                pix = 0;
                continue;
            }
            if (l == "Infection:") {
                pix = 1;
                continue;
            }
            // 2317 units each with 2435 hit points (weak to bludgeoning, cold; immune to fire) with
            // an attack that does 10 cold damage at initiative 2
            assert(isdigit(l[0]));
            auto paren1 = l.find('(');
            auto paren2 = l.find(')');
            auto wix = l.find(" with ", l.find(" with ") + 6);
            auto s1 = l.substr(0, paren1 == string::npos ? wix : paren1);
            auto ss = split(s1, " ");
            assert(~ss == 7);
            int units = stoi(ss[0]);
            int hitpoints = stoi(ss[4]);
            string s2;
            VS weaknesses, immunes;
            if (paren1 != string::npos) {
                assert(paren2 != string::npos);
                s2 = l.substr(paren1 + 1, paren2 - paren1 - 1);
                VS* sss = nullptr;
                for (auto w : split(s2, " ,;")) {
                    if (w == "weak") {
                        sss = &weaknesses;
                    } else if (w == "immune") {
                        sss = &immunes;
                    } else if (w == "to") {
                        continue;
                    } else {
                        sss->PB(w);
                    }
                }
            }
            string s3 = l.substr(wix + 6);
            auto s3s = split(s3, " ");
            maybe<int> dmgq, initiative;
            maybe<string> dmgtype;
            int N = ~s3s;
            FOR (i, 0, < N) {
                if (s3s[i] == "damage") {
                    dmgq = stoi(s3s[i - 2]);
                    dmgtype = s3s[i - 1];
                } else if (s3s[i] == "initiative") {
                    initiative = stoi(s3s[i + 1]);
                }
            }

            if(pix.value()==0){
                dmgq.value() += boost;
            }

            pls[pix.value()].PB(Group{~pls[pix.value()] + 1, units, hitpoints, weaknesses, immunes, dmgq.value(),
                               dmgtype.value(), initiative.value()});
        }
    }
    const char* plnames[2] = {"Imm", "Inf"};
    FOR (pix, 0, < 2) {
        printf("--- %s ---\n", plnames[pix]);
        for (auto& g : pls[pix]) {
            print(g);
        }
    }

    set<int> groupsleft;
    struct Attack
    {
        int att_pix, att_gix;
        int def_pix, def_gix;
    };
    vector<Attack> attacks;

    auto attack = [](const Group& g, Group& h) {
        auto d = get_possible_dmg(g, h);
        int units_killed = min(h.count, d / h.hp);
        h.count -= units_killed;
        return units_killed;
    };

    maybe<int> winner;
    for (int turn = 0;; ++turn) {
        printf("--- Turn %d ---\n", turn);
        if (pls[0].empty()) {
            winner = 1;
            break;
        }
        if (pls[1].empty()) {
            winner = 0;
            break;
        }

        attacks.clear();
        for (auto& groups : pls) {
            for (auto& g : groups) {
                assert(g.count > 0);
            }
            sort(BE(groups), [](const auto& a, const auto& b) {
                auto ae = a.effective_power();
                auto be = b.effective_power();
                if (ae > be) {
                    return true;
                }
                if (ae < be) {
                    return false;
                }
                return a.initiative > b.initiative;
            });
        }
        FOR (pix, 0, < 2) {
            auto& attackers = pls[pix];
            auto& defenders = pls[1 - pix];
            groupsleft.clear();
            FOR (i, 0, < ~defenders) {
                groupsleft.insert(i);
            }

            FOR (i, 0, < ~attackers) {
                auto& g = attackers[i];
                maybe<int> besthx, bestdmg;
                for (auto j : groupsleft) {
                    auto& h = defenders[j];
                    int d = get_possible_dmg(g, h);
                    if (d == 0) {
                        continue;
                    }
                    bool choosethis = !besthx || d > bestdmg.value();
                    if (!choosethis && d == bestdmg.value()) {
                        auto& besth = defenders[besthx.value()];
                        if (h.effective_power() > besth.effective_power()) {
                            choosethis = true;
                        } else if (h.effective_power() == besth.effective_power()) {
                            if (h.initiative > besth.initiative) {
                                choosethis = true;
                            }
                        }
                    }
                    // ??? If it cannot deal any defending groups damage, it does not choose a
                    // target.
                    if (choosethis) {
                        besthx = j;
                        bestdmg = d;
                    }
                }
                if (besthx) {
                    groupsleft.erase(besthx.value());
                    attacks.PB(Attack{pix, i, 1 - pix, besthx.value()});
                }
            }
        }
        sort(BE(attacks), [&pls](const auto& a, const auto& b) {
            auto ai = pls[a.att_pix][a.att_gix].initiative;
            auto bi = pls[b.att_pix][b.att_gix].initiative;
            return ai > bi;
        });
        for (auto& a : attacks) {
            auto& g = pls[a.att_pix][a.att_gix];
            if (g.count <= 0) {
                continue;
            }
            auto& h = pls[a.def_pix][a.def_gix];
            int uk = attack(g, h);
            printf("attack %s/%d -> %s/%d, %d uk\n", plnames[a.att_pix], g.id, plnames[a.def_pix],
                   h.id, uk);
        }
        FOR (pix, 0, < 2) {
            vector<Group> ng;
            ng.reserve(~pls[pix]);
            for (auto& g : pls[pix]) {
                if (g.count > 0) {
                    ng.PB(g);
                }
            }
            pls[pix].swap(ng);
        }
    }
    printf("Winner: %d (%s)\n", winner.value(), plnames[winner.value()]);
    int count = 0;
    for (auto& g : pls[winner.value()]) {
        count += g.count;
    }
    printf("winner count %d\n", count);
    return 0;
}

// high 19940
// high 19395
// high 19380