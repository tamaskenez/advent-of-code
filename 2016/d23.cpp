#include "common.h"

using i64 = int64_t;

struct Ins
{
    enum Opcode
    {
        INC,
        DEC,
        CPY,
        JNZ,
        TGL
    } opcode;
    enum Reg
    {
        REG_A,
        REG_B,
        REG_C,
        REG_D,
        IMMED,
        UNUSED
    };
    pair<Reg, i64> arg0, arg1;
};

const char* to_cstring(Ins::Opcode o)
{
    switch (o) {
        case Ins::INC:
            return "INC";
        case Ins::DEC:
            return "DEC";
        case Ins::CPY:
            return "CPY";
        case Ins::JNZ:
            return "JNZ";
        case Ins::TGL:
            return "TGL";
    }
    UNREACHABLE;
    return "<INVALID>";
}

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
    optional<i64*> maybe_reg_ptr(pair<Ins::Reg, i64> n)
    {
        if (n.FST == Ins::REG_A) {
            return &a;
        }
        if (n.FST == Ins::REG_B) {
            return &b;
        }
        if (n.FST == Ins::REG_C) {
            return &c;
        }
        if (n.FST == Ins::REG_D) {
            return &d;
        }
        fprintf(stderr, "ERROR1\n");
        terminate();
        return {};
    }
    i64 value_or_read_reg(pair<Ins::Reg, i64> n)
    {
        if (n.FST == Ins::REG_A) {
            return a;
        }
        if (n.FST == Ins::REG_B) {
            return b;
        }
        if (n.FST == Ins::REG_C) {
            return c;
        }
        if (n.FST == Ins::REG_D) {
            return d;
        }
        if (n.FST == Ins::IMMED) {
            return n.SND;
        }
        fprintf(stderr, "ERROR2\n");
        terminate();
        return 0;
    }
};

pair<Ins::Reg, i64> str_to_val_or_reg(const string& s)
{
    if (s == "a") {
        return make_pair(Ins::REG_A, 0);
    }
    if (s == "b") {
        return make_pair(Ins::REG_B, 0);
    }
    if (s == "c") {
        return make_pair(Ins::REG_C, 0);
    }
    if (s == "d") {
        return make_pair(Ins::REG_D, 0);
    }
    return make_pair(Ins::IMMED, stoi(s));
}

pair<Ins::Reg, i64> str_to_reg(const string& s)
{
    auto pp = str_to_val_or_reg(s);
    assert(pp.FST != Ins::IMMED);
    return pp;
}

Ins string_to_ins(const string& in)
{
    auto vs = split(in, " ");
    assert(!vs.empty());
    if (vs[0] == "cpy") {
        assert(~vs == 3);
        return Ins{Ins::CPY, str_to_val_or_reg(vs[1]), str_to_reg(vs[2])};
    }
    if (vs[0] == "inc") {
        assert(~vs == 2);
        return Ins{Ins::INC, str_to_reg(vs[1]), {Ins::UNUSED, 0}};
    }
    if (vs[0] == "dec") {
        assert(~vs == 2);
        return Ins{Ins::DEC, str_to_reg(vs[1]), {Ins::UNUSED, 0}};
    }
    if (vs[0] == "jnz") {
        assert(~vs == 3);
        return Ins{Ins::JNZ, str_to_val_or_reg(vs[1]), str_to_val_or_reg(vs[2])};
    }
    if (vs[0] == "tgl") {
        assert(~vs == 2);
        return Ins{Ins::TGL, str_to_val_or_reg(vs[1]), {Ins::UNUSED, 0}};
    }
    UNREACHABLE;
    return {};
}

void execute(Machine& m, vector<Ins> ins);

void execute(Machine& m, VS ins)
{
    if(true){
        vector<Ins> ins2;
        for(auto&s:ins){
            ins2.PB(string_to_ins(s));
        }
        execute(m,ins2);
        return;
    }
    int counter = 0;
    for (;; ++counter) {
        if (m.pc < 0 || ~ins <= m.pc) {
            printf("invalid pc: %d, exit\n", m.pc);
            break;
        }
        auto& in = ins[m.pc];
        if (counter % 1000000 == 0) {
            printf("pc %2d: %25s | %lld %lld %lld %lld\n", m.pc, in.c_str(), m.a, m.b, m.c, m.d);
        }
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
        } else if (vs[0] == "tgl") {
            assert(~vs == 2);
            auto x = m.value_or_read_reg(vs[1]);
            auto xx = m.pc + x;
            if (is_between_co<long long>(xx, 0, ~ins)) {
                auto& in = ins[xx];
                if (starts_with(in, "inc")) {
                    in.replace(0, 3, "dec");
                } else if (starts_with(in, "dec")) {
                    in.replace(0, 3, "inc");
                } else if (starts_with(in, "cpy")) {
                    in.replace(0, 3, "jnz");
                } else if (starts_with(in, "jnz")) {
                    in.replace(0, 3, "cpy");
                } else if (starts_with(in, "tgl")) {
                    in.replace(0, 3, "inc");
                } else {
                    UNREACHABLE;
                }
            }
            ++m.pc;
        } else {
            UNREACHABLE;
        }
    }
}

void execute(Machine& m, vector<Ins> ins)
{
    int counter = 0;
    for (;; ++counter) {
        if (m.pc < 0 || ~ins <= m.pc) {
            printf("invalid pc: %d, exit\n", m.pc);
            break;
        }
        auto& in = ins[m.pc];
        if (counter % 100000000 == 0) {
            printf("pc %2d: %25s | %lld %lld %lld %lld\n", m.pc, to_cstring(in.opcode), m.a, m.b,
                   m.c, m.d);
        }
        if (in.opcode == Ins::CPY) {
            // cpy x y copies x (either an integer or the value of a register) into register y.
            auto x = m.value_or_read_reg(in.arg0);
            auto m_py = m.maybe_reg_ptr(in.arg1);
            assert(m_py);
            **m_py = x;
            ++m.pc;
        } else if (in.opcode == Ins::INC) {
            // inc x increases the value of register x by one.
            auto m_x = m.maybe_reg_ptr(in.arg0);
            assert(m_x);
            ++(**m_x);
            ++m.pc;
        } else if (in.opcode == Ins::DEC) {
            // dec x decreases the value of register x by one.
            auto m_x = m.maybe_reg_ptr(in.arg0);
            --(**m_x);
            ++m.pc;
        } else if (in.opcode == Ins::JNZ) {
            // jnz x y jumps to an instruction y away (positive means forward; negative means
            // backward), but only if x is not zero.
            auto x = m.value_or_read_reg(in.arg0);
            auto y = m.value_or_read_reg(in.arg1);
            if (x != 0) {
                m.pc += y;
            } else {
                ++m.pc;
            }
        } else if (in.opcode == Ins::TGL) {
            auto x = m.value_or_read_reg(in.arg0);
            auto xx = m.pc + x;
            if (is_between_co<long long>(xx, 0, ~ins)) {
                auto& in = ins[xx];
                switch (in.opcode) {
                    case Ins::INC:
                        in.opcode = Ins::DEC;
                        break;
                    case Ins::DEC:
                        in.opcode = Ins::INC;
                        break;
                    case Ins::CPY:
                        in.opcode = Ins::JNZ;
                        break;
                    case Ins::JNZ:
                        in.opcode = Ins::CPY;
                        break;
                    case Ins::TGL:
                        in.opcode = Ins::INC;
                        break;
                    default:
                        UNREACHABLE;
                }
            }
            ++m.pc;
        } else {
            UNREACHABLE;
        }
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d23_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    {
        Machine m;
        m.a = 7;
        execute(m, lines);
        printf("m.a: %lld\n", m.a);
    }
    {
        Machine m;
        m.a = 12;
        execute(m, lines);
        printf("m.a: %lld\n", m.a);
    }
    return 0;
}
