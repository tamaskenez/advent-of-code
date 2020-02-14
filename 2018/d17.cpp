#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d17_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    return 0;
}
