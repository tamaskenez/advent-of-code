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

    int64_t read_arg(int arg_idx, Mode mode) const
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
    int64_t address_of_arg(int arg_idx, Mode mode) const
    {
        switch (mode) {
            case POSITION_MODE:
                return read(pc + arg_idx);
            case RELATIVE_MODE:
                return read(pc + arg_idx) + relative_base;
            case IMMEDIATE_MODE:
            default:
                assert(false);
        }
        return INT64_MIN;
    }
};

int64_t safe_plus(int64_t x, int64_t y)
{
    if (x > y) {
        swap(x, y);
    }
    if (x < 0) {
        assert(INT64_MIN - x <= y);
    } else {
        assert(y <= INT64_MAX - x);
    }
    return x + y;
}

int64_t safe_mult(int64_t x, int64_t y)
{
    if (x == 0 || y == 0) {
        return 0;
    }
    if (x == INT64_MIN) {
        assert(y == 1);
    } else if (y == INT64_MIN) {
        assert(x == 1);
    } else {
        if (x < 0) {
            x = -x;
            y = -y;
        }
        if (y > 0) {
            // x > 0, y > 0
            assert(y <= INT64_MAX / x);
        } else {
            // x > 0, y < 0
            assert(x <= INT64_MIN / y);
        }
    }
    return x * y;
}

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
            auto z = m.address_of_arg(3, zm);
            m.write(z, safe_plus(x, y));
            m.pc += 4;
        } else if (opcode == 2) {
            auto xm = mode_from_opcode(c, 1);
            auto ym = mode_from_opcode(c, 2);
            auto zm = mode_from_opcode(c, 3);
            auto x = m.read_arg(1, xm);
            auto y = m.read_arg(2, ym);
            auto z = m.address_of_arg(3, zm);
            m.write(z, safe_mult(x, y));
            m.pc += 4;
        } else if (opcode == 3) {
            auto xm = mode_from_opcode(c, 1);
            auto x = m.address_of_arg(1, xm);
            assert(!inputs.empty());
            auto input_value = inputs.front();
            inputs.erase(inputs.begin());
            m.write(x, input_value);
            m.pc += 2;
        } else if (opcode == 4) {
            auto xm = mode_from_opcode(c, 1);
            auto output_value = m.read_arg(1, xm);
            m.pc += 2;
            assert(inputs.empty());
            return output_value;
        } else if (opcode == 5) {
            auto x = m.read_arg(1, mode_from_opcode(c, 1));
            m.pc = x != 0 ? m.read_arg(2, mode_from_opcode(c, 2)) : m.pc + 3;
        } else if (opcode == 6) {
            auto x = m.read_arg(1, mode_from_opcode(c, 1));
            m.pc = x == 0 ? m.read_arg(2, mode_from_opcode(c, 2)) : m.pc + 3;
        } else if (opcode == 7) {
            auto x = m.read_arg(1, mode_from_opcode(c, 1));
            auto y = m.read_arg(2, mode_from_opcode(c, 2));
            auto z = m.address_of_arg(3, mode_from_opcode(c, 3));
            m.write(z, x < y ? 1 : 0);
            m.pc += 4;
        } else if (opcode == 8) {
            auto x = m.read_arg(1, mode_from_opcode(c, 1));
            auto y = m.read_arg(2, mode_from_opcode(c, 2));
            auto z = m.address_of_arg(3, mode_from_opcode(c, 3));
            m.write(z, x == y ? 1 : 0);
            m.pc += 4;
        } else if (opcode == 9) {
            auto x = m.read_arg(1, mode_from_opcode(c, 1));
            auto new_relative_base = m.relative_base + x;
            assert(INT_MIN <= new_relative_base && new_relative_base <= INT_MAX);
            m.relative_base = new_relative_base;
            m.pc += 2;
        } else if (opcode == 99) {
            return {};
        } else {
            assert(false);
        }
    }
    assert(false);
    return {};
}

int main()
{
    VI64 xs = {109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99};
    {
        Machine machine(xs);
        for (int i = 0;; ++i) {
            auto output = run_until_output_or_halt(machine, VI64{});
            if (!output) {
                assert(i == ~xs);
                break;
            }
            assert(*output == xs[i]);
        }
    }

    xs = {1102, 34915192, 34915192, 7, 4, 7, 99, 0};
    {
        Machine machine(xs);
        for (int i = 0;; ++i) {
            auto output = run_until_output_or_halt(machine, VI64{});
            if (!output) {
                break;
            }
            printf("#%d: %s\n", i, to_string(*output).c_str());
        }
    }
    xs = {104, 1125899906842624, 99};
    {
        Machine machine(xs);
        auto output = run_until_output_or_halt(machine, VI64{});
        assert(output);
        assert(*output == 1125899906842624);
    }

    {
        Machine machine(d9_input);
        for (int i = 0;; ++i) {
            auto output = run_until_output_or_halt(machine, i == 0 ? VI64{1} : VI64{});
            if (!output) {
                break;
            }
            printf("Output: %s\n", to_string(*output).c_str());
        }
    }

    {
        Machine machine(d9_input);
        for (int i = 0;; ++i) {
            auto output = run_until_output_or_halt(machine, i == 0 ? VI64{2} : VI64{});
            if (!output) {
                break;
            }
            printf("Output: %s\n", to_string(*output).c_str());
        }
    }
    return 0;
}