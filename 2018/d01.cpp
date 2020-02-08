#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d01_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int r = 0;
    for (auto& l : lines) {
        r += stoi(l);
    }
    printf("%d\n", r);

    {
        bool done = false;
        set<int> fs;
        fs.insert(0);
        int f = 0;
        for (; !done;) {
            for (auto& l : lines) {
                f += stoi(l);
                if (contains(fs, f)) {
                    printf("%d\n", f);
                    done = true;
                    break;
                }
                fs.insert(f);
            }
        }
    }
    return 0;
}
