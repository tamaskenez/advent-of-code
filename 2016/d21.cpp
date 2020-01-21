#include "common.h"

const string INPUT = "abcdefgh";
// const string INPUT = "abcde";

string scramble(string w, const VS& lines)
{
    for (auto& l : lines) {
        auto w0 = w;
        auto vs = split(l, " ");
        if (vs[0] == "swap") {
            if (vs[1] == "position") {
                // swap position X with position Y means that the letters at indexes X and Y
                // (counting from 0) should be swapped.
                // swap position 4 with position 6
                auto x = stoi(vs[2]);
                auto y = stoi(vs[5]);
                swap(w[x], w[y]);
            } else if (vs[1] == "letter") {
                // swap letter X with letter Y means that the letters X and Y
                // should be swapped (regardless of where they appear in the string).
                // swap letter a with letter h
                auto sx = vs[2];
                auto sy = vs[5];
                assert(~sx == 1 && ~sy == 1);
                auto x = sx[0];
                auto y = sy[0];
                for (auto& c : w) {
                    if (c == x) {
                        c = y;
                    } else if (c == y) {
                        c = x;
                    }
                }
            } else {
                UNREACHABLE;
            }
        } else if (vs[0] == "rotate") {
            if (vs[1] == "right") {
                // rotate left/right X steps means that the whole string should be rotated; for
                // example, one right rotation would turn abcd into dabc.
                // rotate left 5 steps
                auto x = stoi(vs[2]);
                rotate(w.begin(), w.begin() + (~w - x), w.end());
            } else if (vs[1] == "left") {
                auto x = stoi(vs[2]);
                rotate(w.begin(), w.begin() + x, w.end());
            } else if (vs[1] == "based") {
                // rotate based on position of letter X
                // means that the whole string should be rotated to the right based on the index
                // of letter X (counting from 0) as determined before this instruction does any
                // rotations. Once the index is determined, rotate the string to the right one
                // time, plus a number of times equal to that index, plus one additional time if
                // the index was at least 4.
                // rotate based on position of letter g
                auto sx = vs[6];
                assert(~sx == 1);
                auto x = sx[0];
                auto xpos = w.find(x);
                assert(xpos != string::npos);
                int rots = 1 + xpos;
                if (xpos >= 4) {
                    ++rots;
                }
                rots = rots % ~w;
                if (rots != 0) {
                    rotate(w.begin(), w.begin() + (~w - rots), w.end());
                    printf("");
                }
            } else {
                UNREACHABLE;
            }
        } else if (vs[0] == "reverse") {
            // reverse positions X through Y means that the span of letters at indexes X through
            // Y (including the letters at X and Y) should be reversed in order.
            // reverse positions 2 through 6
            auto x = stoi(vs[2]);
            auto y = stoi(vs[4]);
            reverse(w.begin() + x, w.begin() + y + 1);
        } else if (vs[0] == "move") {
            // move position X to position Y means that the letter which is at index X should be
            // removed from the string, then inserted such that it ends up at index Y.
            // move position 7 to position 2
            auto x = stoi(vs[2]);
            auto y = stoi(vs[5]);
            assert_between_co(x, 0, ~w);
            assert_between_co(y, 0, ~w);
            auto wx = w[x];
            w.erase(x, 1);
            w.insert(y, 1, wx);
        } else {
            UNREACHABLE;
        }
    }
    return w;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d21_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    {
        auto w = scramble(INPUT, lines);
        printf("%s\n", w.c_str());
    }
    {
        const string TARGET = "fbgdceah";
        string w = "abcdefgh";
        do {
            if (scramble(w, lines) == TARGET) {
                printf("part2 %s\n", w.c_str());
            }
        } while (std::next_permutation(BE(w)));
    }
    return 0;
}

// not eahcfbdg
// not edfcbhga
// not fegchbad