#include "common.h"

struct Player
{
    int hp = 0;
    int mana = 0;
};

struct Boss
{
    int hp = 0;
    int damage = 0;
};

const auto BOSS_INITIAL = Boss{51, 9};
const auto PLAYER_INITIAL = Player{50, 500};

enum Spell
{
    SPELL_MM,
    SPELL_DR,
    SPELL_SH,
    SPELL_PO,
    SPELL_RC,
    MAX_SPELL
};

const VI SPELL_COSTS = {53, 73, 113, 173, 229};

struct GameState
{
    Player player;
    Boss boss;
    array<int, MAX_SPELL> spell_timer;
    bool part2 = false;
    GameState() { spell_timer.fill(0); }
};

enum Outcome
{
    BOSS_WON,
    PLAYER_WON,
    NOBODY_WON
};

Outcome do_spells(GameState& gs)
{
    FOR (i, 0, < MAX_SPELL) {
        if (gs.spell_timer[i] > 0) {
            --gs.spell_timer[i];
            switch ((Spell)i) {
                case SPELL_SH:
                    break;
                case SPELL_PO:
                    gs.boss.hp -= 3;
                    if (gs.boss.hp <= 0) {
                        return PLAYER_WON;
                    }
                    break;
                case SPELL_RC:
                    gs.player.mana += 101;
                    break;
                case SPELL_MM:
                case SPELL_DR:
                default:
                    assert(false);
            }
        }
    }
    return NOBODY_WON;
}

Outcome player_turn(GameState& gs, Spell spell)
{
    if (gs.part2) {
        --gs.player.hp;
        if (gs.player.hp <= 0) {
            return BOSS_WON;
        }
    }
    auto oc = do_spells(gs);
    if (oc == PLAYER_WON) {
        return PLAYER_WON;
    }
    assert(oc == NOBODY_WON);

    assert(0 <= spell && spell < MAX_SPELL);
    if (gs.spell_timer[spell] > 0) {
        return BOSS_WON;
    }
    assert(gs.spell_timer[spell] == 0);
    int spell_cost = SPELL_COSTS[spell];
    assert(gs.player.mana >= spell_cost);
    gs.player.mana -= spell_cost;
    switch (spell) {
        case SPELL_MM:
            gs.boss.hp -= 4;
            if (gs.boss.hp <= 0) {
                return PLAYER_WON;
            }
            break;
        case SPELL_DR:
            gs.boss.hp -= 2;
            if (gs.boss.hp <= 0) {
                return PLAYER_WON;
            }
            gs.player.hp += 2;
            break;
        case SPELL_SH:
            gs.spell_timer[spell] = 6;
            break;
        case SPELL_PO:
            gs.spell_timer[spell] = 6;
            break;
        case SPELL_RC:
            gs.spell_timer[spell] = 5;
            break;
        default:
            assert(false);
    }
    return NOBODY_WON;
}

Outcome boss_turn(GameState& gs)
{
    auto oc = do_spells(gs);
    if (oc == PLAYER_WON) {
        return PLAYER_WON;
    }
    assert(oc == NOBODY_WON);
    int player_armor = gs.spell_timer[SPELL_SH] > 0 ? 7 : 0;
    int damage = max(1, gs.boss.damage - player_armor);
    gs.player.hp -= damage;
    if (gs.player.hp <= 0) {
        return BOSS_WON;
    }
    return NOBODY_WON;
}

Outcome simulate_steps(const VI& steps)
{
    GameState gs;
    gs.player = PLAYER_INITIAL;
    gs.boss = BOSS_INITIAL;
    FOR (i, 0, < ~steps) {
        if (gs.player.mana < SPELL_COSTS[steps[i]]) {
            return BOSS_WON;
        }
        auto oc = player_turn(gs, (Spell)steps[i]);
        if (oc != NOBODY_WON) {
            return oc;
        }
        oc = boss_turn(gs);
        if (oc != NOBODY_WON) {
            return oc;
        }
    }
    return NOBODY_WON;
}

void solve(bool part2)
{
    map<int, vector<GameState>> spent_to_gs;

    GameState gs0;
    gs0.part2 = part2;
    gs0.player = PLAYER_INITIAL;
    gs0.boss = BOSS_INITIAL;

    spent_to_gs.insert(make_pair(0, vector<GameState>{gs0}));

    set<int> winner_spendings;

    for (;;) {
        assert(~spent_to_gs.empty());
        if (!winner_spendings.empty() && *winner_spendings.begin() <= spent_to_gs.begin()->first) {
            printf("part1 %d\n", *winner_spendings.begin());
            break;
        }
        auto it = spent_to_gs.begin();
        auto& gss = it->second;
        assert(!gss.empty());
        const int spent_so_far = it->first;
        const auto gs = move(gss.back());
        gss.pop_back();
        if (gss.empty()) {
            spent_to_gs.erase(it);
        }
        // don't use gss, it from now
        FOR (spell, 0, < MAX_SPELL) {
            if (SPELL_COSTS[spell] > gs.player.mana) {
                continue;
            }
            auto gs_copy = gs;
            auto oc = player_turn(gs_copy, (Spell)spell);
            if (oc == BOSS_WON) {
                continue;
            }
            if (oc == PLAYER_WON) {
                winner_spendings.insert(spent_so_far + SPELL_COSTS[spell]);
                continue;
            }
            // Nobody won, do boss;
            oc = boss_turn(gs_copy);
            if (oc == BOSS_WON) {
                continue;
            }
            if (oc == PLAYER_WON) {
                winner_spendings.insert(spent_so_far + SPELL_COSTS[spell]);
                continue;
            }
            spent_to_gs[spent_so_far + SPELL_COSTS[spell]].push_back(gs_copy);
        }
    }
}

int main()
{
    {
        GameState gs;
        gs.player.hp = 10;
        gs.player.mana = 250;
        gs.boss.hp = 13;
        gs.boss.damage = 8;

        player_turn(gs, SPELL_PO);
        boss_turn(gs);
        player_turn(gs, SPELL_MM);
        boss_turn(gs);
    }
    {
        GameState gs;
        gs.player.hp = 10;
        gs.player.mana = 250;
        gs.boss.hp = 14;
        gs.boss.damage = 8;

        player_turn(gs, SPELL_RC);
        boss_turn(gs);
        player_turn(gs, SPELL_SH);
        boss_turn(gs);
        player_turn(gs, SPELL_DR);
        boss_turn(gs);
        player_turn(gs, SPELL_PO);
        boss_turn(gs);
        player_turn(gs, SPELL_MM);
        boss_turn(gs);
    }

    solve(false);
    solve(true);
    return 0;
}

// >671