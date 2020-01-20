#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d06_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    const int N = 8;
    array<map<char, int>, N> m;
    for (auto& l : lines) {
        assert(~l == N);
        FOR (i, 0, < N) {
            auto c = l[i];
            ++m[i][c];
        }
    }
    printf("part1 ");
    FOR (i, 0, < N) {
        int mm = 0;
        char c;
        for (auto& kv : m[i]) {
            if (kv.second > mm) {
                c = kv.first;
                mm = kv.second;
            }
        }
        printf("%c", c);
    }
    printf("\n");

    printf("part2 ");
    FOR (i, 0, < N) {
        int mm = INT_MAX;
        char c;
        for (auto& kv : m[i]) {
            if (kv.second < mm) {
                c = kv.first;
                mm = kv.second;
            }
        }
        printf("%c", c);
    }
    printf("\n");
    return 0;
}
// 4 36