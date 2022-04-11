#include "common.h"

using Regs = unordered_map<char, int64_t>;

using ALL3 = array<int64_t, 3>;

namespace std {
template <>
struct std::hash<ALL3>
{
    std::size_t operator()(ALL3 const& s) const noexcept { return hash_range(BE(s)); }
};
}  // namespace std

unordered_map<ALL3, optional<string>> cache;

optional<string> get_postfix_on_success(int64_t w,
                                        int64_t z,
                                        int pc,
                                        const VS& lines,
                                        int next_input)
{
    auto key = ALL3{w, z, pc};
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }
    int64_t x = 0, y = 0;
    for (; pc < ~lines; ++pc) {
        auto ls = split(lines[pc], " ");
        assert(~ls[1] == 1);
        char reg = ls[1][0];
        if (ls[0] == "inp") {
            assert(~ls == 2);
            assert(ls[1] == "w");
            FORBACK (digit, 9, >= 1) {
                if (next_input < 5) {
                    printf("%s%c\n", string(next_input, '.').c_str(), digit + '0');
                }
                auto postfix = get_postfix_on_success(digit, z, pc + 1, lines, next_input + 1);
                if (postfix) {
                    auto result = char(digit + '0') + *postfix;
                    cache[key] = result;
                    return result;
                }
            }
            cache[key] = nullopt;
            return nullopt;
        }
        int64_t* target = nullptr;
        switch (reg) {
            case 'w':
                target = &w;
                break;
            case 'x':
                target = &x;
                break;
            case 'y':
                target = &y;
                break;
            case 'z':
                target = &z;
                break;
            default:
                assert(false);
        }
        assert(~ls == 3);
        int64_t sec;
        if (~ls[2] == 1 && isalpha(ls[2][0])) {
            switch (ls[2][0]) {
                case 'w':
                    sec = w;
                    break;
                case 'x':
                    sec = x;
                    break;
                case 'y':
                    sec = y;
                    break;
                case 'z':
                    sec = z;
                    break;
                default:
                    assert(false);
            }
        } else {
            sec = stoll(ls[2]);
        }
        if (ls[0] == "mul") {
            *target *= sec;
        } else if (ls[0] == "div") {
            assert(sec != 0);
            *target /= sec;
        } else if (ls[0] == "mod") {
            assert(*target >= 0 && sec > 0);
            *target %= sec;
        } else if (ls[0] == "add") {
            *target += sec;
        } else if (ls[0] == "eql") {
            *target = *target == sec ? 1 : 0;
        } else {
            assert(0);
        }
    }
    optional<string> result;
    if (z == 0) {
        result.emplace();
    }
    cache[key] = result;
    return result;
}

void P1(const VS& lines)
{
    auto p1 = get_postfix_on_success(0, 0, 0, lines, 0);
    if (p1) {
        printf("P1: %s\n", p1->c_str());
    } else {
        printf("Not found.\n");
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input_orig.txt");
    assert(f.good());
    auto lines = read_lines(f);
    P1(lines);

    return 0;
}
