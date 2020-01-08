#include "common.h"

VS split(const string& s)
{
    return split(s, " ");
}

enum Op
{
    AND,
    NOT,
    OR,
    LSHIFT,
    RSHIFT,
    PON
};

struct Expr
{
    Op op;
    string x, y;
};

using U16 = uint16_t;

bool is_number(const string& s)
{
    for (auto c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

U16 compute(const string& var, const map<string, Expr>& ote, map<string, U16>& ass)
{
    if (is_number(var)) {
        auto i = stoi(var);
        assert(0 <= i && i < 65536);
        return (U16)i;
    }

    auto it = ass.find(var);
    if (it != ass.end()) {
        return it->second;
    }
    auto jt = ote.find(var);
    assert(jt != ote.end());
    auto& e = jt->second;
    U16 xi = compute(e.x, ote, ass);
    U16 yi = 0;
    if (e.op != NOT && e.op != PON) {
        yi = compute(e.y, ote, ass);
    }
    U16 zi;
    switch (e.op) {
        case PON:
            zi = xi;
            break;
        case NOT:
            zi = ~xi;
            break;
        case OR:
            zi = xi | yi;
            break;
        case AND:
            zi = xi & yi;
            break;
        case LSHIFT:
            zi = (U16)(xi << yi);
            break;
        case RSHIFT:
            zi = xi >> yi;
            break;
        default:
            assert(false);
    }
    ass[var] = zi;
    return zi;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d7_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, Expr> ote;
    for (auto& l : lines) {
        auto vs = split(l);
        assert(~vs >= 3);
        if (~vs == 3) {
            assert(vs[1] == "->");
            auto x = vs[0];
            auto z = vs[2];
            ote[z] = Expr{PON, x, ""};
        } else if (vs[0] == "NOT") {
            assert(~vs == 4);
            assert(vs[2] == "->");
            auto x = vs[1];
            auto z = vs[3];
            ote[z] = Expr{NOT, x, ""};
        } else {
            assert(~vs == 5);
            assert(vs[3] == "->");
            auto x = vs[0];
            auto y = vs[2];
            auto z = vs[4];
            Op op;
            if (vs[1] == "AND") {
                op = AND;
            } else if (vs[1] == "OR") {
                op = OR;
            } else if (vs[1] == "LSHIFT") {
                op = LSHIFT;
            } else if (vs[1] == "RSHIFT") {
                op = RSHIFT;
            } else {
                assert(false);
            }
            ote[z] = Expr{op, x, y};
        }
    }
    map<string, U16> ass;
    auto r = compute("a", ote, ass);
    printf("part1 %d\n", r);

    map<string, U16> ass2;
    ass2["b"] = r;

    auto r2 = compute("a", ote, ass2);
    printf("part2 %d\n", r2);
    return 0;
}

// 30:15
