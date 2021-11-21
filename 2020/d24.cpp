#include "common.h"

enum HDir
{
    e,
    se,
    sw,
    w,
    nw,
    ne
};

using HPos = array<int, 2>;  // row column like matrix

HPos one_step(HPos pos, HDir hd)
{
    switch (hd) {
        case e:
            pos[1] += 2;
            break;
        case se:
            pos[0]++;
            pos[1]++;
            break;
        case sw:
            pos[0]++;
            pos[1]--;
            break;
        case w:
            pos[1] -= 2;
            break;
        case nw:
            pos[0]--;
            pos[1]--;
            break;
        case ne:
            pos[0]--;
            pos[1]++;
            break;
    }
    return pos;
}

HPos follow_path(const vector<HDir>& path)
{
    HPos pos{0, 0};
    for (auto& hd : path) {
        pos = one_step(pos, hd);
    }
    return pos;
}

array<HPos, 6> generate_nbs(HPos p)
{
    int i = 0;
    array<HPos, 6> r;
    for (auto hd : {HDir::e, HDir::se, HDir::sw, HDir::w, HDir::nw, HDir::ne}) {
        r[i++] = one_step(p, hd);
    }
    return r;
}

set<HPos> generate_white_tiles(const set<HPos>& black_tiles)
{
    set<HPos> white_tiles;
    for (auto hp : black_tiles) {
        auto nbs = generate_nbs(hp);
        for (auto nb : nbs) {
            if (black_tiles.count(nb) == 0) {
                white_tiles.insert(nb);
            }
        }
    }
    return white_tiles;
}

int black_nbs_count(const map<HPos, bool>& tiles, HPos pos)
{
    int r = 0;
    for (auto nb : generate_nbs(pos)) {
        auto it = tiles.find(nb);
        if (it != tiles.end() && it->second) {
            r++;
        }
    }
    return r;
}

// true = black
void P2(const set<HPos>& black_tiles)
{
    map<HPos, bool> tiles;
    for (auto t : black_tiles) {
        tiles[t] = true;
    }
    for (auto t : generate_white_tiles(black_tiles)) {
        tiles[t] = false;
    }
    vector<HPos> to_turn;
    FOR (s, 0, < 100) {
        to_turn.clear();
        for (auto [pos, black] : tiles) {
            auto bnbs = black_nbs_count(tiles, pos);
            if (black) {
                if (bnbs == 0 || bnbs > 2) {
                    to_turn.PB(pos);
                }
            } else {
                if (bnbs == 2) {
                    to_turn.PB(pos);
                }
            }
        }
        for (auto pos : to_turn) {
            auto it = tiles.find(pos);
            bool black = it->second;
            it->second = !black;
            if (!black) {
                for (auto nb : generate_nbs(pos)) {
                    if (tiles.count(nb) == 0) {
                        tiles[nb] = false;
                    }
                }
            }
        }
    }
    int count = 0;
    for (auto [pos, black] : tiles) {
        if (black) {
            count++;
        }
    }
    printf("P2: %d\n", count);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<vector<HDir>> paths;
    for (auto l : lines) {
        l = trim(l);
        vector<HDir> hdirs;
        for (int i = 0; i < ~l; ++i) {
            auto d = l.substr(i, 2);
            HDir hd;
            if (d == "se") {
                hd = HDir::se;
                ++i;
            } else if (d == "sw") {
                hd = HDir::sw;
                ++i;
            } else if (d == "nw") {
                hd = HDir::nw;
                ++i;
            } else if (d == "ne") {
                hd = HDir::ne;
                ++i;
            } else if (d[0] == 'e') {
                hd = HDir::e;
            } else if (d[0] == 'w') {
                hd = HDir::w;
            } else {
                assert(false);
            }
            hdirs.push_back(hd);
        }
        paths.PB(hdirs);
    }
    set<HPos> black_tiles;
    HPos ref{0, 0};
    for (auto& p : paths) {
        auto target = follow_path(p);
        if (black_tiles.count(target) == 0) {
            black_tiles.insert(target);
        } else {
            black_tiles.erase(target);
        }
    }
    printf("P1: %d\n", ~black_tiles);
    P2(black_tiles);
    return 0;
}

// 16:38
