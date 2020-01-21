#include "common.h"

int parse_t(const string& s)
{
    assert(!s.empty() && s.back() == 'T');
    return stoi(s.substr(0, ~s - 1));
}

int parse_perc(const string& s)
{
    assert(!s.empty() && s.back() == '%');
    return stoi(s.substr(0, ~s - 1));
}

struct Node
{
    AI2 xy;
    int size, used, avail, use;
};

const int MAX_W = 38;
const int MAX_H = 28;

template <class T>
struct Grid
{
    array<T, MAX_W * MAX_H> a;
    int W, H;
    Grid(int w, int h) : W(w), H(h) {}
    T& operator()(AI2 xy)
    {
        assert_between_co(xy[0], 0, W);
        assert_between_co(xy[1], 0, H);
        return a[xy[0] + W * xy[1]];
    }
    const T& operator()(AI2 xy) const
    {
        assert_between_co(xy[0], 0, W);
        assert_between_co(xy[1], 0, H);
        return a[xy[0] + W * xy[1]];
    }
};

string calc_hash_string(AI2 data_loc, const Grid<int>& used_grid)
{
    string s = to_string(data_loc[0]) + "," + to_string(data_loc[1]) + ":";
    for (auto i : used_grid.a) {
        s += to_string(i) + ",";
    }
    return s;
}

int lb_move_empty(AI2 a, AI2 b, const Grid<int>& used_grid, const Grid<int>& size_grid)
{
    const int W = used_grid.W;
    const int H = used_grid.H;
    assert(size_grid.W == W && size_grid.H == H);
    // Lower bound to move an empty cell from a to next to b.
    vector<AI2> front, next_front;
    set<AI2> visited;
    front.PB(a);
    visited.insert(a);
    int steps = 0;
    for (;; ++steps) {
        next_front.clear();
        assert(!front.empty());
        for (const auto st : front) {
            if (st == b) {
                return steps;
            }
            for (auto dir : {AI2{-1, 0}, AI2{1, 0}, AI2{0, 1}, AI2{0, -1}}) {
                auto next = st + dir;
                if (!is_between_co(next[0], 0, W) || !is_between_co(next[1], 0, H)) {
                    continue;
                }
                if (size_grid(st) < used_grid(next)) {
                    continue;
                }
                if (contains(visited, next)) {
                    continue;
                }
                next_front.PB(next);
                visited.insert(next);
            }
        }
        next_front.swap(front);
    }
}

int calc_lower_bound_to_go(AI2 data_loc,
                           AI2 empty_loc,
                           const Grid<int>& used_grid,
                           const Grid<int>& size_grid)
{
    auto a = AI2{used_grid.W - 1, 0};
    assert(data_loc == a);
    return lb_move_empty(empty_loc, AI2{used_grid.W - 2, 0}, used_grid, size_grid);
}

struct State
{
    const AI2 data_loc;
    const AI2 empty_loc;
    const Grid<int> used_grid;
    const int steps_so_far;
    const string hash_string;
    const int lower_bound_to_go;

    State(AI2 data_loc,
          AI2 empty_loc,
          const Grid<int>& used_grid,
          int steps_so_far,
          const Grid<int>& size_grid)
        : data_loc(data_loc),
          empty_loc(empty_loc),
          used_grid(used_grid),
          steps_so_far(steps_so_far),
          hash_string(calc_hash_string(data_loc, used_grid)),
          lower_bound_to_go(calc_lower_bound_to_go(data_loc, empty_loc, used_grid, size_grid))
    {}
    int full_lower_bound() const { return steps_so_far + lower_bound_to_go; }
};

template <class T>
using UPTR = unique_ptr<T>;

void solve2b(Grid<int> used_grid, int steps_so_far, const Grid<int>& size_grid)
{
    const int W = used_grid.W;
    auto empty_loc = AI2{W - 2, 0};
    auto data_loc = AI2{W - 1, 0};
    assert(used_grid(empty_loc) == 0);
    int steps = 0;
    auto move_to_empty = [&used_grid, &size_grid, &empty_loc, &data_loc](AI2 a) {
        assert(used_grid(empty_loc) == 0);
        assert(size_grid(empty_loc) >= used_grid(a));
        assert(manhattan(empty_loc, a) == 1);
        used_grid(empty_loc) += used_grid(a);
        used_grid(a) = 0;
        if (a == data_loc) {
            data_loc = empty_loc;
        }
        empty_loc = a;
    };
    for (; data_loc != AI2{0, 0}; ++steps) {
        auto de = empty_loc - data_loc;
        if (de == AI2{-1, 0}) {
            move_to_empty(data_loc);
        } else if (de == AI2{1, 0}) {
            move_to_empty(empty_loc + AI2{0, 1});
        } else if (de == AI2{1, 1}) {
            move_to_empty(data_loc + AI2{0, 1});
        } else if (de == AI2{0, 1}) {
            move_to_empty(data_loc + AI2{-1, 1});
        } else if (de == AI2{-1, 1}) {
            move_to_empty(data_loc + AI2{-1, 0});
        } else {
            UNREACHABLE;
        }
    }
    printf("part2 %d\n", steps_so_far + steps);
    (void)used_grid;
}
int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<AI2, Node> nodes;
    RunningStat<int> xrange, yrange;
    FOR (i, 2, < ~lines) {
        auto& l = lines[i];
        auto vs = split(l, " ");
        // /dev/grid/node-x0-y0     93T   68T    25T   73%
        auto path = vs[0];
        auto s_size = vs[1];
        auto s_used = vs[2];
        auto s_avail = vs[3];
        auto s_use_perc = vs[4];
        auto size = parse_t(vs[1]);
        auto used = parse_t(vs[2]);
        auto avail = parse_t(vs[3]);
        auto use_perc = parse_perc(vs[4]);
        auto ns = split(path, "-");
        assert(~ns == 3);
        auto x = stoi(ns[1].substr(1));
        auto y = stoi(ns[2].substr(1));
        nodes[AI2{x, y}] = Node{AI2{x, y}, size, used, avail, use_perc};
        xrange.add(x);
        yrange.add(y);
    }

    printf("xrange %d %d\n", *xrange.lower, *xrange.upper);
    printf("yrange %d %d\n", *yrange.lower, *yrange.upper);

    assert(*xrange.lower == 0);
    assert(*yrange.lower == 0);
    int W = *xrange.upper + 1;
    int H = *yrange.upper + 1;
    Grid<int> size_grid(W, H);
    Grid<int> used_grid(W, H);
    size_grid.a.fill(0);
    used_grid.a.fill(0);

    vector<Node> ns;
    for (auto& kv : nodes) {
        ns.PB(kv.SND);
        size_grid(kv.first) = kv.second.size;
        used_grid(kv.first) = kv.second.used;
    }

    FOR (y, 0, < H) {
        if (y > 0) {
            FOR (x, 0, < W) {
                auto& n = nodes.at(AI2{x, y - 1});
                auto& m = nodes.at(AI2{x, y});
                if (m.used > 0 && n.avail >= m.used) {
                    printf("    ^    ");
                } else {
                    printf("         ");
                }
            }
            printf("\n");
        }
        FOR (x, 0, < W) {
            auto xy = AI2{x, y};
            int used = used_grid(xy);
            int size = size_grid(xy);
            char pre = ' ';
            char post = ' ';
            if (used > 0) {
                if (x > 0) {
                    if (nodes[AI2{x - 1, y}].avail >= used) {
                        pre = '<';
                    }
                }
                if (x + 1 < W) {
                    if (nodes[AI2{x + 1, y}].avail >= used) {
                        post = '>';
                    }
                }
            }
            printf("%c%3d/%3d%c", pre, used, size, post);
        }
        printf("\n");
        if (y + 1 < H) {
            FOR (x, 0, < W) {
                auto& n = nodes.at(AI2{x, y});
                auto& m = nodes.at(AI2{x, y + 1});
                if (n.used > 0 && m.avail >= n.used) {
                    printf("    V    ");
                } else {
                    printf("         ");
                }
            }
            printf("\n");
        }
    }

    int viable = 0;
    vector<pair<AI2, int>> movable;
    vector<AI2> unmovable;
    FOR (i, 0, < ~ns) {
        int m = 0;
        auto& nsi = ns[i];
        FOR (j, 0, < ~ns) {
            if (i == j) {
                continue;
            }
            auto& nsj = ns[j];
            if (nsi.used != 0 && nsi.used <= nsj.avail) {
                printf("xy %d-%d => xy %d-%d\n", nsi.xy[0], nsi.xy[1], nsj.xy[0], nsj.xy[1]);
                ++viable;
                ++m;
            }
        }
        if (m > 0) {
            movable.PB(make_pair(nsi.xy, m));
        } else {
            unmovable.PB(nsi.xy);
        }
    }
    printf("%d\n", viable);

    auto data_loc = AI2{W - 1, 0};
    int empty_count = 0;
    AI2 initital_empty_loc;
    for (auto& kv : nodes) {
        if (kv.second.used == 0) {
            ++empty_count;
            initital_empty_loc = kv.FST;
        }
    }
    assert(empty_count == 1);
    assert(nodes.find(data_loc) != nodes.end());
    printf("data loc: x%d y%d\n", data_loc[0], data_loc[1]);
    auto st0 = make_unique<State>(data_loc, initital_empty_loc, used_grid, 0, size_grid);

    map<int, vector<UPTR<State>>> frontier;
    unordered_map<string, State*> frontier_by_hash;
    frontier_by_hash.insert(make_pair(st0->hash_string, st0.get()));
    frontier[st0->full_lower_bound()].PB(move(st0));
    unordered_set<string> settled;

    while (!frontier.empty()) {
        auto it = frontier.begin();
        assert(!it->SND.empty());
        printf("frontier %d %d left\n", it->first, ~it->second);
        auto st = move(it->SND.back());
        it->SND.pop_back();
        frontier_by_hash.erase(st->hash_string);
        if (it->SND.empty()) {
            frontier.erase(it);
        }
        must_insert(settled, st->hash_string);
        if (st->empty_loc == AI2{W - 2, 0}) {
            printf("part2/a %d steps\n", st->steps_so_far);
            solve2b(st->used_grid, st->steps_so_far, size_grid);
            break;
        }
        // printf("empty loc %d %d\n", st->empty_loc[0], st->empty_loc[1]);
        assert(st->used_grid(st->empty_loc) == 0);
        for (auto dir : {AI2{-1, 0}, AI2{1, 0}, AI2{0, 1}, AI2{0, -1}}) {
            auto moved_from_loc = st->empty_loc + dir;
            if (!is_between_co(moved_from_loc[0], 0, W) ||
                !is_between_co(moved_from_loc[1], 0, H)) {
                continue;
            }
            auto moved_from_used = st->used_grid(moved_from_loc);
            assert(moved_from_used > 0);
            auto moved_to_loc = st->empty_loc;
            int moved_to_avail = size_grid(moved_to_loc) - st->used_grid(moved_to_loc);
            if (moved_to_avail < moved_from_used) {
                continue;
            }

            auto next_used_grid = st->used_grid;
            next_used_grid(moved_from_loc) = 0;
            next_used_grid(moved_to_loc) += moved_from_used;
            assert(next_used_grid(moved_to_loc) <= size_grid(moved_to_loc));
            auto next_st =
                make_unique<State>(moved_from_loc == st->data_loc ? moved_to_loc : st->data_loc,
                                   moved_from_loc, next_used_grid, st->steps_so_far + 1, size_grid);
            if (moved_from_loc == st->data_loc) {
                printf("data loc: %d\n", manhattan(moved_to_loc, AI2{0, 0}));
                if (moved_to_loc == AI2{0, 0}) {
                    printf("?\n");
                }
            }
            if (contains(settled, next_st->hash_string)) {
                continue;
            }
            auto hit = frontier_by_hash.find(next_st->hash_string);
            if (hit != frontier_by_hash.end()) {
                // This state already in frontier.
                if (hit->second->steps_so_far <= next_st->steps_so_far) {
                    // And it's better or equal.
                    continue;
                }
                // And it's worse.
                auto to_remove_st = hit->second;
                frontier_by_hash.erase(hit);
                auto fit = frontier.find(to_remove_st->full_lower_bound());
                assert(fit != frontier.end());
                auto& vf = fit->second;
                bool found = false;
                for (auto vit = vf.begin(); vit != vf.end(); ++vit) {
                    if (vit->get() == to_remove_st) {
                        found = true;
                        vf.erase(vit);
                        if (vf.empty()) {
                            frontier.erase(fit);
                        }
                        break;
                    }
                }
                assert(found);
            }
            frontier_by_hash[next_st->hash_string] = next_st.get();
            auto lb1 = st->full_lower_bound();
            auto lb2 = next_st->full_lower_bound();
            assert(lb1 <= lb2);
            frontier[next_st->full_lower_bound()].PB(move(next_st));
        }
    }

    return 0;
}
// paused at 3 15
