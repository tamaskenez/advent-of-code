#include "common.h"

// 3:10 -> 16:00

#include <set>

using VI64 = vector<int64_t>;

// clang-format off
const VI64 main_input = {1,330,331,332,109,2734,1102,1182,1,15,1102,1,1429,24,1002,0,1,570,1006,570,36,1001,571,0,0,1001,570,-1,570,1001,24,1,24,1106,0,18,1008,571,0,571,1001,15,1,15,1008,15,1429,570,1006,570,14,21102,58,1,0,1105,1,786,1006,332,62,99,21101,0,333,1,21102,73,1,0,1105,1,579,1101,0,0,572,1101,0,0,573,3,574,101,1,573,573,1007,574,65,570,1005,570,151,107,67,574,570,1005,570,151,1001,574,-64,574,1002,574,-1,574,1001,572,1,572,1007,572,11,570,1006,570,165,101,1182,572,127,1001,574,0,0,3,574,101,1,573,573,1008,574,10,570,1005,570,189,1008,574,44,570,1006,570,158,1105,1,81,21102,1,340,1,1105,1,177,21101,0,477,1,1106,0,177,21101,0,514,1,21101,0,176,0,1106,0,579,99,21102,1,184,0,1106,0,579,4,574,104,10,99,1007,573,22,570,1006,570,165,1001,572,0,1182,21102,1,375,1,21101,211,0,0,1106,0,579,21101,1182,11,1,21102,1,222,0,1105,1,979,21102,1,388,1,21102,233,1,0,1105,1,579,21101,1182,22,1,21101,0,244,0,1106,0,979,21101,401,0,1,21101,0,255,0,1105,1,579,21101,1182,33,1,21102,266,1,0,1106,0,979,21102,1,414,1,21102,1,277,0,1106,0,579,3,575,1008,575,89,570,1008,575,121,575,1,575,570,575,3,574,1008,574,10,570,1006,570,291,104,10,21102,1182,1,1,21101,313,0,0,1106,0,622,1005,575,327,1102,1,1,575,21102,327,1,0,1105,1,786,4,438,99,0,1,1,6,77,97,105,110,58,10,33,10,69,120,112,101,99,116,101,100,32,102,117,110,99,116,105,111,110,32,110,97,109,101,32,98,117,116,32,103,111,116,58,32,0,12,70,117,110,99,116,105,111,110,32,65,58,10,12,70,117,110,99,116,105,111,110,32,66,58,10,12,70,117,110,99,116,105,111,110,32,67,58,10,23,67,111,110,116,105,110,117,111,117,115,32,118,105,100,101,111,32,102,101,101,100,63,10,0,37,10,69,120,112,101,99,116,101,100,32,82,44,32,76,44,32,111,114,32,100,105,115,116,97,110,99,101,32,98,117,116,32,103,111,116,58,32,36,10,69,120,112,101,99,116,101,100,32,99,111,109,109,97,32,111,114,32,110,101,119,108,105,110,101,32,98,117,116,32,103,111,116,58,32,43,10,68,101,102,105,110,105,116,105,111,110,115,32,109,97,121,32,98,101,32,97,116,32,109,111,115,116,32,50,48,32,99,104,97,114,97,99,116,101,114,115,33,10,94,62,118,60,0,1,0,-1,-1,0,1,0,0,0,0,0,0,1,6,0,0,109,4,1202,-3,1,587,20101,0,0,-1,22101,1,-3,-3,21101,0,0,-2,2208,-2,-1,570,1005,570,617,2201,-3,-2,609,4,0,21201,-2,1,-2,1105,1,597,109,-4,2106,0,0,109,5,2102,1,-4,630,20102,1,0,-2,22101,1,-4,-4,21102,0,1,-3,2208,-3,-2,570,1005,570,781,2201,-4,-3,652,21002,0,1,-1,1208,-1,-4,570,1005,570,709,1208,-1,-5,570,1005,570,734,1207,-1,0,570,1005,570,759,1206,-1,774,1001,578,562,684,1,0,576,576,1001,578,566,692,1,0,577,577,21101,0,702,0,1105,1,786,21201,-1,-1,-1,1106,0,676,1001,578,1,578,1008,578,4,570,1006,570,724,1001,578,-4,578,21101,0,731,0,1106,0,786,1105,1,774,1001,578,-1,578,1008,578,-1,570,1006,570,749,1001,578,4,578,21101,0,756,0,1106,0,786,1106,0,774,21202,-1,-11,1,22101,1182,1,1,21102,774,1,0,1105,1,622,21201,-3,1,-3,1105,1,640,109,-5,2106,0,0,109,7,1005,575,802,21002,576,1,-6,20101,0,577,-5,1105,1,814,21102,1,0,-1,21102,1,0,-5,21102,0,1,-6,20208,-6,576,-2,208,-5,577,570,22002,570,-2,-2,21202,-5,29,-3,22201,-6,-3,-3,22101,1429,-3,-3,1202,-3,1,843,1005,0,863,21202,-2,42,-4,22101,46,-4,-4,1206,-2,924,21102,1,1,-1,1105,1,924,1205,-2,873,21102,1,35,-4,1105,1,924,1202,-3,1,878,1008,0,1,570,1006,570,916,1001,374,1,374,2101,0,-3,895,1101,2,0,0,2102,1,-3,902,1001,438,0,438,2202,-6,-5,570,1,570,374,570,1,570,438,438,1001,578,558,922,20101,0,0,-4,1006,575,959,204,-4,22101,1,-6,-6,1208,-6,29,570,1006,570,814,104,10,22101,1,-5,-5,1208,-5,45,570,1006,570,810,104,10,1206,-1,974,99,1206,-1,974,1101,1,0,575,21101,973,0,0,1105,1,786,99,109,-7,2105,1,0,109,6,21101,0,0,-4,21102,1,0,-3,203,-2,22101,1,-3,-3,21208,-2,82,-1,1205,-1,1030,21208,-2,76,-1,1205,-1,1037,21207,-2,48,-1,1205,-1,1124,22107,57,-2,-1,1205,-1,1124,21201,-2,-48,-2,1105,1,1041,21102,-4,1,-2,1106,0,1041,21101,-5,0,-2,21201,-4,1,-4,21207,-4,11,-1,1206,-1,1138,2201,-5,-4,1059,1201,-2,0,0,203,-2,22101,1,-3,-3,21207,-2,48,-1,1205,-1,1107,22107,57,-2,-1,1205,-1,1107,21201,-2,-48,-2,2201,-5,-4,1090,20102,10,0,-1,22201,-2,-1,-2,2201,-5,-4,1103,2101,0,-2,0,1106,0,1060,21208,-2,10,-1,1205,-1,1162,21208,-2,44,-1,1206,-1,1131,1105,1,989,21101,439,0,1,1105,1,1150,21102,1,477,1,1105,1,1150,21102,1,514,1,21102,1,1149,0,1105,1,579,99,21101,1157,0,0,1106,0,579,204,-2,104,10,99,21207,-3,22,-1,1206,-1,1138,2101,0,-5,1176,1202,-4,1,0,109,-6,2105,1,0,6,5,28,1,28,1,28,1,28,1,28,1,20,11,1,7,10,1,7,1,1,1,1,1,5,1,10,1,5,11,1,1,10,1,5,1,1,1,1,1,1,1,3,1,1,1,10,9,1,1,1,1,1,5,16,1,3,1,1,1,1,1,1,1,18,5,1,1,1,1,1,1,24,1,1,1,1,1,24,1,1,1,1,1,24,1,1,1,1,1,24,5,7,1,18,1,9,1,18,1,9,1,18,1,9,1,18,1,9,1,18,1,9,1,12,7,9,1,12,1,15,1,12,1,15,1,12,1,15,1,12,1,15,1,12,1,15,1,2,5,5,1,9,7,2,1,3,1,5,1,9,1,8,1,3,1,5,1,9,1,8,1,3,1,5,1,9,1,8,1,3,13,3,1,8,1,9,1,5,1,3,1,8,11,5,1,1,5,22,1,1,1,1,1,1,1,22,1,1,1,1,1,1,1,22,1,1,1,1,1,1,1,22,13,18,1,1,1,1,1,5,1,16,5,1,1,5,1,16,1,1,1,3,1,5,1,16,1,1,11,16,1,5,1,22,7,6};
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

struct SearchPos
{
    AI2 loc;
    Machine m;
    SearchPos(const AI2& loc, Machine m) : loc(loc), m(move(m)) {}
};

AI2 operator+(AI2 x, AI2 y)
{
    return AI2{x[0] + y[0], x[1] + y[1]};
}

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

AI2 rloc{-1, -1};
DIR_CODE rdir_code = INVALID_CODE;

Wall wall;

void solve()
{
    Machine m{main_input};
    int y = 0;
    int x = 0;
    auto [outputs, input_needed] = run_until_input_needed_or_halt(m);
    assert(!input_needed);
    for (auto r : outputs) {
        if (r == '^') {
            rloc = AI2{x, y};
            rdir_code = UP_CODE;
        }
        switch (r) {
            case 10:
                printf("\n");
                ++y;
                x = 0;
                break;
            default:
                if (32 <= r && r < 128) {
                    printf("%c", (char)r);
                    wall.set(AI2{x, y}, r);
                    ++x;
                } else {
                    assert(false);
                }
        }
    }

    int sum = 0;
    for (auto& kv : wall.tiles) {
        if (kv.second == '#') {
            auto xy = kv.first;
            if (wall.at(xy + UP) == '#' && wall.at(xy + DOWN) == '#' && wall.at(xy + LEFT) == '#' &&
                wall.at(xy + RIGHT) == '#') {
                printf("%d %d\n", xy[0], xy[1]);
                sum += xy[0] * xy[1];
            }
        }
    }
    printf("calib: %d\n", sum);
}

void print(const VI64 outputs)
{
    for (auto c : outputs) {
        printf("%c", (char)c);
    }
}

const array<AI2, 4> DIRS = {UP, RIGHT, DOWN, LEFT};

int manhattan(AI2 a, AI2 b)
{
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

VI64 to_vi64(const string& s)
{
    VI64 r;
    for (auto c : s) {
        r.push_back(c);
    }
    return r;
}

int diff(pair<int, int> pp)
{
    return pp.second - pp.first;
}

void solve2()
{
    Machine m{main_input};
    assert(m.mem[0] == 1);
    m.mem[0] = 2;

    auto [outputs, input_needed] = run_until_input_needed_or_halt(m);
    assert(input_needed);
    print(outputs);

    assert((rloc != AI2{-1, -1}));
    assert((rdir_code != INVALID_CODE));

    set<AI2> tovisit;
    for (auto& kv : wall.tiles) {
        if (kv.second == '#') {
            tovisit.insert(kv.first);
        }
    }

    wall.set(rloc, '#');

    struct Step
    {
        char action;  // R L F
        int forward;
        bool operator<(const Step& x) const
        {
            if (action < x.action) {
                return true;
            }
            if (action > x.action) {
                return false;
            }
            return forward < x.forward;
        }
    };

    struct Planner
    {
        AI2 rloc;
        int rdir_code;
        void move_one(AI2 new_loc)
        {
            auto rdir = DIRS[rdir_code];
            if (rloc + rdir != new_loc) {
                if (rloc + DIRS[(rdir_code + 1) % 4] == new_loc) {
                    steps.push_back(Step{'R', -1});
                    rdir_code = (rdir_code + 1) % 4;
                } else if (rloc + DIRS[(rdir_code + 3) % 4] == new_loc) {
                    steps.push_back(Step{'L', -1});
                    rdir_code = (rdir_code + 3) % 4;
                } else {
                    rdir_code = (rdir_code + 2) % 4;
                    steps.push_back(Step{'R', -1});
                    steps.push_back(Step{'R', -1});
                }
            }
            assert(rloc + DIRS[rdir_code] == new_loc);
            rloc += DIRS[rdir_code];
            if (steps.empty() || steps.back().action != 'F') {
                steps.push_back(Step{'F', 1});
            } else {
                ++steps.back().forward;
            }
        }
        vector<Step> steps;
    } planner;

    planner.rloc = rloc;
    planner.rdir_code = rdir_code;

    while (!tovisit.empty()) {
        vector<int> dirs;
        FOR (d, -1, <= 1) {
            auto dir_code = (4 + planner.rdir_code + d) % 4;
            auto dir = DIRS[dir_code];
            auto nb = planner.rloc + dir;
            if (wall.at(nb) == '#') {
                dirs.push_back(dir_code);
            }
        }
        int dir_code;
        if (~dirs == 0) {
            assert(tovisit.empty());
            break;
        }
        if (~dirs == 1) {
            dir_code = dirs[0];
        } else {
            assert(find(BE(dirs), planner.rdir_code) != dirs.end());
            dir_code = planner.rdir_code;
        }
        auto dir = DIRS[dir_code];
        auto nb = planner.rloc + dir;
        planner.move_one(nb);
        tovisit.erase(planner.rloc);
    }
    VS lines;
    for (auto s : planner.steps) {
        string m;
        switch (s.action) {
            case 'R':
                m = "R";
                break;
            case 'L':
                m = "L";
                break;
            case 'F':
                m = to_string(s.forward);
                break;
            default:
                assert(false);
        }
        if (lines.empty() || ~lines.back() > 20 - (~m + 1)) {
            lines.emplace_back();
        }
        if (!lines.back().empty()) {
            lines.back() += ",";
        }
        lines.back() += m;
    }
    for (auto& l : lines) {
        printf("%s\n", l.c_str());
    }
    string main;
    FOR (i, 0, < ~lines) {
        if (!main.empty()) {
            main += ",";
        }
        main += ('A' + i);
    }
    printf("\n");
    VI64 inputs = to_vi64(main);

    inputs = to_vi64(string("A,B,A,B,C,B,C,A,B,C\n"));
    lines.resize(3);
    lines[0] = "R,4,R,10,R,8,R,4";
    lines[1] = "R,10,R,6,R,4";
    lines[2] = "R,4,L,12,R,6,L,12";
    tie(outputs, input_needed) = run_until_input_needed_or_halt(m, inputs);
    print(outputs);
    FOR (i, 0, < 3) {
        assert(input_needed);
        inputs = to_vi64(lines[i] + "\n");
        tie(outputs, input_needed) = run_until_input_needed_or_halt(m, inputs);
        print(outputs);
    }
    assert(input_needed);
    inputs = to_vi64("Y\n");
    tie(outputs, input_needed) = run_until_input_needed_or_halt(m, inputs);
    print(outputs);

    for (int i = ~outputs - 10; i < ~outputs; ++i) {
        printf("%s ", to_string(outputs[i]).c_str());
    }
    printf("\n");
    int a = 3;
}

int main()
{
    solve();
    solve2();
    return 0;
}