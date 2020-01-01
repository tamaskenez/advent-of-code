#include <set>

#include "common.h"

using VI64 = vector<int64_t>;

// clang-format off
const VI64 input = {3,1033,1008,1033,1,1032,1005,1032,31,1008,1033,2,1032,1005,1032,58,1008,1033,3,1032,1005,1032,81,1008,1033,4,1032,1005,1032,104,99,1001,1034,0,1039,1001,1036,0,1041,1001,1035,-1,1040,1008,1038,0,1043,102,-1,1043,1032,1,1037,1032,1042,1105,1,124,102,1,1034,1039,1001,1036,0,1041,1001,1035,1,1040,1008,1038,0,1043,1,1037,1038,1042,1106,0,124,1001,1034,-1,1039,1008,1036,0,1041,1001,1035,0,1040,101,0,1038,1043,101,0,1037,1042,1106,0,124,1001,1034,1,1039,1008,1036,0,1041,1002,1035,1,1040,102,1,1038,1043,1001,1037,0,1042,1006,1039,217,1006,1040,217,1008,1039,40,1032,1005,1032,217,1008,1040,40,1032,1005,1032,217,1008,1039,37,1032,1006,1032,165,1008,1040,5,1032,1006,1032,165,1102,1,2,1044,1105,1,224,2,1041,1043,1032,1006,1032,179,1102,1,1,1044,1106,0,224,1,1041,1043,1032,1006,1032,217,1,1042,1043,1032,1001,1032,-1,1032,1002,1032,39,1032,1,1032,1039,1032,101,-1,1032,1032,101,252,1032,211,1007,0,64,1044,1106,0,224,1101,0,0,1044,1105,1,224,1006,1044,247,1002,1039,1,1034,101,0,1040,1035,102,1,1041,1036,102,1,1043,1038,101,0,1042,1037,4,1044,1106,0,0,13,40,97,1,18,1,79,93,56,16,38,41,78,11,78,25,46,84,31,38,76,17,96,5,78,50,8,67,77,54,42,82,39,2,8,5,11,85,37,93,37,7,97,12,94,2,44,70,74,78,34,45,94,75,19,8,84,72,2,9,69,74,6,11,75,79,42,35,86,83,23,82,88,40,81,70,8,58,46,57,77,65,76,68,79,61,24,80,61,88,70,42,32,71,16,23,99,77,73,57,45,99,39,29,97,4,90,76,3,5,86,11,95,94,90,59,13,37,94,29,57,42,99,4,45,96,22,74,33,73,70,24,96,4,82,10,3,79,37,81,97,72,42,66,3,27,98,4,73,49,55,86,12,41,65,38,21,66,27,80,87,53,86,26,85,80,42,26,92,17,79,76,58,69,2,71,7,88,12,61,73,16,67,48,83,87,8,21,72,67,50,70,7,71,9,53,46,81,99,47,3,70,11,23,68,22,86,43,32,92,30,78,94,61,81,32,60,89,97,58,23,27,52,99,85,90,41,20,11,87,73,57,83,30,79,2,58,93,32,81,16,86,35,87,38,73,88,11,6,65,32,20,81,87,89,12,11,66,42,84,12,79,14,23,72,37,85,95,15,48,80,92,59,56,7,95,85,21,82,53,93,45,73,29,79,6,17,68,79,34,72,47,39,81,93,63,83,51,67,99,1,74,56,89,47,86,95,51,94,46,3,95,18,81,20,85,19,90,60,24,65,65,46,91,17,82,37,87,21,83,80,22,28,75,17,68,72,40,67,82,19,9,79,42,86,55,93,91,41,76,55,22,74,61,91,42,96,73,11,1,79,60,85,82,40,76,88,84,2,14,97,89,29,69,39,43,65,19,58,97,68,45,50,2,91,54,52,93,82,61,76,22,15,77,63,76,60,81,42,89,77,45,80,3,92,17,10,98,16,92,38,71,2,46,81,81,11,7,43,82,68,82,93,25,44,87,60,49,48,7,47,82,82,26,65,93,50,75,57,92,57,78,11,39,99,2,93,42,69,6,66,60,96,79,50,20,75,84,48,98,57,5,93,98,62,78,85,53,85,32,37,90,90,30,43,74,57,81,19,35,19,94,50,65,60,98,65,46,86,75,68,16,31,83,75,56,93,35,42,89,32,69,35,2,60,82,58,53,1,87,18,66,82,41,73,73,7,99,91,89,48,83,20,81,31,66,17,93,23,41,86,65,57,72,13,13,82,94,79,77,54,89,90,62,95,35,74,82,37,43,33,66,77,3,86,26,87,35,69,19,24,85,62,18,9,72,42,69,25,95,57,34,41,82,36,90,24,36,27,67,49,30,70,75,82,44,33,67,70,35,36,69,33,85,10,87,50,72,8,74,97,18,95,25,97,5,84,16,65,60,89,15,86,81,9,75,73,58,72,39,91,10,55,3,11,86,96,18,98,97,28,22,98,49,89,19,84,18,98,34,92,67,37,80,17,8,65,72,2,91,95,55,76,19,30,78,40,96,78,34,91,99,23,14,71,38,37,71,59,93,78,83,61,24,31,97,25,85,8,16,84,15,65,77,14,96,98,6,89,33,98,59,4,84,66,18,74,48,12,41,86,31,45,33,74,97,86,55,85,16,34,54,91,77,3,19,65,70,18,90,41,98,25,55,22,95,15,92,14,67,20,88,5,51,69,92,33,69,75,56,36,91,3,80,13,78,36,88,50,88,79,65,24,66,5,99,45,98,88,66,30,92,98,84,5,90,13,67,95,96,33,77,30,80,39,99,81,95,55,86,0,0,21,21,1,10,1,0,0,0,0,0,0};
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
    UNKNOWN = 0,
    EMPTY,
    WALL,
    MAX_TILE
};

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
        assert(0 <= t && t < MAX_TILE);
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

enum DIR_CODE
{
    NORTH_CODE = 1,
    SOUTH_CODE,
    WEST_CODE,
    EAST_CODE
};

const AI2 NORTH_DIR{0, -1};
const AI2 SOUTH_DIR{0, 1};
const AI2 WEST_DIR{-1, 0};
const AI2 EAST_DIR{1, 0};

const array<AI2, 4> DIRS = {NORTH_DIR, SOUTH_DIR, WEST_DIR, EAST_DIR};
AI2 operator+(AI2 x, AI2 y)
{
    return AI2{x[0] + y[0], x[1] + y[1]};
}

// Return next_frontier and oxygen location.
tuple<vector<SearchPos>, optional<AI2>> iterate_search(Wall& wall,
                                                       const vector<SearchPos>& frontier)
{
    vector<SearchPos> next_frontier;
    optional<AI2> oxygen_loc;
    for (auto& sp : frontier) {
        FOR (dir_code, 1, <= 4) {
            auto new_loc = sp.loc + DIRS[dir_code - 1];
            auto new_tile = wall.at(new_loc);
            if (new_tile == UNKNOWN) {
                Machine new_machine{sp.m};
                VI64 m_in{dir_code};
                auto r = run_until_output_or_halt(new_machine, m_in);
                assert(r);
                switch (*r) {
                    case 0:
                        wall.set(new_loc, WALL);
                        break;
                    case 2:
                        oxygen_loc = new_loc;
                        [[fallthrough]];
                    case 1:
                        wall.set(new_loc, EMPTY);
                        next_frontier.emplace_back(new_loc, move(new_machine));
                        break;
                    default:
                        assert(false);
                }
            }
        }
    }
    return {next_frontier, oxygen_loc};
}

void solve()
{
    Wall wall;
    wall.set(AI2{0, 0}, EMPTY);

    vector<SearchPos> frontier;
    frontier.emplace_back(AI2{0, 0}, Machine{input});

    optional<SearchPos> oxygen_loc_sp;
    for (int current_step_number = 1;; ++current_step_number) {
        auto[next_frontier, oxygen_loc] = iterate_search(wall, frontier);
        print(wall);
        if (oxygen_loc) {
            printf("Oxygen reached in %d steps.\n", current_step_number);
            bool found = false;
            for (auto& sp : next_frontier) {
                if (sp.loc == *oxygen_loc) {
                    oxygen_loc_sp = move(sp);
                    found = true;
                    break;
                }
            }
            assert(found);
            break;
        }
        frontier.swap(next_frontier);
    }

    wall.tiles.clear();
    wall.set(AI2{0, 0}, EMPTY);
    frontier.assign(1, move(*oxygen_loc_sp));
    for (int current_step_number = 0;; ++current_step_number) {
        auto[next_frontier, oxygen_loc] = iterate_search(wall, frontier);
        print(wall);
        if (next_frontier.empty()) {
            printf("Oxygen filled area in %d steps.\n", current_step_number);
            return;
        }
        frontier.swap(next_frontier);
    }
}

int main()
{
    solve();
    return 0;
}