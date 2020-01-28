#include "common.h"

int solve(AI2 start, AI2 end, const VS& board, const int H, const int W)
{
    vector<AI2> front, next_front;
    set<AI2> visited;
    front.PB(start);
    visited.insert(start);
    int steps = 0;
    for (;; ++steps) {
        next_front.clear();
        assert(!front.empty());
        for (const auto st : front) {
            if (st == end) {
                return steps;
            }
            for (auto dir : {AI2{-1, 0}, AI2{1, 0}, AI2{0, 1}, AI2{0, -1}}) {
                auto next_loc = st + dir;
                if (!is_between_co(next_loc[0], 0, H) || !is_between_co(next_loc[1], 0, W)) {
                    continue;
                }
                auto c = board[next_loc[0]][next_loc[1]];
                if (c != '.') {
                    continue;
                }
                if (contains(visited, next_loc)) {
                    continue;
                }
                next_front.PB(next_loc);
                visited.insert(next_loc);
            }
        }
        next_front.swap(front);
    }
    UNREACHABLE;
    return INT_MAX;
}

int solve(const vector<AI2>& targets,
          const VS& board,
          const int H,
          const int W,
          AI2 start,
          bool return_start)
{
    AI2 loc = start;
    int r = 0;
    for (auto t : targets) {
        r += solve(loc, t, board, H, W);
        loc = t;
    }
    if (return_start) {
        r += solve(loc, start, board, H, W);
    }
    return r;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    const int W = ~lines[0];
    assert(W > 0);
    VS board;
    vector<AI2> targets;
    AI2 start;
    for (auto& l : lines) {
        if (l.empty()) {
            break;
        }
        assert(~l == W);
        auto s = l;
        FOR (col, 0, < W) {
            auto& c = s[col];
            if (c == '0') {
                start = AI2{~board, col};
                c = '.';
            } else if (isdigit(c)) {
                targets.PB(AI2{~board, col});
                c = '.';
            } else {
                assert(c == '#' || c == '.');
            }
        }
        board.PB(s);
    }
    const int H = ~board;

 if(0)   {
        RunningStat<int> steps;
        do {
            steps.add(solve(targets, board, H, W, start, false));
        } while (std::next_permutation(BE(targets)));
        printf("part1 %d\n", *steps.lower);
    }
    {
        RunningStat<int> steps;
        do {
            steps.add(solve(targets, board, H, W, start, true));
        } while (std::next_permutation(BE(targets)));
        printf("part2 %d\n", *steps.lower);
    }
    return 0;
}
