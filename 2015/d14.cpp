#include "common.h"

struct Rd
{
    int speed, sd, rd;
};

int get_dist_after(const Rd& rd, int total_secs)
{
    int d = 0;
    int secs_passed = 0;
    for (;;) {
        int this_sd = min(rd.sd, total_secs - secs_passed);
        secs_passed += this_sd;
        d += this_sd * rd.speed;
        if (secs_passed == total_secs) {
            break;
        }
        int this_rd = min(rd.rd, total_secs - secs_passed);
        secs_passed += this_rd;
        if (secs_passed == total_secs) {
            break;
        }
    }
    return d;
}

VI get_dist_after2(const Rd& rd, int total_secs)
{
    VI vi(total_secs + 1);
    int d = 0;
    int secs_passed = 0;
    for (;;) {
        int this_sd = min(rd.sd, total_secs - secs_passed);
        FOR (i, 1, <= this_sd) {
            vi[secs_passed + i] = d + i * rd.speed;
        }
        secs_passed += this_sd;
        d += this_sd * rd.speed;
        if (secs_passed == total_secs) {
            break;
        }
        int this_rd = min(rd.rd, total_secs - secs_passed);
        FOR (i, 1, <= this_rd) {
            vi[secs_passed + i] = d;
        }
        secs_passed += this_rd;
        if (secs_passed == total_secs) {
            break;
        }
    }
    return vi;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d14_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, Rd> rds;
    for (auto& l : lines) {
        auto vs = split(l, " .,");
        assert(~vs == 15);
        auto name = vs[0];
        auto speed = stoi(vs[3]);
        auto speed_dur = stoi(vs[6]);
        auto rest_dur = stoi(vs[13]);
        rds.insert(make_pair(name, Rd{speed, speed_dur, rest_dur}));
    }
    {
        int best_d = INT_MIN;
        for (auto& kv : rds) {
            int d = get_dist_after(kv.second, 2503);
            if (d > best_d) {
                best_d = d;
            }
        }
        printf("part1 %d\n", best_d);
    }
    {
        map<string, int> rdix;
        for (auto& kv : rds) {
            rdix.insert(make_pair(kv.FST, ~rdix));
        }
        vector<VI> after_sec_rdix_dist(2504, VI(~rdix));
        for (auto& kv : rds) {
            auto ds = get_dist_after2(kv.second, 2503);
            assert(~ds == 2504);
            auto rdx = rdix.at(kv.FST);
            FOR (i, 0, <= 2503) {
                after_sec_rdix_dist[i][rdx] = ds[i];
            }
        }
        VI points(~rdix);
        FOR (i, 1, <= 2503) {
            auto& ai = after_sec_rdix_dist[i];
            auto maxdhere = *max_element(BE(ai));
            FOR (j, 0, < ~rdix) {
                if (ai[j] == maxdhere) {
                    ++points[j];
                }
            }
        }
        auto maxpoints = *max_element(BE(points));
        printf("part2 %d\n", maxpoints);
    }
    return 0;
}

// 2292
// 437
// 2637

// 1449