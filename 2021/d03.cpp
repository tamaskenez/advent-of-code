#include "common.h"

int get_bit(const string& s, int i)
{
    int n = s.size();
    assert(0 <= i && i < n);
    auto c = s[n - i - 1];
    assert(c == '0' || c == '1');
    return c == '1' ? 1 : 0;
}

int binary_string_to_int(const string& s)
{
    int r = 0;
    FOR (i, 0, < ~s) {
        if (get_bit(s, i)) {
            r += (1 << i);
        }
    }
    return r;
}

int get_one_count(const set<string>& ss, int i)
{
    int r = 0;
    for (auto& s : ss) {
        if (get_bit(s, i)) {
            ++r;
        }
    }
    return r;
}

int count_ones_at_charpos(const set<string>& strings, int charpos)
{
    int r = 0;
    for (auto& s : strings) {
        assert(0 <= charpos && charpos < ~s);
        auto c = s[charpos];
        assert(c == '0' || c == '1');
        if (c == '1') {
            ++r;
        }
    }
    return r;
}

void main2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d03_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    set<string> input;
    int n_bits = 0;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        if (n_bits) {
            assert(n_bits == ~l);
        } else {
            n_bits = ~l;
        }
        input.insert(l);
    }
    int gamma = 0, epsilon = 0;
    FOR (charpos, 0, < n_bits) {
        int n_ones = count_ones_at_charpos(input, charpos);
        int n_zeros = ~input - n_ones;
        int bitpos = n_bits - charpos - 1;
        if (n_ones > n_zeros) {
            gamma += (1 << bitpos);
        } else {
            epsilon += (1 << bitpos);
        }
    }
    printf("  gamma: %d\n", gamma);
    printf("epsilon: %d\n", epsilon);
    printf("     P1: %d\n", gamma * epsilon);
    auto S = input;
    FOR (charpos, 0, < n_bits) {
        if (~S <= 1) {
            assert(~S == 1);
            break;
        }
        int n_ones = count_ones_at_charpos(S, charpos);
        int n_zeros = ~S - n_ones;
        char most_common = n_ones >= n_zeros ? '1' : '0';
        for (auto it = S.begin(); it != S.end();) {
            if ((*it)[charpos] == most_common) {
                ++it;
            } else {
                it = S.erase(it);
            }
        }
    }
    int oxygen = binary_string_to_int(*(S.begin()));
    S = input;
    FOR (charpos, 0, < n_bits) {
        if (~S <= 1) {
            assert(~S == 1);
            break;
        }
        int n_ones = count_ones_at_charpos(S, charpos);
        int n_zeros = ~S - n_ones;
        char least_common = n_ones >= n_zeros ? '0' : '1';
        for (auto it = S.begin(); it != S.end();) {
            if ((*it)[charpos] == least_common) {
                ++it;
            } else {
                it = S.erase(it);
            }
        }
    }
    int co2 = binary_string_to_int(*(S.begin()));
    printf(" oxygen: %d\n", oxygen);
    printf("    co2: %d\n", co2);
    printf("     P2: %d\n", oxygen * co2);
}

int main()
{
    main2();
    printf("----\n");
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d03_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<int, int> count_ones;
    int max_bits = 0;
    int NC = 0;
    vector<string> LL;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        int n = l.size();
        max_bits = max(max_bits, n);
        FOR (i, 0, < n) {
            if (get_bit(l, i)) {
                count_ones[i]++;
            }
        }
        LL.PB(l);
        ++NC;
    }
    int gamma = 0, epsilon = 0;
    FOR (i, 0, < max_bits) {
        if (count_ones[i] > NC / 2) {
            gamma += (1 << i);
        } else {
            epsilon += (1 << i);
        }
    }
    printf("  gamma: %d\n", gamma);
    printf("epsilon: %d\n", epsilon);
    printf("     P1: %d\n", gamma * epsilon);

    set<string> SO(BE(LL));
    auto SCO = SO;
    FOR (j, 0, < max_bits) {
        int i = max_bits - j - 1;
        if (SO.size() > 1) {
            auto n_ones = get_one_count(SO, i);
            int n_zeros = ~SO - n_ones;
            int mostcommon = 0;
            if (n_ones >= n_zeros) {
                mostcommon = 1;
            }
            for (auto it = SO.begin(); it != SO.end();) {
                if (get_bit(*it, i) == mostcommon) {
                    ++it;
                } else {
                    it = SO.erase(it);
                }
            }
        }
        if (SCO.size() > 1) {
            auto n_ones = get_one_count(SCO, i);
            int n_zeros = ~SCO - n_ones;
            int leastcommon = 1;
            if (n_ones >= n_zeros) {
                leastcommon = 0;
            }
            for (auto it = SCO.begin(); it != SCO.end();) {
                if (get_bit(*it, i) == leastcommon) {
                    ++it;
                } else {
                    it = SCO.erase(it);
                }
            }
        }
    }
    assert(~SO == 1);
    assert(~SCO == 1);
    int oxygen = binary_string_to_int(*(SO.begin()));
    int co2 = binary_string_to_int(*(SCO.begin()));
    printf(" oxygen: %d\n", oxygen);
    printf("    co2: %d\n", co2);
    printf("     P2: %d\n", oxygen * co2);
    return 0;
}
// 1327

// 2595824 too high
