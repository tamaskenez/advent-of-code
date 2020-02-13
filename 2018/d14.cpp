#include "common.h"

using I64 = int64_t;

const I64 INPUT = 765071LL;
const VI iii = {7, 6, 5, 0, 7, 1};

int main()
{
    I64 e1 = 0;
    I64 e2 = 1;
    vector<int> recipes = {3, 7};
    I64 after = INPUT;
    I64 next_to_check = 0;
    bool done = false;
    for (; !done || ~recipes < after + 10;) {
        auto r1 = recipes[e1];
        auto r2 = recipes[e2];
        auto rr = r1 + r2;
        if (rr < 10) {
            recipes.PB(rr);
        } else {
            recipes.PB(rr / 10);
            recipes.PB(rr % 10);
        }
        e1 = (e1 + 1 + r1) % ~recipes;
        e2 = (e2 + 1 + r2) % ~recipes;
        while (!done && next_to_check + ~iii <= ~recipes) {
            bool ok = true;
            FOR (k, 0, < ~iii) {
                if (recipes[next_to_check + k] != iii[k]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                done = true;
                printf("p2 %lld\n", next_to_check);
            }
            ++next_to_check;
        }
    }
    FOR (i, after, < after + 10) {
        printf("%d", recipes[i]);
    }
    return 0;
}
