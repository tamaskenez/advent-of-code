#include <iostream>

#include "common.h"

using i64 = int64_t;

// not 13
const int PRE = 25;

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d9_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    vector<i64> nums;
    for (auto l : lines) {
        auto i = atoll(l.c_str());
        nums.PB(i);
    }
    unordered_set<i64> prevs;
    i64 reqsum;
    FOR (i, 0, < ~nums) {
        int b = i - PRE;
        if (b < 0) {
            continue;
        }
        prevs.clear();
        FOR (j, 0, < PRE - 1) {
            auto nj = nums[b + j];
            FOR (k, j + 1, < PRE) {
                auto nk = nums[b + k];
                if (nj == nk) {
                    continue;
                }
                prevs.insert(nj + nk);
            }
        }
        if (prevs.count(nums[i]) == 0) {
            cout << "P1: " << nums[i] << "\n";
            reqsum = nums[i];
            break;
        }
    }

    i64 sum = 0;
    int b = 0;
    int e = 0;
    for (;;) {
        assert(b <= e);
        if (e == ~nums) {
            break;
        }
        sum += nums[e++];
        if (sum == reqsum) {
            break;
        }
        if (sum > reqsum) {
            sum -= nums[b];
            ++b;
            while (sum > reqsum) {
                e--;
                sum -= nums[e];
                assert(b <= e);
            }
            if (sum == reqsum) {
                break;
            }
        } else {
        }
    }
    if (sum == reqsum) {
        auto mm = minmax_element(nums.begin() + b, nums.begin() + e);
        auto a = *mm.first + *mm.second;
        printf("P2: ");
        cout << a << "\n";
    } else {
        cout << "notfound\n";
    }

    return 0;
}

// 11.3
