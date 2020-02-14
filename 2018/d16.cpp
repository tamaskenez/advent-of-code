#include "common.h"

VI to_ints(const VS& ss)
{
    VI vs;
    vs.reserve(~ss);
    for (auto& s : ss) {
        vs.PB(stoi(s));
    }
    return vs;
}

enum Ops
{
    ADDR,
    ADDI,
    MULR,
    MULI,
    BANR,
    BANI,
    BORR,
    BORI,
    SETR,
    SETI,
    GTIR,
    GTRI,
    GTRR,
    EQIR,
    EQRI,
    EQRR,
    OPCODE_COUNT
};

void execute(const VI& is, VI& regs)
{
    assert(~is == 4);
    assert_between_co(is[0], 0, (int)OPCODE_COUNT);

    auto rega = [&regs, &is]() -> int { return regs[is[1]]; };
    auto regb = [&regs, &is]() -> int { return regs[is[2]]; };
    auto regc = [&regs, &is]() -> int& { return regs[is[3]]; };
    auto vala = [&is]() -> int { return is[1]; };
    auto valb = [&is]() -> int { return is[2]; };
    switch ((Ops)is[0]) {
        case ADDR:
            regc() = rega() + regb();
            break;
        case ADDI:
            regc() = rega() + valb();
            break;
        case MULR:
            regc() = rega() * regb();
            break;
        case MULI:
            regc() = rega() * valb();
            break;
        case BANR:
            regc() = rega() & regb();
            break;
        case BANI:
            regc() = rega() & valb();
            break;
        case BORR:
            regc() = rega() | regb();
            break;
        case BORI:
            regc() = rega() | valb();
            break;
        case SETR:
            regc() = rega();
            break;
        case SETI:
            regc() = vala();
            break;
        case GTIR:
            regc() = vala() > regb() ? 1 : 0;
            break;
        case GTRI:
            regc() = rega() > valb() ? 1 : 0;
            break;
        case GTRR:
            regc() = rega() > regb() ? 1 : 0;
            break;
        case EQIR:
            regc() = vala() == regb() ? 1 : 0;
            break;
        case EQRI:
            regc() = rega() == valb() ? 1 : 0;
            break;
        case EQRR:
            regc() = rega() == regb() ? 1 : 0;
            break;
        default:
            UNREACHABLE;
    }
}

unordered_map<int, int> i2r;

void execute_program(const VS& program)
{
    VI regs(4, 0);
    for (auto& l : program) {
        auto vs = to_ints(split(l, " \t"));
        vs[0] = i2r.at(vs[0]);
        execute(vs, regs);
    }
    printf("reg0 %d\n", regs[0]);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d16_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int counter3 = 0;
    map<int, set<int>> inop_to_realop;
    VS program;
    FOR (i, 0, < ~lines) {
        auto& li = lines[i];
        if (li.empty()) {
            continue;
        }
        if (starts_with(li, "Before: ")) {
            auto sbf = split(li.substr(8), "[], \t");
            assert(~sbf == 4);
            auto sop = split(lines[++i], " \t");
            ++i;
            assert(starts_with(lines[i], "After: "));
            auto saf = split(lines[i].substr(7), "[], \t");
            assert(~saf == 4);
            //
            auto bef0 = to_ints(sbf);
            auto ops = to_ints(sop);
            auto inop = ops[0];
            auto aft0 = to_ints(saf);
            int count = 0;
            set<int> realop;
            FOR (op, 0, < (int)OPCODE_COUNT) {
                ops[0] = op;
                auto bef = bef0;
                execute(ops, bef);
                if (bef == aft0) {
                    ++count;
                    realop.insert(op);
                }
            }
            assert(!realop.empty());
            if (contains(inop_to_realop, inop)) {
                auto& s1 = inop_to_realop[inop];
                s1 = vector2set(set_intersection(BE(s1), BE(realop)));
                assert(!s1.empty());
            } else {
                inop_to_realop[inop] = realop;
            }
            if (count >= 3) {
                ++counter3;
            }
        } else {
            program.PB(lines[i]);
            auto vs = to_ints(split(lines[i], " \t"));
        }
    }
    printf("%d\n", counter3);
    for (; true;) {
        for (auto& kv : inop_to_realop) {
            if (~kv.second != 1) {
                continue;
            }
            auto single_op = *kv.second.begin();
            for (auto& kv2 : inop_to_realop) {
                if (kv.first == kv2.first) {
                    continue;
                }
                kv2.second.erase(single_op);
                assert(!kv2.second.empty());
            }
        }
        int nonsing = 0;
        for (auto& kv : inop_to_realop) {
            assert(!kv.second.empty());
            if (~kv.second > 1) {
                ++nonsing;
            }
        }
        if (nonsing == 0) {
            break;
        }
    }

    for (auto& kv : inop_to_realop) {
        assert(~kv.second == 1);
        i2r[kv.first] = *kv.second.begin();
    }
    execute_program(program);
    return 0;
}
