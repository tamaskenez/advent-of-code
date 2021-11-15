#include "common.h"

using u64 = uint64_t;

struct Code
{
    u64 code = 20151125;
    u64 next()
    {
        code = (code * 252533) % 33554393;
        return code;
    }
};

// row 2947, column 3029.
int main()
{
    Code cg;
    // map<PII, u64> codes;
    PII rc(1, 1);
    for (;;) {
        // codes[rc]=cg.code;
        if (rc == make_pair(2947, 3029)) {
            printf("part1 %s\n", to_string(cg.code).c_str());
            break;
        }
        cg.next();
        --rc.FST;
        ++rc.SND;
        if (rc.FST == 0) {
            rc.FST = rc.SND;
            rc.SND = 1;
        }
    }
#if 0
    FOR(r,1,<7){
        FOR(c,1,<7){
            auto it = codes.find(make_pair(r,c));
            if(it!=codes.end()){
                printf("%s ",to_string(it->second).c_str());
            } else {
                printf("? ");
            }
        }
        printf("\n");
    }
#endif
    return 0;
}
