#include <set>

#include "common.h"

using VI64 = vector<int64_t>;

// clang-format off
const VI64 input = {1,380,379,385,1008,2575,987010,381,1005,381,12,99,109,2576,1101,0,0,383,1102,0,1,382,21002,382,1,1,20102,1,383,2,21102,1,37,0,1105,1,578,4,382,4,383,204,1,1001,382,1,382,1007,382,44,381,1005,381,22,1001,383,1,383,1007,383,22,381,1005,381,18,1006,385,69,99,104,-1,104,0,4,386,3,384,1007,384,0,381,1005,381,94,107,0,384,381,1005,381,108,1106,0,161,107,1,392,381,1006,381,161,1102,-1,1,384,1106,0,119,1007,392,42,381,1006,381,161,1102,1,1,384,20102,1,392,1,21101,0,20,2,21101,0,0,3,21102,138,1,0,1106,0,549,1,392,384,392,20102,1,392,1,21102,1,20,2,21101,0,3,3,21101,161,0,0,1105,1,549,1101,0,0,384,20001,388,390,1,20101,0,389,2,21101,180,0,0,1106,0,578,1206,1,213,1208,1,2,381,1006,381,205,20001,388,390,1,20102,1,389,2,21101,0,205,0,1106,0,393,1002,390,-1,390,1101,0,1,384,20102,1,388,1,20001,389,391,2,21101,228,0,0,1105,1,578,1206,1,261,1208,1,2,381,1006,381,253,21002,388,1,1,20001,389,391,2,21101,0,253,0,1106,0,393,1002,391,-1,391,1102,1,1,384,1005,384,161,20001,388,390,1,20001,389,391,2,21102,1,279,0,1106,0,578,1206,1,316,1208,1,2,381,1006,381,304,20001,388,390,1,20001,389,391,2,21102,1,304,0,1105,1,393,1002,390,-1,390,1002,391,-1,391,1102,1,1,384,1005,384,161,21002,388,1,1,21001,389,0,2,21101,0,0,3,21101,338,0,0,1105,1,549,1,388,390,388,1,389,391,389,20101,0,388,1,21002,389,1,2,21101,4,0,3,21101,0,365,0,1105,1,549,1007,389,21,381,1005,381,75,104,-1,104,0,104,0,99,0,1,0,0,0,0,0,0,239,20,17,1,1,22,109,3,21201,-2,0,1,22101,0,-1,2,21102,0,1,3,21102,1,414,0,1106,0,549,22101,0,-2,1,22101,0,-1,2,21101,0,429,0,1106,0,601,1202,1,1,435,1,386,0,386,104,-1,104,0,4,386,1001,387,-1,387,1005,387,451,99,109,-3,2106,0,0,109,8,22202,-7,-6,-3,22201,-3,-5,-3,21202,-4,64,-2,2207,-3,-2,381,1005,381,492,21202,-2,-1,-1,22201,-3,-1,-3,2207,-3,-2,381,1006,381,481,21202,-4,8,-2,2207,-3,-2,381,1005,381,518,21202,-2,-1,-1,22201,-3,-1,-3,2207,-3,-2,381,1006,381,507,2207,-3,-4,381,1005,381,540,21202,-4,-1,-1,22201,-3,-1,-3,2207,-3,-4,381,1006,381,529,22102,1,-3,-7,109,-8,2105,1,0,109,4,1202,-2,44,566,201,-3,566,566,101,639,566,566,2101,0,-1,0,204,-3,204,-2,204,-1,109,-4,2106,0,0,109,3,1202,-1,44,593,201,-2,593,593,101,639,593,593,21001,0,0,-2,109,-3,2106,0,0,109,3,22102,22,-2,1,22201,1,-1,1,21102,1,487,2,21101,744,0,3,21101,968,0,4,21102,1,630,0,1106,0,456,21201,1,1607,-2,109,-3,2105,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,2,2,0,0,2,0,2,2,2,2,0,0,2,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,0,2,2,2,0,0,0,0,0,0,0,1,1,0,0,0,2,0,0,2,2,0,0,2,0,2,0,2,2,2,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,2,2,2,0,2,2,0,0,1,1,0,0,0,2,0,2,2,2,2,0,0,0,0,2,2,0,2,0,2,0,2,2,2,2,0,2,2,2,0,0,2,2,0,0,2,0,0,2,2,2,2,0,1,1,0,2,2,0,2,0,2,2,2,2,0,0,2,2,0,0,0,0,0,0,0,2,2,2,2,2,0,2,2,0,2,2,2,2,0,0,0,2,0,0,2,0,1,1,0,0,2,0,0,2,0,0,0,0,0,2,0,0,2,2,0,0,0,0,0,2,0,0,0,2,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,0,1,1,0,2,0,2,2,0,2,0,0,0,0,0,0,2,0,2,0,0,0,0,0,2,0,0,2,2,0,0,0,0,2,2,0,0,0,2,2,0,0,2,0,0,1,1,0,0,0,2,2,2,0,2,0,2,0,0,2,0,0,2,0,0,0,2,0,0,2,0,2,0,0,0,0,2,0,0,2,2,0,2,2,0,0,2,0,0,1,1,0,0,2,0,2,0,2,0,2,2,0,0,2,2,0,0,0,0,0,2,0,2,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,1,1,0,0,2,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,2,2,0,0,2,2,2,0,0,2,2,2,2,2,0,0,0,1,1,0,2,0,2,0,0,0,2,0,0,0,2,2,0,0,2,0,0,0,0,0,0,0,2,2,0,2,2,0,2,0,2,0,0,0,2,2,0,0,0,0,0,1,1,0,2,2,0,0,0,2,2,0,0,0,0,2,0,0,2,0,2,2,2,0,0,0,2,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,1,1,0,0,0,2,2,2,2,0,2,2,2,0,0,2,2,2,2,0,0,2,0,2,0,0,0,0,2,2,2,2,2,2,0,2,2,2,0,0,2,2,2,0,1,1,0,2,0,2,2,0,2,0,0,2,0,2,2,0,0,0,2,0,0,0,0,0,2,2,2,0,0,2,0,2,2,0,0,2,2,2,0,2,2,0,0,0,1,1,0,0,2,0,0,2,2,0,0,2,2,2,0,0,0,0,0,2,2,0,0,0,2,0,2,0,0,0,0,2,2,0,0,0,0,0,2,0,0,2,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,57,82,58,90,4,73,33,23,24,29,55,37,9,40,59,69,10,33,96,78,20,58,37,47,72,45,47,56,93,19,16,83,93,11,32,43,50,31,7,12,5,78,48,96,41,7,16,29,13,73,66,66,92,19,23,43,96,4,16,93,75,60,8,73,91,76,9,88,82,70,92,77,46,8,65,93,47,32,89,1,36,54,7,32,62,28,7,45,82,37,84,88,54,9,73,91,65,94,81,31,32,88,16,47,10,57,20,80,81,63,4,37,98,58,78,66,58,40,47,33,27,4,21,36,55,38,6,5,12,71,20,85,7,26,28,55,12,69,86,5,9,9,32,12,47,65,98,1,48,40,31,84,67,67,43,97,52,62,20,91,76,31,75,98,55,35,43,69,37,46,5,51,96,10,49,91,32,44,96,63,25,80,90,47,58,37,81,82,30,18,90,69,80,85,46,68,91,78,97,54,44,18,38,78,11,21,1,55,66,4,55,52,74,53,61,6,70,43,86,97,97,36,98,58,18,14,29,84,13,78,60,57,20,55,18,82,82,84,83,24,18,15,43,39,55,61,29,2,15,45,7,51,9,26,88,51,70,11,20,21,74,23,60,76,14,16,42,80,45,81,49,4,29,2,45,6,13,54,48,91,78,7,88,27,82,10,28,70,46,56,93,3,26,19,41,46,34,39,43,22,8,48,13,68,38,50,70,1,17,78,16,46,86,32,47,83,46,47,63,61,22,10,45,6,97,52,88,54,10,47,28,47,79,31,10,89,79,44,83,77,23,85,46,76,68,20,13,40,94,51,40,75,65,69,88,76,13,94,25,38,68,40,96,25,26,9,7,51,17,84,24,90,94,13,62,27,28,4,55,80,2,86,83,76,73,62,66,90,71,54,26,78,36,6,66,58,89,42,44,94,92,46,91,68,98,38,37,49,28,74,80,23,3,42,42,90,1,38,52,59,48,65,50,98,90,39,21,16,20,25,57,36,53,49,79,79,14,85,39,9,24,58,9,19,72,70,2,10,43,7,58,66,84,70,29,18,97,76,16,56,91,1,32,23,89,20,96,27,40,71,35,42,79,80,61,97,78,2,81,6,51,87,23,47,73,84,57,16,87,42,66,79,33,28,30,34,16,92,22,60,68,34,26,47,50,52,32,80,18,40,48,59,23,24,80,49,14,61,93,66,35,14,68,52,24,21,7,27,65,57,63,91,18,93,7,84,56,51,31,38,28,90,52,5,61,37,81,44,17,79,63,50,54,56,58,7,39,96,80,27,53,73,27,77,59,37,37,24,30,22,47,57,84,76,27,20,1,16,83,96,82,40,55,44,77,1,60,59,94,8,12,40,75,94,65,40,34,35,13,69,46,79,52,73,23,79,25,73,81,75,33,94,57,45,92,41,82,76,86,5,34,16,47,42,61,25,70,52,54,28,12,57,3,61,80,50,65,42,94,97,97,65,50,89,94,7,21,1,21,68,69,75,13,2,64,67,32,85,73,72,7,49,43,92,59,90,4,12,98,28,53,36,97,53,11,45,21,24,74,11,85,3,11,47,54,5,47,22,98,18,30,82,1,79,59,3,27,25,70,6,79,94,85,17,58,4,23,33,64,40,56,43,14,77,98,75,13,33,45,12,22,6,46,33,48,62,77,50,40,65,88,8,50,43,67,41,2,74,81,44,66,59,52,86,51,35,4,24,58,56,85,57,58,81,41,24,63,73,80,21,63,90,69,94,36,26,85,12,86,64,1,5,35,58,36,29,75,82,15,18,63,73,16,4,62,53,30,91,85,42,46,13,57,53,24,93,91,28,10,19,94,44,82,24,57,24,85,23,6,34,83,83,63,84,65,51,72,54,85,70,40,26,76,76,31,19,93,65,25,63,88,10,3,53,62,31,12,39,42,18,23,26,27,27,56,9,82,50,86,23,5,44,24,86,62,31,6,59,70,53,29,67,82,41,51,51,39,47,14,26,88,5,51,88,57,36,13,19,43,11,80,30,39,50,35,91,91,92,57,28,9,6,29,53,51,59,4,60,86,94,16,78,34,2,37,8,34,61,36,50,94,28,74,6,58,37,59,98,79,89,74,96,19,27,40,13,50,72,32,10,87,38,75,25,40,52,36,64,77,15,6,5,16,25,67,57,94,24,4,8,31,73,36,47,28,23,14,77,94,9,79,44,45,4,98,54,47,28,987010};
// clang-format on

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
            assert(y == -1 || x <= INT64_MIN / y);
        }
    }
    return x * y;
}

// Run until output or halt.
// Consume all the inputs.
// Return output or nothing when it halts.
optional<int64_t> run_until_output_or_halt(Machine& m, VI64& inputs, bool consume_all_inputs = true)
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
            assert(!consume_all_inputs || inputs.empty());
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

optional<int64_t> run_until_output_or_halt(Machine& m)
{
    VI64 xs;
    return run_until_output_or_halt(m, xs);
}

const AI2 DIR_UP{0, -1};
const AI2 DIR_LEFT{-1, 0};
const AI2 DIR_DOWN{0, 1};
const AI2 DIR_RIGHT{1, 0};

AI2 turn_right(const AI2 x)
{
    return AI2{-x[1], x[0]};
}

AI2 turn_left(const AI2 x)
{
    return AI2{x[1], -x[0]};
}

enum Tile
{
    EMPTY = 0,
    WALL = 1,     // W
    BLOCK = 2,    // b
    HPADDLE = 3,  // -
    BALL = 4,     // O
    MAX_TILE = 5
};

struct Wall
{
    AI2 robot_pos{0, 0};
    AI2 robot_dir{DIR_UP};
    map<AI2, Tile> tiles;
    Tile at(AI2 xy) const
    {
        auto it = tiles.find(xy);
        if (it == tiles.end()) {
            return EMPTY;
        }
        return it->second;
    }
    void set(AI2 xy, int t)
    {
        assert(0 <= t && t < MAX_TILE);
        if (t == 0) {
            tiles.erase(xy);
        } else {
            tiles[xy] = (Tile)t;
        }
    }
};

void operator+=(AI2& x, AI2 y)
{
    x[0] += y[0];
    x[1] += y[1];
}

int as_int(int64_t x)
{
    assert(INT_MIN <= x && x <= INT_MAX);
    return (int)x;
}

int print(const Wall& wall)
{
    printf("\n");
    AI2 mn{0, 0}, mx{0, 0};
    for (auto kv : wall.tiles) {
        auto w = kv.first;
        if (mn == mx) {
            mn = w;
            mx = AI2{w[0] + 1, w[1] + 1};
        } else {
            mn = AI2{min(mn[0], w[0]), min(mn[1], w[1])};
            mx = AI2{max(mx[0], w[0] + 1), max(mx[1], w[1] + 1)};
        }
    }
    const char* TILE_CHARS = "+Wb-O";
    int block_count = 0;
    FOR (y, mn[1], < mx[1]) {
        FOR (x, mn[0], < mx[0]) {
            auto c = wall.at(AI2{x, y});
            if (c == BLOCK) {
                ++block_count;
            }
            printf("%c", TILE_CHARS[c]);
        }
        printf("\n");
    }
    return block_count;
}

int main()
{
    {
        Machine m{input};
        Wall wall;
        for (;;) {
            auto ox = run_until_output_or_halt(m);
            if (!ox) {
                printf("Halt instead of first output.\n");
                break;
            }
            auto oy = run_until_output_or_halt(m);
            assert(oy);
            auto ot = run_until_output_or_halt(m);
            assert(ot);
            wall.set(AI2{as_int(*ox), as_int(*oy)}, *ot);
        }
        int block_count = print(wall);
        printf("Block count: %d\n", block_count);
    }
    {
        Machine m{input};
        m.mem[0] = 2;
        Wall wall;
        int score = 0;
        optional<AI2> paddle_xy, ball_xy, prev_ball_xy;
        int ball_dir = 0;
        VI64 joystick;
        string status;
        bool after_first_score = false;
        string prev_status;
        // joystick = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (;;) {
            optional<int> joystick_to_send;
            if (paddle_xy && ball_xy) {
                if (ball_xy->at(1) + 1 == paddle_xy->at(1) && ball_xy->at(0) == paddle_xy->at(0)) {
                    joystick_to_send = 0;
                } else {
                    int next_ball_x = (*ball_xy)[0] + ball_dir;
                    if (next_ball_x < (*paddle_xy)[0]) {
                        joystick_to_send = -1;
                    } else if (next_ball_x > (*paddle_xy)[0]) {
                        joystick_to_send = 1;
                    } else {
                        joystick_to_send = 0;
                    }
                }
            }
            if (joystick_to_send) {
                joystick = {*joystick_to_send};
            } else {
                joystick.clear();
            }
            auto jb = joystick;
            auto ox = run_until_output_or_halt(m, joystick, false);
            if (jb != joystick) {
                assert(~jb == ~joystick + 1);
                char buf[100];
                sprintf(buf, "joystick received: %d", as_int(jb.front()));
                status = buf;
                paddle_xy->at(0) += jb.front();
                printf("joystick: %d\n", as_int(jb.front()));
            } else {
                status = "joystick not sent";
            }
            if (!ox) {
                printf("Halt instead of first output.\n");
                break;
            }
            auto oy = run_until_output_or_halt(m);
            assert(oy);
            auto ot = run_until_output_or_halt(m);
            assert(ot);
            bool draw = false;
            bool got_score = false;
            if (*ox == -1 && *oy == 0) {
                score = as_int(*ot);
                draw = true;
                got_score = true;
                printf("Score: %d\n", score);
            } else {
                wall.set(AI2{as_int(*ox), as_int(*oy)}, *ot);
                if (*ot == BALL) {
                    draw = true;
                    if (ball_xy) {
                        ball_dir = *ox - ball_xy->at(0);
                    }
                    ball_xy = AI2{as_int(*ox), as_int(*oy)};
                    printf("ball %d %d\n", as_int(*ox), as_int(*oy));
                    if (paddle_xy && ball_xy && paddle_xy->at(1) == ball_xy->at(1)) {
                        int a = 3;
                    }
                } else if (*ot == HPADDLE) {
                    paddle_xy = AI2{as_int(*ox), as_int(*oy)};
                    draw = true;
                    printf("                     paddle %d %d\n", as_int(*ox), as_int(*oy));
                    if (paddle_xy && ball_xy && paddle_xy->at(1) == ball_xy->at(1)) {
                        int a = 3;
                    }
                }
            }
            if (draw || status != prev_status) {
                prev_status = status;
                print(wall);
                // printf("Score: %d, %s\n", score, status.c_str());
                after_first_score = true;
            }
        }
    }
    return 0;
}