#include "common.h"

const int GAP = 3;   // attack power
const int EAP = 13;  // attack power

struct Player
{
    char avatar;
    AI2 rc;
    int hp = 200;  // hit points
    bool operator<(const Player& b) const { return rc < b.rc; }
};

void remove_dead_players(vector<Player>& players)
{
    vector<Player> n;
    n.reserve(~players);
    for (auto& p : players) {
        if (p.hp > 0) {
            n.PB(p);
        }
    }
    players.swap(n);
}

VI get_enemies_next_to_this(const vector<Player>& ps, AI2 rc, char avatar)
{
    VI r;
    FOR (i, 0, < ~ps) {
        auto& p = ps[i];
        if (p.rc == rc || p.avatar == avatar || p.hp <= 0) {
            continue;
        }
        if (manhattan(p.rc, rc) == 1) {
            r.PB(i);
        }
    }
    return r;
}

char batc(const VS& board, AI2 rc)
{
    auto [r, c] = rc;
    if (r < 0 || c < 0) {
        return ' ';
    }
    if (r >= ~board) {
        return ' ';
    }
    auto& row = board[r];
    if (c >= ~row) {
        return ' ';
    }
    return row[c];
}

char& batm(VS& board, AI2 rc)
{
    auto [r, c] = rc;
    assert(r >= 0 && c >= 0 && r < ~board);
    auto& row = board[r];
    assert(c < ~row);
    return row[c];
}

auto SORTED_DIRS = DIRS4;

vector<AI2> get_empty_squares_next_to_these(const VS& board, const vector<Player>& ps, char avatar)
{
    vector<AI2> result;
    for (auto& p : ps) {
        if (p.avatar != avatar || p.hp <= 0) {
            continue;
        }
        for (auto dir : SORTED_DIRS) {
            auto rc = p.rc + dir;
            auto mch = batc(board, rc);
            if (mch == '.') {
                result.PB(rc);
            }
        }
    }
    return result;
}

struct TargetFirstStep
{
    AI2 target;
    AI2 first_step;
};

maybe<TargetFirstStep> get_first_target_and_first_step(const VS& board, AI2 prc, char pavatar)
{
    const AI2 NO_FIRST_STEP{INT_MIN, INT_MIN};
    map<AI2, AI2> visited = {{prc, NO_FIRST_STEP}};  // visited and first step
    vector<AI2> front = {prc};
    vector<AI2> next_front;
    for (;;) {
        next_front.clear();
        if (front.empty()) {
            return {};
        }
        for (auto q : front) {
            for (auto d : SORTED_DIRS) {
                auto nrc = q + d;
                if (contains(visited, nrc)) {
                    continue;
                }
                auto ch = batc(board, nrc);
                if (ch != '.') {
                    continue;
                }
                auto first_step = prc == q ? nrc : visited.at(q);
                assert(first_step != NO_FIRST_STEP);
                visited.insert(make_pair(nrc, first_step));
                next_front.PB(nrc);
            }
        }
        sort(BE(next_front));
        for (auto nf : next_front) {
            for (auto d : SORTED_DIRS) {
                auto nrc = nf + d;
                auto ch = batc(board, nrc);
                if ((ch == 'G' || ch == 'E') && ch != pavatar) {
                    return TargetFirstStep{nf, visited.at(nf)};
                }
            }
        }
        next_front.swap(front);
    }
}

void print(const VS& board)
{
    for (auto& r : board) {
        printf("%s\n", r.c_str());
    }
    printf("\n");
}

int main()
{
    sort(BE(SORTED_DIRS));
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d15_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    const int H = ~lines;
    RunningStat<int> w;
    for (auto& l : lines) {
        w.add(~l);
    }
    const int W = *w.upper;
    auto board = lines;
    printf("%d %d\n", H, W);

    vector<Player> players;
    FOR (rix, 0, < H) {
        FOR (cix, 0, < W) {
            auto ch = board[rix][cix];
            switch (ch) {
                case '#':
                case '.':
                    break;
                case 'G':
                    players.PB(Player{'G', AI2{rix, cix}});
                    break;
                case 'E':
                    players.PB(Player{'E', AI2{rix, cix}});
                    break;
                default:
                    UNREACHABLE;
            }
        }
    }

    int turn = 0;
    print(board);
    for (;; ++turn) {
        sort(BE(players));
        bool found_targets = false;
        for (auto& p : players) {
            if (p.hp <= 0) {
                continue;
            }
            auto ve = get_enemies_next_to_this(players, p.rc, p.avatar);
            if (ve.empty()) {
                // no enemies in range
                // look for target
                auto mtfs = get_first_target_and_first_step(board, p.rc, p.avatar);
                if (!mtfs) {
                    // no target, skip
                    continue;
                }
                found_targets = true;
                // auto target = mtfs->target;
                auto first_step = mtfs->first_step;
                // move to first_step;
                auto& fromch = batm(board, p.rc);
                assert(fromch == p.avatar);
                fromch = '.';
                auto& toch = batm(board, first_step);
                assert(toch == '.');
                toch = p.avatar;
                p.rc = first_step;
                ve = get_enemies_next_to_this(players, p.rc, p.avatar);
            }
            if (ve.empty()) {
                // no enemies around
                continue;
            }
            found_targets = true;
            sort(BE(ve), [&players](int a, int b) {
                auto& pa = players[a];
                auto& pb = players[b];
                if (pa.hp < pb.hp) {
                    return true;
                }
                if (pa.hp > pb.hp) {
                    return false;
                }
                return pa.rc < pb.rc;
            });
            auto& enemy = players[ve[0]];
            assert(enemy.avatar != p.avatar);
            enemy.hp -= p.avatar == 'G' ? GAP : EAP;
            if (enemy.hp <= 0) {
                if (enemy.avatar == 'E') {
                    printf("not good\n");
                    exit(-1);
                }
                auto& ch = batm(board, enemy.rc);
                assert(ch == enemy.avatar);
                ch = '.';
            }
        }
        remove_dead_players(players);
        if (!found_targets) {
            printf("End of game\n");
            int shp = 0;
            for (auto& p : players) {
                printf("'%c' hp %d, (%d %d)\n", p.avatar, p.hp, p.rc[0], p.rc[1]);
                shp += p.hp;
            }
            print(board);
            printf("turns %d shp %d, product %d\n", turn, shp, turn * shp);
            printf("one less turns product %d\n", (turn - 1) * shp);
            break;
        }
        print(board);
    }
    return 0;
}

// high 230867