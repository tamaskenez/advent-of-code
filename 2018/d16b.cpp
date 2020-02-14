#include "common.h"

VI map_stoi(const VS& ss)
{
    VI r;
    for (auto& s : ss) {
        r.PB(stoi(s));
    }
    return r;
}

enum Opcodes
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
    OPCODE_COUNT,
};

void execute(const VI& bytes, VI& regs)
{
    assert(~bytes == 4);
    assert(~regs == 4);
    auto ra = [&bytes, &regs]() { return regs[bytes[1]]; };
    auto rb = [&bytes, &regs]() { return regs[bytes[2]]; };
    auto va = [&bytes]() { return bytes[1]; };
    auto vb = [&bytes]() { return bytes[2]; };
    auto rc = [&bytes, &regs]() -> int& { return regs[bytes[3]]; };
    switch ((Opcodes)bytes[0]) {
        case ADDR:
            rc() = ra() + rb();
            break;
        case ADDI:
            rc() = ra() + vb();
            break;
        case MULR:
            rc() = ra() * rb();
            break;
        case MULI:
            rc() = ra() * vb();
            break;
        case BANR:
            rc() = ra() & rb();
            break;
        case BANI:
            rc() = ra() & vb();
            break;
        case BORR:
            rc() = ra() | rb();
            break;
        case BORI:
            rc() = ra() | vb();
            break;
        case SETR:
            rc() = ra();
            break;
        case SETI:
            rc() = va();
            break;
        case GTIR:
            rc() = va() > rb() ? 1 : 0;
            break;
        case GTRI:
            rc() = ra() > vb() ? 1 : 0;
            break;
        case GTRR:
            rc() = ra() > rb() ? 1 : 0;
            break;
        case EQIR:
            rc() = va() == rb() ? 1 : 0;
            break;
        case EQRI:
            rc() = ra() == vb() ? 1 : 0;
            break;
        case EQRR:
            rc() = ra() == rb() ? 1 : 0;
            break;
        default:
            UNREACHABLE;
    }
}

map<int, int> byte2op;

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d16_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    VS program;
    int counter3 = 0;
    map<int, set<int>> possibles;
    FOR (i, 0, < ~lines) {
        auto& li = lines[i];
        if (li.empty()) {
            continue;
        }
        if (starts_with(li, "Before: ")) {
            const auto before = map_stoi(split(li.substr(8), "[] \t,"));
            auto bytes = map_stoi(split(lines[++i], " \t"));
            ++i;
            assert(starts_with(lines[i], "After: "));
            auto after = map_stoi(split(lines[i].substr(7), "[] \t,"));
            int couldbe_counter = 0;
            assert(~before == 4);
            assert(~bytes == 4);
            assert(~after == 4);
            auto op0 = bytes[0];
            FOR (opcode, 0, < OPCODE_COUNT) {
                bytes[0] = opcode;
                auto b = before;
                execute(bytes, b);
                if (b == after) {
                    ++couldbe_counter;
                    possibles[op0].insert(opcode);
                }
            }
            if (couldbe_counter >= 3) {
                ++counter3;
            }
        } else {
            program.PB(li);
        }
    }
    printf("counter3 %d\n", counter3);

    for (;;) {
        for (auto& kv : possibles) {
            if (~kv.second != 1) {
                continue;
            }
            auto single_op = *kv.second.begin();
            for (auto& p : possibles) {
                if (p.first == kv.first) {
                    continue;
                }
                p.second.erase(single_op);
                assert(!p.second.empty());
            }
        }
        int nonsingles = 0;
        for (auto& kv : possibles) {
            if (~kv.second > 1) {
                ++nonsingles;
            }
        }
        if (nonsingles == 0) {
            break;
        }
        printf("nons %d\n", nonsingles);
    }

    for (auto& kv : possibles) {
        assert(~kv.second==1);
        byte2op[kv.first]=*kv.second.begin();
    }

    VI regs(4,0);
    for(auto&l:program){
        auto bytes = map_stoi(split(l, " \t"));
        bytes[0] = byte2op.at(bytes[0]);
        execute(bytes, regs);
    }
    printf("r0 %d\n", regs[0]);
    return 0;
}
