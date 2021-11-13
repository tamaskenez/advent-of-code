#include "common.h"

VS iterate(const VS& A)
{
    int w = ~A[0];
    int h = ~A;
    auto B = A;
    FOR (r, 0, < h) {
        assert(~A[r]==w);
        FOR (c, 0, < w) {
            int n_occ = 0;
            FOR (rr, max(r - 1, 0), < min(r + 2, h)) {
                FOR (cc, max(c - 1, 0), < min(c + 2, w)) {
                    if (rr == r && cc == c) {
                        continue;
                    }
                    if (A[rr][cc] == '#') {
                        ++n_occ;
                    }
                }
            }
            if (A[r][c] == 'L' && n_occ == 0) {
                B[r][c] = '#';
            } else if (A[r][c] == '#' && n_occ >= 4) {
                B[r][c] = 'L';
            }
        }
    }
    return B;
}

bool is_occupied_towards(AI2 rc, AI2 drc, const VS&A) {
    int w = ~A[0];
    int h = ~A;
    for(;;){
      rc += drc;
      if(rc[0] < 0 || h <= rc[0] || rc[1] < 0 || w <= rc[1]){return false;}
      auto c = A[rc[0]][rc[1]];
      if(c=='L'){return false; }
      if(c=='#'){return true; }
    }
}

VS iterate2(const VS& A)
{
    int w = ~A[0];
    int h = ~A;
    auto B = A;
    FOR (r, 0, < h) {
        assert(~A[r]==w);
        FOR (c, 0, < w) {
            int n_occ = 0;
            FOR (dr, -1, <=1) {
                FOR (dc, -1, <=1) {
                    if(dr==0&&dc==0){continue;}
                    if(is_occupied_towards(AI2{r,c},AI2{dr,dc},A)){
                      n_occ++;
                    }
                }
            }
            if (A[r][c] == 'L' && n_occ == 0) {
                B[r][c] = '#';
            } else if (A[r][c] == '#' && n_occ >= 5) {
                B[r][c] = 'L';
            }
        }
    }
    return B;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d11_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    auto s0 = lines;
    printf("%d x %d\n", ~s0, ~s0[0]);
    for (;;) {
        auto s1 = iterate(s0);
        if (s1 == s0) {
            break;
        }
        swap(s0, s1);
    }
    int n_occ = 0;
    for (auto& r : s0) {
        for (auto c : r) {
            if (c == '#') {
                n_occ++;
            }
        }
    }
    printf("P1: %d\n", n_occ);

    s0 = lines;
    for (;;) {
        auto s1 = iterate2(s0);
        if (s1 == s0) {
            break;
        }
        swap(s0, s1);
    }
    n_occ = 0;
    for (auto& r : s0) {
        for (auto c : r) {
            if (c == '#') {
                n_occ++;
            }
        }
    }
    printf("P2: %d\n", n_occ);
    return 0;
}
// 2167 low
//17
