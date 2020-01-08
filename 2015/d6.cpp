#include "common.h"

AI2 numbers_at(const string& s, int x)
{
    assert(isdigit(s[x]));
    auto n1 = stoi(s.substr(x));
    auto p = s.find(',', x);
    assert(p != string::npos);
    assert(isdigit(s[p + 1]));
    auto n2 = stoi(s.substr(p + 1));
    return AI2{n1, n2};
}

void solve1()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d6_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<bitset<1000>> M(1000);
    for (auto l : lines) {
        int task = -1;
        AI2 ns1;
        if (starts_with(l, "turn on ")) {
            ns1 = numbers_at(l, 8);
            task = 0;
        } else if (starts_with(l, "turn off ")) {
            ns1 = numbers_at(l, 9);
            task = 1;
        } else if (starts_with(l, "toggle ")) {
            ns1 = numbers_at(l, 7);
            task = 2;
        } else {
            assert(false);
        }
        auto p = l.find("through ");
        assert(p != string::npos);
        auto ns2 = numbers_at(l, p + 8);
        char buf[1000];
        switch (task) {
            case 0:
                sprintf(buf, "turn on %d,%d through %d,%d", ns1[0], ns1[1], ns2[0], ns2[1]);
                FOR (r, ns1[0], <= ns2[0]) {
                    FOR (c, ns1[1], <= ns2[1]) {
                        M[r].set(c);
                    }
                }
                break;
            case 1:
                sprintf(buf, "turn off %d,%d through %d,%d", ns1[0], ns1[1], ns2[0], ns2[1]);
                FOR (r, ns1[0], <= ns2[0]) {
                    FOR (c, ns1[1], <= ns2[1]) {
                        M[r].reset(c);
                    }
                }
                break;
            case 2:
                sprintf(buf, "toggle %d,%d through %d,%d", ns1[0], ns1[1], ns2[0], ns2[1]);
                FOR (r, ns1[0], <= ns2[0]) {
                    FOR (c, ns1[1], <= ns2[1]) {
                        M[r].flip(c);
                    }
                }
                break;
            default:
                assert(false);
        }
        assert(l == buf);
    }
    int count = 0;
    for (auto& v : M) {
        count += v.count();
    }
    printf("count: %d\n", count);
}

void solve2()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d6_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    array<array<int, 1000>, 1000> M;
    array<int, 1000> allzero;
    allzero.fill(0);
    M.fill(allzero);
    for (auto l : lines) {
        int task = -1;
        AI2 ns1;
        if (starts_with(l, "turn on ")) {
            ns1 = numbers_at(l, 8);
            task = 0;
        } else if (starts_with(l, "turn off ")) {
            ns1 = numbers_at(l, 9);
            task = 1;
        } else if (starts_with(l, "toggle ")) {
            ns1 = numbers_at(l, 7);
            task = 2;
        } else {
            assert(false);
        }
        auto p = l.find("through ");
        assert(p != string::npos);
        auto ns2 = numbers_at(l, p + 8);
        char buf[1000];
        switch (task) {
            case 0:
                sprintf(buf, "turn on %d,%d through %d,%d", ns1[0], ns1[1], ns2[0], ns2[1]);
                FOR (r, ns1[0], <= ns2[0]) {
                    FOR (c, ns1[1], <= ns2[1]) {
                        ++M[r][c];
                    }
                }
                break;
            case 1:
                sprintf(buf, "turn off %d,%d through %d,%d", ns1[0], ns1[1], ns2[0], ns2[1]);
                FOR (r, ns1[0], <= ns2[0]) {
                    FOR (c, ns1[1], <= ns2[1]) {
                        auto& i = M[r][c];
                        i = max(i - 1, 0);
                    }
                }
                break;
            case 2:
                sprintf(buf, "toggle %d,%d through %d,%d", ns1[0], ns1[1], ns2[0], ns2[1]);
                FOR (r, ns1[0], <= ns2[0]) {
                    FOR (c, ns1[1], <= ns2[1]) {
                        M[r][c] += 2;
                    }
                }
                break;
            default:
                assert(false);
        }
        assert(l == buf);
    }
    int count = 0;
    FOR (r, 0, <= 999) {
        FOR (c, 0, <= 999) {
            count += M[r][c];
        }
    }
    printf("count: %d\n", count);
}

int main()
{
    solve1();
    solve2();
}
