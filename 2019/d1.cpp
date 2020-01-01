#include <fstream>
#include <string>

#include "common.h"

const char* s = CMAKE_CURRENT_SOURCE_DIR;

int calc_fuel(int m)
{
    auto i = m / 3 - 2;
    return i > 0 ? i : 0;
}

int calc_fuel2(int m)
{
    int s = 0;
    for (;;) {
        m = calc_fuel(m);
        if (m == 0) {
            break;
        }
        s += m;
    }
    return s;
}

int main()
{
    assert(calc_fuel(12) == 2);
    assert(calc_fuel(14) == 2);
    assert(calc_fuel(1969) == 654);
    assert(calc_fuel(100756) == 33583);
    fstream f(CMAKE_CURRENT_SOURCE_DIR "/d1_input.txt");
    VI xs;
    for (;;) {
        int i;
        f >> i;
        if (!f.good()) {
            break;
        }
        xs.push_back(i);
    }
    int64_t sum = 0;
    for (auto i : xs) {
        sum += calc_fuel(i);
    }
    printf("total: %s\n", to_string(sum).c_str());

    assert(calc_fuel2(1969) == 966);
    assert(calc_fuel2(100756) == 50346);

    int64_t sum2 = 0;
    for (auto i : xs) {
        sum2 += calc_fuel2(i);
    }
    printf("total2: %s\n", to_string(sum2).c_str());

    return 0;
}