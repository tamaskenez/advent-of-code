#include "common.h"

// w1=w2=w3
// 1st group as few
// 1st group min product

VI pkgs = {1,  2,  3,  5,  7,  13, 17, 19, 23, 29,  31,  37,  41,  43, 53,
           59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};

void get_configs(const int* b,
                 const int* e,
                 const VI& weights_so_far,
                 map<int, vector<VI>>& configs,
                 int missing_weight,
                 bool one_is_enough)
{
    auto total = accumulate(b, e, 0);
    if (total < missing_weight) {
        return;
    }
    if (total == missing_weight) {
        auto ws = weights_so_far;
        ws.reserve(~ws + (e - b));
        FOR (wix, b, < e) {
            ws.PB(*wix);
        }
        configs[~ws].emplace_back(move(ws));
        return;
    }
    get_configs(b + 1, e, weights_so_far, configs, missing_weight, one_is_enough);
    if (one_is_enough && !configs.empty()) {
        return;
    }
    auto pb = *b;
    if (pb <= missing_weight) {
        auto wsf2 = weights_so_far;
        wsf2.PB(pb);
        get_configs(b + 1, e, wsf2, configs, missing_weight - pb, one_is_enough);
    }
}

int main()
{
    reverse(BE(pkgs));
    auto total = accumulate(BE(pkgs), 0);
    {
        map<int, vector<VI>> configs;
        get_configs(pkgs.data(), pkgs.data() + ~pkgs, VI{}, configs, total / 3, false);
        for (auto& kv : configs) {
            printf("P1 %d %d\n", kv.first, ~kv.second);
            RunningStat<uint64_t> best;
            for (auto& cf : kv.second) {
                uint64_t product = 1;
                for (auto i : cf) {
                    product *= i;
                }
                set<int> si;
                for (auto i : pkgs) {
                    si.insert(i);
                }
                for (auto i : cf) {
                    si.erase(i);
                }
                VI pkgs2(BE(si));
                map<int, vector<VI>> configs2;
                get_configs(pkgs2.data(), pkgs2.data() + ~pkgs2, VI{}, configs2, total / 3, true);
                if (!configs2.empty()) {
                    best.add(product);
                }
            }
            if (best.lower) {
                printf("part1 %llu\n", *best.lower);
                break;
            }
        }
    }
    {
        map<int, vector<VI>> configs;
        get_configs(pkgs.data(), pkgs.data() + ~pkgs, VI{}, configs, total / 4, false);
        for (auto& kv : configs) {
            printf("P2 %d %d\n", kv.first, ~kv.second);
            RunningStat<uint64_t> best;
            for (auto& cf : kv.second) {
                uint64_t product = 1;
                for (auto i : cf) {
                    product *= i;
                }
                set<int> si;
                for (auto i : pkgs) {
                    si.insert(i);
                }
                for (auto i : cf) {
                    si.erase(i);
                }
                VI pkgs2(BE(si));
                map<int, vector<VI>> configs2;
                get_configs(pkgs2.data(), pkgs2.data() + ~pkgs2, VI{}, configs2, total / 4, false);
                if (!configs2.empty()) {
                    bool done = false;
                    for (auto& kv2 : configs2) {
                        if (done) {
                            break;
                        }
                        for (auto& cf2 : kv2.second) {
                            auto si2 = si;
                            for (auto i : cf2) {
                                si.erase(i);
                            }
                            VI pkgs3(BE(si2));
                            map<int, vector<VI>> configs3;
                            get_configs(pkgs3.data(), pkgs3.data() + ~pkgs3, VI{}, configs3,
                                        total / 4, true);
                            if (!configs3.empty()) {
                                best.add(product);
                                done = true;
                                break;
                            }
                        }
                    }
                }
            }
            if (best.lower) {
                printf("part2 %llu\n", *best.lower);
                break;
            }
        }
    }
    return 0;
}
