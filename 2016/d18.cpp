#include "common.h"

const string INPUT =
    ".^.^..^......^^^^^...^^^...^...^....^^.^...^.^^^^....^...^^.^^^...^^^^.^^.^.^^..^.^^^..^^^^^^."
    "^^^..^";

string next_row(const string& s)
{
    string nr = string(~s, ' ');
    FOR (i, 0, < ~s) {
        auto l = (i - 1 >= 0) ? s[i - 1] : '.';
        auto c = s[i];
        auto r = (i + 1 < ~s) ? s[i + 1] : '.';
        string w = string(1, l) + string(1, c) + string(1, r);
        bool is_trap = w == "^^." || w == ".^^" || w == "^.." || w == "..^";
        nr[i] = is_trap ? '^' : '.';
        // Its left and center tiles are traps, but its right tile is not.
        // Its center and right tiles are traps, but its left tile is not.
        // Only its left tile is a trap.
        // Only its right tile is a trap.
    }
    return nr;
}

int main()
{
    VS rows;
    rows.PB(INPUT);
    while (~rows < 400000) {
        rows.PB(next_row(rows.back()));
    }
    int total = 0;
    for (auto& r : rows) {
        for (auto c : r) {
            if (c == '.') {
                ++total;
            } else {
                assert(c == '^');
            }
        }
    }
    printf("%d\n", total);
    return 0;
}
