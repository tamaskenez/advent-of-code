#include "common.h"

// boss no armor
// damage min 1

enum Spell
{
    MagicMissile,
    Drain,
    Shield,
    Poison,
    Recharge
};
const int NUM_SPELLS = 5;

struct Boss
{
    int hp = 51;
    int damage = 9;
    void print() const { printf("Boss has %d hit points\n", hp); }
};

struct Player
{
    int hp = 50;
    int mana = 500;
    int shield = 0;
    int poison = 0;
    int recharge = 0;
    int armor() const { return shield > 0 ? 7 : 0; }

    void print() const
    {
        printf("Player has %d hit points, %d armor, %d mana\n", hp, armor(), mana);
    }
};

enum Outcome
{
    PLAYER_WON,
    BOSS_WON,
    NOBODY_WON
};

const array<int, NUM_SPELLS> SPELL_COSTS = {53, 73, 113, 173, 229};

struct GameState
{
    Player player;
    Boss boss;
    bool part2 = false;
};

Outcome apply_effects(GameState& gs)
{
    auto& player = gs.player;
    auto& boss = gs.boss;

    if (player.shield > 0) {
        --player.shield;
    }

    if (player.poison > 0) {
        --player.poison;
        boss.hp -= 3;
        if (boss.hp <= 0) {
            return PLAYER_WON;
        }
    }
    if (player.recharge > 0) {
        --player.recharge;
        player.mana += 101;
    }
    return NOBODY_WON;
}

Outcome boss_turn(GameState& gs)
{
    auto oc = apply_effects(gs);
    if (oc != NOBODY_WON) {
        return oc;
    }

    auto& player = gs.player;
    auto& boss = gs.boss;

    int damage = max(1, boss.damage - player.armor());
    player.hp -= damage;
    if (player.hp <= 0) {
        return BOSS_WON;
    }
    return NOBODY_WON;
}

Outcome player_turn(GameState& gs, Spell spell)
{
    auto& player = gs.player;
    if (gs.part2) {
        --player.hp;
        if (player.hp <= 0) {
            return BOSS_WON;
        }
    }
    auto oc = apply_effects(gs);
    if (oc != NOBODY_WON) {
        return oc;
    }

    auto& boss = gs.boss;
    int spell_cost = SPELL_COSTS[spell];
    if (spell_cost > player.mana) {
        return BOSS_WON;
    }
    player.mana -= spell_cost;

    switch (spell) {
        case MagicMissile:
            boss.hp -= 4;
            if (boss.hp <= 0) {
                return PLAYER_WON;
            }
            break;
        case Drain:
            boss.hp -= 2;
            player.hp += 2;
            if (boss.hp <= 0) {
                return PLAYER_WON;
            }
            break;
        case Shield:
            if (player.shield > 0) {
                return BOSS_WON;
            }
            player.shield = 6;
            break;
        case Poison:
            if (player.poison > 0) {
                return BOSS_WON;
            }
            player.poison = 6;
            break;
        case Recharge:
            if (player.recharge > 0) {
                return BOSS_WON;
            }
            player.recharge = 5;
            break;
        default:
            assert(false);
    }
    return NOBODY_WON;
}

bool print_won(Outcome oc)
{
    switch (oc) {
        case PLAYER_WON:
            printf("PLAYER WON\n");
            return true;
        case BOSS_WON:
            printf("BOSS WON\n");
            return true;
        case NOBODY_WON:
            return false;
    }
    assert(false);
}

void test_run(const vector<Spell>& spells, int boss_hp)
{
    GameState gs;
    gs.player.hp = 10;
    gs.player.mana = 250;
    gs.boss.hp = boss_hp;
    gs.boss.damage = 8;
    for (auto spell : spells) {
        printf("-- Player turn --\n");
        gs.player.print();
        gs.boss.print();
        auto oc = player_turn(gs, spell);
        if (print_won(oc)) {
            break;
        }

        printf("-- Boss turn --\n");
        gs.player.print();
        gs.boss.print();
        oc = boss_turn(gs);
        if (print_won(oc)) {
            break;
        }
    }
}

int l_count = 0;

int least_mana_to_player_win(const GameState& gs, const int mana_spent)
{
    ++l_count;
    if (l_count % 10000000 == 0) {
        printf("l_count: %d\n", l_count);
    }
    RunningStat<int> best;
    FOR (spell, 0, < NUM_SPELLS) {
        int spell_cost = SPELL_COSTS[spell];
        int new_mana_spent = mana_spent + spell_cost;
        auto gs_copy = gs;
        auto oc = player_turn(gs_copy, (Spell)spell);
        if (oc == BOSS_WON) {
            continue;
        }
        if (oc == PLAYER_WON) {
            best.add(new_mana_spent);
            continue;
        }
        assert(oc == NOBODY_WON);
        oc = boss_turn(gs_copy);
        if (oc == BOSS_WON) {
            continue;
        }
        if (oc == PLAYER_WON) {
            best.add(new_mana_spent);
            continue;
        }
        assert(oc == NOBODY_WON);
        best.add(least_mana_to_player_win(gs_copy, new_mana_spent));
    }
    if (best.lower) {
        return *best.lower;
    }
    return INT_MAX;
}

int main()
{
    if (false) {
        printf("---------------\n");
        test_run({Poison, MagicMissile}, 13);
        printf("---------------\n");
        test_run({Recharge, Shield, Drain, Poison, MagicMissile}, 14);
    }
    {
        GameState gs;
        int r = least_mana_to_player_win(gs, 0);
        printf("part1 %d\n", r);
    }
    {
        GameState gs;
        gs.part2 = true;
        int r = least_mana_to_player_win(gs, 0);
        printf("part2 %d\n", r);
    }
    return 0;
}