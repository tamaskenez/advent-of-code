#include "common.h"

string decompress(const string& x)
{
    string r;
    int i = 0;
    const int N = ~x;
    for (; i < N;) {
        auto c = x[i++];
        if (c == '(') {
            string m;
            while (i < N && x[i] != ')') {
                m += x[i];
                ++i;
            }
            assert(i < N && x[i] == ')');
            ++i;
            auto vs = split(m, "x");
            assert(~vs == 2);
            auto rep_len = stoi(vs[0]);
            auto rep_cnt = stoi(vs[1]);
            assert(i + rep_len <= N);
            auto to_repeat = x.substr(i, rep_len);
            i += rep_len;
            FOR (rn, 0, < rep_cnt) {
                r += to_repeat;
            }
        } else {
            r += c;
        }
    }
    return r;
}

using i64 = int64_t;
i64 decompressed_length(const string& s, int x0, int n)
{
    i64 total = 0;
    assert(x0 + n <= ~s);
    int i = x0;
    for (; i < x0 + n;) {
        auto c = s[i++];
        if (c != '(') {
            ++total;
            continue;
        }
        string m;
        while (i < x0 + n && s[i] != ')') {
            m += s[i];
            ++i;
        }
        assert(i < x0 + n && s[i] == ')');
        ++i;
        auto vs = split(m, "x");
        assert(~vs == 2);
        auto rep_len = stoi(vs[0]);
        auto rep_cnt = stoi(vs[1]);
        assert(i + rep_len <= x0 + n);
        total += decompressed_length(s, i, rep_len) * rep_cnt;
        i += rep_len;
    }
    return total;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d09_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto dcl = decompress(lines[0]);
    printf("%d\n", ~dcl);
    auto p2 = decompressed_length(lines[0], 0, ~lines[0]);
    printf("p2 %lld\n", p2);
    return 0;
}

// not 26888304055