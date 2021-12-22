#include "common.h"

int P1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    set<AI3> s;
    for (auto l : lines) {
        bool on;
        if (starts_with(l, "on ")) {
            on = true;
            l = l.substr(3);
        } else if (starts_with(l, "off ")) {
            on = false;
            l = l.substr(4);
        } else
            assert(false);
        auto ls = split(l, "xyz=., ");
        auto lo = AI3{stoi(ls[0]), stoi(ls[2]), stoi(ls[4])};
        auto hi = AI3{stoi(ls[1]), stoi(ls[3]), stoi(ls[5])};
        bool inside = true;
        FOR (i, 0, < 3) {
            if (lo[i] < -50 || hi[i] > 50) {
                inside = false;
            }
        }
        if (!inside) {
            continue;
        }
        FOR (x, lo[0], <= hi[0]) {
            FOR (y, lo[1], <= hi[1]) {
                FOR (z, lo[2], <= hi[2]) {
                    auto p = AI3{x, y, z};
                    if (on) {
                        s.insert(p);
                    } else {
                        s.erase(p);
                    }
                }
            }
        }
    }
    printf("P1: %d\n", ~s);
    return 0;
}

struct Cube
{
    AI3 b, e;
    bool operator<(const Cube& y) const
    {
        if (b < y.b) {
            return true;
        }
        if (b > y.b) {
            return true;
        }
        return e < y.e;
    }
    bool operator==(const Cube& y) const { return b == y.b && e == y.e; }
};

bool is_disjunct(int tb, int te, int ub, int ue)
{
    assert(tb < te);
    assert(ub < ue);
    return te <= ub || ue <= tb;
}

bool is_disjunct(const Cube& t, const Cube& u)
{
    FOR (i, 0, < 3) {
        if (is_disjunct(t.b[i], t.e[i], u.b[i], u.e[i])) {
            return true;
        }
    }
    return false;
}

bool is_within(const Cube& t, const Cube& u)
{
    FOR (i, 0, < 3) {
        bool inside = u.b[i] <= t.b[i] && t.e[i] <= u.e[i];
        if (!inside) {
            return false;
        }
    }
    return true;
}

vector<Cube> split_along(const Cube& cube, const array<vector<int>, 3>& boundaries)
{
    vector<Cube> pcs = {cube};
    FOR (i, 0, < 3) {
        auto& bs = boundaries[i];
        assert(!bs.empty());
        vector<Cube> new_pcs;
        for (auto& pc : pcs) {
            if (is_disjunct(bs.front(), bs.back(), pc.b[i], pc.e[i]) ||
                (bs.front() <= pc.b[i] && pc.e[i] <= bs.back())) {
                assert(is_within(pc, cube));
                new_pcs.PB(pc);
            } else {
                auto itb = lower_bound(BE(bs), pc.b[i]);
                assert(itb != bs.end());
                auto ite = lower_bound(BE(bs), pc.e[i]);
                if (*itb != pc.b[i]) {
                    assert(*itb > pc.b[i]);
                    auto new_cube = pc;
                    new_cube.e[i] = *itb;
                    assert(is_within(new_cube, pc));
                    assert(is_within(new_cube, cube));
                    new_pcs.PB(new_cube);
                }
                for (; itb != ite; ++itb) {
                    auto new_cube = pc;
                    new_cube.b[i] = *itb;
                    auto nit = next(itb);
                    if (nit != bs.end() && *nit < new_cube.e[i]) {
                        new_cube.e[i] = *nit;
                    }
                    assert(cube.b[i] <= new_cube.b[i] && new_cube.e[i] <= cube.e[i]);
                    assert(new_cube.b[i] < new_cube.e[i]);
                    assert(is_within(new_cube, cube));
                    new_pcs.PB(new_cube);
                }
            }
        }
        pcs.swap(new_pcs);
    }
    return pcs;
}

// return new incoming cubes = incoming_cubes - cube
vector<Cube> handle_incoming_cube_on(const Cube& cube, const vector<Cube>& incoming_cubes)
{
    array<vector<int>, 3> old_cube_boundaries;

    FOR (i, 0, < 3) {
        auto& bs = old_cube_boundaries[i];
        bs.PB(cube.b[i]);
        bs.PB(cube.e[i]);
    }

    vector<Cube> new_incoming_cubes;
    for (auto ic : incoming_cubes) {
        auto ic_pcs = split_along(ic, old_cube_boundaries);
        for (auto icpc : ic_pcs) {
            if (is_disjunct(cube, icpc)) {
                new_incoming_cubes.PB(icpc);
            }
        }
    }
    return new_incoming_cubes;
}

// return old cube pieces = cube - incoming cube
vector<Cube> handle_incoming_cube_off(const Cube& cube, const Cube& ic)
{
    array<vector<int>, 3> ic_boundaries;

    FOR (i, 0, < 3) {
        auto& bs = ic_boundaries[i];
        bs.PB(ic.b[i]);
        bs.PB(ic.e[i]);
    }

    auto old_cube_pcs = split_along(cube, ic_boundaries);
    vector<Cube> new_old_cube_pcs;

    for (auto pc : old_cube_pcs) {
        if (is_disjunct(pc, ic)) {
            new_old_cube_pcs.PB(pc);
        }
    }
    return new_old_cube_pcs;
}

struct CubeSpace
{
    vector<Cube> leaves;
    int split_dim = -1;
    int split_value = INT_MIN;
    CubeSpace* left = nullptr;
    CubeSpace* right = nullptr;
    explicit CubeSpace(vector<Cube>&& leaves) : leaves(move(leaves)) {}
    CubeSpace() = default;
    int size() const { return split_dim == -1 ? ~leaves : left->size() + right->size(); }
    int64_t volume() const
    {
        if (split_dim == -1) {
            int64_t volume = 0;
            for (auto& c : leaves) {
                auto v = c.e - c.b;
                volume += (int64_t)v[0] * (int64_t)v[1] * (int64_t)v[2];
            }
            return volume;
        } else {
            return left->volume() + right->volume();
        }
    }
};

pair<optional<Cube>, optional<Cube>> split(const Cube& c, int split_dim, int split_value)
{
    if (c.e[split_dim] <= split_value) {
        return {c, nullopt};
    } else if (split_value <= c.b[split_dim]) {
        return {nullopt, c};
    } else {
        auto cl = c;
        auto cr = c;
        cl.e[split_dim] = split_value;
        cr.b[split_dim] = split_value;
        return {cl, cr};
    }
}

void split(const Cube& c, int split_dim, int split_value, vector<Cube>& left, vector<Cube>& right)
{
    auto lr = split(c, split_dim, split_value);
    if (lr.FST) {
        left.PB(*lr.FST);
    }
    if (lr.SND) {
        right.PB(*lr.SND);
    }
}

void maybe_split(CubeSpace& cube_space)
{
    assert(cube_space.split_dim == -1);
    if (~cube_space.leaves < 8) {
        return;
    }
    optional<AI3> best_split_dim_value_leafcount;

    vector<int> boundaries;
    FOR (split_dim, 0, < 3) {
        boundaries.clear();
        for (auto& c : cube_space.leaves) {
            boundaries.PB(c.b[split_dim]);
            boundaries.PB(c.e[split_dim]);
        }
        sort_unique_trunc(boundaries);
        int split_value = boundaries[~boundaries / 2];
        int lc = 0, rc = 0;
        for (auto& c : cube_space.leaves) {
            if (c.e[split_dim] <= split_value) {
                ++lc;
            } else if (split_value <= c.b[split_dim]) {
                ++rc;
            } else {
                ++lc;
                ++rc;
            }
        }
        int leafcount = max(lc, rc);
        if (!best_split_dim_value_leafcount || leafcount < best_split_dim_value_leafcount->at(2)) {
            best_split_dim_value_leafcount = AI3{split_dim, split_value, leafcount};
        }
    }
    cube_space.split_dim = best_split_dim_value_leafcount->at(0);
    cube_space.split_value = best_split_dim_value_leafcount->at(1);
    vector<Cube> left, right;
    for (auto& c : cube_space.leaves) {
        split(c, cube_space.split_dim, cube_space.split_value, left, right);
    }
    cube_space.leaves.clear();
    cube_space.left = new CubeSpace(move(left));
    cube_space.right = new CubeSpace(move(right));
}

void update_with_oncubes(CubeSpace& cube_space, vector<Cube> oncubes)
{
    if (oncubes.empty()) {
        return;
    }
    if (cube_space.split_dim < 0) {
        // Update here
        for (auto& dc : cube_space.leaves) {
            oncubes = handle_incoming_cube_on(dc, oncubes);
        }
        cube_space.leaves.insert(cube_space.leaves.end(), BE(oncubes));
        maybe_split(cube_space);
    } else {
        vector<Cube> left, right;
        for (auto c : oncubes) {
            split(c, cube_space.split_dim, cube_space.split_value, left, right);
        }
        update_with_oncubes(*cube_space.left, move(left));
        update_with_oncubes(*cube_space.right, move(right));
    }
}

void update_with_offcube(CubeSpace& cube_space, const Cube& c)
{
    if (cube_space.split_dim == -1) {
        vector<Cube> new_leaves;
        for (auto& dc : cube_space.leaves) {
            auto dc_pcs = handle_incoming_cube_off(dc, c);
            new_leaves.insert(new_leaves.end(), BE(dc_pcs));
        }
        cube_space.leaves.swap(new_leaves);
        maybe_split(cube_space);
    } else {
        auto lr = split(c, cube_space.split_dim, cube_space.split_value);
        if (lr.FST) {
            update_with_offcube(*cube_space.left, *lr.FST);
        }
        if (lr.SND) {
            update_with_offcube(*cube_space.right, *lr.SND);
        }
    }
}

int P2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    int step = 1;
    vector<pair<Cube, bool>> cube_steps;
    for (auto l : lines) {
        bool on = false;
        if (starts_with(l, "on ")) {
            on = true;
            l = l.substr(3);
        } else if (starts_with(l, "off ")) {
            on = false;
            l = l.substr(4);
        } else
            assert(false);
        auto ls = split(l, "xyz=., ");
        auto b = AI3{stoi(ls[0]), stoi(ls[2]), stoi(ls[4])};
        auto e = AI3{stoi(ls[1]) + 1, stoi(ls[3]) + 1, stoi(ls[5]) + 1};

        cube_steps.PB(make_pair(Cube{b, e}, on));
    }

    CubeSpace cube_space;
    for (auto [cube, on] : cube_steps) {
        if (on) {
            update_with_oncubes(cube_space, vector<Cube>({cube}));
            auto a3 = cube_space.size();
            printf("step %d on -> %d cubes\n", step++, a3);
        } else {
            update_with_offcube(cube_space, cube);
            auto a2 = cube_space.size();
            printf("step %d off -> %d cubes\n", step++, a2);
        }
    }
    printf("P2: %lld\n", cube_space.volume());
    return 0;
}

int main()
{
    // P1();
    P2();
    return 0;
}
