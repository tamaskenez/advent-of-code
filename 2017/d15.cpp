#include "common.h"

// Generator A starts with 722
// Generator B starts with 354

using U32 = uint32_t;
using U64 = uint64_t;
const U64 A_FAC = 16807;
const U64 B_FAC = 48271;

#if 1
const U32 GEN_A_START = 722;
const U32 GEN_B_START = 354;
#else
const U32 GEN_A_START = 65;
const U32 GEN_B_START = 8921;
#endif

struct Gen
{
    U32 v;
    U64 fac;
    Gen(U32 start, U64 fac) : v(start), fac(fac) {}
    void next() { v = (v * fac) % 2147483647UL; }
};

struct Gen2
{
    U32 v;
    U64 fac;
    U32 d;
    Gen2(U32 start, U64 fac, int d) : v(start), fac(fac), d(d) {}
    void next()
    {
        for (;;) {
            v = (v * fac) % 2147483647UL;
            if(v%d==0){return;}
        }
    }
};

int main()
{
    {
        Gen gena(GEN_A_START, A_FAC);
        Gen genb(GEN_B_START, B_FAC);
        int matchcount = 0;
        FOR (i, 0, < 40000000) {
            gena.next();
            genb.next();
            auto a = gena.v & 0xffff;
            auto b = genb.v & 0xffff;
            if (a == b) {
                ++matchcount;
            }
        }
        printf("%d\n", matchcount);
    }
    {
        Gen2 gena(GEN_A_START, A_FAC, 4);
        Gen2 genb(GEN_B_START, B_FAC, 8);
        int matchcount = 0;
        FOR (i, 0, < 5000000) {
            gena.next();
            genb.next();
            auto a = gena.v & 0xffff;
            auto b = genb.v & 0xffff;
            if (a == b) {
                ++matchcount;
            }
        }
        printf("%d\n", matchcount);
    }
    return 0;
}
// 608low