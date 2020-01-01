#include "common.h"

const int N_CARDS = 10007;
const string DWI = "deal with increment ";
const string CUT = "cut ";
const string DINS = "deal into new stack";

enum OpCode
{
    OP_CUT,
    OP_DWI,
    OP_DINS
};

struct DTable
{
private:
    int i = 0;
    int ks1 = 0;

public:
    DTable() = default;
    DTable(int64_t N, int i) : i(i) { ks1 = get_k(1, N % i); }
    int get_k_cached(int a) const
    {
        assert(0 <= a && a < i);
        return (a * ks1) % i;
    }

private:
    int get_k(int a, int b) const
    {
        assert(0 <= a && a < i);
        // mod(a + k * b, i) = 0
        FOR (k, 0, < i) {
            if ((a + k * b) % i == 0) {
                return k;
            }
        }
        assert(false);
        return INT_MIN;
    }
};

struct Op
{
    OpCode opcode;
    int i;
    DTable dtable;
};
vector<Op> ops;

VI deck;
void do_dwi(int i)
{
    VI nd(~deck, -1);
    int pos = 0;
    for (auto c : deck) {
        nd[pos] = c;
        pos = (pos + i) % ~deck;
    }
    deck.swap(nd);
}

const int64_t DS = 119315717514047;
const int64_t SC = 101741582076661;

int64_t source_pos_before_dwi(int i, int64_t dest_pos, int64_t N)
{
    assert(N % i != 0);
#if 0
    auto full_cycle_items = N / i + 1;
    auto full_cycle_count = N % i;
    auto partial_cycle_count = i - full_cycle_count;
    auto partial_cycle_items = full_cycle_items - 1;

    int64_t first_guess = -1;
    if (0 <= dest_pos && dest_pos < i * partial_cycle_items) {
        auto col = dest_pos / i;
        auto row = dest_pos % i;
        first_guess = row * full_cycle_items + col;
    } else {
        assert(i * partial_cycle_items < dest_pos && dest_pos < N);
        auto dest_pos2 = dest_pos - i * partial_cycle_items;
        auto col = dest_pos2 / (i - 1) + partial_cycle_items;
        auto row = dest_pos2 % (i - 1);
        first_guess = row * full_cycle_items + col;
    }
#endif
    int64_t source_pos = 0;
    for (;;) {
        auto q = dest_pos / i;
        dest_pos -= q * i;
        source_pos += q;
        if (dest_pos == 0) {
            // assert(first_guess==source_pos);
            return source_pos;
        }
        dest_pos = N + dest_pos - i;
        ++source_pos;
    }
}

void do_cut(int i)
{
    if (i < 0) {
        i = ~deck + i;
    }
    VI r(deck.begin() + i, deck.end());
    r.insert(r.end(), deck.begin(), deck.begin() + i);
    deck.swap(r);
}

int64_t source_pos_before_cut(int64_t i, int64_t dest_pos, const int64_t N)
{
    if (i < 0) {
        return source_pos_before_cut(N + i, dest_pos, N);
    } else {
        // card pos [0, i) go to [N-i, N)
        // card pos [i, N) go to [0, N-i)
        if (N - i <= dest_pos && dest_pos < N) {
            return dest_pos - (N - i);
        } else if (0 <= dest_pos && dest_pos < N - i) {
            return dest_pos + i;
        } else {
            assert(false);
            fprintf(stderr, "UNREACHABLE\n");
            std::terminate();
        }
    }
}

void do_dins()
{
    reverse(BE(deck));
}

int64_t source_pos_before_dins(int64_t dest_pos, int64_t N)
{
    return N - 1 - dest_pos;
}

bool starts_with(const string& x, const string& y)
{
    return ~x >= ~y && x.substr(0, ~y) == y;
}

int64_t source_pos_before_dwi2(int i, int64_t dest_pos, int64_t N)
{
    int k = DTable(N, i).get_k_cached(dest_pos % i);
    return dest_pos / i + (dest_pos % i + k * (N % i)) / i + k * (N / i);
}
int64_t source_pos_before_dwi3(int i, int64_t dest_pos, int64_t N, int k)
{
    return dest_pos / i + (dest_pos % i + k * (N % i)) / i + k * (N / i);
}

void solve2()
{
    int64_t FINAL_DEST_POS = 2020;
    int64_t dest_pos = FINAL_DEST_POS;
    // int64_t dest_pos = 2514;
    const int64_t N = DS;
    const int64_t sc = SC;
    // const int64_t sc = 1;
    printf("After all iterations card is at %lld\n", dest_pos);
    int64_t after_its_when_at_fdp = sc;
    for (int64_t after_its = sc; after_its > 0; --after_its) {
        printf("dest_pos %lld\n", dest_pos);
        if (dest_pos == FINAL_DEST_POS) {
            if (after_its_when_at_fdp != INT64_MIN) {
                auto d = after_its_when_at_fdp - after_its;
                printf("!!! %lld\n", d);
                if (d != 0) {
                    auto k = after_its / d;
                    after_its -= k * d;
                }
            }
            after_its_when_at_fdp = after_its;
        }
        FORBACK (ip, ~ops - 1, >= 0) {
            auto op = ops[ip];
            switch (op.opcode) {
                case OP_DINS:
                    dest_pos = source_pos_before_dins(dest_pos, N);
                    break;
                case OP_CUT:
                    dest_pos = source_pos_before_cut(op.i, dest_pos, N);
                    break;
                case OP_DWI: {
                    int k = op.dtable.get_k_cached(dest_pos % op.i);
                    dest_pos = source_pos_before_dwi3(op.i, dest_pos, N, k);
                } break;
                default:
                    assert(false);
            }
        }
    }
    printf("part2 %lld\n", dest_pos);
    return;
}

void trace(int its)
{
    int dest_pos = INT_MIN;
    FOR (i, 0, < ~deck) {
        if (deck[i] == 2019) {
            dest_pos = i;
            break;
        }
    }
    assert(dest_pos != INT_MIN);
    printf("After op#%d card 2019 is at %d\n", its, dest_pos);
}

/*
struct DTables {
    int get_k(int64_t N, int i, int a){
        auto it = xs.find(pair
    }
}
*/

struct AB
{
    // a x + b
    int64_t a, b;
    bool operator<(AB y) const
    {
        if (a < y.a) {
            return true;
        }
        if (a > y.a) {
            return false;
        }
        return b < y.b;
    }
};

struct U128
{
    uint64_t lo, hi;
    void add_shift(uint64_t x, int sh)
    {
        assert(0 <= sh && sh <= 64);
        if (sh < 64) {
            add(x << sh);
        }
        if (sh > 0) {
            add_to_hi(x >> (64 - sh));
        }
    }
    void add(uint64_t x)
    {
        auto a = (lo & ((1UL << 63) - 1));
        auto b = (x & ((1UL << 63) - 1));
        auto ab = a + b;
        switch ((lo >> 63) + (x >> 63)) {
            case 0:
                break;
            case 1:
                if (ab >> 63) {
                    add_to_hi(1);
                } else {
                    ab |= (1UL << 63);
                }
                break;
            case 2:
                add_to_hi(1);
                break;
            default:
                assert(false);
        }
        lo = ab;
    }
    void add_to_hi(uint64_t x)
    {
        assert(hi < (1UL << 63) && (hi < (1UL << 63)));
        hi += x;
    }
};

__uint128_t mult64(uint64_t a, uint64_t b)
{
    return (__uint128_t)a * (__uint128_t)b;
}

AB add(AB in, int64_t f, int64_t N)
{
    return AB{in.a, (in.b + f) % N};
}

AB invert(AB in, int64_t N)
{
    return AB{(N - in.a) % N, (N - 1 - in.b) % N};
}

int64_t mod(__uint128_t x, int64_t y)
{
    auto r = x % (__uint128_t)y;
    assert(r < INT64_MAX);
    return (int64_t)r;
}

AB compose(AB first_op, AB second_op, int64_t N)
{
    auto K1 = mod(mult64(second_op.a, first_op.b), N);
    auto K2 = K1 + second_op.b;
    auto K3 = K2 % N;
    return AB{mod(mult64(second_op.a, first_op.a), N), K3};
}

struct ARKey
{
    AB ab;
    int64_t its;
    bool operator<(const ARKey& y) const
    {
        if (ab < y.ab) {
            return true;
        }
        if (y.ab < ab) {
            return false;
        }
        return its < y.its;
    }
};

map<ARKey, AB> armap;

AB apply_repeatedly(AB ab, int64_t its, int64_t N)
{
    auto key = ARKey{ab, its};
    auto it = armap.find(key);
    if (it != armap.end()) {
        return it->second;
    }
    assert(its >= 0);
    if (its == 0) {
        return AB{1, 0};
    }
    if (its == 1) {
        return ab;
    }
    auto half = its / 2;
    auto ab1 = apply_repeatedly(ab, half, N);
    auto ab2 = apply_repeatedly(ab, its - half, N);
    auto r = compose(ab1, ab2, N);
    armap.insert(make_pair(key, r));
    return r;
}

AB multiply_int(AB in, int i, int64_t N)
{
    return AB{(in.a * i) % N, (in.b * i) % N};
}

/*
AB multiply(AB in, int64_t f, int64_t N)
{
    assert(f > 0);
    return AB{multiply_mod(in.a, f, N), multiply_mod(in.b, f, N)};
}
*/

using i128 = __int128_t;
using i64 = int64_t;

i64 modulo_inverse(i64 a, i64 n)
{
    i64 t = 0;
    i64 newt = 1;
    auto r = n;
    i64 newr = a;
    while (newr != 0) {
        auto quotient = r / newr;
        tie(t, newt) = make_tuple(newt, t - quotient * newt);
        tie(r, newr) = make_tuple(newr, r - quotient * newr);
    }
    assert(r <= 1);  // otherwise a is not invertible
    if (t < 0) {
        t += n;
    }
    return t;
}

// Solves a x =mod n= b for x.
i64 linear_congruence(i64 a, i64 b, i64 n)
{
    return ((i128)modulo_inverse(a, n) * (i128)b) % n;
}

void solve3()
{
    int64_t N;
    int64_t ITS;
    int64_t FINAL_POS;
    if (false) {
        N = 10007;
        ITS = 1;
        FINAL_POS = 2514;
    } else {
        N = DS;
        ITS = SC;
        FINAL_POS = 2020;
    }
    auto ab = AB{1, 0};

    for (auto op : ops) {
        switch (op.opcode) {
            case OP_DINS:
                ab = invert(ab, N);
                break;
            case OP_CUT:
                ab = add(ab, -op.i, N);
                break;
            case OP_DWI:
                ab = multiply_int(ab, op.i, N);
                break;
            default:
                assert(false);
        }
    }

    auto ab_its = apply_repeatedly(ab, ITS, N);

    auto W = (N + FINAL_POS - ab_its.b);

    auto sp = linear_congruence(ab_its.a, W, N);

    auto Wmoda = W % ab_its.a;
    auto a_minus_Wmoda = ab_its.a - Wmoda;
    auto Nmoda = N % ab_its.a;

    for (__int128_t K = 0; K < ab_its.a; ++K) {
        if (K % 10000000 == 0) {
            printf("%f%%\n", (double)K / (double)ab_its.a * 100.0);
        }
        auto x = (int64_t)((K * Nmoda) % ab_its.a);
        auto y = a_minus_Wmoda;
        // printf("%lld\n", llabs((int64_t)x - (int64_t)y));
        if (x == y) {
            assert((Wmoda + (K * N) % ab_its.a) % ab_its.a == 0);
            auto A1 = W / ab_its.a;
            auto A2 = (K * N) / ab_its.a;
            auto A3 = (Wmoda + (K * N) % ab_its.a) / ab_its.a;
            auto sp = A1 + A2 + A3;
            printf("K: %lld, sp: %lld\n", (int64_t)K, (int64_t)sp);
            break;
        }
    }
}

bool operator==(AB x, AB y)
{
    return x.a == y.a && x.b == y.b;
}

int main()
{
    deck.resize(N_CARDS);
    iota(BE(deck), 0);
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d22_input.txt");
    auto lines = read_lines(f);
    trace(0);
    int its = 0;
    for (auto& l : lines) {
        if (starts_with(l, DWI)) {
            auto i = stoi(l.substr(~DWI));
            do_dwi(i);
            ops.push_back(Op{OP_DWI, i, DTable(DS, i)});
        } else if (starts_with(l, CUT)) {
            auto i = stoi(l.substr(~CUT));
            do_cut(i);
            ops.push_back(Op{OP_CUT, i, DTable{}});
        } else if (l == DINS) {
            do_dins();
            ops.push_back(Op{OP_DINS, INT_MIN, DTable{}});
        } else {
            assert(false);
        }
        ++its;
        trace(its);
    }
    FOR (i, 0, < ~deck) {
        if (deck[i] == 2019) {
            printf("part1 %d\n", i);
            break;
        }
    }
    solve3();
    return 0;
}
