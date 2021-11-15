#include "common.h"

// 3:10 -> 16:00

#include <set>

using VI64 = vector<int64_t>;

// clang-format off
const VI64 main_input = {109,2050,21102,966,1,1,21101,0,13,0,1106,0,1378,21101,0,20,0,1106,0,1337,21101,0,27,0,1106,0,1279,1208,1,65,748,1005,748,73,1208,1,79,748,1005,748,110,1208,1,78,748,1005,748,132,1208,1,87,748,1005,748,169,1208,1,82,748,1005,748,239,21101,0,1041,1,21101,73,0,0,1105,1,1421,21101,0,78,1,21101,1041,0,2,21102,88,1,0,1105,1,1301,21101,0,68,1,21101,0,1041,2,21102,1,103,0,1105,1,1301,1101,0,1,750,1105,1,298,21102,1,82,1,21102,1041,1,2,21101,0,125,0,1106,0,1301,1101,2,0,750,1105,1,298,21102,1,79,1,21101,1041,0,2,21102,147,1,0,1105,1,1301,21102,84,1,1,21101,0,1041,2,21102,1,162,0,1105,1,1301,1102,3,1,750,1106,0,298,21101,65,0,1,21102,1,1041,2,21101,184,0,0,1106,0,1301,21102,76,1,1,21102,1041,1,2,21102,1,199,0,1105,1,1301,21101,75,0,1,21101,1041,0,2,21102,1,214,0,1105,1,1301,21101,221,0,0,1106,0,1337,21101,0,10,1,21102,1,1041,2,21102,1,236,0,1106,0,1301,1105,1,553,21101,85,0,1,21101,0,1041,2,21102,254,1,0,1106,0,1301,21101,78,0,1,21102,1041,1,2,21102,269,1,0,1106,0,1301,21101,276,0,0,1106,0,1337,21102,1,10,1,21101,1041,0,2,21101,291,0,0,1105,1,1301,1101,0,1,755,1106,0,553,21101,32,0,1,21101,1041,0,2,21102,1,313,0,1105,1,1301,21102,1,320,0,1105,1,1337,21101,327,0,0,1105,1,1279,1202,1,1,749,21102,65,1,2,21102,73,1,3,21101,0,346,0,1106,0,1889,1206,1,367,1007,749,69,748,1005,748,360,1102,1,1,756,1001,749,-64,751,1105,1,406,1008,749,74,748,1006,748,381,1102,-1,1,751,1105,1,406,1008,749,84,748,1006,748,395,1101,0,-2,751,1106,0,406,21101,0,1100,1,21101,0,406,0,1105,1,1421,21102,32,1,1,21101,0,1100,2,21101,0,421,0,1105,1,1301,21101,0,428,0,1105,1,1337,21101,0,435,0,1105,1,1279,2102,1,1,749,1008,749,74,748,1006,748,453,1102,-1,1,752,1106,0,478,1008,749,84,748,1006,748,467,1102,1,-2,752,1105,1,478,21101,1168,0,1,21101,0,478,0,1105,1,1421,21101,485,0,0,1105,1,1337,21102,10,1,1,21101,1168,0,2,21101,500,0,0,1105,1,1301,1007,920,15,748,1005,748,518,21102,1,1209,1,21102,518,1,0,1105,1,1421,1002,920,3,529,1001,529,921,529,101,0,750,0,1001,529,1,537,101,0,751,0,1001,537,1,545,101,0,752,0,1001,920,1,920,1105,1,13,1005,755,577,1006,756,570,21102,1100,1,1,21101,0,570,0,1105,1,1421,21101,987,0,1,1106,0,581,21102,1001,1,1,21101,588,0,0,1106,0,1378,1102,758,1,594,101,0,0,753,1006,753,654,21002,753,1,1,21101,610,0,0,1106,0,667,21101,0,0,1,21101,621,0,0,1105,1,1463,1205,1,647,21102,1,1015,1,21101,0,635,0,1105,1,1378,21101,0,1,1,21102,1,646,0,1105,1,1463,99,1001,594,1,594,1106,0,592,1006,755,664,1101,0,0,755,1106,0,647,4,754,99,109,2,1101,726,0,757,22101,0,-1,1,21101,0,9,2,21102,1,697,3,21101,692,0,0,1105,1,1913,109,-2,2105,1,0,109,2,1002,757,1,706,2101,0,-1,0,1001,757,1,757,109,-2,2105,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,255,63,95,191,127,223,159,0,171,214,141,78,200,198,175,85,158,60,172,61,118,43,154,138,71,114,39,216,227,166,98,109,188,186,245,53,237,169,229,168,251,179,142,153,87,110,107,51,101,226,241,113,205,79,69,92,156,34,157,201,236,68,218,177,108,111,35,228,234,120,253,119,220,50,206,140,217,187,207,62,126,125,230,57,250,86,243,246,152,252,178,249,181,189,222,219,93,196,155,232,76,213,242,184,167,99,202,103,58,170,121,162,173,59,54,182,106,244,231,123,238,49,46,116,239,221,248,197,136,174,235,47,42,203,84,143,56,190,77,183,124,247,212,38,94,137,115,102,199,254,215,122,70,233,185,139,163,55,204,100,117,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,73,110,112,117,116,32,105,110,115,116,114,117,99,116,105,111,110,115,58,10,13,10,87,97,108,107,105,110,103,46,46,46,10,10,13,10,82,117,110,110,105,110,103,46,46,46,10,10,25,10,68,105,100,110,39,116,32,109,97,107,101,32,105,116,32,97,99,114,111,115,115,58,10,10,58,73,110,118,97,108,105,100,32,111,112,101,114,97,116,105,111,110,59,32,101,120,112,101,99,116,101,100,32,115,111,109,101,116,104,105,110,103,32,108,105,107,101,32,65,78,68,44,32,79,82,44,32,111,114,32,78,79,84,67,73,110,118,97,108,105,100,32,102,105,114,115,116,32,97,114,103,117,109,101,110,116,59,32,101,120,112,101,99,116,101,100,32,115,111,109,101,116,104,105,110,103,32,108,105,107,101,32,65,44,32,66,44,32,67,44,32,68,44,32,74,44,32,111,114,32,84,40,73,110,118,97,108,105,100,32,115,101,99,111,110,100,32,97,114,103,117,109,101,110,116,59,32,101,120,112,101,99,116,101,100,32,74,32,111,114,32,84,52,79,117,116,32,111,102,32,109,101,109,111,114,121,59,32,97,116,32,109,111,115,116,32,49,53,32,105,110,115,116,114,117,99,116,105,111,110,115,32,99,97,110,32,98,101,32,115,116,111,114,101,100,0,109,1,1005,1262,1270,3,1262,21001,1262,0,0,109,-1,2106,0,0,109,1,21102,1,1288,0,1105,1,1263,20102,1,1262,0,1102,1,0,1262,109,-1,2106,0,0,109,5,21101,0,1310,0,1106,0,1279,22102,1,1,-2,22208,-2,-4,-1,1205,-1,1332,21202,-3,1,1,21101,0,1332,0,1106,0,1421,109,-5,2106,0,0,109,2,21101,1346,0,0,1105,1,1263,21208,1,32,-1,1205,-1,1363,21208,1,9,-1,1205,-1,1363,1106,0,1373,21102,1370,1,0,1105,1,1279,1105,1,1339,109,-2,2106,0,0,109,5,1202,-4,1,1386,20101,0,0,-2,22101,1,-4,-4,21101,0,0,-3,22208,-3,-2,-1,1205,-1,1416,2201,-4,-3,1408,4,0,21201,-3,1,-3,1106,0,1396,109,-5,2106,0,0,109,2,104,10,22101,0,-1,1,21102,1,1436,0,1106,0,1378,104,10,99,109,-2,2105,1,0,109,3,20002,594,753,-1,22202,-1,-2,-1,201,-1,754,754,109,-3,2106,0,0,109,10,21102,1,5,-5,21102,1,1,-4,21101,0,0,-3,1206,-9,1555,21102,1,3,-6,21101,5,0,-7,22208,-7,-5,-8,1206,-8,1507,22208,-6,-4,-8,1206,-8,1507,104,64,1105,1,1529,1205,-6,1527,1201,-7,716,1515,21002,0,-11,-8,21201,-8,46,-8,204,-8,1106,0,1529,104,46,21201,-7,1,-7,21207,-7,22,-8,1205,-8,1488,104,10,21201,-6,-1,-6,21207,-6,0,-8,1206,-8,1484,104,10,21207,-4,1,-8,1206,-8,1569,21101,0,0,-9,1106,0,1689,21208,-5,21,-8,1206,-8,1583,21101,1,0,-9,1105,1,1689,1201,-5,716,1588,21001,0,0,-2,21208,-4,1,-1,22202,-2,-1,-1,1205,-2,1613,22101,0,-5,1,21101,1613,0,0,1105,1,1444,1206,-1,1634,21202,-5,1,1,21102,1,1627,0,1106,0,1694,1206,1,1634,21102,1,2,-3,22107,1,-4,-8,22201,-1,-8,-8,1206,-8,1649,21201,-5,1,-5,1206,-3,1663,21201,-3,-1,-3,21201,-4,1,-4,1105,1,1667,21201,-4,-1,-4,21208,-4,0,-1,1201,-5,716,1676,22002,0,-1,-1,1206,-1,1686,21102,1,1,-4,1106,0,1477,109,-10,2106,0,0,109,11,21102,0,1,-6,21102,1,0,-8,21101,0,0,-7,20208,-6,920,-9,1205,-9,1880,21202,-6,3,-9,1201,-9,921,1725,20102,1,0,-5,1001,1725,1,1733,20101,0,0,-4,21201,-4,0,1,21102,1,1,2,21102,1,9,3,21101,1754,0,0,1106,0,1889,1206,1,1772,2201,-10,-4,1766,1001,1766,716,1766,21001,0,0,-3,1106,0,1790,21208,-4,-1,-9,1206,-9,1786,22101,0,-8,-3,1106,0,1790,21202,-7,1,-3,1001,1733,1,1795,21002,0,1,-2,21208,-2,-1,-9,1206,-9,1812,22101,0,-8,-1,1106,0,1816,21201,-7,0,-1,21208,-5,1,-9,1205,-9,1837,21208,-5,2,-9,1205,-9,1844,21208,-3,0,-1,1105,1,1855,22202,-3,-1,-1,1105,1,1855,22201,-3,-1,-1,22107,0,-1,-1,1106,0,1855,21208,-2,-1,-9,1206,-9,1869,21202,-1,1,-8,1106,0,1873,22101,0,-1,-7,21201,-6,1,-6,1105,1,1708,21202,-8,1,-10,109,-11,2105,1,0,109,7,22207,-6,-5,-3,22207,-4,-6,-2,22201,-3,-2,-1,21208,-1,0,-6,109,-7,2105,1,0,0,109,5,1202,-2,1,1912,21207,-4,0,-1,1206,-1,1930,21102,0,1,-4,21202,-4,1,1,21201,-3,0,2,21101,0,1,3,21101,0,1949,0,1106,0,1954,109,-5,2106,0,0,109,6,21207,-4,1,-1,1206,-1,1977,22207,-5,-3,-1,1206,-1,1977,21202,-5,1,-5,1106,0,2045,21202,-5,1,1,21201,-4,-1,2,21202,-3,2,3,21102,1,1996,0,1106,0,1954,21202,1,1,-5,21101,1,0,-2,22207,-5,-3,-1,1206,-1,2015,21101,0,0,-2,22202,-3,-2,-3,22107,0,-4,-1,1206,-1,2037,22101,0,-2,1,21101,2037,0,0,105,1,1912,21202,-3,-1,-3,22201,-5,-3,-5,109,-6,2105,1,0};
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

// Run until input needed or halt.
// Return outputs and true = input needed, false = halt.
tuple<VI64, bool> run_until_input_needed_or_halt(Machine& m,
                                                 VI64& inputs,
                                                 bool consume_all_inputs = true)
{
    VI64 outputs;
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
        } else if (opcode == 3) {  // INPUT
            auto xm = mode_from_opcode(c, 1);
            auto x = m.address_of_arg(1, xm);
            if (inputs.empty()) {
                return make_tuple(outputs, true);
            }
            auto input_value = inputs.front();
            inputs.erase(inputs.begin());
            m.write(x, input_value);
            m.pc += 2;
        } else if (opcode == 4) {  // OUTPUT
            auto xm = mode_from_opcode(c, 1);
            auto output_value = m.read_arg(1, xm);
            m.pc += 2;
            outputs.push_back(output_value);
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
            assert(inputs.empty() || !consume_all_inputs);
            return make_tuple(outputs, false);
        } else {
            assert(false);
        }
    }
    assert(false);
    return {};
}

tuple<VI64, bool> run_until_input_needed_or_halt(Machine& m)
{
    VI64 xs;
    return run_until_input_needed_or_halt(m, xs);
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

using Tile = char;
const char UNKNOWN = 0;

struct Wall
{
    map<AI2, Tile> tiles;
    Tile at(AI2 xy) const
    {
        auto it = tiles.find(xy);
        if (it == tiles.end()) {
            return UNKNOWN;
        }
        return it->second;
    }
    void set(AI2 xy, int t)
    {
        assert(0 <= t && t < 128);
        if (t == UNKNOWN) {
            tiles.erase(xy);
        } else {
            tiles[xy] = (Tile)t;
        }
    }
};

/*
void print(const Wall& wall)
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
    const char* TILE_CHARS = " .#";
    FOR (y, mn[1], < mx[1]) {
        FOR (x, mn[0], < mx[0]) {
            auto c = wall.at(AI2{x, y});
            printf("%c", TILE_CHARS[c]);
        }
        printf("\n");
    }
}
*/
const AI2 UP{0, -1};
const AI2 DOWN{0, 1};
const AI2 LEFT{-1, 0};
const AI2 RIGHT{1, 0};

enum DIR_CODE
{
    UP_CODE = 0,
    RIGHT_CODE,
    DOWN_CODE,
    LEFT_CODE,
    INVALID_CODE,
};

Wall wall;

void solve()
{
    Machine m{main_input};
    VI64 in;
    auto [out, ni] = run_until_input_needed_or_halt(m, in);
    assert(ni);
    // clang-format off
const string CODE = R"(NOT A T
NOT T T
AND B T
AND C T
AND D T
NOT T J
AND D J
NOT A T
OR T J
WALK
)";
    // clang-format on
    in = to_vi64(CODE);
    tie(out, ni) = run_until_input_needed_or_halt(m, in);
    print(out);
    FOR (i, max(0, ~out - 10), < ~out) {
        printf("%d: %s\n", i, to_string(out[i]).c_str());
    }
}

void solve2()
{
    Machine m{main_input};
    VI64 in;
    auto [out, ni] = run_until_input_needed_or_halt(m, in);
    assert(ni);
    // clang-format off
    // !A || (D && H);
    // !A || (D && H && ((!B || !C) && !(B && F && G)));
    const string CODE = R"(NOT B J
NOT C T
OR T J
NOT B T
NOT T T
AND F T
AND G T
NOT T T
AND T J
AND D J
AND H J
NOT A T
OR T J
RUN
)";
    // clang-format on
    in = to_vi64(CODE);
    tie(out, ni) = run_until_input_needed_or_halt(m, in);
    print(out);
    FOR (i, max(0, ~out - 10), < ~out) {
        printf("%d: %s\n", i, to_string(out[i]).c_str());
    }
}

enum Outcome
{
    DIE,
    DEPENDS,
    LIVE
};
// .012345678
// .ABCDEFGHI
Outcome test(int terrain, int x, bool jump, int length)
{
    if (x >= length) {
        return LIVE;
    }
    auto mask = 1 << x;
    assert(x == -1 || (terrain & mask));
    x += jump ? 4 : 1;
    if (x >= length) {
        return LIVE;
    }
    mask = 1 << x;
    if (terrain & mask) {
        auto oj = test(terrain, x, true, length);
        auto onj = test(terrain, x, false, length);
        return max(oj, onj);
    } else {
        return DIE;
    }
}

enum Advice
{
    DONT_JUMP,
    DONT_CARE,
    JUMP
};

Advice test(int terrain)
{
    const int N = 16;
    int better_to_jump = 0;
    int better_not_to_jump = 0;
    int dies = 0;
    int lives = 0;

    FOR (i, 0, < (1 << (N - 9))) {
        auto full_terrain = terrain | (i << 9);
        auto oj = test(full_terrain, -1, true, N);
        auto onj = test(full_terrain, -1, false, N);
        if (oj == LIVE) {
            if (onj == LIVE) {
                ++lives;
            } else {
                assert(onj == DIE);
                ++better_to_jump;
            }
        } else {
            assert(oj == DIE);
            if (onj == LIVE) {
                ++better_not_to_jump;
            } else {
                assert(onj == DIE);
                ++dies;
            }
        }
    }
    int total = 1 << (N - 9);
    if (dies == total) {
        return DONT_CARE;
    }
    if (better_to_jump > 0 && better_not_to_jump == 0) {
        return JUMP;
    }
    if (better_to_jump == 0 && better_not_to_jump > 0) {
        return DONT_JUMP;
    }
    return DONT_CARE;
    if (better_to_jump == 0 && better_not_to_jump == 0) {
        return DONT_JUMP;
    }
    if (better_to_jump > better_not_to_jump) {
        return JUMP;
    }
    if (better_to_jump < better_not_to_jump) {
        return DONT_JUMP;
    }
    return DONT_JUMP;
}

bool formula(int terrain)
{
    auto A = terrain & (1 << 0);
    auto B = terrain & (1 << 1);
    auto C = terrain & (1 << 2);
    auto D = terrain & (1 << 3);
    auto E = terrain & (1 << 4);
    auto F = terrain & (1 << 5);
    auto G = terrain & (1 << 6);
    auto H = terrain & (1 << 7);
    auto I = terrain & (1 << 8);
    (void)A;
    (void)B;
    (void)C;
    (void)D;
    (void)E;
    (void)F;
    (void)G;
    (void)H;
    (void)I;
    //    bool J = !A || (D && H && !((B && C) || (B && F && G)));
    bool J = !A || (D && H && (!(B && C) && !(B && F && G)));
    return J;
}

void print_terrain(int a)
{
    FOR (j, 0, < 9) {
        printf("%c", a & (1 << j) ? 'X' : '.');
    }
    printf("\n");
}

void test()
{
    array<VI, 3> rs;
    VI should_jump, shouldnt_jump;

    FOR (k, 0, < 512) {
        auto oc = test(k);
        rs[oc].push_back(k);
        auto J = formula(k);
        if (oc == DONT_JUMP && J) {
            shouldnt_jump.push_back(k);
        } else if (oc == JUMP && !J) {
            should_jump.push_back(k);
        }
    }
    printf("Should jump:\n");
    for (auto k : should_jump) {
        print_terrain(k);
    }
    printf("Shouldn't jump:\n");
    for (auto k : shouldnt_jump) {
        print_terrain(k);
    }
    return;
    FOR (i, 0, < 3) {
        auto& as = rs[i];
        switch (i) {
            case 0:
                printf("Don't jump:\n");
                break;
            case 1:
                printf("Don't care:\n");
                break;
            case 2:
                printf("Jump:\n");
                break;
            default:
                assert(false);
        }
        for (auto& a : as) {
            FOR (j, 0, < 9) {
                printf("%c", a & (1 << j) ? 'X' : '.');
            }
            printf("\n");
        }
        printf("\n");
    }
}
int main()
{
    // solve();
    test();
    solve2();
    return 0;
}