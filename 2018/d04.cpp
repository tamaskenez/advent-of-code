#include "common.h"

using AI5 = array<int, 5>;

enum What
{
    w_wakes,
    w_falls,
    w_begins
};

struct Guard
{
    map<int, int> awake, asleep;
    int asleep_count = 0;
};

struct E
{
    AI5 ts;
    What w;
    string line;
    int gid = -1;
    bool operator<(const E& b) const { return ts < b.ts; }
};

AI3 ymd(AI5 x)
{
    return AI3{x[0], x[1], x[2]};
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d04_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    //[1518-11-02 00:42] wakes up
    //[1518-11-13 00:40] falls asleep
    // [1518-08-03 23:52] Guard #157 begins shift
    vector<E> es;
    for (auto& l : lines) {
        auto xs = split(l, "[- :]\t#");
        assert(~xs >= 5);
        AI5 ts;
        FOR (i, 0, < 5) {
            ts[i] = stoi(xs[i]);
        }
        if (xs[5] == "wakes") {
            es.PB(E{ts, w_wakes, l});
        } else if (xs[5] == "falls") {
            es.PB(E{ts, w_falls, l});
        } else {
            assert(xs[5] == "Guard");
            assert(~xs == 9);
            es.PB(E{ts, w_begins, l, stoi(xs[6])});
        }
    }
    sort(BE(es));
    map<int, Guard> guards;
    int guard = -1;
    AI5 pending_since;
    bool asleep;
    for (auto& e : es) {
        printf("%s\n", e.line.c_str());
        if (guard >= 0) {
            auto currtime = pending_since;
            for (;;) {
                if (asleep && currtime[3] == 0) {
                    ++guards[guard].asleep[currtime[4]];
                    ++guards[guard].asleep_count;
                }
                if (++currtime[4] == 60) {
                    currtime[4] = 0;
                    ++currtime[3];
                }

                if (ymd(currtime) == ymd(e.ts)) {
                    assert(currtime[3] < 24);
                    // next event same day
                    if (currtime == e.ts) {
                        break;
                    }
                } else {
                    // next event different day
                    if (currtime[3] == 24) {
                        currtime[3] = 0;
                        currtime[0] = e.ts[0];
                        currtime[1] = e.ts[1];
                        currtime[2] = e.ts[2];
                    }
                    if (currtime == e.ts) {
                        break;
                    }
                }
            }
        }
        pending_since = e.ts;
        switch (e.w) {
            case w_begins:
                guard = e.gid;
                assert(guard >= 0);
                asleep = false;
                break;
            case w_falls:
                asleep = true;
                break;
            case w_wakes:
                asleep = false;
                break;
            default:
                UNREACHABLE;
        }
    }
    int ma = 0;
    int mag;
    for (auto& kv : guards) {
        if (kv.second.asleep_count > ma) {
            ma = kv.second.asleep_count;
            mag = kv.first;
        }
    }
    auto& g = guards[mag];
    int mam = -1;
    int mamc = -1;
    for (auto& kv : g.asleep) {
        if (kv.second > mamc) {
            mamc = kv.second;
            mam = kv.first;
        }
    }
    printf("%d\n", mag * mam);
    map<int, map<int, int>> mmm;  // minute - guard - count
    for (auto& g : guards) {
        for (auto& kv : g.second.asleep) {
            mmm[kv.first][g.first] += kv.second;
        }
    }
    {
        int best_minute = -1;
        int best_guard = -1;
        int best_count = -1;
        for (auto& kv : mmm) {
            int minute = kv.first;
            for (auto& qq : kv.second) {
                if (qq.second > best_count) {
                    best_count = qq.second;
                    best_guard = qq.first;
                    best_minute = minute;
                }
            }
        }
        printf("%d\n", best_guard * best_minute);
    }
    return 0;
}
