#include "common.h"

int calc_perm(const VI& ps, const map<PII, int>& happens)
{
    int N = ~ps;
    int total = 0;
    FOR (i, 0, < N) {
        int left = (i + N - 1) % N;
        int right = (i + 1) % N;
        int pi = ps[i];
        int pl = ps[left];
        int pr = ps[right];
        if (pi == -1) {
            continue;
        }
        if (pl != -1) {
            total += happens.at(make_pair(pi, pl));
        }
        if (pr != -1) {
            total += happens.at(make_pair(pi, pr));
        }
    }
    return total;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d13_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, int> persons;
    map<PII, int> happens;
    for (auto& l : lines) {
        auto vs = split(l, " .");
        assert(~vs == 11);
        auto p1 = vs[0];
        auto p2 = vs[10];
        auto gl = vs[2];
        auto n = stoi(vs[3]);
        if (gl != "gain") {
            assert(gl == "lose");
            n = -n;
        }
        persons.insert(make_pair(p1, ~persons));
        persons.insert(make_pair(p2, ~persons));
        int ip1 = persons.at(p1);
        int ip2 = persons.at(p2);
        must_insert(happens, make_pair(make_pair(ip1, ip2), n));
    }

    {
        VI ps(~persons);
        iota(BE(ps), 0);

        int best_x = INT_MIN;
        do {
            int x = calc_perm(ps, happens);
            if (x > best_x) {
                best_x = x;
            }
        } while (std::next_permutation(BE(ps)));
        printf("part1 %d\n", best_x);
    }

    {
        VI ps(~persons + 1);
        iota(BE(ps), -1);

        int best_x = INT_MIN;
        do {
            int x = calc_perm(ps, happens);
            if (x > best_x) {
                best_x = x;
            }
        } while (std::next_permutation(BE(ps)));
        printf("part2 %d\n", best_x);
    }
    return 0;
}

// 13:24
// 647
