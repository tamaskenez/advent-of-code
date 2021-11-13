#include <iostream>

#include "common.h"

using u64 = uint64_t;

struct Mask
{
    u64 mask{0};
    u64 value{0};
};

struct AMask
{
    u64 ormask{0};  // bit to set to 1
    u64 xmask{0};   // bits with x
    vector<int> xs;
};

struct Machine
{
    Mask mask;
    map<u64, u64> mem;
    void set_mem(u64 addr, u64 v)
    {
        auto there = mem[addr];
        mem[addr] = mask.value | (v & ~mask.mask);
    }
};

struct AMachine
{
    AMask amask;
    map<u64, u64> mem;
    void set_mem(u64 addr, u64 v)
    {
        auto baseaddr = (addr | amask.ormask) & ~amask.xmask;
        FOR (i, (u64)0, < (u64)1 << ~amask.xs) {
            auto a = baseaddr;
            FOR (j, 0, < ~amask.xs) {
                if (i & ((u64)1 << j)) {
                    a |= (u64)1 << amask.xs[j];
                }
            }
            mem[a] = v;
        }
    }
};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d14_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    Machine m;
    AMachine am;
    Mask mask;
    for (auto l : lines) {
        if (eat_string(l, "mask = ")) {
            assert(~l == 36);
            Mask mask;
            AMask amask;
            FOR (i, 0, < 36) {
                auto c = l[35 - i];
                if (c == '0') {
                    mask.mask |= (u64)1 << i;
                } else if (c == '1') {
                    mask.mask |= (u64)1 << i;
                    mask.value |= (u64)1 << i;
                    amask.ormask |= (u64)1 << i;
                } else {
                    assert(c == 'X');
                    amask.xmask |= (u64)1 << i;
                    amask.xs.PB(i);
                }
            }
            m.mask = mask;
            am.amask = amask;
        } else if (eat_string(l, "mem[")) {
            auto addr = eat_integer<u64>(l).value();
            bool b = eat_string(l, "] = ");
            assert(b);
            auto v = eat_integer<u64>(l).value();
            m.set_mem(addr, v);
            am.set_mem(addr, v);
        } else {
            assert(false);
        }
    }
    u64 sum = 0;
    for (auto [k, v] : m.mem) {
        sum += v;
    }
    cout << "P1: " << sum << endl;

    sum = 0;
    for (auto [k, v] : am.mem) {
        sum += v;
    }
    cout << "P2: " << sum << endl;
    return 0;
}

// not 56998680342811752

// 22:3
