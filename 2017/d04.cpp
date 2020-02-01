#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d04_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int n_valid = 0;
    int n_valid2 = 0;
    int total = 0;
    for (auto& l : lines) {
        auto vs = split(l, " ");
        set<string> ss, ss2;
        bool valid = true;
        bool valid2 = true;
        for (auto& w : vs) {
            if (contains(ss, w)) {
                valid = false;
            }
            ss.insert(w);
            string w2 = w;
            sort(BE(w2));
            if (contains(ss2, w2)) {
                valid2 = false;
            }
            ss2.insert(w2);
        }
        if (valid) {
            ++n_valid;
        }
        if (valid2) {
            ++n_valid2;
        }
        ++total;
    }
    printf("total %d, valid %d valid2 %d\n", total, n_valid, n_valid2);
    return 0;
}
