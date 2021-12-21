#include "common.h"

struct Game
{
    array<int, 2> players;
    int next_player = 0;
    int next_dice = 1;
    array<int, 2> scores = {0, 0};
    int roll_count = 0;

    int roll()
    {
        int r = next_dice++;
        ++roll_count;
        if (next_dice == 101) {
            next_dice = 1;
        }
        return r;
    }
    void step()
    {
        int s = roll() + roll() + roll();
        auto& p = players[next_player];
        p = ((p - 1 + s) % 10) + 1;
        auto& score = scores[next_player];
        score += p;
        next_player = 1 - next_player;
    }
};

void P1(int pl1, int pl2)
{
    Game game;
    game.players[0] = pl1;
    game.players[1] = pl2;
    for (;;) {
        game.step();
        optional<int> winner;
        if (game.scores[0] >= 1000) {
            winner = 0;
        } else if (game.scores[1] >= 1000) {
            winner = 1;
        }
        if (winner) {
            printf("P1: %d\n", game.scores[1 - *winner] * game.roll_count);
            break;
        }
    }
}

struct G
{
    int cell;
    int steps_left;
    int score_to_get;
    bool operator<(const G& y) const
    {
        return AI3{cell, steps_left, score_to_get} < AI3{y.cell, y.steps_left, y.score_to_get};
    }
};

struct H
{
    int cell;
    int steps_left;
    int score_to_get_less;
    bool operator<(const H& y) const
    {
        return AI3{cell, steps_left, score_to_get_less} <
               AI3{y.cell, y.steps_left, y.score_to_get_less};
    }
};

vector<pair<int, int>> outcomes = {{1, 3}, {3, 4}, {6, 5}, {7, 6}, {6, 7}, {3, 8}, {1, 9}};

map<G, int64_t> cache;
map<H, int64_t> cacheb;

int64_t how_many_times_wins(G g)
{
    assert(g.steps_left >= 0);
    if (g.steps_left == 0) {
        return g.score_to_get <= 0 ? 1 : 0;
    }
    assert(g.steps_left > 0);
    if (g.score_to_get <= 0) {
        return 0;
    }

    auto it = cache.find(g);
    if (it != cache.end()) {
        return it->second;
    }

    int64_t result_count = 0;
    for (auto [times, die] : outcomes) {
        auto new_cell = ((g.cell - 1 + die) % 10) + 1;
        result_count +=
            times * how_many_times_wins(G{new_cell, g.steps_left - 1, g.score_to_get - new_cell});
    }
    cache[g] = result_count;
    return result_count;
}

int64_t how_many_times_loses(H g)
{
    assert(g.steps_left >= 0);
    if (g.score_to_get_less <= 0) {
        return 0;
    }
    assert(g.score_to_get_less > 0);
    if (g.steps_left == 0) {
        return 1;
    }

    auto it = cacheb.find(g);
    if (it != cacheb.end()) {
        return it->second;
    }
    assert(g.steps_left > 0);
    int64_t result_count = 0;
    for (auto [times, die] : outcomes) {
        auto new_cell = ((g.cell - 1 + die) % 10) + 1;
        result_count += times * how_many_times_loses(
                                    H{new_cell, g.steps_left - 1, g.score_to_get_less - new_cell});
    }
    cacheb[g] = result_count;
    return result_count;
}

map<AI4, tuple<int64_t, int64_t>> cachec;
tuple<int64_t, int64_t> number_of_wins_for_both(int pos1, int pos2, int score1, int score2)
{
    auto key = AI4{pos1, pos2, score1, score2};
    auto it = cachec.find(key);
    if (it != cachec.end()) {
        return it->second;
    }
    tuple<int64_t, int64_t> wins;
    for (auto [times, die] : outcomes) {
        auto new_pos1 = (pos1 - 1 + die) % 10 + 1;
        auto new_score1 = score1 + new_pos1;
        if (new_score1 >= 21) {
            get<0>(wins) += times;
            continue;
        }
        auto reverse_wins = number_of_wins_for_both(pos2, new_pos1, score2, new_score1);
        get<0>(wins) += times * get<1>(reverse_wins);
        get<1>(wins) += times * get<0>(reverse_wins);
    }
    cachec[key] = wins;
    return wins;
}

int main()
{
    // P1(4, 8);
    P1(2, 1);

    // starting at 1, in 1 step reach 21 how many possible way?
    auto p1_starts_at = 2;
    auto p2_starts_at = 1;
    int64_t p1_wins = 0;
    int64_t p2_wins = 0;
    auto winner_score = 21;
    for (int p1_wins_in_steps = 1; p1_wins_in_steps <= 10; ++p1_wins_in_steps) {
        auto player1_wins_this_many_times =
            how_many_times_wins(G{p1_starts_at, p1_wins_in_steps, winner_score});
        auto player2_loses_this_many_times =
            how_many_times_loses(H{p2_starts_at, p1_wins_in_steps - 1, winner_score});
        p1_wins += player1_wins_this_many_times * player2_loses_this_many_times;
    }
    for (int p2_wins_in_steps = 1; p2_wins_in_steps <= 10; ++p2_wins_in_steps) {
        auto player1_loses_this_many_times =
            how_many_times_loses(H{p1_starts_at, p2_wins_in_steps, winner_score});
        auto player2_wins_this_many_times =
            how_many_times_wins(G{p2_starts_at, p2_wins_in_steps, winner_score});
        p2_wins += player2_wins_this_many_times * player1_loses_this_many_times;
    }
    printf("player 1 wins: %lld\nplayer 2 wins: %lld\n", p1_wins, p2_wins);
    printf("P2: %lld\n", std::max(p1_wins, p2_wins));

    auto [a, b] = number_of_wins_for_both(2, 1, 0, 0);
    printf("player 1 wins: %lld\nplayer 2 wins: %lld\n", a, b);
    printf("P2: %lld\n", std::max(a, b));

    return 0;
}

// high 444356092776317
