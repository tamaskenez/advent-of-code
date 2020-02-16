#include "common.h"

using Map = map<AI2, set<AI2>>;

maybe<int> try_get_dirix(char ch)
{
    const char* nsew = "NSEW";
    auto p = strchr(nsew, ch);
    if (p) {
        return p - nsew;
    }
    return {};
}

struct Straight
{
    VI dirs;
    int nextp;
};

Straight parse_straight(const string& rx, int p)
{
    VI dirs;
    for (;; ++p) {
        auto mdx = try_get_dirix(rx[p]);
        if (!mdx) {
            break;
        }
        dirs.PB(*mdx);
    }
    return Straight{move(dirs), p};
}

array<AI2, 4> NSEW_DIRS = {
    AI2{0, 1},
    AI2{0, -1},
    AI2{1, 0},
    AI2{-1, 0},
};

AI2 play_into_map(const VI& dirs, AI2 xy, Map& mp)
{
    for (auto& d : dirs) {
        auto nextxy = xy + NSEW_DIRS[d];
        mp[xy].insert(nextxy);
        mp[nextxy].insert(xy);
        xy = nextxy;
    }
    return xy;
}

struct ParseResult2
{
    vector<AI2> ends;
    int nextp;
};

ParseResult2 parse_branches(Map& mp, AI2 start, const string& rx, int p);

ParseResult2 parse_branch(Map& mp, AI2 startxy, const string& rx, int p)
{
    vector<AI2> xys(1, startxy);
    for (;;) {
        auto ch = rx[p];
        if (ch == '|' || ch == ')' || ch == '$') {
            return ParseResult2{xys, p};
        }
        if (ch == '(') {
            assert(~xys == 1);
            auto pr = parse_branches(mp, xys[0], rx, p + 1);
            p = pr.nextp;
            xys = pr.ends;
            assert(rx[p] == ')');
            ++p;
            continue;
        }
        assert(try_get_dirix(ch));
        auto ps = parse_straight(rx, p);
        assert(p < ps.nextp);
        p = ps.nextp;
        assert(~xys == 1);
        xys = {play_into_map(ps.dirs, xys[0], mp)};
    }
}

ParseResult2 parse_branches(Map& mp, AI2 start, const string& rx, int p)
{
    vector<AI2> ends;
    for (;;) {
        auto ch = rx[p];
        if (ch == '$' || ch == ')') {
            break;
        }
        auto pb = parse_branch(mp, start, rx, p);
        ends.insert(ends.end(), BE(pb.ends));
        p = pb.nextp;
        if (rx[p] == '|') {
            ++p;
            continue;
        }
    }
    if (ends.empty()) {
        return ParseResult2{vector<AI2>(1, start), p};
    } else {
        sort_unique_trunc(ends);
        return ParseResult2{move(ends), p};
    }
}

`Map parse_into_map(const string& rx)
{
    assert(!rx.empty() && rx[0] == '^' && rx.back() == '$');

    Map mp;
    auto pr = parse_branches(mp, AI2{0, 0}, rx, 1);
    assert(pr.nextp == ~rx - 1);
    return mp;
}

void print(const Map& mp)
{
    set<AI2> rooms;
    for (auto& kv : mp) {
        auto& [from, to] = kv;
        rooms.insert(from);
        for (auto r : to) {
            rooms.insert(r);
        }
    }
    RunningStat<int> rx, ry;
    for (auto r : rooms) {
        rx.add(r[0]);
        ry.add(r[1]);
    }
    FORBACK (y, *ry.upper, >= *ry.lower) {
        FOR (x, *rx.lower, <= *rx.upper) {
            if (contains(mp.at(AI2{x, y}), AI2{x, y + 1})) {
                printf("#-");
            } else {
                printf("##");
            }
        }
        printf("#\n");
        FOR (x, *rx.lower, <= *rx.upper) {
            char rch = x == 0 && y == 0 ? 'X' : '.';
            if (contains(mp.at(AI2{x, y}), AI2{x - 1, y})) {
                printf("|%c", rch);
            } else {
                printf("#%c", rch);
            }
        }
        printf("#\n");
    }
    FOR (x, *rx.lower, <= *rx.upper) {
        printf("##");
    }
    printf("#\n");
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto mp = parse_into_map(lines[0]);
    print(mp);
    map<AI2, int> toreach;
    toreach.insert(MKP(AI2{0, 0}, 0));
    vector<AI2> work, nextwork;
    work.PB(AI2{0, 0});
    RunningStat<int> steps;
    int count = 0;
    while (!work.empty()) {
        nextwork.clear();
        for (auto w : work) {
            auto s = toreach.at(w);
            for (auto nw : mp[w]) {
                if (!contains(toreach, nw)) {
                    toreach[nw] = s + 1;
                    steps.add(s + 1);
                    if (s + 1 >= 1000) {
                        ++count;
                    }
                    nextwork.PB(nw);
                }
            }
        }
        nextwork.swap(work);
    }
    printf("max steps: %d\n", *steps.upper);
    printf("count %d\n", count);
    return 0;
}
