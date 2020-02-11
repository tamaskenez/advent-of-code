#include "common.h"

bool all_done(const vector<char>& cs, const unordered_set<char>& done)
{
    for (auto c : cs) {
        if (!contains(done, c)) {
            return false;
        }
    }
    return true;
}

void solve1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d07_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<char, vector<char>> step_to_conds;
    for (auto& l : lines) {
        // Step Y must be finished before step L can begin.
        auto xs = split(l, " \t.");
        auto pri = xs[1];
        auto post = xs[7];
        assert(~pri == 1);
        assert(~post == 1);
        step_to_conds[post[0]].PB(pri[0]);
        step_to_conds[pri[0]];
    }
    unordered_set<char> done;
    auto N = ~step_to_conds;
    while (~done != N) {
        bool changed = false;
        for (auto& kv : step_to_conds) {
            if (all_done(kv.second, done)) {
                changed = true;
                done.insert(kv.first);
                printf("%c", kv.first);
                step_to_conds.erase(kv.first);
                break;
            }
        }
        assert(changed);
    }
    printf("\n");
}

void solve2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d07_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<char, vector<char>> step_to_conds;
    for (auto& l : lines) {
        // Step Y must be finished before step L can begin.
        auto xs = split(l, " \t.");
        auto pri = xs[1];
        auto post = xs[7];
        assert(~pri == 1);
        assert(~post == 1);
        step_to_conds[post[0]].PB(pri[0]);
        step_to_conds[pri[0]];
    }
    unordered_set<char> done;
    auto N = ~step_to_conds;
    int NWS = 5;
    VI wleft(NWS, 0);
    vector<char> wtask(NWS, -1);
    int time_passed = 0;

    auto advance_time = [&wleft, &time_passed, &done, NWS, &wtask]() {
        // no free worker, advance time
        ++time_passed;
        FOR (i, 0, < NWS) {
            auto& wl = wleft[i];
            auto& wt = wtask[i];
            if (wl > 0) {
                --wl;
                if (wl == 0) {
                    assert(wt >= 0);
                    done.insert(wt);
                    wt = -1;
                }
            }
        }
    };

    while (~done != N) {
        FOR (i, 0, < NWS) {
            printf("%d to %c | ", wleft[i], wtask[i]);
        }
        printf("\n");
        int free_worker = -1;
        FOR (i, 0, < ~wleft) {
            if (wleft[i] == 0) {
                free_worker = i;
                break;
            }
        }
        if (free_worker < 0) {
            advance_time();
            continue;
        }
        // assign the next task to a worker
        bool changed = false;
        for (auto& kv : step_to_conds) {
            if (all_done(kv.second, done)) {
                changed = true;
                wtask[free_worker] = kv.first;
                wleft[free_worker] = kv.first - 'A' + 1 + 60;
                // printf("%c", kv.first);
                step_to_conds.erase(kv.first);
                break;
            }
        }
        if (!changed) {
            advance_time();
        }
    }
    printf("%d\n", time_passed);
}

void solve3()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d07_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<char, vector<char>> step_to_conds;
    for (auto& l : lines) {
        // Step Y must be finished before step L can begin.
        auto xs = split(l, " \t.");
        auto pri = xs[1];
        auto post = xs[7];
        assert(~pri == 1);
        assert(~post == 1);
        step_to_conds[post[0]].PB(pri[0]);
        step_to_conds[pri[0]];
    }
    unordered_set<char> done;
    auto N = ~step_to_conds;
    int NWS = 5;
    struct Worker
    {
        char task;
        int time_left;
    };

    vector<maybe<Worker>> ws(NWS);
    int time_passed = 0;

    auto print = [&ws, &time_passed]() {
        for (auto& w : ws) {
            printf("time: %d, ", time_passed);
            if (w) {
                printf("%d to %c | ", w->time_left, w->task);
            } else {
                printf("  idle  | ");
            }
        }
        printf("\n");
    };

    auto advance_time = [&ws, &time_passed, &done, &print]() {
        print();
        // no free worker, advance time
        ++time_passed;
        for (auto& w : ws) {
            if (w) {
                assert(w->time_left > 0);
                if (--w->time_left == 0) {
                    assert(w->task >= 0);
                    done.insert(w->task);
                    w.reset();
                }
            }
        }
    };

    while (~done != N) {
        int free_worker = -1;
        FOR (i, 0, < ~ws) {
            if (!ws[i]) {
                free_worker = i;
                break;
            }
        }
        bool do_advance_time = free_worker < 0;
        if (!do_advance_time) {
            // assign the next task to a worker
            do_advance_time = true;
            for (auto& kv : step_to_conds) {
                if (all_done(kv.second, done)) {
                    ws[free_worker] = Worker{kv.first, kv.first - 'A' + 1 + 60};
                    step_to_conds.erase(kv.first);
                    do_advance_time = false;
                    break;
                }
            }
        }
         if (do_advance_time) {
            advance_time();
        }
    }
    print();
    printf("%d\n", time_passed);
}

// 16:54 + ...
// 822 low
// 253 low
int main()
{
    // solve1();
    // solve2();
    solve3();
}
