#include "common.h"

using i64 = int64_t;

struct Computer
{
    i64 a = 1, b = 0;
    i64 pc = 0;

    i64& get_reg(const string& x)
    {
        if (x == "a") {
            return a;
        } else if (x == "b") {
            return b;
        }
        assert(false);
    }
};

struct Instr
{
    string code;
    string reg;
};

bool is_even(i64 x)
{
    return (x & 1) == 0;
}

void execute_instr(Computer& comp, const string& instr)
{
    auto vs = split(instr, " ,");
    auto code = vs[0];
    if (code == "hlf") {
        auto reg = vs[1];
        assert(~vs == 2);
        comp.get_reg(reg) /= 2;
        ++comp.pc;
    } else if (code == "tpl") {
        auto reg = vs[1];
        assert(~vs == 2);
        auto& r = comp.get_reg(reg);
        assert(r <= INT64_MAX / 3);
        r *= 3;
        ++comp.pc;
    } else if (code == "inc") {
        auto reg = vs[1];
        assert(~vs == 2);
        auto& r = comp.get_reg(reg);
        assert(r < INT64_MAX - 1);
        ++r;
        ++comp.pc;
    } else if (code == "jmp") {
        auto offset = stoi(vs[1]);
        assert(~vs == 2);
        comp.pc += offset;
    } else if (code == "jie") {
        assert(~vs == 3);
        auto reg = vs[1];
        auto offset = stoi(vs[2]);
        if (is_even(comp.get_reg(reg))) {
            comp.pc += offset;
        } else {
            ++comp.pc;
        }
    } else if (code == "jio") {
        assert(~vs == 3);
        auto reg = vs[1];
        auto offset = stoi(vs[2]);
        if (comp.get_reg(reg) == 1) {
            comp.pc += offset;
        } else {
            ++comp.pc;
        }
    } else {
        assert(false);
    }
}

void execute_instrs(const VS& instrs)
{
    Computer computer;
    for (;;) {
        assert(0 <= computer.pc && computer.pc < ~instrs);
        execute_instr(computer, instrs[computer.pc]);
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d23_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    execute_instrs(lines);
    return 0;
}

// not 120