#include "common.h"

using AI16 = array<int, 16>;

string permute(string s, const VS& vs)
{
    const int N = ~s;
    for (auto& v : vs) {
        auto xs = split(v.substr(1), "/");
        switch (v[0]) {
            case 's': {
                auto n = stoi(xs[0]);
                s = s.substr(N - n) + s.substr(0, N - n);
            } break;
            case 'x': {
                auto a = stoi(xs[0]);
                auto b = stoi(xs[1]);
                swap(s[a], s[b]);
            } break;
            case 'p': {
                auto a = s.find(xs[0]);
                auto b = s.find(xs[1]);
                swap(s[a], s[b]);
            } break;
            default:
                UNREACHABLE;
        }
    }
    return s;
}

struct Pm
{
    AI16 indexperm;
};

struct Instr
{
    char c0;
    int a = -1;
    int b = -1;
    char x0 = 0;
    char x1 = 0;
    Instr(char c0, int n) : c0(c0), a(n) {}
    Instr(char c0, int a, int b) : c0(c0), a(a), b(b) {}
    Instr(char c0, char x0, char x1) : c0(c0), x0(x0), x1(x1) {}
};

vector<Instr> permute2(const VS& vs)
{
    vector<Instr> is;
    for (auto& v : vs) {
        auto xs = split(v.substr(1), "/");
        switch (v[0]) {
            case 's': {
                auto n = stoi(xs[0]);
                is.PB(Instr('s', n));
            } break;
            case 'x': {
                auto a = stoi(xs[0]);
                auto b = stoi(xs[1]);
                is.PB(Instr('x', a, b));
            } break;
            case 'p': {
                assert(~(xs[0]) == 1);
                assert(~(xs[1]) == 1);
                is.PB(Instr('p', xs[0][0], xs[1][0]));
            } break;
            default:
                UNREACHABLE;
        }
    }
    return is;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d16_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto vs = split(lines[0], ",");
    const string S0 = "abcdefghijklmnop";
    string s = S0;
    auto N = ~s;
    assert(N == 16);
    s = permute(s, vs);
    printf("%s\n", s.c_str());

    auto is = permute2(vs);

    using I64 = int64_t;

    {
        string other_s = S0;
        unordered_map<string, int> ss;
        ss[other_s] = 0;
        int steps_done = 0;
        for (;;) {
            if (steps_done == 1000000000) {
                break;
            }
            other_s = permute(other_s, vs);
            ++steps_done;
            auto it = ss.find(other_s);
            if (it != ss.end()) {
                int prev_steps_done = it->second;
                int diff = steps_done - prev_steps_done;
                printf("after %d steps = after %d steps (diff=%d)\n", steps_done, prev_steps_done,
                       diff);
                int to_go = 1000000000-steps_done;
                to_go = to_go%diff;
                FOR(j,0,<to_go){
                    other_s = permute(other_s, vs);
                }
                break;
            } else {
                ss[other_s] = steps_done;
            }
        }
        printf("other_s %s\n", other_s.c_str());
        exit(0);
    }

    map<I64, AI16> perms;
    AI16 p;
    FOR (i, 0, < 16) {
        p[i] = s.find(S0[i]);
    }
    I64 last_pn = 1;
    AI16 last_perm = p;
    perms[last_pn] = last_perm;
    const auto ONE_BILLION = 1000000LL * 1000LL;
    for (;;) {
        I64 next_pn = last_pn * 2;
        if (next_pn > ONE_BILLION) {
            break;
        }
        AI16 next_perm;
        FOR (i, 0, < 16) {
            next_perm[i] = last_perm[last_perm[i]];
        }
        perms[next_pn] = next_perm;
        last_perm = next_perm;
        last_pn = next_pn;
    }
    auto t = S0;
    I64 to_go = ONE_BILLION;
    to_go = 2;

    // ceijbfoamgkdnlph
    // other_s cloeidmbjgpfhkna
    // ibmgefpcnokjldha
    string other_s;
    {
        other_s = S0;
        FOR (i, 0LL, < to_go) {
            other_s = permute(other_s, vs);
        }
        printf("other_s %s\n", other_s.c_str());
    }
    while (to_go > 0) {
        auto it = perms.upper_bound(to_go);
        --it;
        assert(to_go >= it->first);
        to_go -= it->first;
        auto& p = it->second;
        string tt = t;
        FOR (i, 0, < 16) {
            tt[p[i]] = t[i];
        }
        t = tt;
    }
    assert(to_go == 0);
    printf("%s\n", t.c_str());
    return 0;
}
// nblpefamdhkojgci not