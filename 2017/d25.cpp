#include "common.h"

int main()
{
#if 0
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d25_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
#endif
    auto DP = 12368930;
    map<int, int> tape;
    char state = 'A';
    int cursor = 0;
    FOR (i, 0, < DP) {
        auto& cv = tape[cursor];
        switch (state) {
            case 'A':
                if (cv == 0) {
                    cv = 1;
                    ++cursor;
                    state = 'B';
                } else {
                    cv = 0;
                    ++cursor;
                    state = 'C';
                }
                break;
            case 'B':
                if (cv == 0) {
                    cv = 0;
                    --cursor;
                    state = 'A';
                } else {
                    cv = 0;
                    ++cursor;
                    state = 'D';
                }
                break;
            case 'C':
                if (cv == 0) {
                    cv = 1;
                    ++cursor;
                    state = 'D';
                } else {
                    cv = 1;
                    ++cursor;
                    state = 'A';
                }
                break;
            case 'D':
                if (cv == 0) {
                    cv = 1;
                    --cursor;
                    state = 'E';
                } else {
                    cv = 0;
                    --cursor;
                    state = 'D';
                }
                break;
            case 'E':
                if (cv == 0) {
                    cv = 1;
                    ++cursor;
                    state = 'F';
                } else {
                    cv = 1;
                    --cursor;
                    state = 'B';
                }
                break;
            case 'F':
                if (cv == 0) {
                    cv = 1;
                    ++cursor;
                    state = 'A';
                } else {
                    cv = 1;
                    ++cursor;
                    state = 'E';
                }
                break;
            default:
                UNREACHABLE;
        }
    }
    int count = 0;
    for (auto& kv : tape) {
        if (kv.second) {
            ++count;
        }
    }
    printf("count: %d\n", count);
    return 0;
}
