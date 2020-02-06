#include "common.h"

using I64 = int64_t;

void f()
{
    I64 b = 84;
    I64 c = b;
    b = 100 * b + 100000;
    c = b + 17000;
    I64 h = 0;
label_23:
    I64 f = 1;
    I64 d = 2;
    for (I64 d = 2; d != b; ++d) {
        if (b%d==0){
            auto bod = b/d;
            if(2<=bod&&bod<b){
                f=0;
            }
        }
        /*
        for (I64 e = 2; e != b; ++e) {
            if (d * e == b) {
                f = 0;
            }
        }
         */
    }
    if (f == 0) {
        ++h;
    }
    if (b != c) {
        b += 17;
        goto label_23;
    }
    printf("h: %lld\n", h);
}

struct Vm
{
    bool part2 = false;
    map<char, I64> regs;
    optional<I64> freq_last_snd;
    int pc = 0;
    vector<I64> input, output;
    bool terminated = false;
    bool waiting = false;
    int mul_count = 0;

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
    auto prev_regs = vm.regs;
    for (;;) {
        if (vm.pc < 0 || ~is <= vm.pc) {
            vm.terminated = true;
            printf("exit, pc: %d\n", vm.pc);
            return;
        }

        printf("\n\t");
        for (auto& kv : vm.regs) {
            printf("%c: %lld ", kv.first, kv.second);
        }
        printf("\n-- [%d] %s, with\n\t", vm.pc, is[vm.pc].c_str());

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
            auto z = vm.read(xs[1]) + vm.read(xs[2]);
            vm.reg_ref(xs[1]) = z;
        } else if (xs[0] == "sub") {
            assert(~xs == 3);
            auto z = vm.read(xs[1]) - vm.read(xs[2]);
            vm.reg_ref(xs[1]) = z;
        } else if (xs[0] == "mul") {
            assert(~xs == 3);
            auto z = (I64)vm.read(xs[1]) * (I64)vm.read(xs[2]);
            vm.reg_ref(xs[1]) = z;
            ++vm.mul_count;
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
        } else if (xs[0] == "jnz") {
            assert(~xs == 3);
            if (vm.read(xs[1]) != 0) {
                vm.pc += vm.read(xs[2]);
                --vm.pc;
            }
        } else {
            UNREACHABLE;
        }
        ++vm.pc;
        for (auto& kv : vm.regs) {
            printf("%c: %lld ", kv.first, kv.second);
        }
        printf("\n");
        int a = 3;
    }
}

int main()
{
    f();
    return 0;
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d23_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

   if(0) {
        Vm vm;
        execute(vm, lines);
        printf("mul count %d\n", vm.mul_count);
    }
    {
        printf("start part2\n");
        Vm vm;
        vm.regs['a'] = 1;
        execute(vm, lines);
        auto h = vm.regs['h'];
        printf("h %lld\n", h);
    }

    return 0;
}

// 191 low