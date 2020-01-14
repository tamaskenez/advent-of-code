#include "common.h"

struct Plst
{
    int hp, damage, armor;
};

struct CDA
{
    string name;
    int cost, damage, armor;
    string to_string() const
    {
        return name + " " + std::to_string(cost) + " " + std::to_string(damage) + " " +
               std::to_string(armor);
    }
};

auto st_player0 = Plst{100, 0, 0};
auto st_boss0 = Plst{103, 9, 2};

bool does_player_win(Plst player, Plst boss)
{
    int pld = max(1, player.damage - boss.armor);
    int bd = max(1, boss.damage - player.armor);
    for (;;) {
        boss.hp -= pld;
        if (boss.hp <= 0) {
            return true;
        }
        player.hp -= bd;
        if (player.hp <= 0) {
            return false;
        }
    }
}

CDA cda_from_line(const string& l)
{
    auto vs = split(l, " ");
    assert(~vs == 4);
    return CDA{vs[0], stoi(vs[1]), stoi(vs[2]), stoi(vs[3])};
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d21_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<CDA> weapons(5), armors(5), rings(6);
    assert(~lines == 16);
    FOR (i, 0, < 5) {
        weapons[i] = cda_from_line(lines[i]);
    }
    FOR (i, 0, < 5) {
        armors[i] = cda_from_line(lines[5 + i]);
    }
    FOR (i, 0, < 6) {
        rings[i] = cda_from_line(lines[10 + i]);
    }

    printf("-- Weapons\n");
    for (auto& cda : weapons) {
        printf("%s\n", cda.to_string().c_str());
    }
    printf("-- Armors\n");
    for (auto& cda : armors) {
        printf("%s\n", cda.to_string().c_str());
    }
    printf("-- Rings\n");
    for (auto& cda : rings) {
        printf("%s\n", cda.to_string().c_str());
    }
    printf("\n");

    int best_gold = INT_MAX;
    int worst_gold = INT_MIN;
    struct WL
    {
        int wins = 0;
        int loses = 0;
    };
    map<int, WL> wls;
    FOR (weapon, 0, < ~weapons) {
        FOR (armor, -1, < ~armors) {
            FOR (ring1, -1, < ~rings) {
                FOR (ring2, -1, < ~rings) {
                    if (ring1 >= 0 && ring2 >= 0 && ring1 == ring2) {
                        continue;
                    }
                    int gold = 0;
                    auto player = st_player0;
                    if (weapon >= 0) {
                        auto w = weapons[weapon];
                        player.damage += w.damage;
                        gold += w.cost;
                    }
                    if (armor >= 0) {
                        auto a = armors[armor];
                        player.armor += a.armor;
                        gold += a.cost;
                    }
                    if (ring1 >= 0) {
                        auto r = rings[ring1];
                        player.armor += r.armor;
                        player.damage += r.damage;
                        gold += r.cost;
                    }
                    if (ring2 >= 0) {
                        auto r = rings[ring2];
                        player.armor += r.armor;
                        player.damage += r.damage;
                        gold += r.cost;
                    }
                    bool player_wins = does_player_win(player, st_boss0);
                    if (player_wins) {
                        ++wls[gold].wins;
                    } else {
                        ++wls[gold].loses;
                    }
                    if (gold < best_gold && player_wins) {
                        best_gold = gold;
                    }
                    if (gold > worst_gold && !player_wins) {
                        worst_gold = gold;
                    }
                }
            }
        }
    }
    printf("%d\n", best_gold);
    printf("%d\n", worst_gold);
    if (0) {
        for (auto& kv : wls) {
            auto wl = kv.second;
            if (wl.loses == 0) {
                printf("%d: WINS\n", kv.first);
            } else if (wl.wins == 0) {
                printf("%d: LOSES\n", kv.first);
            } else {
                printf("%d: MIXED %d-%d\n", kv.first, wl.wins, wl.loses);
            }
        }
    }
    return 0;
}

// 21 33
// 202
// not 175
// not 182
