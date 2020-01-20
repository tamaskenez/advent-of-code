#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d03_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int count = 0;
    for (auto& l : lines) {
        auto vs = split(l, " ");
        assert(~vs == 3);
        auto a = stoi(vs[0]);
        auto b = stoi(vs[1]);
        auto c = stoi(vs[2]);
        if (a + b > c && b + c > a && c + a > b) {
            ++count;
        }
    }
    printf("%d\n", count);
    assert(~lines % 3 == 0);
    array<VS, 3> vs;
    count=0;
    for (int i = 0; i < ~lines; i += 3) {
        FOR (j, 0, < 3) {
            vs[j] = split(lines[i+j], " ");
        }
        FOR (j, 0, < 3) {
            auto a = stoi(vs[0][j]);
            auto b = stoi(vs[1][j]);
            auto c = stoi(vs[2][j]);
            if (a + b > c && b + c > a && c + a > b) {
                ++count;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}
// 2 56