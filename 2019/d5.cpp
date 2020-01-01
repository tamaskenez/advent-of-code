#include "common.h"

const int EOD = INT_MIN;
const int input[] = {
    3,    225,   1,     225,   6,    6,     1100,  1,     238,   225,   104,  0,     1101,  72,
    36,   225,   1101,  87,    26,   225,   2,     144,   13,    224,   101,  -1872, 224,   224,
    4,    224,   102,   8,     223,  223,   1001,  224,   2,     224,   1,    223,   224,   223,
    1102, 66,    61,    225,   1102, 25,    49,    224,   101,   -1225, 224,  224,   4,     224,
    1002, 223,   8,     223,   1001, 224,   5,     224,   1,     223,   224,  223,   1101,  35,
    77,   224,   101,   -112,  224,  224,   4,     224,   102,   8,     223,  223,   1001,  224,
    2,    224,   1,     223,   224,  223,   1002,  195,   30,    224,   1001, 224,   -2550, 224,
    4,    224,   1002,  223,   8,    223,   1001,  224,   1,     224,   1,    224,   223,   223,
    1102, 30,    44,    225,   1102, 24,    21,    225,   1,     170,   117,  224,   101,   -46,
    224,  224,   4,     224,   1002, 223,   8,     223,   101,   5,     224,  224,   1,     224,
    223,  223,   1102,  63,    26,   225,   102,   74,    114,   224,   1001, 224,   -3256, 224,
    4,    224,   102,   8,     223,  223,   1001,  224,   3,     224,   1,    224,   223,   223,
    1101, 58,    22,    225,   101,  13,    17,    224,   101,   -100,  224,  224,   4,     224,
    1002, 223,   8,     223,   101,  6,     224,   224,   1,     224,   223,  223,   1101,  85,
    18,   225,   1001,  44,    7,    224,   101,   -68,   224,   224,   4,    224,   102,   8,
    223,  223,   1001,  224,   5,    224,   1,     223,   224,   223,   4,    223,   99,    0,
    0,    0,     677,   0,     0,    0,     0,     0,     0,     0,     0,    0,     0,     0,
    1105, 0,     99999, 1105,  227,  247,   1105,  1,     99999, 1005,  227,  99999, 1005,  0,
    256,  1105,  1,     99999, 1106, 227,   99999, 1106,  0,     265,   1105, 1,     99999, 1006,
    0,    99999, 1006,  227,   274,  1105,  1,     99999, 1105,  1,     280,  1105,  1,     99999,
    1,    225,   225,   225,   1101, 294,   0,     0,     105,   1,     0,    1105,  1,     99999,
    1106, 0,     300,   1105,  1,    99999, 1,     225,   225,   225,   1101, 314,   0,     0,
    106,  0,     0,     1105,  1,    99999, 7,     677,   226,   224,   102,  2,     223,   223,
    1005, 224,   329,   101,   1,    223,   223,   8,     677,   226,   224,  1002,  223,   2,
    223,  1005,  224,   344,   1001, 223,   1,     223,   1107,  677,   677,  224,   102,   2,
    223,  223,   1005,  224,   359,  1001,  223,   1,     223,   1107,  226,  677,   224,   102,
    2,    223,   223,   1005,  224,  374,   101,   1,     223,   223,   7,    226,   677,   224,
    102,  2,     223,   223,   1005, 224,   389,   101,   1,     223,   223,  8,     226,   677,
    224,  1002,  223,   2,     223,  1005,  224,   404,   101,   1,     223,  223,   1008,  226,
    677,  224,   1002,  223,   2,    223,   1005,  224,   419,   1001,  223,  1,     223,   107,
    677,  677,   224,   102,   2,    223,   223,   1005,  224,   434,   101,  1,     223,   223,
    1108, 677,   226,   224,   1002, 223,   2,     223,   1006,  224,   449,  101,   1,     223,
    223,  1108,  677,   677,   224,  102,   2,     223,   223,   1006,  224,  464,   101,   1,
    223,  223,   1007,  677,   226,  224,   102,   2,     223,   223,   1006, 224,   479,   101,
    1,    223,   223,   1008,  226,  226,   224,   102,   2,     223,   223,  1006,  224,   494,
    101,  1,     223,   223,   108,  226,   226,   224,   1002,  223,   2,    223,   1006,  224,
    509,  101,   1,     223,   223,  107,   226,   226,   224,   102,   2,    223,   223,   1006,
    224,  524,   101,   1,     223,  223,   1107,  677,   226,   224,   102,  2,     223,   223,
    1005, 224,   539,   1001,  223,  1,     223,   108,   226,   677,   224,  1002,  223,   2,
    223,  1005,  224,   554,   101,  1,     223,   223,   1007,  226,   226,  224,   102,   2,
    223,  223,   1005,  224,   569,  101,   1,     223,   223,   8,     226,  226,   224,   102,
    2,    223,   223,   1006,  224,  584,   101,   1,     223,   223,   1008, 677,   677,   224,
    1002, 223,   2,     223,   1005, 224,   599,   1001,  223,   1,     223,  107,   226,   677,
    224,  1002,  223,   2,     223,  1005,  224,   614,   1001,  223,   1,    223,   1108,  226,
    677,  224,   102,   2,     223,  223,   1006,  224,   629,   101,   1,    223,   223,   7,
    677,  677,   224,   1002,  223,  2,     223,   1005,  224,   644,   1001, 223,   1,     223,
    108,  677,   677,   224,   102,  2,     223,   223,   1005,  224,   659,  101,   1,     223,
    223,  1007,  677,   677,   224,  102,   2,     223,   223,   1006,  224,  674,   101,   1,
    223,  223,   4,     223,   99,   226,   EOD};

bool imode(int c, int par)
{
    int m;
    switch (par) {
        case 1:
            m = (c / 100) % 10;
            break;
        case 2:
            m = (c / 1000) % 10;
            break;
        case 3:
            m = (c / 10000) % 10;
            break;
        default:
            assert(false);
    }
    assert(m == 0 || m == 1);
    return m == 1;
}

VI run(VI xs, optional<int> input_value)
{
    auto read = [&xs](int i, bool im = true) {
        assert(0 <= i && i < ~xs);
        auto xsi = xs[i];
        if (im) {
            return xsi;
        }
        assert(0 <= xsi && xsi < ~xs);
        return xs[xsi];
    };

    auto write = [&xs](int i, int x) {
        assert(0 <= i && i < ~xs);
        xs[i] = x;
    };

    int pc = 0;
    VI output_values;
    for (;;) {
        auto c = xs[pc];
        int opcode = c % 100;
        if (opcode == 1) {
            auto xm = imode(c, 1);
            auto ym = imode(c, 2);
            assert(!imode(c, 3));
            auto x = read(pc + 1, xm);
            auto y = read(pc + 2, ym);
            auto z = read(pc + 3);
            write(z, x + y);
            pc += 4;
        } else if (opcode == 2) {
            auto xm = imode(c, 1);
            auto ym = imode(c, 2);
            assert(!imode(c, 3));
            auto x = read(pc + 1, xm);
            auto y = read(pc + 2, ym);
            auto z = read(pc + 3);
            write(z, x * y);
            pc += 4;
        } else if (opcode == 3) {
            assert(!imode(c, 1));
            auto x = read(pc + 1);
            write(x, *input_value);
            pc += 2;
        } else if (opcode == 4) {
            auto xm = imode(c, 1);
            output_values.push_back(read(pc + 1, xm));
            pc += 2;
        } else if (opcode == 5) {
            auto x = read(pc + 1, imode(c, 1));
            pc = x != 0 ? read(pc + 2, imode(c, 2)) : pc + 3;
        } else if (opcode == 6) {
            auto x = read(pc + 1, imode(c, 1));
            pc = x == 0 ? read(pc + 2, imode(c, 2)) : pc + 3;
        } else if (opcode == 7) {
            auto x = read(pc + 1, imode(c, 1));
            auto y = read(pc + 2, imode(c, 2));
            assert(!imode(c, 3));
            write(read(pc + 3), x < y ? 1 : 0);
            pc += 4;
        } else if (opcode == 8) {
            auto x = read(pc + 1, imode(c, 1));
            auto y = read(pc + 2, imode(c, 2));
            assert(!imode(c, 3));
            write(read(pc + 3), x == y ? 1 : 0);
            pc += 4;
        } else if (opcode == 99) {
            break;
        } else {
            assert(false);
        }
    }
    return output_values;
}

int main()
{
    VI xs;

    // Using position mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if
    // it is not).
    xs = {3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    assert(run(xs, 7) == VI{0});
    assert(run(xs, 8) == VI{1});
    assert(run(xs, 9) == VI{0});

    // Using position mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if
    // it is not).
    xs = {3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8};
    assert(run(xs, 7) == VI{1});
    assert(run(xs, 8) == VI{0});
    assert(run(xs, 9) == VI{0});

    // Using immediate mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if
    // it is not).
    xs = {3, 3, 1108, -1, 8, 3, 4, 3, 99};
    assert(run(xs, 7) == VI{0});
    assert(run(xs, 8) == VI{1});
    assert(run(xs, 9) == VI{0});

    // Using immediate mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if
    // it is not).
    xs = {3, 3, 1107, -1, 8, 3, 4, 3, 99};
    assert(run(xs, 7) == VI{1});
    assert(run(xs, 8) == VI{0});
    assert(run(xs, 9) == VI{0});

    //    Here are some jump tests that take an input, then output 0 if the input was zero or 1 if
    //    the input was non-zero:

    xs = {3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    assert(run(xs, -1) == VI{1});
    assert(run(xs, 0) == VI{0});
    assert(run(xs, 1) == VI{1});
    xs = {3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    assert(run(xs, -1) == VI{1});
    assert(run(xs, 0) == VI{0});
    assert(run(xs, 1) == VI{1});

    xs = {3,    21,   1008, 21, 8,    20,   1005, 20, 22,  107, 8,    21, 20,   1006, 20, 31,
          1106, 0,    36,   98, 0,    0,    1002, 21, 125, 20,  4,    20, 1105, 1,    46, 104,
          999,  1105, 1,    46, 1101, 1000, 1,    20, 4,   20,  1105, 1,  46,   98,   99};
    assert(run(xs, 7) == VI{999});
    assert(run(xs, 8) == VI{1000});
    assert(run(xs, 9) == VI{1001});

    xs.clear();
    for (auto p = input; *p != EOD; ++p) {
        xs.push_back(*p);
    }

    for (auto input_value : {1, 5}) {
        printf("input_value: %d\n", input_value);
        auto output_values = run(xs, input_value);
        printf("output values: [");
        for (auto o : output_values) {
            printf("%d ", o);
        }
        printf("]\n");
    }
    return 0;
}