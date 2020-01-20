#include "common.h"

using i64 = int64_t;

struct Machine
{
    i64 a = 0, b = 0, c = 0, d = 0;
    int pc = 0;

    optional<i64*> maybe_reg_ptr(const string& n)
    {
        if (n == "a") {
            return &a;
        }
        if (n == "b") {
            return &b;
        }
        if (n == "c") {
            return &c;
        }
        if (n == "d") {
            return &d;
        }
        return {};
    }
    i64 value_or_read_reg(const string& n)
    {
        i64 x;
        auto m_px = maybe_reg_ptr(n);
        if (m_px) {
            x = **m_px;
        } else {
            x = stoi(n);
        }
        return x;
    }
};

void execute(Machine& m, const VS& ins)
{
    for (;;) {
        if (m.pc < 0 || ~ins <= m.pc) {
            printf("invalid pc: %d, exit\n", m.pc);
            break;
        }
        auto& in = ins[m.pc];
        auto vs = split(in, " ");
        assert(!vs.empty());
        if (vs[0] == "cpy") {
            assert(~vs == 3);
            // cpy x y copies x (either an integer or the value of a register) into register y.
            auto x = m.value_or_read_reg(vs[1]);
            auto m_py = m.maybe_reg_ptr(vs[2]);
            assert(m_py);
            **m_py = x;
            ++m.pc;
        } else if (vs[0] == "inc") {
            // inc x increases the value of register x by one.
            assert(~vs == 2);
            auto m_x = m.maybe_reg_ptr(vs[1]);
            assert(m_x);
            ++(**m_x);
            ++m.pc;
        } else if (vs[0] == "dec") {
            // dec x decreases the value of register x by one.
            assert(~vs == 2);
            auto m_x = m.maybe_reg_ptr(vs[1]);
            assert(m_x);
            --(**m_x);
            ++m.pc;
        } else if (vs[0] == "jnz") {
            // jnz x y jumps to an instruction y away (positive means forward; negative means
            // backward), but only if x is not zero.
            assert(~vs == 3);
            auto x = m.value_or_read_reg(vs[1]);
            auto y = m.value_or_read_reg(vs[2]);
            if (x != 0) {
                m.pc += y;
            } else {
                ++m.pc;
            }
        } else {
            UNREACHABLE;
        }
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    {
        Machine m;
        execute(m, lines);
        printf("m.a: %lld\n", m.a);
    }
    {
        Machine m;
        m.c = 1;
        execute(m, lines);
        printf("m.a: %lld\n", m.a);
    }
    return 0;
}
