#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d09_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto l = lines[0];

    // l="{}";

    bool ing = false;
    VI scores = {0};
    int sum = 0;
    int gar = 0;
    FOR (i, 0, < ~l) {
        auto c = l[i];
        if (ing) {
            // garbage
            if (c == '!') {
                ++i;
            } else if (c == '>') {
                ing = false;
            } else {
                ++gar;
            }
        } else {
            // normal
            if (c == '{') {
                scores.PB(scores.back() + 1);
                auto sb = scores.back();
                auto new_sum = sum + sb;
                assert(sb >= 0);
                assert(new_sum > 0);
                sum = new_sum;
            } else if (c == '}') {
                scores.pop_back();
            } else if (c == '<') {
                ing = true;
            }
        }
    }
    printf("%d\n", sum);
    printf("%d\n", gar);
    return 0;
}

// low 256
