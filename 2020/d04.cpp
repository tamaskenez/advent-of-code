#include "common.h"

const set<string> expected_fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

bool is_valid(string pp)
{
    set<string> fields;
    auto ss = split(pp, " ");
    for (auto f : ss) {
        auto ff = trim(f);
        auto fn = ff.substr(0, 3);
        assert(fields.count(fn) == 0);
        fields.insert(fn);
    }

    return set_difference(BE(expected_fields), BE(fields)).empty();
}

maybe<int> get_four_digits(string s)
{
    for (auto c : s) {
        if (!isdigit(c))
            return nullopt;
    }
    return atoi(s.c_str());
}

bool is_digits(string s)
{
    for (auto c : s)
        if (!isdigit(c))
            return false;
    return true;
}

maybe<int> get_as_int(string s)
{
    if (!is_digits(s))
        return nullopt;
    if (s[0] == 0 && ~s > 1)
        return nullopt;
    return atoi(s.c_str());
}

bool is_valid2(string pp)
{
    set<string> fields;
    auto ss = split(pp, " ");
    for (auto f : ss) {
        auto ff = trim(f);
        auto fn = ff.substr(0, 3);
        assert(~ff > 4 && ff[3] == ':');
        auto v = ff.substr(4);
        assert(fields.count(fn) == 0);
        if (fn == "byr") {
            // byr (Birth Year) - four digits; at least 1920 and at most 2002.
            auto r = get_four_digits(v);
            bool valid = r && 1920 <= *r && *r <= 2002;
            if (!valid)
                return false;
        } else if (fn == "iyr") {
            // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
            auto r = get_four_digits(v);
            bool valid = r && 2010 <= *r && *r <= 2020;
            if (!valid)
                return false;
        } else if (fn == "eyr") {
            // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
            auto r = get_four_digits(v);
            bool valid = r && 2020 <= *r && *r <= 2030;
            if (!valid)
                return false;
        } else if (fn == "hgt") {
            // hgt (Height) - a number followed by either cm or in:
            // If cm, the number must be at least 150 and at most 193.
            // If in, the number must be at least 59 and at most 76.
            auto valid = ends_with(v, "cm") || ends_with(v, "in");
            if (!valid)
                return false;
            auto r = get_as_int(v.substr(0, ~v - 2));
            if (!r)
                return false;
            if (ends_with(v, "cm")) {
                valid = 150 <= *r && *r <= 193;
            } else {
                valid = 59 <= *r && *r <= 76;
            }
            if (!valid)
                return false;
        } else if (fn == "hcl") {
            // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
            bool valid = ~v == 7 && v[0] == '#';
            if (!valid)
                return false;
            for (auto c : v.substr(1)) {
                valid = isdigit(c) || ('a' <= c && c <= 'f');
                if (!valid)
                    return false;
            }
        } else if (fn == "ecl") {
            // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
            static const set<string> colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            if (colors.count(v) == 0)
                return false;
        } else if (fn == "pid") {
            // pid (Passport ID) - a nine-digit number, including leading zeroes.
            auto valid = ~v == 9 && is_digits(v);
            if (!valid)
                return false;
        } else if (fn == "cid") {
            // cid (Country ID) - ignored, missing or not.
        } else {
            assert(false);
        }
        fields.insert(fn);
    }
    printf("");
    auto sd = set_difference(BE(expected_fields), BE(fields));
    return set_difference(BE(expected_fields), BE(fields)).empty();
}

int main()
{
    common_test();
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d4_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    auto s = ~lines;
    string pp;
    int vc = 0, vc2 = 0;
    for (auto l : lines) {
        auto ll = trim(l);
        if (ll.empty()) {
            if (!pp.empty()) {
                if (is_valid(pp)) {
                    ++vc;
                }
                if (is_valid2(pp)) {
                    ++vc2;
                }
                pp.clear();
            }
        } else {
            pp += ' ';
            pp += ll;
        }
    }
    if (!pp.empty()) {
        if (is_valid(pp)) {
            ++vc;
        }
        if (is_valid2(pp)) {
            ++vc2;
        }
        pp.clear();
    }
    printf("P1: %d\n", vc);
    printf("P2: %d\n", vc2);
    return 0;
}
