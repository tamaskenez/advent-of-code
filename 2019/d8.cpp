HAS BEEN DESTROYED ON D9
#include "common.h"

    using VI64 = vector<int64_t>;

const VI64 d9_input = {
    1102, 34463338, 34463338, 63,    1007,  63,    34463338, 63,    1005,  63,    53,    1101,
    3,    0,        1000,     109,   988,   209,   12,       9,     1000,  209,   6,     209,
    3,    203,      0,        1008,  1000,  1,     63,       1005,  63,    65,    1008,  1000,
    2,    63,       1005,     63,    904,   1008,  1000,     0,     63,    1005,  63,    58,
    4,    25,       104,      0,     99,    4,     0,        104,   0,     99,    4,     17,
    104,  0,        99,       0,     0,     1102,  1,        31,    1018,  1102,  352,   1,
    1023, 1101,     0,        1,     1021,  1101,  0,        33,    1003,  1102,  1,     36,
    1007, 1102,     21,       1,     1005,  1101,  359,      0,     1022,  1101,  0,     787,
    1024, 1102,     1,        24,    1011,  1101,  30,       0,     1014,  1101,  22,    0,
    1016, 1101,     0,        0,     1020,  1102,  1,        29,    1000,  1101,  778,   0,
    1025, 1102,     23,       1,     1017,  1102,  1,        28,    1002,  1101,  38,    0,
    1019, 1102,     1,        27,    1013,  1102,  1,        32,    1012,  1101,  0,     37,
    1006, 1101,     444,      0,     1027,  1102,  1,        20,    1009,  1101,  0,     447,
    1026, 1101,     0,        39,    1008,  1101,  35,       0,     1010,  1102,  559,   1,
    1028, 1102,     26,       1,     1004,  1102,  1,        25,    1015,  1102,  1,     34,
    1001, 1101,     0,        554,   1029,  109,   -3,       2101,  0,     9,     63,    1008,
    63,   34,       63,       1005,  63,    205,   1001,     64,    1,     64,    1105,  1,
    207,  4,        187,      1002,  64,    2,     64,       109,   23,    21107, 40,    39,
    -7,   1005,     1013,     227,   1001,  64,    1,        64,    1106,  0,     229,   4,
    213,  1002,     64,       2,     64,    109,   -17,      1202,  -2,    1,     63,    1008,
    63,   36,       63,       1005,  63,    249,   1106,     0,     255,   4,     235,   1001,
    64,   1,        64,       1002,  64,    2,     64,       109,   -6,    1202,  10,    1,
    63,   1008,     63,       36,    63,    1005,  63,       277,   4,     261,   1106,  0,
    281,  1001,     64,       1,     64,    1002,  64,       2,     64,    109,   -2,    1208,
    9,    26,       63,       1005,  63,    303,   4,        287,   1001,  64,    1,     64,
    1106, 0,        303,      1002,  64,    2,     64,       109,   32,    1206,  -7,    321,
    4,    309,      1001,     64,    1,     64,    1106,     0,     321,   1002,  64,    2,
    64,   109,      -29,      1207,  7,     20,    63,       1005,  63,    337,   1105,  1,
    343,  4,        327,      1001,  64,    1,     64,       1002,  64,    2,     64,    109,
    27,   2105,     1,        -2,    1001,  64,    1,        64,    1106,  0,     361,   4,
    349,  1002,     64,       2,     64,    109,   -25,      2108,  39,    7,     63,    1005,
    63,   377,      1106,     0,     383,   4,     367,      1001,  64,    1,     64,    1002,
    64,   2,        64,       109,   1,     1201,  6,        0,     63,    1008,  63,    36,
    63,   1005,     63,       409,   4,     389,   1001,     64,    1,     64,    1105,  1,
    409,  1002,     64,       2,     64,    109,   1,        2102,  1,     1,     63,    1008,
    63,   33,       63,       1005,  63,    435,   4,        415,   1001,  64,    1,     64,
    1105, 1,        435,      1002,  64,    2,     64,       109,   28,    2106,  0,     -3,
    1106, 0,        453,      4,     441,   1001,  64,       1,     64,    1002,  64,    2,
    64,   109,      -13,      21101, 41,    0,     1,        1008,  1018,  44,    63,    1005,
    63,   477,      1001,     64,    1,     64,    1106,     0,     479,   4,     459,   1002,
    64,   2,        64,       109,   4,     21108, 42,       42,    -2,    1005,  1019,  501,
    4,    485,      1001,     64,    1,     64,    1106,     0,     501,   1002,  64,    2,
    64,   109,      -21,      2101,  0,     2,     63,       1008,  63,    28,    63,    1005,
    63,   523,      4,        507,   1105,  1,     527,      1001,  64,    1,     64,    1002,
    64,   2,        64,       109,   26,    1205,  -5,       545,   4,     533,   1001,  64,
    1,    64,       1105,     1,     545,   1002,  64,       2,     64,    109,   3,     2106,
    0,    -1,       4,        551,   1106,  0,     563,      1001,  64,    1,     64,    1002,
    64,   2,        64,       109,   -33,   1201,  4,        0,     63,    1008,  63,    28,
    63,   1005,     63,       583,   1105,  1,     589,      4,     569,   1001,  64,    1,
    64,   1002,     64,       2,     64,    109,   11,       2107,  27,    -3,    63,    1005,
    63,   609,      1001,     64,    1,     64,    1106,     0,     611,   4,     595,   1002,
    64,   2,        64,       109,   8,     21102, 43,       1,     3,     1008,  1018,  43,
    63,   1005,     63,       637,   4,     617,   1001,     64,    1,     64,    1105,  1,
    637,  1002,     64,       2,     64,    109,   -5,       21108, 44,    41,    0,     1005,
    1010, 653,      1105,     1,     659,   4,     643,      1001,  64,    1,     64,    1002,
    64,   2,        64,       109,   -13,   2108,  21,       8,     63,    1005,  63,    681,
    4,    665,      1001,     64,    1,     64,    1106,     0,     681,   1002,  64,    2,
    64,   109,      6,        1207,  0,     34,    63,       1005,  63,    703,   4,     687,
    1001, 64,       1,        64,    1105,  1,     703,      1002,  64,    2,     64,    109,
    7,    1208,     -7,       35,    63,    1005,  63,       723,   1001,  64,    1,     64,
    1106, 0,        725,      4,     709,   1002,  64,       2,     64,    109,   -13,   2102,
    1,    7,        63,       1008,  63,    23,    63,       1005,  63,    745,   1105,  1,
    751,  4,        731,      1001,  64,    1,     64,       1002,  64,    2,     64,    109,
    13,   1205,     10,       767,   1001,  64,    1,        64,    1105,  1,     769,   4,
    757,  1002,     64,       2,     64,    109,   14,       2105,  1,     0,     4,     775,
    1001, 64,       1,        64,    1106,  0,     787,      1002,  64,    2,     64,    109,
    -20,  21107,    45,       46,    7,     1005,  1011,     809,   4,     793,   1001,  64,
    1,    64,       1105,     1,     809,   1002,  64,       2,     64,    109,   -3,    2107,
    25,   3,        63,       1005,  63,    827,   4,        815,   1106,  0,     831,   1001,
    64,   1,        64,       1002,  64,    2,     64,       109,   13,    1206,  7,     847,
    1001, 64,       1,        64,    1106,  0,     849,      4,     837,   1002,  64,    2,
    64,   109,      -11,      21101, 46,    0,     7,        1008,  1010,  46,    63,    1005,
    63,   871,      4,        855,   1106,  0,     875,      1001,  64,    1,     64,    1002,
    64,   2,        64,       109,   15,    21102, 47,       1,     -4,    1008,  1014,  48,
    63,   1005,     63,       895,   1106,  0,     901,      4,     881,   1001,  64,    1,
    64,   4,        64,       99,    21102, 27,    1,        1,     21101, 0,     915,   0,
    1106, 0,        922,      21201, 1,     63208, 1,        204,   1,     99,    109,   3,
    1207, -2,       3,        63,    1005,  63,    964,      21201, -2,    -1,    1,     21102,
    1,    942,      0,        1106,  0,     922,   21202,    1,     1,     -1,    21201, -2,
    -3,   1,        21101,    957,   0,     0,     1105,     1,     922,   22201, 1,     -1,
    -2,   1106,     0,        968,   21201, -2,    0,        -2,    109,   -3,    2106,  0,
    0};

enum Mode
{
    POSITION_MODE = 0,
    IMMEDIATE_MODE = 1,
    RELATIVE_MODE = 2,
    INVALID_MODE = INT_MIN
};

Mode mode_from_opcode(int64_t opcode, int64_t par_idx)
{
    int64_t m;
    switch (par_idx) {
        case 1:
            m = (opcode / 100) % 10;
            break;
        case 2:
            m = (opcode / 1000) % 10;
            break;
        case 3:
            m = (opcode / 10000) % 10;
            break;
        default:
            assert(false);
    }
    switch (m) {
        case 0:
            return POSITION_MODE;
        case 1:
            return IMMEDIATE_MODE;
        case 2:
            return RELATIVE_MODE;
        default:
            assert(false);
    }
    return INVALID_MODE;
}

struct Machine
{
    VI64 mem;
    int pc = 0;
    int relative_base = 0;
    explicit Machine(VI64 mem) : mem(move(mem)) {}

    int64_t read(int address) const
    {
        assert(0 <= address);
        return address < ~mem ? mem[address] : (int64_t)0;
    };

    void write(int address, int64_t x)
    {
        assert(0 <= address);
        if (address >= ~mem) {
            assert(address < 10e6);
            mem.resize(address + 1, 0);
        }
        mem[address] = x;
    };

    int64_t read_arg(int arg_idx, Mode mode)
    {
        switch (mode) {
            case POSITION_MODE:
                return read(read(pc + arg_idx));
            case IMMEDIATE_MODE:
                return read(pc + arg_idx);
            case RELATIVE_MODE:
                return read(read(pc + arg_idx) + relative_base);
            default:
                assert(false);
        }
        return INT64_MIN;
    }
    int64_t read_address_arg(int arg_idx, Mode mode)
    {
        switch (mode) {
            case POSITION_MODE:
                return read(read(pc + arg_idx));
                return read(pc + arg_idx);
            case RELATIVE_MODE:
                return read(read(pc + arg_idx) + relative_base);
            case IMMEDIATE_MODE:
            default:
                assert(false);
        }
        return INT64_MIN;
    }
};

// Run until output or halt.
// Consume all the inputs.
// Return output or nothing when it halts.
optional<int64_t> run_until_output_or_halt(Machine& m, VI64 inputs)
{
    for (;;) {
        auto c = m.read(m.pc);
        int opcode = c % 100;
        if (opcode == 1) {
            auto xm = mode_from_opcode(c, 1);
            auto ym = mode_from_opcode(c, 2);
            auto zm = mode_from_opcode(c, 3);
            auto x = m.read_arg(1, xm);
            auto y = m.read_arg(2, ym);
            auto z = m.read_address_arg(3, zm);
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