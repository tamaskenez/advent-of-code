#include "common.h"

using I64 = int64_t;

struct Vm
{
    bool part2 = false;
    map<char, I64> regs;
    optional<I64> freq_last_snd;
    int pc = 0;
    vector<I64> input, output;
    bool terminated = false;
    bool waiting = false;

    Vm() = default;
    explicit Vm(int program_id) : part2(true) { regs['p'] = program_id; }

    I64 read(const string& s)
    {
        if (~s == 1 && isalpha(s[0])) {
            return regs[s[0]];
        }
        return stoi(s);
    }
    I64& reg_ref(const string& s)
    {
        assert(~s == 1 && isalpha(s[0]));
        return regs[s[0]];
    }
};

void execute(Vm& vm, const VS& is)
{
    assert(!vm.terminated);
    vm.waiting = false;
    bool first_rcv_done = false;
    for (;;) {
        if (vm.pc < 0 || ~is <= vm.pc) {
            vm.terminated = true;
            printf("exit, pc: %d\n", vm.pc);
            return;
        }
        auto xs = split(is[vm.pc], " ");
        if (xs[0] == "snd") {
            assert(~xs == 2);
            auto n = vm.read(xs[1]);
            if (!vm.part2) {
                vm.freq_last_snd = n;
            } else {
                vm.output.PB(n);
            }
        } else if (xs[0] == "set") {
            assert(~xs == 3);
            vm.reg_ref(xs[1]) = vm.read(xs[2]);
        } else if (xs[0] == "add") {
            assert(~xs == 3);
            auto z = (I64)vm.read(xs[1]) + (I64)vm.read(xs[2]);
            vm.reg_ref(xs[1]) = z;
        } else if (xs[0] == "mul") {
            assert(~xs == 3);
            auto z = (I64)vm.read(xs[1]) * (I64)vm.read(xs[2]);
            vm.reg_ref(xs[1]) = z;
        } else if (xs[0] == "mod") {
            assert(~xs == 3);
            auto z = (I64)vm.read(xs[1]) % (I64)vm.read(xs[2]);
            vm.reg_ref(xs[1]) = z;
        } else if (xs[0] == "rcv") {
            assert(~xs == 2);
            if (!vm.part2) {
                if (vm.read(xs[1]) != 0) {
                    auto f = *vm.freq_last_snd;
                    if (!first_rcv_done) {
                        printf("first rcv: %lld\n", f);
                        first_rcv_done = true;
                    }
                }
                return;
            } else {
                if (!vm.input.empty()) {
                    auto q = vm.input[0];
                    vm.input.erase(vm.input.begin());
                    vm.reg_ref(xs[1]) = q;
                } else {
                    vm.waiting = true;
                    return;
                }
            }
        } else if (xs[0] == "jgz") {
            assert(~xs == 3);
            if (vm.read(xs[1]) > 0) {
                vm.pc += vm.read(xs[2]);
                --vm.pc;
            }
        } else {
            UNREACHABLE;
        }
        ++vm.pc;
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d18_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    {
        Vm vm;
        execute(vm, lines);
    }

    {
        Vm vm0(0), vm1(1);
        int p1sendcount = 0;
        for (;;) {
            bool change = false;
            if (!vm0.terminated) {
                if (!vm0.waiting || !vm0.input.empty()) {
                    execute(vm0, lines);
                    vm1.input.insert(vm1.input.end(), BE(vm0.output));
                    vm0.output.clear();
                    change = true;
                }
            }
            if (!vm1.terminated) {
                if (!vm1.waiting || !vm1.input.empty()) {
                    execute(vm1, lines);
                    p1sendcount += ~vm1.output;
                    vm0.input.insert(vm0.input.end(), BE(vm1.output));
                    vm1.output.clear();
                    change = true;
                }
            }
            if (!change) {
                break;
            }
        }
        printf("%d\n", p1sendcount);
    }
    return 0;
}

// 191 low