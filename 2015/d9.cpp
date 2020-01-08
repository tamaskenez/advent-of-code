#include "common.h"

int calc_len(const VI& ps, const map<pair<string, string>, int>& ds, const VS& locs)
{
    VI dists;
    dists.reserve(~ps);
    FOR (i, 0, < ~ps) {
        auto vi = ps[i];
        auto vj = ps[(i + 1) % ~ps];
        auto it = ds.find(make_pair(locs[vi], locs[vj]));
        if (it == ds.end()) {
            return INT_MAX;
        }
        dists.PB(it->second);
    }
    return accumulate(BE(dists), 0) - *max_element(BE(dists));
}

int calc_len2(const VI& ps, const map<pair<string, string>, int>& ds, const VS& locs)
{
    VI dists;
    dists.reserve(~ps);
    FOR (i, 0, < ~ps) {
        auto vi = ps[i];
        auto vj = ps[(i + 1) % ~ps];
        auto it = ds.find(make_pair(locs[vi], locs[vj]));
        if (it == ds.end()) {
            return INT_MAX;
        }
        dists.PB(it->second);
    }
    return accumulate(BE(dists), 0) - *min_element(BE(dists));
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d9_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<pair<string, string>, int> ds;
    VS locs;
    for (auto& l : lines) {
        auto xs = split(l, " ");
        assert(~xs == 5 && xs[1] == "to" && xs[3] == "=");
        auto a = xs[0];
        auto b = xs[2];
        auto c = stoi(xs[4]);
        ds[make_pair(a, b)] = c;
        ds[make_pair(b, a)] = c;
        locs.PB(a);
        locs.PB(b);
    }
    sort_unique_trunc(locs);
    VI ps;
    ps.resize(~locs);
    iota(BE(ps), 0);

    int best_len = INT_MAX;
    do {
        int len = calc_len(ps, ds, locs);
        if (len < best_len) {
            best_len = len;
        }
    } while (std::next_permutation(BE(ps)));

    printf("part1 %d\n", best_len);

    int worst_len = INT_MIN;
    do {
        int len = calc_len2(ps, ds, locs);
        if (len > worst_len) {
            worst_len = len;
        }
    } while (std::next_permutation(BE(ps)));

    printf("part2 %d\n", worst_len);
    return 0;
}

// not 216

//19:35
