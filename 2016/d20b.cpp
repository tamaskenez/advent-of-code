#include "common.h"

using i64 = int64_t;

struct IV
{
    i64 lower, upper;  // upper exclusive
};

bool is_overlapping(IV a, IV b)
{
    assert(a.lower < a.upper);
    assert(b.lower < b.upper);
    if (a.upper < b.lower) {
        return false;
    }
    if (b.upper < a.lower) {
        return false;
    }
    return true;
}

IV merge(IV a, IV b)
{
    assert(is_overlapping(a, b));
    return IV{min(a.lower, b.lower), max(a.upper, b.upper)};
}

void merge_into(map<i64, i64>& ivs, const IV& iv)
{
    if (iv.lower == iv.upper) {
        return;
    }
    assert(iv.lower < iv.upper);
    if (ivs.empty()) {
        ivs[iv.lower] = iv.upper;
        return;
    }
    // find one interval that is overlaps with iv
    auto can_be_overlapping = ivs.upper_bound(iv.lower);
    if (can_be_overlapping == ivs.begin()) {
        // this is the first which can be overlapping
    } else {
        --can_be_overlapping;
    }
    for (;;) {
        assert(can_be_overlapping != ivs.end());
        auto iv2 = IV{can_be_overlapping->first, can_be_overlapping->second};
        if (is_overlapping(iv2, iv)) {
            ivs.erase(can_be_overlapping);
            auto iv3 = merge(iv2, iv);
            merge_into(ivs, iv3);
            return;
        }
        ++can_be_overlapping;
        if (can_be_overlapping == ivs.end()) {
            ivs[iv.lower] = iv.upper;
            return;
        }
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<i64, i64> ivs;  // disjunct
    for (auto& l : lines) {
        auto vs = split(l, "-");
        assert(~vs == 2);
        i64 a = stoul(vs[0]);
        i64 b = stoul(vs[1]);
        assert(to_string(a) == vs[0]);
        assert(to_string(b) == vs[1]);
        merge_into(ivs, IV{a, b + 1});
    }
    i64 cand = 0;
    for (;;) {
        auto it = ivs.find(cand);
        if (it == ivs.end()) {
            printf("%lld\n", cand);
            break;
        }
        cand = it->second;
    }
    i64 total=0;
    auto it = ivs.begin();
    total += it->first - 0;
    for(;;++it){
        auto jt = it;
        ++jt;
        if(jt==ivs.end()){
            total += UINT32_MAX - it->second + 1;
            break;
        }
        total += jt->first - it->second;
    }
    printf("total %lld\n",total);
    return 0;
}
