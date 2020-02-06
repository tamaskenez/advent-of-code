#include "common.h"

const int INPUT = 349;
// const int INPUT=3;
int main()
{
    {
        VI buf = {0};
        int cp = 0;
        FOR (i, 1, <= 2017) {
            cp = (cp + INPUT) % ~buf;
            buf.insert(buf.begin() + cp + 1, i);
            cp = (cp + 1) % ~buf;
        }
        cp = (cp + 1) % ~buf;
        printf("%d\n", buf[cp]);
    }
    {
        int buf1 = -1;
        int bufsize = 1;
        int cp = 0;
        FOR (i, 1, <= 50000000) {
            cp = (cp + INPUT) % bufsize;
            int insertpos = cp + 1;
            if (insertpos == 1) {
                buf1 = i;
            }
            ++bufsize;
            cp = (cp + 1) % bufsize;
        }
        printf("%d\n", buf1);
    }
    return 0;
}

// 417 low
