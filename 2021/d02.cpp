#include "common.h"
// 5:06
// 8:00
int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d02_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    AI2 coords{0, 0};
    AI2 coords2{0, 0};
    int aim = 0;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        auto spi = l.find(' ');
        assert(spi != string::npos);
        auto w = l.substr(0, spi);
        auto sx = l.substr(spi + 1);
        auto x = stoi(sx);
        if (w == "forward") {
            coords[0] += x;
            coords2[0] += x;
            coords2[1] += x * aim;
        } else if (w == "down") {
            coords[1] += x;
            aim += x;
        } else if (w == "up") {
            coords[1] -= x;
            aim -= x;
        } else {
            assert(false);
        }
    }
    auto p1 = coords[0] * coords[1];
    auto p2 = coords2[0] * coords2[1];
    printf("P1 %d\n", p1);
    printf("P2 %d\n", p2);
    return 0;
}
