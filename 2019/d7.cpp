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

VI run(VI xs, VI& inputs)
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
            assert(!inputs.empty());
            auto input_value = inputs.front();
            inputs.erase(inputs.begin());
            write(x, input_value);
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

struct Machine
{
    VI mem;
    int pc = 0;
    explicit Machine(VI mem) : mem(move(mem)) {}
};

// Run until output or halt.
// Consume all the inputs.
// Return output or nothing.
optional<int> run_until_output_or_halt(Machine& m, VI inputs)
{
    auto read = [&m](int i, bool im = true) {
        assert(0 <= i && i < ~m.mem);
        auto xsi = m.mem[i];
        if (im) {
            return xsi;
        }
        assert(0 <= xsi && xsi < ~m.mem);
        return m.mem[xsi];
    };

    auto write = [&m](int i, int x) {
        assert(0 <= i && i < ~m.mem);
        m.mem[i] = x;
    };

    for (;;) {
        auto c = read(m.pc);
        int opcode = c % 100;
        if (opcode == 1) {
            auto xm = imode(c, 1);
            auto ym = imode(c, 2);
            assert(!imode(c, 3));
            auto x = read(m.pc + 1, xm);
            auto y = read(m.pc + 2, ym);
            auto z = read(m.pc + 3);
            auto xy = (int64_t)x + (int64_t)y;
            assert(INT_MIN <= xy && xy <= INT_MAX);
            write(z, (int)xy);
            m.pc += 4;
        } else if (opcode == 2) {
            auto xm = imode(c, 1);
            auto ym = imode(c, 2);
            assert(!imode(c, 3));
            auto x = read(m.pc + 1, xm);
            auto y = read(m.pc + 2, ym);
            auto z = read(m.pc + 3);
            auto xy = (int64_t)x * (int64_t)y;
            assert(INT_MIN <= xy && xy <= INT_MAX);
            write(z, (int)xy);
            m.pc += 4;
        } else if (opcode == 3) {
            assert(!imode(c, 1));
            auto x = read(m.pc + 1);
            assert(!inputs.empty());
            auto input_value = inputs.front();
            inputs.erase(inputs.begin());
            write(x, input_value);
            m.pc += 2;
        } else if (opcode == 4) {
            auto xm = imode(c, 1);
            auto output_value = read(m.pc + 1, xm);
            m.pc += 2;
            assert(inputs.empty());
            return output_value;
        } else if (opcode == 5) {
            auto x = read(m.pc + 1, imode(c, 1));
            m.pc = x != 0 ? read(m.pc + 2, imode(c, 2)) : m.pc + 3;
        } else if (opcode == 6) {
            auto x = read(m.pc + 1, imode(c, 1));
            m.pc = x == 0 ? read(m.pc + 2, imode(c, 2)) : m.pc + 3;
        } else if (opcode == 7) {
            auto x = read(m.pc + 1, imode(c, 1));
            auto y = read(m.pc + 2, imode(c, 2));
            assert(!imode(c, 3));
            write(read(m.pc + 3), x < y ? 1 : 0);
            m.pc += 4;
        } else if (opcode == 8) {
            auto x = read(m.pc + 1, imode(c, 1));
            auto y = read(m.pc + 2, imode(c, 2));
            assert(!imode(c, 3));
            write(read(m.pc + 3), x == y ? 1 : 0);
            m.pc += 4;
        } else if (opcode == 99) {
            return {};
        } else {
            assert(false);
        }
    }
    assert(false);
    return {};
}

int run_amps(const VI& xs, const VI phases)
{
    int signal = 0;
    for (auto phase : phases) {
        auto inputs = VI{phase, signal};
        auto outputs = run(xs, inputs);
        assert(inputs.empty());
        assert(~outputs == 1);
        signal = outputs[0];
    }
    return signal;
}

int run_amps_feedback(const VI& xs, const VI phases)
{
    vector<Machine> machines;
    for (auto phase : phases) {
        machines.emplace_back(xs);
    }
    int signal = 0;
    FOR (i, 0, < ~phases) {
        auto output = run_until_output_or_halt(machines[i], VI{phases[i], signal});
        assert(output);
        signal = *output;
    }
    int idx = 0;
    for (;; idx = (idx + 1) % ~phases) {
        auto output = run_until_output_or_halt(machines[idx], VI{signal});
        if (!output) {
            break;
        }
        signal = *output;
    }
    return signal;
}

int main()
{
    VI xs;
    xs = {3, 15, 3, 16, 1002, 16, 10, 16, 1, 16, 15, 15, 4, 15, 99, 0, 0};
    int signal = run_amps(xs, {4, 3, 2, 1, 0});
    assert(signal == 43210);

    xs = {3, 23, 3,  24, 1002, 24, 10, 24, 1002, 23, -1, 23, 101,
          5, 23, 23, 1,  24,   23, 23, 4,  23,   99, 0,  0};
    signal = run_amps(xs, {0, 1, 2, 3, 4});
    assert(signal == 54321);

    xs = {3,  31, 3,  32, 1002, 32, 10, 32, 1001, 31, -2, 31, 1007, 31, 0, 33, 1002,
          33, 7,  33, 1,  33,   31, 31, 1,  32,   31, 31, 4,  31,   99, 0, 0,  0};
    signal = run_amps(xs, {1, 0, 4, 3, 2});
    assert(signal == 65210);

    const VI xs0 = {
        3,    8,    1001, 8,    10,   8,     105,  1,    0,    0,    21,   46,  55,   76,  89,
        106,  187,  268,  349,  430,  99999, 3,    9,    101,  4,    9,    9,   1002, 9,   2,
        9,    101,  5,    9,    9,    1002,  9,    2,    9,    101,  2,    9,   9,    4,   9,
        99,   3,    9,    1002, 9,    5,     9,    4,    9,    99,   3,    9,   1001, 9,   2,
        9,    1002, 9,    4,    9,    101,   2,    9,    9,    1002, 9,    3,   9,    4,   9,
        99,   3,    9,    1001, 9,    3,     9,    1002, 9,    2,    9,    4,   9,    99,  3,
        9,    1002, 9,    4,    9,    1001,  9,    4,    9,    102,  5,    9,   9,    4,   9,
        99,   3,    9,    101,  1,    9,     9,    4,    9,    3,    9,    102, 2,    9,   9,
        4,    9,    3,    9,    1001, 9,     2,    9,    4,    9,    3,    9,   101,  2,   9,
        9,    4,    9,    3,    9,    1001,  9,    1,    9,    4,    9,    3,   9,    101, 1,
        9,    9,    4,    9,    3,    9,     102,  2,    9,    9,    4,    9,   3,    9,   102,
        2,    9,    9,    4,    9,    3,     9,    1002, 9,    2,    9,    4,   9,    3,   9,
        101,  1,    9,    9,    4,    9,     99,   3,    9,    102,  2,    9,   9,    4,   9,
        3,    9,    1002, 9,    2,    9,     4,    9,    3,    9,    101,  1,   9,    9,   4,
        9,    3,    9,    101,  2,    9,     9,    4,    9,    3,    9,    102, 2,    9,   9,
        4,    9,    3,    9,    102,  2,     9,    9,    4,    9,    3,    9,   102,  2,   9,
        9,    4,    9,    3,    9,    1001,  9,    1,    9,    4,    9,    3,   9,    101, 2,
        9,    9,    4,    9,    3,    9,     1002, 9,    2,    9,    4,    9,   99,   3,   9,
        101,  1,    9,    9,    4,    9,     3,    9,    101,  1,    9,    9,   4,    9,   3,
        9,    101,  2,    9,    9,    4,     9,    3,    9,    1002, 9,    2,   9,    4,   9,
        3,    9,    1001, 9,    2,    9,     4,    9,    3,    9,    1001, 9,   1,    9,   4,
        9,    3,    9,    1001, 9,    2,     9,    4,    9,    3,    9,    102, 2,    9,   9,
        4,    9,    3,    9,    102,  2,     9,    9,    4,    9,    3,    9,   102,  2,   9,
        9,    4,    9,    99,   3,    9,     101,  1,    9,    9,    4,    9,   3,    9,   102,
        2,    9,    9,    4,    9,    3,     9,    101,  2,    9,    9,    4,   9,    3,   9,
        101,  1,    9,    9,    4,    9,     3,    9,    102,  2,    9,    9,   4,    9,   3,
        9,    1002, 9,    2,    9,    4,     9,    3,    9,    102,  2,    9,   9,    4,   9,
        3,    9,    1001, 9,    2,    9,     4,    9,    3,    9,    102,  2,   9,    9,   4,
        9,    3,    9,    101,  1,    9,     9,    4,    9,    99,   3,    9,   1001, 9,   1,
        9,    4,    9,    3,    9,    1001,  9,    1,    9,    4,    9,    3,   9,    102, 2,
        9,    9,    4,    9,    3,    9,     102,  2,    9,    9,    4,    9,   3,    9,   1001,
        9,    1,    9,    4,    9,    3,     9,    1001, 9,    1,    9,    4,   9,    3,   9,
        1001, 9,    1,    9,    4,    9,     3,    9,    1002, 9,    2,    9,   4,    9,   3,
        9,    101,  2,    9,    9,    4,     9,    3,    9,    101,  1,    9,   9,    4,   9,
        99};

    xs = xs0;
    VI phases{0, 1, 2, 3, 4};
    int best_signal = INT_MIN;
    do {
        signal = run_amps(xs, phases);
        if (signal > best_signal) {
            best_signal = signal;
        }
    } while (std::next_permutation(BE(phases)));
    printf("best_signal: %d\n", best_signal);

    xs = {3,  26, 1001, 26,   -4, 26, 3,  27,   1002, 27, 2,  27, 1, 27, 26,
          27, 4,  27,   1001, 28, -1, 28, 1005, 28,   6,  99, 0,  0, 5};
    signal = run_amps_feedback(xs, {9, 8, 7, 6, 5});
    assert(signal == 139629729);

    xs = {3,    52,   1001, 52,   -5,   52, 3,  53, 1,    52, 56, 54, 1007, 54, 5,
          55,   1005, 55,   26,   1001, 54, -5, 54, 1105, 1,  12, 1,  53,   54, 53,
          1008, 54,   0,    55,   1001, 55, 1,  55, 2,    53, 55, 53, 4,    53, 1001,
          56,   -1,   56,   1005, 56,   6,  99, 0,  0,    0,  0,  10};
    signal = run_amps_feedback(xs, {9, 7, 8, 5, 6});
    assert(signal == 18216);

    xs = xs0;
    phases = {5, 6, 7, 8, 9};
    best_signal = INT_MIN;
    do {
        signal = run_amps_feedback(xs, phases);
        if (signal > best_signal) {
            best_signal = signal;
        }
    } while (std::next_permutation(BE(phases)));
    printf("best_signal: %d\n", best_signal);
    return 0;
}