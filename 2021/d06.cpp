#include "common.h"

// const string input = "3,4,3,1,2";
const string input =
    "1,1,1,1,3,1,4,1,4,1,1,2,5,2,5,1,1,1,4,3,1,4,1,1,1,1,1,1,1,2,1,2,4,1,1,1,1,1,1,1,3,1,1,5,1,1,2,"
    "1,5,1,1,1,1,1,1,1,1,4,3,1,1,1,2,1,1,5,2,1,1,1,1,4,5,1,1,2,4,1,1,1,5,1,1,1,1,5,1,3,1,1,4,2,1,5,"
    "1,2,1,1,1,1,1,3,3,1,5,1,1,1,1,3,1,1,1,4,1,1,1,4,1,4,3,1,1,1,4,1,2,1,1,1,2,1,1,1,1,5,1,1,3,5,1,"
    "1,5,2,1,1,1,1,1,4,4,1,1,2,1,1,1,4,1,1,1,1,5,3,1,1,1,5,1,1,1,4,1,4,1,1,1,5,1,1,3,2,2,1,1,1,4,1,"
    "3,1,1,1,2,1,3,1,1,1,1,4,1,1,1,1,2,1,4,1,1,1,1,1,4,1,1,2,4,2,1,2,3,1,3,1,1,2,1,1,1,3,1,1,3,1,1,"
    "4,1,3,1,1,2,1,1,1,4,1,1,3,1,1,5,1,1,3,1,1,1,1,5,1,1,1,1,1,2,3,4,1,1,1,1,1,2,1,1,1,1,1,1,1,3,2,"
    "2,1,3,5,1,1,4,4,1,3,4,1,2,4,1,1,3,1";

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d06_input.txt");
    assert(f.good());
    auto str_ages = split(input, ",");
    map<int, int64_t> ages;
    for (auto sa : str_ages) {
        auto age = stoi(sa);
        ages[age]++;
    }
    FOR (days, 1, <= 256) {
        map<int, int64_t> new_ages;
        for (auto [age, count] : ages) {
            if (age == 0) {
                new_ages[6] += count;
                new_ages[8] += count;
            } else {
                new_ages[age - 1] += count;
            }
        }
        ages.swap(new_ages);
    }
    int64_t total = 0;
    for (auto [age, count] : ages) {
        total += count;
    }
    printf("total: %lld\n", total);
    return 0;
}
// 1149
