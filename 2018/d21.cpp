#include "common.h"

using I64 = int64_t;

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

const VS inames = {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
                   "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"};

struct Instr
{
    Ops op;
    AI3 args;
};

const bool debug = false;
struct Vm
{
    array<I64, 6> regs;
    I64 ip = 0;
    maybe<int> ip_bound;
    Vm() { regs.fill(0); }
    void execute(const Instr& is)
    {
        if (ip_bound) {
            regs[*ip_bound] = ip;
        }
        if (debug) {
            printf("[%lld] {%lld %lld %lld %lld %lld %lld} %s %d %d %d  ->  ", ip, regs[0], regs[1],
                   regs[2], regs[3], regs[4], regs[5], inames[is.op].c_str(), is.args[0],
                   is.args[1], is.args[2]);
        }
        auto rega = [this, &is]() -> I64 {
            int rn = is.args[0];
            return regs[rn];
        };
        auto regb = [this, &is]() -> I64 { return regs[is.args[1]]; };
        auto regc = [this, &is]() -> I64& { return regs[is.args[2]]; };
        auto vala = [&is]() -> I64 { return is.args[0]; };
        auto valb = [&is]() -> I64 { return is.args[1]; };

        if(ip==28){
            static unordered_set<I64> r2s;
            static vector<I64> so_far;
            if(contains(r2s, regs[2])){
                printf("part2 %lld\n", so_far.back());
                exit(0);
            }
            so_far.PB(regs[2]);
            r2s.insert(regs[2]);
            //printf("r2: %lld\n", regs[2]);
            //exit(0);
        }
        {
            switch (is.op) {
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
        if (ip_bound) {
            ip = regs[*ip_bound];
        }
        if (debug) {
            printf("-> [%lld] {%lld %lld %lld %lld %lld %lld}\n", ip, regs[0], regs[1], regs[2],
                   regs[3], regs[4], regs[5]);
        }
        ++ip;
    }
};

void execute_program(Vm& vm, const vector<Instr>& program)
{
    for (;;) {
        if (vm.ip < 0 || ~program <= vm.ip) {
            printf("exit ip %lld\n", vm.ip);
            break;
        }
        vm.execute(program[vm.ip]);
    }
    printf("reg0 %lld\n", vm.regs[0]);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d21_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<Instr> program;
    maybe<int> ip_bound;
    FOR (i, 0, < ~lines) {
        auto& li = lines[i];
        if (li.empty()) {
            continue;
        }
        if (starts_with(li, "#ip")) {
            auto vs = map_to_vec(split(li, "#pi \t"), CALL(stoi));
            assert(~vs == 1);
            ip_bound = vs[0];
        } else {
            auto xs = split(li, " \t");
            assert(~xs == 4);
            auto it = find(BE(inames), xs[0]);
            assert(it != inames.end());
            int i = it - inames.begin();
            assert_between_co(i, 0, (int)OPCODE_COUNT);
            AI3 args = {stoi(xs[1]), stoi(xs[2]), stoi(xs[3])};
            program.PB(Instr{(Ops)i, args});
        }
    }
    {
        Vm vm;
        vm.regs[0] = 10000000000000;
        vm.ip_bound = ip_bound;
        execute_program(vm, program);
    }
    return 0;
}
