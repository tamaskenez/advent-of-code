#include "common.h"

AI2 range_text_to_range(string s)
{
    auto ss = split(s, "-");
    assert(~ss == 2);
    return AI2{atoi(ss[0].c_str()), atoi(ss[1].c_str())};
}

struct Rule
{
    string name;
    AI2 ranges[2];
};

bool in_range(AI2 range, int v)
{
    return range[0] <= v && v <= range[1];
}

int main()
{
    vector<Rule> rules;
    vector<VI> nearbies;
    VI my_ticket;

    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d16_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int phase = 0;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        if (l == "your ticket:") {
            phase = 1;
            continue;
        }
        if (l == "nearby tickets:") {
            phase = 2;
            continue;
        }
        switch (phase) {
            case 0: {
                auto ms = split(l, ":");
                assert(~ms == 2);
                auto vs = split(ms[1], " ");
                assert(~vs == 3);
                auto field_name = ms[0];
                auto range1 = vs[0];
                assert(vs[1] == "or");
                auto range2 = vs[2];
                auto r1 = range_text_to_range(range1);
                auto r2 = range_text_to_range(range2);
                Rule r;
                r.name = field_name;
                r.ranges[0] = r1;
                r.ranges[1] = r2;
                rules.PB(r);
            } break;
            case 1: {
                auto vs = split(l, ",");
                for (auto v : vs) {
                    my_ticket.PB(atoi(v.c_str()));
                }
            } break;
            case 2: {
                auto vs = split(l, ",");
                vector<int> xs;
                for (auto& v : vs) {
                    xs.PB(atoi(v.c_str()));
                }
                nearbies.PB(xs);
            } break;
            default:
                assert(false);
        }
    }
    int p1 = 0;
    vector<VI> valids;
    for (auto& nb : nearbies) {
        bool had_invalid_field = false;
        for (auto fv : nb) {
            bool valid = false;
            for (auto r : rules) {
                if (in_range(r.ranges[0], fv) || in_range(r.ranges[1], fv)) {
                    valid = true;
                    break;
                } else {
                }
            }
            if (!valid) {
                p1 += fv;
                had_invalid_field = true;
            }
        }
        if (!had_invalid_field) {
            valids.PB(nb);
        }
    }
    printf("P1: %d\n", p1);
    printf("all nearbies %d, valids %d\n", ~nearbies, ~valids);

    auto NF = ~rules;
    unordered_set<int> all_rules;
    FOR (i, 0, < NF) {
        all_rules.insert(i);
    }
    vector<unordered_set<int>> vus(NF, all_rules);  // vus[field_ix] = { rule_ix* }
    for (auto v : valids) {
        assert(~v == NF);
        FOR (f_ix, 0, < NF) {
            VI rule_ix_to_remove;
            auto f_val = v[f_ix];
            for (auto r_ix : vus[f_ix]) {
                auto& rule = rules[r_ix];
                if (in_range(rule.ranges[0], f_val) || in_range(rule.ranges[1], f_val)) {
                } else {
                    rule_ix_to_remove.PB(r_ix);
                }
            }
            for (auto rixtr : rule_ix_to_remove) {
                vus[f_ix].erase(rixtr);
            }
            assert(!vus[f_ix].empty());
        }
    }
    unordered_set<int> fix_to_process;
    FOR (i, 0, < NF) {
        fix_to_process.insert(i);
    }
    while (!fix_to_process.empty()) {
        bool changed = false;
        for (auto f_ix : fix_to_process) {
            if (~vus[f_ix] == 1) {
                , m fix_to_process.erase(f_ix);
                auto bound_rule_ix = *vus[f_ix].begin();
                for (auto other_f_ix : fix_to_process) {
                    vus[other_f_ix].erase(bound_rule_ix);
                }
                changed = true;
                break;
            }
        }
        assert(changed);
    }
    assert(~my_ticket == NF);
    int64_t p2 = 1;
    FOR (f_ix, 0, < NF) {
        assert(~vus[f_ix] == 1);
        auto rule_ix = *vus[f_ix].begin();
        auto& rule = rules[rule_ix];
        printf("%s: %d\n", rule.name.c_str(), my_ticket[f_ix]);
        if (starts_with(rule.name, "departure")) {
            p2 *= my_ticket[f_ix];
        }
    }
    printf("P2: %lld\n", p2);
    return 0;
}
// 19:43
// not 434014277
