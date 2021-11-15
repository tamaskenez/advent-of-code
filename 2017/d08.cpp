#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d08_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, int> regs;
    RunningStat<int> st2;
    for (auto& l : lines) {
        auto ss = split(l, " \t");
        //  0  1    2    3  4 5   6
        // eai dec -933 if bz == -6439
        auto x = regs[ss[4]];
        auto y = stoi(ss[6]);
        auto op = ss[5];
        bool b;
        if (op == "==") {
            b = x == y;
        } else if (op == "!=") {
            b = x != y;
        } else if (op == "<") {
            b = x < y;
        } else if (op == "<=") {
            b = x <= y;
        } else if (op == ">") {
            b = x > y;
        } else if (op == ">=") {
            b = x >= y;
        } else {
            UNREACHABLE;
        }
        if (b) {
            auto& r = regs[ss[0]];
            auto n = stoi(ss[2]);
            if (ss[1] == "dec")
                n = -n;
            else
                assert(ss[1] == "inc");
            r += n;
            st2.add(r);
        }
    }
    RunningStat<int> st;
    for (auto& kv : regs) {
        st.add(kv.second);
    }
    printf("%d\n", *st.upper);
    printf("%d\n", *st2.upper);
    return 0;
}
