#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d12_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    const string initial = lines[0];
    map<string, bool> rules;
    maybe<int> rulelen;
    FOR (i, 1, < ~lines) {
        auto xs = split(lines[i], " =>\t");
        assert(~xs == 2);
        assert(xs[1] == "." || xs[1] == "#");
        rules[xs[0]] = xs[1] == "#";
        if (rulelen) {
            assert(*rulelen == ~(xs[0]));
        } else {
            rulelen = ~(xs[0]);
        }
    }
    const int RL = *rulelen;
    assert((RL & 1) == 1);
    const int hrl = RL / 2;
    {
        set<int> s, ns;
        FOR (i, 0, < ~initial) {
            if (initial[i] == '#') {
                s.insert(i);
            }
        }
        FOR (iter, 0, < 20) {
            ns.clear();
            int lower, upper;
            if (s.empty()) {
                lower = 0;
                upper = 0;
            } else {
                lower = *s.begin();
                auto it = s.end();
                --it;
                upper = *it;
            }
            lower -= hrl;
            upper += hrl;
            FOR (pos, lower, <= upper) {
                string r(RL, '.');
                FOR (k, -hrl, <= hrl) {
                    if (contains(s, pos + k)) {
                        r[k + hrl] = '#';
                    }
                }
                auto it = rules.find(r);
                assert(it != rules.end());
                if (it->second) {
                    ns.insert(pos);
                }
            }
            s.swap(ns);
        }
        int sum = 0;
        for (auto i : s) {
            sum += i;
        }
        printf("%d\n", sum);
    }
    {
        set<int> s, ns;
        FOR (i, 0, < ~initial) {
            if (initial[i] == '#') {
                s.insert(i);
            }
        }
        FOR (iter, 0, < 50000000) {
            ns.clear();
            int lower, upper;
            if (s.empty()) {
                lower = 0;
                upper = 0;
            } else {
                lower = *s.begin();
                auto it = s.end();
                --it;
                upper = *it;
            }
            lower -= hrl;
            upper += hrl;
            FOR (pos, lower, <= upper) {
                string r(RL, '.');
                FOR (k, -hrl, <= hrl) {
                    if (contains(s, pos + k)) {
                        r[k + hrl] = '#';
                    }
                }
                auto it = rules.find(r);
                assert(it != rules.end());
                if (it->second) {
                    ns.insert(pos);
                }
            }
            s.swap(ns);
            int sum = 0;
            for (auto i : s) {
                sum += i;
            }
            int actiter = iter+1;
            printf("iter %d, %d, 194*actiter-sum %f, 194*actiter-679 %f\n", iter, sum,194.0*actiter-sum, 194.0*actiter-679);
            int a = 3;
            break;
        }
    }
    auto p2 = 194*50000000000LL-679;
    printf("%lld\n", p2);
    return 0;
}
