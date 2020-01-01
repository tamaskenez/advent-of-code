#include "common.h"

const int EOD = INT_MIN;
const int input1[] = {1, 0, 0, 0, 99, EOD};     // 2,0,0,0,99
const int input2[] = {2, 3, 0, 3, 99, EOD};     // 2,3,0,6,99 (3 * 2 = 6).
const int input3[] = {2, 4, 4, 5, 99, 0, EOD};  // becomes 2,4,4,5,99,9801 (99 * 99 = 9801).
const int input4[] = {1, 1, 1, 4, 99, 5, 6, 0, 99, EOD};  // becomes 30,1,1,4,2,5,6,0,99.

const int input[] = {
    1, 0,   0,  3,   1, 1,   2,   3,   1, 3,   4,   3,   1,  5,  0,   3,   2, 6,   1,   19,
    1, 19,  9,  23,  1, 23,  9,   27,  1, 10,  27,  31,  1,  13, 31,  35,  1, 35,  10,  39,
    2, 39,  9,  43,  1, 43,  13,  47,  1, 5,   47,  51,  1,  6,  51,  55,  1, 13,  55,  59,
    1, 59,  6,  63,  1, 63,  10,  67,  2, 67,  6,   71,  1,  71, 5,   75,  2, 75,  10,  79,
    1, 79,  6,  83,  1, 83,  5,   87,  1, 87,  6,   91,  1,  91, 13,  95,  1, 95,  6,   99,
    2, 99,  10, 103, 1, 103, 6,   107, 2, 6,   107, 111, 1,  13, 111, 115, 2, 115, 10,  119,
    1, 119, 5,  123, 2, 10,  123, 127, 2, 127, 9,   131, 1,  5,  131, 135, 2, 10,  135, 139,
    2, 139, 9,  143, 1, 143, 2,   147, 1, 5,   147, 0,   99, 2,  0,   14,  0, EOD};

VI run(VI xs, int noun, int verb)
{
    auto read = [&xs](int i) {
        assert(0 <= i && i < ~xs);
        return xs[i];
    };

    auto write = [&xs](int i, int x) {
        assert(0 <= i && i < ~xs);
        xs[i] = x;
    };

    write(1, noun);
    write(2, verb);

    int pc = 0;
    for (;;) {
        auto c = xs[pc];
        if (c == 1) {
            auto x = read(pc + 1);
            auto y = read(pc + 2);
            auto z = read(pc + 3);
            write(z, read(x) + read(y));
            pc += 4;
        } else if (c == 2) {
            auto x = read(pc + 1);
            auto y = read(pc + 2);
            auto z = read(pc + 3);
            write(z, read(x) * read(y));
            pc += 4;
        } else if (c == 99) {
            break;
        } else {
            assert(false);
        }
    }
    return xs;
}

int main()
{
    VI xs;
    for (auto p = input; *p != EOD; ++p) {
        xs.push_back(*p);
    }

    // PART1
    auto ys = run(xs, 12, 1);
    printf("ys[0] = %d\n", ys[0]);

    // PART2
    FOR (noun, 0, <= 99) {
        FOR (verb, 0, <= 99) {
            auto ys = run(xs, noun, verb);
            if (ys[0] == 19690720) {
                printf("100 * noun + verb = %d\n", 100 * noun + verb);
            }
        }
    }

    return 0;
}