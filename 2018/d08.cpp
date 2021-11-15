#include "common.h"

struct Node
{
    vector<Node> children;
    VI mdes;
    int value()
    {
        if (children.empty()) {
            return accumulate(BE(mdes), 0);
        }
        int s = 0;
        for (auto mde : mdes) {
            if (mde == 0) {
                continue;
            }
            int ix = mde - 1;
            if (ix < 0 || ~children <= ix) {
                continue;
            }
            s += children[ix].value();
        }
        return s;
    }
};

int sum_meta_below_this(const VI& xs, int& i)
{
    assert(i + 2 <= ~xs);
    int ncs = xs[i];
    int nme = xs[i + 1];
    i += 2;
    int sme = 0;
    FOR (k, 0, < ncs) {
        sme += sum_meta_below_this(xs, i);
    }
    FOR (k, 0, < nme) {
        assert(i < ~xs);
        sme += xs[i++];
    }
    return sme;
}

Node read_tree(const VI& xs, int& i)
{
    Node n;
    assert(i + 2 <= ~xs);
    int ncs = xs[i];
    int nme = xs[i + 1];
    i += 2;
    int sme = 0;
    FOR (k, 0, < ncs) {
        n.children.PB(read_tree(xs, i));
    }
    FOR (k, 0, < nme) {
        assert(i < ~xs);
        n.mdes.PB(xs[i++]);
    }
    return n;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d08_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto ss = split(lines[0], " \t");
    VI xs;
    for (auto& s : ss) {
        xs.PB(stoi(s));
    }

    int i = 0;
    int s = sum_meta_below_this(xs, i);
    assert(i == ~xs);
    printf("%d\n", s);

    i = 0;
    printf("%d\n", read_tree(xs, i).value());

    return 0;
}
