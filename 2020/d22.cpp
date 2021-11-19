#include "common.h"

struct Player
{
    deque<int> deck;
};
using Players = array<Player, 2>;
// front is top
// back is bottom

// Returns done.
bool make_one_turn(Players& players)
{
    assert(!players[0].deck.empty() && !players[1].deck.empty());
    array<int, 2> cards;
    FOR (i, 0, < 2) {
        cards[i] = players[i].deck.front();
        players[i].deck.pop_front();
    }
    assert(cards[0] != cards[1]);
    auto wix = cards[0] > cards[1] ? 0 : 1;
    auto& wp = players[wix];
    wp.deck.push_back(cards[wix]);
    wp.deck.push_back(cards[1 - wix]);
    return players[1 - wix].deck.empty();
}

int64_t deck_value(const deque<int>& deck)
{
    int64_t s = 0;
    FOR (i, 1, <= ~deck) {
        int ix = ~deck - i;
        s += (int64_t)deck[ix] * i;
    }
    return s;
}

struct Decks
{
    vector<char> deck1, deck2;
    bool operator==(const Decks& y) const { return deck1 == y.deck1 && deck2 == y.deck2; }
    bool operator<(const Decks& y) const
    {
        if (deck1 < y.deck1) {
            return true;
        }
        if (deck1 > y.deck1) {
            return false;
        }
        return deck2 < y.deck2;
    }
};

namespace std {
template <>
struct hash<::Decks>
{
    std::size_t operator()(const ::Decks& x) const noexcept
    {
        auto h = hash_range(BE(x.deck1));
        hash_range(h, BE(x.deck2));
        return h;
    }
};
}  // namespace std

void P1(Players players)
{
    int turn = 0;
    for (;;) {
        bool done = make_one_turn(players);
        ++turn;
        if (done) {
            break;
        }
    }
    auto wix = players[0].deck.empty() ? 1 : 0;
    assert(!players[wix].deck.empty());
    auto value = deck_value(players[wix].deck);
    printf("turns: %d, value: %lld\n", turn, value);
}

Decks decks_from_players(const Players& players)
{
    Decks new_pd;
    new_pd.deck1 = vector<char>(BE(players[0].deck));
    new_pd.deck2 = vector<char>(BE(players[1].deck));
    return new_pd;
}

int recursive_game(Players players, int depth);

// Returns winner idx 0 or 1
optional<int> make_one_turn(Players& players, unordered_set<Decks>& previous_decks, int depth)
{
    assert(!players[0].deck.empty() && !players[1].deck.empty());

    array<int, 2> cards;
    bool both_have_at_least_as_many_left_as_what_they_pulled = true;
    FOR (i, 0, < 2) {
        cards[i] = players[i].deck.front();
        players[i].deck.pop_front();
        int remaining = ~players[i].deck;
        if (remaining < cards[i]) {
            both_have_at_least_as_many_left_as_what_they_pulled = false;
        }
    }
    assert(cards[0] != cards[1]);

    int wix;
    if (both_have_at_least_as_many_left_as_what_they_pulled) {
        // new rec combat
        Players players_copy;
        FOR (i, 0, < 2) {
            players_copy[i].deck =
                deque<int>(players[i].deck.begin(), players[i].deck.begin() + cards[i]);
        }
        wix = recursive_game(players_copy, depth + 1);
    } else {
        wix = cards[0] > cards[1] ? 0 : 1;
    }

    auto& wp = players[wix];
    wp.deck.push_back(cards[wix]);
    wp.deck.push_back(cards[1 - wix]);
    auto new_pd = decks_from_players(players);
    bool was_there = !previous_decks.insert(new_pd).second;
    if (players[1 - wix].deck.empty()) {
        return wix;
    } else {
        if (was_there) {
            return 0;  // Player 0 would win in the next round.
        }
        return nullopt;
    }
}

unordered_map<Decks, int> winner_for_starting_deck;

// Return winner
int recursive_game(Players players, int depth)
{
    auto starting_decks = decks_from_players(players);
    auto it = winner_for_starting_deck.find(starting_decks);
    if (it != winner_for_starting_deck.end()) {
        return it->second;
    }
    unordered_set<Decks> previous_decks;
    int turn = 0;

    optional<int> winner;
    for (;;) {
        winner = make_one_turn(players, previous_decks, depth);
        ++turn;
        if (winner) {
            winner_for_starting_deck[starting_decks] = *winner;
            printf("Depth %d won in %d turns\n", depth, turn);
            return *winner;
        }
    }
}

void P2(Players players)
{
    unordered_set<Decks> previous_decks;
    int turn = 0;

    optional<int> winner;
    for (;;) {
        winner = make_one_turn(players, previous_decks, 0);
        ++turn;
        if (winner) {
            break;
        }
    }
    auto wix = winner.value();
    assert(!players[wix].deck.empty());
    auto value = deck_value(players[wix].deck);
    printf("winner: player#%d, value: %lld\n", wix + 1, value);
    printf("turns: %d, value: %lld\n", turn, value);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    Players players;
    Player* player = nullptr;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        if (l == "Player 1:") {
            player = &players[0];
            continue;
        } else if (l == "Player 2:") {
            player = &players[1];
            continue;
        }
        int card = atoi(l.c_str());
        assert(player);
        player->deck.push_back(card);
    }

    // P1(players);
    P2(players);
    return 0;
}

// P1: 17:05
