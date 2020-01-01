#include "common.h"

using VAI3 = vector<AI3>;

const vector<AI3> in_pos1 = {{-1, 0, 2}, {2, -10, -7}, {4, -8, 8}, {3, 5, -1}};
const vector<AI3> in_pos2 = {{-8, -10, 0}, {5, 5, 10}, {2, -7, 3}, {9, -8, -3}};
const VAI3 in_pos = {{-16, -1, -12}, {0, -4, -17}, {-11, 11, 0}, {2, 2, -6}};

struct Moons
{
    vector<AI3> poss, vels;
    Moons(VAI3 poss, VAI3 vels) : poss(move(poss)), vels(move(vels))
    {
        assert(~this->poss == ~this->vels);
    }
    int size() const { return ~poss; }
};

Moons read(const vector<AI3>& i)
{
    return Moons{i, vector<AI3>(~i, AI3{})};
}

void print(const Moons& m, const char* title = nullptr)
{
    if (title) {
        printf("-- %s\n", title);
    }
    FOR (i, 0, < ~m) {
        printf("m%d: (%d, %d, %d) (%d %d %d)\n", i, m.poss[i][0], m.poss[i][1], m.poss[i][2],
               m.vels[i][0], m.vels[i][1], m.vels[i][2]);
    }
}

void advance(Moons& m)
{
    FOR (i, 0, < ~m - 1) {
        FOR (j, i + 1, < ~m) {
            auto& pi = m.poss[i];
            auto& vi = m.vels[i];
            auto& pj = m.poss[j];
            auto& vj = m.vels[j];
            FOR (k, 0, < 3) {
                if (pi[k] < pj[k]) {
                    ++vi[k];
                    --vj[k];
                } else if (pi[k] > pj[k]) {
                    --vi[k];
                    ++vj[k];
                }
            }
        }
    }
    FOR (i, 0, < ~m) {
        FOR (k, 0, < 3) {
            m.poss[i][k] += m.vels[i][k];
        }
    }
}

int energy(const Moons& m)
{
    int total = 0;
    FOR (i, 0, < ~m) {
        int pot = 0;
        int kin = 0;
        FOR (k, 0, < 3) {
            pot += abs(m.poss[i][k]);
            kin += abs(m.vels[i][k]);
        }
        total += pot * kin;
    }
    return total;
}

Moons simulate(Moons m, int steps)
{
    FOR (i, 0, < steps) {
        advance(m);
    }
    return m;
}

uint64_t test_repeat(Moons m)
{
    const Moons m0 = m;
    vector<int> repeats(3, INT_MIN);
    bool done;
    int steps = 0;
    do {
        advance(m);
        ++steps;
        // printf("after step %d\n",steps);
        // print(m);
        done = true;
        FOR (k, 0, < 3) {
            if (repeats[k] != INT_MIN) {
                continue;
            }
            done = false;
            bool equal = true;
            FOR (i, 0, < ~m) {
                if (m.poss[i][k] != m0.poss[i][k] || m.vels[i][k] != m0.vels[i][k]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                repeats[k] = steps;
            }
        }
    } while (!done);

    printf("repeats: %d %d %d\n", repeats[0], repeats[1], repeats[2]);
    auto l = lcm(lcm((uint64_t)repeats[0], (uint64_t)repeats[1]), (uint64_t)repeats[2]);
    FOR (k, 0, < 3) {
        auto q = l / repeats[k];
        printf("%d x %s = %s\n", repeats[k], to_string(q).c_str(),
               to_string(repeats[k] * q).c_str());
    }
    return l;
}

int main()
{
    const auto moons1 = read(in_pos1);
    const auto moons2 = read(in_pos2);
    const auto moons = read(in_pos);

    {
        printf("-- Simulate moons1 for 10.\n");
        print(moons1, "START");
        auto m = simulate(moons1, 10);
        auto te = energy(m);
        print(m, "STEP 10");
        printf("te %d\n", te);
    }

    {
        const int N = 100;
        printf("-- Simulate moons2 for %d.\n", N);
        print(moons2, "START");
        auto m = simulate(moons2, N);
        auto te = energy(m);
        print(m, ("STEP " + to_string(N)).c_str());
        printf("te %d\n", te);
    }

    printf("input te after 1000 steps: %d\n", energy(simulate(moons, 1000)));

    printf("moons1 repeat: %s\n", to_string(test_repeat(moons1)).c_str());
    printf("moons2 repeat: %s\n", to_string(test_repeat(moons2)).c_str());
    printf("moons repeat: %s\n", to_string(test_repeat(moons)).c_str());

    return 0;
}