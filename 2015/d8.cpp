#include "common.h"

int compute_in_mem(const string& x)
{
    assert(~x >= 2);
    assert(x[0] == '"' && x.back() == '"');
    int N = ~x - 1;
    int c = 0;
    for (int i = 1; i < N;) {
        ++c;
        if (x[i] == '\\') {
            assert(i + 1 < N);
            switch (x[i + 1]) {
                case '\\':
                    i += 2;
                    continue;
                case '"':
                    i += 2;
                    continue;
                case 'x':
                    assert(i + 2 < N);
                    i += 4;
                    continue;
            }
        }
        ++i;
    }
    return c;
}

int encode(const string& x)
{
    int r = 0;
    for (auto c : x) {
        switch (c) {
            case '"':
                r += 2;
                break;
            case '\\':
                r += 2;
                break;
            default:
                ++r;
        }
    }
    return r+2;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d8_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int in_code = 0;
    int in_mem = 0;
    int encoded = 0;
    for (auto l : lines) {
        int ic = ~l;
        int ec = encode(l);
        in_code += ic;
        in_mem += compute_in_mem(l);
        encoded += ec;
    }
    printf("part1 %d\n", in_code - in_mem);
    printf("Part2 %d\n", encoded - in_code);
    return 0;
}
//1485 not
// 18:43
