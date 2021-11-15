#include "common.h"

constexpr int H = 10;
constexpr int W = 10;

using Bitmap = array<string, H>;
struct Img
{
    Bitmap bitmap;
};

enum Dir
{
    Top,
    Right,
    Bottom,
    Left,
};

struct CommonEdge
{
    Dir dir;
    string edge;
};

bool operator<(const CommonEdge& x, const CommonEdge& y)
{
    if (x.dir < y.dir) {
        return true;
    }
    if (x.dir > y.dir) {
        return false;
    }
    return x.edge < y.edge;
}

unordered_map<int, Img> imgs;

string getce(Dir dir, const Bitmap& bitmap)
{
    switch (dir) {
        case Top:
            return bitmap[0];
        case Bottom:
            return bitmap[H - 1];
        case Left: {
            string e;
            FOR (i, 0, < H) {
                e += bitmap[i][0];
            }
            return e;
        }
        case Right: {
            string e;
            FOR (i, 0, < H) {
                e += bitmap[i][W - 1];
            }
            return e;
        }
    }
}

Bitmap rotate(const Bitmap b)
{
    Bitmap bb = b;
    assert(H == W);
    FOR (r, 0, < H) {
        FOR (c, 0, < H) {
            bb[r][c] = b[H - 1 - c][r];
        }
    }
    return bb;
}

vector<string> rotate(const vector<string>& b)
{
    assert(!b.empty());
    int H = b.size();
    for (auto& r : b) {
        assert((int)r.size() == H);
    }
    auto bb = b;
    FOR (r, 0, < H) {
        FOR (c, 0, < H) {
            bb[r][c] = b[H - 1 - c][r];
        }
    }
    return bb;
}

optional<Dir> dir_from_tile_to_tile(AI2 from, AI2 to)
{
    if (to == AI2{from[0] - 1, from[1]}) {
        return Dir::Top;
    }
    if (to == AI2{from[0], from[1] + 1}) {
        return Dir::Right;
    }
    if (to == AI2{from[0] + 1, from[1]}) {
        return Dir::Bottom;
    }
    if (to == AI2{from[0], from[1] - 1}) {
        return Dir::Left;
    }
    return nullopt;
}

Dir opposite_dir(Dir d)
{
    switch (d) {
        case Top:
            return Dir::Bottom;
        case Right:
            return Dir::Left;
        case Bottom:
            return Dir::Top;
        case Left:
            return Dir::Right;
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    unordered_set<int> nums_to_process;
    for (int ln = 0; ln < (int)lines.size(); ++ln) {
        auto l = lines[ln];
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        assert(starts_with(l, "Tile "));
        auto numstr = l.substr(5, 4);
        auto num = atoi(numstr.c_str());
        Img img;
        FOR (i, 0, < H) {
            l = lines[++ln];
            l = trim(l);
            assert(l.size() == W);
            img.bitmap[i] = l;
        }
        imgs[num] = img;
        nums_to_process.insert(num);
    }

    AI2 tl{0, 0};
    AI2 br{0, 0};

    struct Tile
    {
        int num;
        bool vlip;
        int cwrot;
        Bitmap bitmap;
    };
    map<AI2, Tile> tiles;

    int num = *nums_to_process.begin();
    printf("first num %d\n", num);
    nums_to_process.erase(num);
    tiles[AI2{0, 0}] = Tile{num, false, 0, imgs.at(num).bitmap};
    set<AI2> tiles_to_do;
    tiles_to_do.insert(AI2{1, 0});
    tiles_to_do.insert(AI2{-1, 0});
    tiles_to_do.insert(AI2{0, 1});
    tiles_to_do.insert(AI2{0, -1});
    set<AI2> tiles_done = {AI2{0, 0}};

    while (!nums_to_process.empty()) {
        if (tiles_to_do.empty()) {
            printf("no more tiles to do\n");
            return EXIT_FAILURE;
        }
        AI2 tile = *tiles_to_do.begin();
        tiles_to_do.erase(tile);
        tiles_done.insert(tile);
        vector<AI2> nbtiles;
        for (int i : {-1, 1}) {
            nbtiles.push_back(AI2{tile[0], tile[1] + i});
            nbtiles.push_back(AI2{tile[0] + i, tile[1]});
        }
        maybe<Tile> tile_found;
        for (auto num : nums_to_process) {
            for (auto vflip : {false, true}) {
                FOR (cwrot, 0, < 4) {
                    const auto& img = imgs.at(num);
                    auto bitmap = img.bitmap;
                    if (vflip) {
                        std::reverse(BE(bitmap));
                    }
                    FOR (r, 0, < cwrot) {
                        bitmap = rotate(bitmap);
                    }
                    // Check if in place
                    bool badedge = false;
                    for (auto nbtile : nbtiles) {
                        auto it = tiles.find(nbtile);
                        if (it == tiles.end()) {
                            continue;
                        }
                        auto& nb = it->second;
                        auto& nbbitmap = nb.bitmap;
                        auto dir = dir_from_tile_to_tile(tile, nbtile);
                        assert(dir);
                        auto thisedge = getce(*dir, bitmap);
                        auto thatedge = getce(opposite_dir(*dir), nbbitmap);
                        if (thisedge != thatedge) {
                            badedge = true;
                            break;
                        }
                    }
                    if (!badedge) {
                        tile_found = Tile{num, vflip, cwrot, bitmap};
                        break;
                    }
                }
                if (tile_found) {
                    break;
                }
            }
            if (tile_found) {
                break;
            }
        }
        if (tile_found) {
            printf("found %d\n", tile_found->num);
            nums_to_process.erase(tile_found->num);
            assert(tiles.count(tile) == 0);
            tiles[tile] = *tile_found;
            vector<AI2> nbtiles;
            for (int i : {-1, 1}) {
                nbtiles.push_back(AI2{tile[0], tile[1] + i});
                nbtiles.push_back(AI2{tile[0] + i, tile[1]});
            }
            for (auto nbtile : nbtiles) {
                if (tiles_done.count(nbtile) == 0) {
                    tiles_to_do.insert(nbtile);
                }
            }
        }
    }

    for (auto& [k, v] : tiles) {
        tl[0] = std::min(tl[0], k[0]);
        tl[1] = std::min(tl[1], k[1]);
        br[0] = std::max(br[0], k[0]);
        br[1] = std::max(br[1], k[1]);
    }

    map<AI2, Tile> tiles2;
    for (auto& [k, v] : tiles) {
        auto z = k - tl;
        tiles2[z] = v;
    }
    auto hw = (br - tl) + AI2{1, 1};
    FOR (r, 0, < hw[0]) {
        FOR (c, 0, < hw[1]) {
            auto t = AI2{r, c};
            auto it = tiles2.find(t);
            if (it == tiles2.end()) {
                printf(".... ");
            } else {
                printf("%d ", it->second.num);
            }
        }
        printf("\n");
    }
    vector<string> bigimage;
    FOR (r, 0, < hw[0] * (H + 1)) {
        if (r % (H + 1) == H) {
            printf("\n");
            continue;
        }
        auto rr = r % (H + 1);
        auto R = r / (H + 1);
        string bigimagerow;
        FOR (c, 0, < hw[1] * (H + 1)) {
            auto cc = c % (H + 1);
            auto C = c / (H + 1);
            if (cc == H) {
                printf(" ");
                continue;
            }
            auto t = AI2{R, C};
            auto it = tiles2.find(t);
            if (it == tiles2.end()) {
                assert(false);
                printf(" ");
                continue;
            }
            printf("%c", it->second.bitmap[rr][cc]);
            if (cc != 0 && cc != H - 1) {
                bigimagerow += it->second.bitmap[rr][cc];
            }
        }
        if (rr != 0 && rr != H - 1) {
            bigimage.push_back(bigimagerow);
        }
        printf("\n");
    }
    FOR (r, 0, < (int)bigimage.size()) {
        printf("%s\n", bigimage[r].c_str());
    }
    array<string, 3> M;
    M[0] = "                  # ";
    M[1] = "#    ##    ##    ###";
    M[2] = " #  #  #  #  #  #   ";
    int mw = M[0].size();
    assert(mw == (int)M[1].size());
    assert(mw == (int)M[2].size());
    int mh = M.size();

    int bh = bigimage.size();
    for (bool vflip : {false, true}) {
        FOR (cwrot, 0, < 4) {
            auto bi = bigimage;
            if (vflip) {
                std::reverse(BE(bi));
            }
            FOR (i, 0, < cwrot) {
                bi = rotate(bi);
            }
            int monster_count = 0;
            set<AI2> smcoords;
            FOR (r, 0, < bh - mh) {
                FOR (c, 0, < bh - mw) {
                    bool ok = true;
                    set<AI2> this_smcoords;
                    FOR (rr, 0, < mh) {
                        FOR (cc, 0, < mw) {
                            if (M[rr][cc] != '#') {
                                continue;
                            }
                            if (bi[r + rr][c + cc] != '#') {
                                ok = false;
                                break;
                            }
                            this_smcoords.insert(AI2{r + rr, c + cc});
                        }
                        if (!ok) {
                            break;
                        }
                    }
                    if (ok) {
                        monster_count++;
                        smcoords.insert(BE(this_smcoords));
                    }
                }
            }
            printf("Monster count %d\n", monster_count);
            if (monster_count != 0) {
                int notpart = 0;
                FOR (r, 0, < bh) {
                    FOR (c, 0, < bh) {
                        char ch = bi[r][c];
                        if (ch == '#' && smcoords.count(AI2{r, c}) == 0) {
                            notpart++;
                        }
                    }
                }
                printf("Not part: %d\n", notpart);
            }
        }
    }
    return 0;
}

// P1: 1:08:12
