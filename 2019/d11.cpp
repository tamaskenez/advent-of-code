#include <set>

#include "common.h"

using VI64 = vector<int64_t>;

// clang-format off
const VI64 input = {3,8,1005,8,311,1106,0,11,0,0,0,104,1,104,0,3,8,1002,8,-1,10,101,1,10,10,4,10,108,0,8,10,4,10,1002,8,1,28,2,103,7,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,1001,8,0,55,2,3,6,10,1,101,5,10,1,6,7,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,0,10,4,10,1001,8,0,89,1,1108,11,10,2,1002,13,10,1006,0,92,1,2,13,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,101,0,8,126,3,8,1002,8,-1,10,101,1,10,10,4,10,108,1,8,10,4,10,1002,8,1,147,1,7,0,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,0,8,10,4,10,101,0,8,173,1006,0,96,3,8,102,-1,8,10,101,1,10,10,4,10,108,0,8,10,4,10,1001,8,0,198,1,3,7,10,1006,0,94,2,1003,20,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,1,10,4,10,102,1,8,232,3,8,102,-1,8,10,101,1,10,10,4,10,108,1,8,10,4,10,102,1,8,253,1006,0,63,1,109,16,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,101,0,8,283,2,1107,14,10,1,105,11,10,101,1,9,9,1007,9,1098,10,1005,10,15,99,109,633,104,0,104,1,21102,837951005592,1,1,21101,328,0,0,1105,1,432,21101,0,847069840276,1,21101,0,339,0,1106,0,432,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21102,179318123543,1,1,21102,386,1,0,1106,0,432,21102,1,29220688067,1,21102,1,397,0,1106,0,432,3,10,104,0,104,0,3,10,104,0,104,0,21102,709580567396,1,1,21102,1,420,0,1105,1,432,21102,1,868498694912,1,21102,431,1,0,1106,0,432,99,109,2,22101,0,-1,1,21101,40,0,2,21101,0,463,3,21101,0,453,0,1105,1,496,109,-2,2106,0,0,0,1,0,0,1,109,2,3,10,204,-1,1001,458,459,474,4,0,1001,458,1,458,108,4,458,10,1006,10,490,1102,1,0,458,109,-2,2105,1,0,0,109,4,1202,-1,1,495,1207,-3,0,10,1006,10,513,21102,0,1,-3,21201,-3,0,1,21202,-2,1,2,21101,0,1,3,21101,0,532,0,1106,0,537,109,-4,2106,0,0,109,5,1207,-3,1,10,1006,10,560,2207,-4,-2,10,1006,10,560,22102,1,-4,-4,1105,1,628,21201,-4,0,1,21201,-3,-1,2,21202,-2,2,3,21101,0,579,0,1105,1,537,22101,0,1,-4,21102,1,1,-1,2207,-4,-2,10,1006,10,598,21102,1,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,620,22102,1,-1,1,21101,0,620,0,106,0,495,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2106,0,0};
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

struct Wall
{
    AI2 robot_pos{0, 0};
    AI2 robot_dir{DIR_UP};
    set<AI2> whites;
    bool current_white() const { return whites.count(robot_pos) > 0; }
};

void operator+=(AI2& x, AI2 y)
{
    x[0] += y[0];
    x[1] += y[1];
}

int main()
{
    Machine m{input};
    Wall wall;
    set<AI2> painted;
    wall.whites.insert(wall.robot_pos);
    for (;;) {
        auto i = wall.current_white() ? 1 : 0;
        auto o1 = run_until_output_or_halt(m, VI64{i});
        if (!o1) {
            printf("Halt instead of first output.\n");
            break;
        }
        if (*o1 == 0) {
            wall.whites.erase(wall.robot_pos);
            // printf("BLACK");
        } else {
            assert(*o1 == 1);
            wall.whites.insert(wall.robot_pos);
            // printf("WHITE");
        }
        painted.insert(wall.robot_pos);
        auto o2 = run_until_output_or_halt(m, VI64{});
        if (!o1) {
            printf("Halt instead of second output.\n");
            break;
        }
        if (*o2 == 0) {
            wall.robot_dir = turn_left(wall.robot_dir);
            // printf(" LEFT\n");
        } else {
            assert(*o2 == 1);
            wall.robot_dir = turn_right(wall.robot_dir);
            // printf(" RIGHT\n");
        }
        wall.robot_pos += wall.robot_dir;
    }
    printf("painted: %d\n", ~painted);
    AI2 mn{0, 0}, mx{0, 0};
    for (auto w : wall.whites) {
        if (mn == mx) {
            mn = w;
            mx = AI2{w[0] + 1, w[1] + 1};
        } else {
            mn = AI2{min(mn[0], w[0]), min(mn[1], w[1])};
            mx = AI2{max(mx[0], w[0] + 1), max(mx[1], w[1] + 1)};
        }
    }
    FOR (y, mn[1], < mx[1]) {
        FOR (x, mn[0], < mx[0]) {
            printf("%c", wall.whites.count(AI2{x, y}) > 0 ? '*' : '.');
        }
        printf("\n");
    }
    return 0;
}