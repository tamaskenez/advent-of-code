#include "common.h"

//clang-format off
string mi =
    "CRnSiRnCaPTiMgYCaPTiRnFArSiThFArCaSiThSiThPBCaCaSiRnSiRnTiTiMgArPBCaPMgYPTiRnFArFArCaSiRnBPMgA"
    "rPRnCaPTiRnFArCaSiThCaCaFArPBCaCaPTiTiRnFArCaSiRnSiAlYSiThRnFArArCaSiRnBFArCaCaSiRnSiThCaCaCaF"
    "YCaPTiBCaSiThCaSiThPMgArSiRnCaPBFYCaCaFArCaCaCaCaSiThCaSiRnPRnFArPBSiThPRnFArSiRnMgArCaFYFArCa"
    "SiRnSiAlArTiTiTiTiTiTiTiRnPMgArPTiTiTiBSiRnSiAlArTiTiRnPMgArCaFYBPBPTiRnSiRnMgArSiThCaFArCaSiT"
    "hFArPRnFArCaSiRnTiBSiThSiRnSiAlYCaFArPRnFArSiThCaFArCaCaSiThCaCaCaSiRnPRnCaFArFYPMgArCaPBCaPBS"
    "iRnFYPBCaFArCaSiAl";
//clang-format on

template <class X, class Y>
using uomap = unordered_map<X, Y>;

template <class X>
using uoset = unordered_set<X>;

VI get_foundats(const string& hs, const string& n)
{
    VI poss;
    int i = 0;
    for (;;) {
        auto found = hs.find(n, i);
        if (found == string::npos) {
            return poss;
        }
        poss.PB(found);
        i = found + 1;
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d19_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, vector<string>> reps;
    unordered_map<string, string> rtol;
    for (auto& l : lines) {
        auto xs = split(l, " =>");
        assert(~xs == 2);
        auto x = xs[0];
        auto y = xs[1];
        reps[x].PB(y);
        must_insert(rtol, make_pair(y, x));
    }
    set<string> all;
    FOR (i, 0, < ~mi) {
        if (islower(mi[i])) {
            continue;
        }
        string from;
        if (i + 1 < ~mi && islower(mi[i + 1])) {
            from = mi.substr(i, 2);
        } else {
            from = mi.substr(i, 1);
        }
        auto it = reps.find(from);
        if (it != reps.end()) {
            auto& vs = it->second;
            for (auto& v : vs) {
                auto s = mi.substr(0, i) + v + mi.substr(i + ~from);
                all.insert(s);
            }
        }
    }
    printf("%d\n", ~all);

    // --------------

    if (true) {
        struct Item
        {
            string to_reduce;
            int steps_so_far;
            bool operator<(const Item& b) const
            {
                if (~to_reduce < ~b.to_reduce) {
                    return true;
                }
                if (~to_reduce > ~b.to_reduce) {
                    return false;
                }
                if (steps_so_far < b.steps_so_far) {
                    return true;
                }
                if (steps_so_far > b.steps_so_far) {
                    return false;
                }
                return false;
            }
        };
        set<Item> items;
        // SOL3
        items.insert(Item{mi, 0});
        while (!items.empty()) {
            auto item = move(*items.begin());
            items.erase(items.begin());
            for (auto& kv : rtol) {
                auto pos = item.to_reduce.find(kv.first);
                if (pos != string::npos) {
                    auto new_item = Item{item.to_reduce.substr(0, pos) + kv.second +
                                             item.to_reduce.substr(pos + ~kv.first),
                                         item.steps_so_far + 1};
                    if (new_item.to_reduce == "e") {
                        printf("part2 %d\n", new_item.steps_so_far);
                        return 0;
                    }
                    items.insert(move(new_item));
                }
            }
        }
    }

    // SOL2
    struct Item
    {
        int x0;        // generate mi.substr(x0)
        string molec;  // from this
        int steps_so_far;
        // prefer higher x0 first
        bool operator<(const Item& y) const
        {
            if (x0 > y.x0) {
                return true;
            }
            if (x0 < y.x0) {
                return false;
            }
            if (steps_so_far < y.steps_so_far) {
                return true;
            }
            if (steps_so_far > y.steps_so_far) {
                return false;
            }
            /*
            if (~molec < ~y.molec) {
                return false;
            }
            if (~molec > ~y.molec) {
                return true;
            }*/
            return molec < y.molec;
        }
    };

    if (false) {
        // mi = "HCaSiRnFYFArSiThRnFAr";
        uoset<string> done;
        set<Item> ws;
        ws.insert(Item{0, "e", 0});
        int best_x0 = 0;
        int count = 0;
        while (!ws.empty()) {
            ++count;
            if (count % 1000000 == 0) {
                printf("count: %d, ~ws: %d\n", count, ~ws);
            }
            auto pis = *ws.begin();
            ws.erase(ws.begin());
            // done.insert(pis.molec);
            printf("pis %d %s %d, ~ws = %d\n", pis.x0, pis.molec.c_str(), pis.steps_so_far, ~ws);
            if (pis.x0 > best_x0) {
                best_x0 = pis.x0;
                printf("best_x0 %d\n", best_x0);
            }
            if (pis.molec == "") {
                printf("part2 %d\n", pis.steps_so_far);
                break;
            }
            const int maxntogen = ~mi - pis.x0;
            // apply all rules to the first atom
            for (auto& kv : reps) {
                auto& rule_lhs = kv.FST;
                if (starts_with(pis.molec, rule_lhs)) {
                    for (auto& rule_rhs : kv.SND) {
                        auto newmolec = rule_rhs + pis.molec.substr(~rule_lhs);
                        if (~newmolec <= maxntogen && !contains(done, newmolec)) {
                            int ncommonchars = 0;
                            while (ncommonchars < ~newmolec &&
                                   mi.at(pis.x0 + ncommonchars) == newmolec.at(ncommonchars)) {
                                ++ncommonchars;
                            }

                            int new_x0 = pis.x0 + ncommonchars;

                            bool can_insert = false;
                            auto left = mi.substr(new_x0);
                            if (left.empty()) {
                                can_insert = true;
                            } else {
                                for (auto& kv : rtol) {
                                    if (starts_with(left, kv.first)) {
                                        can_insert = true;
                                        break;
                                    }
                                }
                            }

                            if (can_insert) {
                                auto new_item = Item{new_x0, newmolec.substr(ncommonchars),
                                                     pis.steps_so_far + 1};
                                ws.insert(move(new_item));
                            }
                            // printf("");
                        }
                    }
                }
            }
        }
        printf("count: %d\n", count);
    }

    return 0;
}

// 192
// 11:09
