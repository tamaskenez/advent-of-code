#include "common.h"

vector<AI2> get_nbs(AI2 rc, AI2 wh)
{
    vector<AI2> result;
    auto [r, c] = rc;
    for (auto xy : {AI2{r + 1, c}, AI2{r - 1, c}, AI2{r, c + 1}, AI2{r, c - 1}}) {
        if (0 <= xy[0] && xy[0] < wh[0] && 0 <= xy[1] && xy[1] < wh[1]) {
            result.PB(xy);
        }
    }
    return result;
}

void P1(const VS& lines)
{
    VS cave = lines;
    auto H = ~lines;
    auto W = ~(lines[0]);
    AI2 wh{H, W};
    int64_t risk = 0;
    FOR (r, 0, < H) {
        FOR (c, 0, < W) {
            auto h = cave[r][c];
            bool ok = true;
            auto nbs = get_nbs(AI2{r, c}, wh);
            for (auto nb : nbs) {
                if (cave[nb[0]][nb[1]] <= h) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                auto hh = (int)(h - '0');
                risk += 1 + hh;
            }
        }
    }
    printf("P1: %lld\n", risk);
}

void P2(const VS& lines)
{
    VS cave = lines;
    auto H = ~lines;
    auto W = ~(lines[0]);
    AI2 wh{H, W};
    set<AI2> togo;
    set<AI2> done;
    FOR (r, 0, < H) {
        FOR (c, 0, < W) {
            if (cave[r][c] != '9') {
                togo.insert(AI2{r, c});
            }
        }
    }
    VI basin_sizes;
    while (!togo.empty()) {
        auto rc = *togo.begin();
        togo.erase(togo.begin());
        set<AI2> togo2 = {rc};
        int basin_size = 0;
        while (!togo2.empty()) {
            auto rc = *togo2.begin();
            togo2.erase(togo2.begin());
            ++basin_size;
            auto nbs = get_nbs(rc, wh);
            for (auto nb : nbs) {
                if (togo.count(nb) > 0) {
                    togo.erase(nb);
                    togo2.insert(nb);
                }
            }
        }
        basin_sizes.PB(basin_size);
    }
    sort(BE(basin_sizes));
    reverse(BE(basin_sizes));
    auto p2 = (int64_t)basin_sizes[0] * basin_sizes[1] * basin_sizes[2];
    printf("P2:%lld\n", p2);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d09_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    P1(lines);
    P2(lines);
    return 0;
}
