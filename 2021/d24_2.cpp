#include "common.h"

struct Eql
{
    int64_t operator()(int64_t a, int64_t b) const { return a == b ? 1 : 0; }
};

struct SafeDivides
{
    int64_t operator()(int64_t a, int64_t b) const
    {
        assert(b != 0);
        return a / b;
    }
};

struct SafeModulus
{
    int64_t operator()(int64_t a, int64_t b) const
    {
        assert(a >= 0 && b > 0);
        return a % b;
    }
};

optional<int64_t> try_number(const string& s)
{
    try {
        auto n = stoll(s);
        if (to_string(n) == s) {
            return n;
        }
    } catch (...) {
    }
    return nullopt;
}

// using VSet = unordered_set<int64_t>;
#if 1
struct VSet
{
private:
    vector<int64_t> v;
    bool sorted = true;

public:
    VSet() = default;
    explicit VSet(int64_t i) : v({i}) {}
    const vector<int64_t>& cont() const
    {
        sort();
        return v;
    }
    void insert(int64_t i)
    {
        v.PB(i);
        sorted = false;
    }
    int operator~() const
    {
        sort();
        return v.size();
    }
    bool contains(int64_t x)
    {
        sort();
        auto it = lower_bound(BE(v), x);
        return it != v.end() && *it == x;
    }
    void sort() const
    {
        if (!sorted) {
            auto* mutable_this = const_cast<VSet*>(this);
            sort_unique_trunc(mutable_this->v);
            mutable_this->sorted = true;
        }
    }
    int64_t single_item() const
    {
        assert(v.size() == 1);
        return v.front();
    }
};
#else
#endif

template <class Op>
VSet do_op(const VSet& a, const VSet& b)
{
    VSet r;
    for (auto x : a.cont()) {
        for (auto y : b.cont()) {
            r.insert(Op()(x, y));
        }
    }
    return r;
}

void print(const map<char, VSet>& regs, char reg)
{
    auto& v = regs.at(reg);
    if (~v <= 16) {
        printf("%c = [", reg);
    } else if (~v <= 100) {
        printf("%c = // %d items\n    [", reg, ~v);
    } else {
        printf("%c = ... // %d items\n", reg, ~v);
        return;
    }
    bool first = true;
    for (auto i : v.cont()) {
        if (!first) {
            printf(" ");
        } else {
            first = false;
        }
        printf("%lld", i);
    }
    printf("]\n");
}

bool program(const vector<VSet>& input);
bool does_return_zero(const vector<VSet>& input)
{
    if (~input[5] > 1) {
        for (auto& vs : input) {
            if (~vs == 1) {
                printf("%lld", vs.single_item());
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
    return program(input);
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input_orig.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<char, VSet> regs;
    bool compile = false;
    FOR (ch, 'a', <= 'z') {
        regs[ch] = VSet(0);
    }

    int next_input = 1;

    int line_no = 1;
    for (auto l : lines) {
        // printf("// line %d\n%s\n", line_no++, l.c_str());

        auto ls = split(l, " ");
        auto opcode = ls[0];
        assert(~ls[1] == 1);
        char reg = ls[1][0];
        if (~ls == 2) {
            regs.at(reg) = input.at(next_input - 1);
            assert(opcode == "inp");
            ++next_input;
            continue;
        }

        assert(~ls == 3);
        VSet sec;
        if (auto n = try_number(ls[2])) {
            sec = VSet(*n);
        } else {
            assert(~ls[2] == 1);
            sec = regs.at(ls[2][0]);
        }

        if (opcode == "mul") {
            regs[reg] = do_op<multiplies<int64_t>>(regs[reg], sec);
            // print(regs, reg);
        } else if (opcode == "add") {
            regs[reg] = do_op<plus<int64_t>>(regs[reg], sec);
            //      print(regs, reg);
        } else if (opcode == "mod") {
            regs[reg] = do_op<SafeModulus>(regs[reg], sec);
            //     print(regs, reg);
        } else if (opcode == "div") {
            regs[reg] = do_op<SafeDivides>(regs[reg], sec);
            //     print(regs, reg);
        } else if (opcode == "eql") {
            regs[reg] = do_op<Eql>(regs[reg], sec);
            //       print(regs, reg);
        } else {
            assert(false);
        }
    }
    assert(next_input == 15);
    return regs['z'].contains(0);
}

optional<string> solve(vector<VSet> input, int i, bool downwards)
{
    assert(0 <= i && i < 14);
    vector<int64_t> js(9, 0);
    iota(BE(js), 1);
    if (downwards) {
        reverse(BE(js));
    }
    for (int64_t j : js) {
        input[i] = VSet(j);
        if (does_return_zero(input)) {
            char winning_digit = char('0' + j);
            if (i + 1 < 14) {
                auto r = solve(input, i + 1, downwards);
                if (r) {
                    return winning_digit + *r;
                } else {
                    continue;
                }
            } else {
                return string({winning_digit});
            }
        }
    }
    return nullopt;
}

void solve(bool downwards)
{
    vector<VSet> input;
    input.resize(14);
    FOR (i, 0, < 14) {
        auto& ii = input[i];
        FOR (i, 1, <= 9) {
            ii.insert(i);
        }
    }
    if (auto biggest = solve(input, 0, downwards)) {
        printf("%s: %s\n", downwards ? "biggest" : "smallest", biggest->c_str());
    } else {
        printf("Not found.\n");
    }
}

int compile()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d24_input_orig.txt");
    assert(f.good());
    auto lines = read_lines(f);
    FOR (ch, 'w', <= 'z') {
        printf("VSet %c(0);\n", ch);
    }
    FOR (i, 1, <= 14) {
        printf("const VSet& i%d = input[%d];\n", i, i - 1);
    }

    int next_input = 1;

    int line_no = 1;
    for (auto l : lines) {
        auto ls = split(l, " ");
        auto opcode = ls[0];
        assert(~ls[1] == 1);
        char reg = ls[1][0];
        if (~ls == 2) {
            assert(opcode == "inp");
            printf("%c=i%d;\n", reg, next_input);
            ++next_input;
            continue;
        }

        assert(~ls == 3);

        assert(~ls == 3);
        string sec;
        if (auto n = try_number(ls[2])) {
            sec = "VSet(" + to_string(*n) + ")";
        } else {
            assert(~ls[2] == 1);
            sec = ls[2];
        }

        if (opcode == "mul") {
            printf("%c=do_op<multiplies<int64_t>>(%c,%s);\n", reg, reg, sec.c_str());
        } else if (opcode == "add") {
            printf("%c=do_op<plus<int64_t>>(%c,%s);\n", reg, reg, sec.c_str());
        } else if (opcode == "mod") {
            printf("%c=do_op<SafeModulus>(%c,%s);\n", reg, reg, sec.c_str());
        } else if (opcode == "div") {
            printf("%c=do_op<SafeDivides>(%c,%s);\n", reg, reg, sec.c_str());
        } else if (opcode == "eql") {
            printf("%c=do_op<Eql>(%c,%s);\n", reg, reg, sec.c_str());
        } else {
            assert(false);
        }
    }
    assert(next_input == 15);
    return 0;
}

int main()
{
    solve(false);
    // compile();
    return 0;
}

#if 1
bool program(const vector<VSet>& input)
{
    VSet w(0);
    VSet x(0);
    VSet y(0);
    VSet z(0);
    const VSet& i1 = input[0];
    const VSet& i2 = input[1];
    const VSet& i3 = input[2];
    const VSet& i4 = input[3];
    const VSet& i5 = input[4];
    const VSet& i6 = input[5];
    const VSet& i7 = input[6];
    const VSet& i8 = input[7];
    const VSet& i9 = input[8];
    const VSet& i10 = input[9];
    const VSet& i11 = input[10];
    const VSet& i12 = input[11];
    const VSet& i13 = input[12];
    const VSet& i14 = input[13];
    w = i1;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(12));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(4));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i2;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(11));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(10));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i3;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(14));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(12));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i4;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-6));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(14));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i5;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(15));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(6));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i6;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(12));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(16));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i7;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-9));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(1));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i8;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(14));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(7));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i9;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(1));
    x = do_op<plus<int64_t>>(x, VSet(14));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(8));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i10;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-5));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(11));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i11;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-9));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(8));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i12;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-5));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(3));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i13;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-2));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(1));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    w = i14;
    x = do_op<multiplies<int64_t>>(x, VSet(0));
    x = do_op<plus<int64_t>>(x, z);
    x = do_op<SafeModulus>(x, VSet(26));
    z = do_op<SafeDivides>(z, VSet(26));
    x = do_op<plus<int64_t>>(x, VSet(-7));
    x = do_op<Eql>(x, w);
    x = do_op<Eql>(x, VSet(0));
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, VSet(25));
    y = do_op<multiplies<int64_t>>(y, x);
    y = do_op<plus<int64_t>>(y, VSet(1));
    z = do_op<multiplies<int64_t>>(z, y);
    y = do_op<multiplies<int64_t>>(y, VSet(0));
    y = do_op<plus<int64_t>>(y, w);
    y = do_op<plus<int64_t>>(y, VSet(8));
    y = do_op<multiplies<int64_t>>(y, x);
    z = do_op<plus<int64_t>>(z, y);
    return z.contains(0);
}
#else
bool program(const vector<VSet>&)
{
    return false;
}
#endif
