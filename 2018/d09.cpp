#include <list>

#include "common.h"

using I64 = int64_t;

// 435 players; last marble is worth 71184 points
#if 1
const int NP = 435;
const int LM = 71184 * 100;
#else
const int NP = 9;
const int LM = 25;
#endif

list<I64>::iterator move_right_circ(list<I64>& l, list<I64>::iterator it, int d)
{
    assert(d >= 0);
    assert(it != l.end());
    FOR (i, 0, < d) {
        ++it;
        if (it == l.end()) {
            it = l.begin();
        }
    }
    return it;
}

list<I64>::iterator move_left_circ(list<I64>& l, list<I64>::iterator it, int d)
{
    assert(d >= 0);
    assert(it != l.end());
    FOR (i, 0, < d) {
        if (it == l.begin()) {
            it = l.end();
        }
        --it;
    }
    return it;
}

void main2()
{
    list<I64> circle;
    circle.PB(0);
    auto cit = circle.begin();
    vector<I64> scores(NP);
    int current_pix = 0;
    FOR (marble_to_place, 1, <= LM) {
        if (marble_to_place % 23 == 0) {
            scores[current_pix] += marble_to_place;
            cit = move_left_circ(circle, cit, 7);
            scores[current_pix] += *cit;
            cit = circle.erase(cit);
            if (cit == circle.end()) {
                cit = circle.begin();
            }
        } else {
            cit = move_right_circ(circle, cit, 2);
            cit = circle.insert(cit, marble_to_place);
        }
        current_pix = (current_pix + 1) % ~scores;
    }
    RunningStat<I64> rs;
    for (auto& s : scores) {
        rs.add(s);
    }
    printf("%lld\n", *rs.upper);
}

int main()
{
    main2();
    return 0;
    deque<int> circle(1, 0);
    // circle.reserve(LM);
    VI scores(NP);
    int current_mix = 0;
    int current_pix = 0;
    int last_perc = -1;
    FOR (marble_to_place, 1, <= LM) {
        int perc = (int)round((double)marble_to_place / LM * 100.0);
        if (last_perc != perc) {
            printf("%d%%\n", perc);
            last_perc = perc;
        }
        int N = ~circle;
        if (marble_to_place % 23 == 0) {
            scores[current_pix] += marble_to_place;
            int toremix = (current_mix + ~circle - 7) % ~circle;
            scores[current_pix] += circle[toremix];
            if (toremix == ~circle - 1) {
                circle.pop_back();
                current_mix = 0;
            } else {
                circle.erase(circle.begin() + toremix);
                current_mix = toremix;
            }
        } else {
            int x1 = (current_mix + 1) % N;
            int x2 = (current_mix + 2) % N;
            if (x1 > x2) {
                swap(x1, x2);
            }
            if (x1 == x2) {
                assert(~circle == 1);
                circle.PB(marble_to_place);
                current_mix = ~circle - 1;
            } else if (x1 == 0 && x2 == N - 1) {
                circle.PB(marble_to_place);
                current_mix = N;
            } else {
                assert(x1 + 1 == x2);
                circle.insert(circle.begin() + x2, marble_to_place);
                current_mix = x2;
            }
        }
        current_pix = (current_pix + 1) % ~scores;
    }

    RunningStat<int> rs;
    for (auto& s : scores) {
        rs.add(s);
    }
    printf("%d\n", *rs.upper);

    return 0;
}
