#include "common.h"

bool is_number(const string& s)
{
    if (s.empty()) {
        return false;
    }
    if (s[0] != '-' && !isdigit(s[0])) {
        return false;
    }
    if (s[0] == '-' && ~s == 1) {
        return false;
    }
    FOR (i, 1, < ~s) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

struct Node
{
    vector<Node*> chs;
    bool red = false;
    int sum = 0;
};

int calc_sums(Node* n)
{
    if (n->red) {
        return 0;
    }
    int total = n->sum;
    for (auto ch : n->chs) {
        total += calc_sums(ch);
    }
    return total;
}

string parse_string(const char*& rest)
{
    assert(rest[0] == '"');
    ++rest;
    string s;
    while (*rest != '"') {
        assert(*rest);
        s += *rest;
        ++rest;
    }
    assert(*rest == '"');
    ++rest;
    return s;
}

int parse_number(const char*& rest)
{
    assert(isdigit(rest[0]));
    int i = rest[0] - '0';
    for (++rest; isdigit(*rest); ++rest) {
        i = 10 * i + (rest[0] - '0');
    }
    return i;
}

int parse_in_object(const char*& rest);

bool try_eat_char(char c, const char*& rest)
{
    if (*rest == c) {
        ++rest;
        return true;
    }
    return false;
}

optional<int> try_eat_number(const char*& rest)
{
    if (try_eat_char('-', rest)) {
        return -parse_number(rest);
    }
    if (isdigit(*rest)) {
        return parse_number(rest);
    }
    return {};
}

bool try_eat_string(const char*& rest)
{
    if (*rest == '"') {
        parse_string(rest);
        return true;
    }
    return false;
}

void eat_char(char c, const char*& rest)
{
    assert(*rest == c);
    ++rest;
}

int parse_value(const char*& rest)
{
    if (!*rest) {
        return 0;
    }
    if (auto n = try_eat_number(rest)) {
        return *n;
    }
    if (try_eat_string(rest)) {
        return 0;
    }
    if (try_eat_char('{', rest)) {
        auto v = parse_in_object(rest);
        eat_char('}', rest);
        return v;
    }
    if (try_eat_char('[', rest)) {
        int total = 0;
        for (;;) {
            total += parse_value(rest);
            if (!try_eat_char(',', rest)) {
                eat_char(']', rest);
                return total;
            }
        }
    }
    assert(false);
}

bool try_eat_string(const char* str, const char*& rest)
{
    int n = strlen(str);
    if (strncmp(str, rest, n) == 0) {
        rest += n;
        return true;
    }
    return false;
}

int parse_in_object(const char*& rest)
{
    int total = 0;
    bool red = false;
    while (*rest == '"') {
        auto key = parse_string(rest);
        eat_char(':', rest);
        if (try_eat_string("\"red\"", rest)) {
            red = true;
        } else {
            total += parse_value(rest);
        }
        if (!try_eat_char(',', rest)) {
            break;
        }
    }
    return red ? 0 : total;
}

void part2b()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input2.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto rest = lines[0].c_str();
    auto v = parse_value(rest);
    printf("part2b %d\n", v);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input2.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    {
        auto input = lines[0];

        // input="{\"a\":{\"b\":4},\"c\":-1}";

        for (auto& c : input) {
            if (!isdigit(c) && c != '-') {
                c = ' ';
            }
        }
        auto nums = split(input, " ");
        int total = 0;
        for (auto& n : nums) {
            total += stoi(n);
        }
        printf("part1 %d\n", total);
    }

    // PART2
    {
        auto input = lines[0];
        VS vs;
        bool inq = false;
        bool start_new_number = true;

        const string that = ":\"red\"";
        FOR (i, 0, < ~input) {
            if (input.substr(i, 6) == that) {
                vs.PB(that);
                continue;
            }
            auto c = input[i];
            if (inq) {
                if (c == '"') {
                    inq = false;
                }
                continue;
            }
            if (!isdigit(c) && !vs.empty() && is_number(vs.back())) {
                start_new_number = true;
            }
            if (c == '"') {
                inq = true;
                continue;
            }

            if (c == '{' || c == '}' || c == '-') {
                if (c == '-') {
                    start_new_number = false;
                }
                vs.PB(string(1, c));
                continue;
            }

            if (isdigit(c)) {
                if (start_new_number || vs.empty() || !(vs.back() == "-" || is_number(vs.back()))) {
                    vs.PB(string(1, c));
                    start_new_number = false;
                } else {
                    vs.back().PB(c);
                }
            }
        }

        auto root = new Node;
        vector<Node*> stk = {root};
        for (auto& v : vs) {
            if (v == "{") {
                auto nn = new Node;
                stk.back()->chs.PB(nn);
                stk.PB(nn);
                continue;
            }
            if (v == "}") {
                assert(!stk.empty());
                stk.pop_back();
                continue;
            }
            if (v == ":\"red\"") {
                assert(!stk.empty());
                stk.back()->red = true;
                continue;
            }
            assert(is_number(v));
            assert(!stk.empty());
            stk.back()->sum += stoi(v);
        }
        printf("part2 %d\n", calc_sums(root));
    }

    part2b();
    return 0;
}

// 126674
// 7 42
// 70814
