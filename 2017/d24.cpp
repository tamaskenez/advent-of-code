#include "common.h"

using PII = pair<int, int>;

void remove(map<int, unordered_map<int, int>>& ps, int a, int b)
{
    auto it = ps.find(a);
    assert(it != ps.end());
    auto jt = it->second.find(b);
    assert(jt->second > 0);
    if (jt->second == 1) {
        it->second.erase(b);
    } else {
        --jt->second;
    }
}

int get_best(int last_conn, map<int, unordered_map<int, int>>& ps, int sum_so_far)
{
    auto it = ps.find(last_conn);
    auto& ends_map = it->second;
    VI endstotry;
    for (auto& ekv : ends_map) {
        auto endx = ekv.first;
        auto count = ekv.second;
        if (count == 0) {
            continue;
        }
        endstotry.PB(endx);
    }
    RunningStat<int> stat;
    for (auto endx : endstotry) {
        remove(ps, last_conn, endx);
        remove(ps, endx, last_conn);
        auto result = get_best(endx, ps, sum_so_far + last_conn + endx);
        stat.add(result);
        ++ps[last_conn][endx];
        ++ps[endx][last_conn];
    }
    if (stat.upper) {
        return *stat.upper;
    } else {
        return sum_so_far;
    }
}

pair<int, int> get_best2(int last_conn,
                         map<int, unordered_map<int, int>>& ps,
                         pair<int, int> sum_so_far)
{
    auto it = ps.find(last_conn);
    auto& ends_map = it->second;
    VI endstotry;
    for (auto& ekv : ends_map) {
        auto endx = ekv.first;
        auto count = ekv.second;
        if (count == 0) {
            continue;
        }
        endstotry.PB(endx);
    }
    pair<int, int> best = sum_so_far;
    for (auto endx : endstotry) {
        remove(ps, last_conn, endx);
        remove(ps, endx, last_conn);
        auto result = get_best2(
            endx, ps, make_pair(sum_so_far.first + last_conn + endx, sum_so_far.second + 1));
        if (result.second > best.second ||
            (result.second == best.second && result.first > best.first)) {
            best = result;
        }
        ++ps[last_conn][endx];
        ++ps[endx][last_conn];
    }
    return best;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<int, unordered_map<int, int>> ps;

    for (auto& l : lines) {
        auto xs = split(l, "/");
        assert(~xs == 2);
        int a = stoi(xs[0]);
        int b = stoi(xs[1]);
        ++ps[a][b];
        ++ps[b][a];
    }

    if (0) {
        int b = get_best(0, ps, 0);
        printf("%d\n", b);
    }
    if (1) {
        auto b = get_best2(0, ps, make_pair(0, 0));
        printf("strength %d length %d\n", b.first, b.second);
    }
    return 0;
}
