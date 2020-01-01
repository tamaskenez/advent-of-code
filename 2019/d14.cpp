#include <fstream>

#include "common.h"

VS lines_from_file(const string& filename)
{
    fstream f((CMAKE_CURRENT_SOURCE_DIR "/") + filename);
    VS xs;
    for (;;) {
        string s;
        std::getline(f, s);
        if (!s.empty()) {
            xs.push_back(s);
        }
        if (!f.good()) {
            break;
        }
    }
    return xs;
}

VS split(const string& l)
{
    VS tokens;
    int i = 0;
    do {
        string t;
        for (; i < ~l && l[i] != ' ' && l[i] != ','; ++i) {
            t += l[i];
        }
        if (!t.empty()) {
            tokens.push_back(t);
        }
        ++i;
    } while (i < ~l);
    return tokens;
}

using Quant = int64_t;

struct QCH
{
    Quant q;
    string ch;
};

struct Rule
{
    vector<QCH> lhs;
    QCH rhs;
};

Rule parse_line(const string& l)
{
    vector<QCH> lhs;
    auto tokens = split(l);
    for (int i = 0; i < ~tokens;) {
        if (tokens[i] == "=>") {
            assert(i == ~tokens - 3);
            auto ti = tokens[i + 1];
            auto tii = tokens[i + 2];
            auto q = stoi(ti);
            return Rule{lhs, QCH{q, tii}};
        }
        assert(i <= ~tokens - 5);
        lhs.emplace_back(QCH{stoi(tokens[i]), tokens[i + 1]});
        i += 2;
    }
    assert(false);
    return {};
}

using RuleMap = map<string, Rule>;

RuleMap parse_input(const VS& lines)
{
    RuleMap rm;
    for (auto& l : lines) {
        auto rule = parse_line(l);
        assert(rm.find(rule.rhs.ch) == rm.end());
        rm[rule.rhs.ch] = rule;
    }
    return rm;
}

double waste(Quant q, const string& ch, const RuleMap& rm, const map<string, double>& costs)
{
    auto it = rm.find(ch);
    assert(it != rm.end());
    auto& lhs = it->second.lhs;
    auto& rhs = it->second.rhs;
    auto factor = (q + rhs.q - 1) / rhs.q;
    if (factor == 0) {
        return 0.0;
    }
    auto rem = factor * rhs.q - q;
    return rem * costs.at(rhs.ch);
}

struct BDResult
{
    map<string, Quant> lhs;
    Quant rhs_surplus;
};

BDResult break_down(Quant q, const string& ch, const RuleMap& rm)
{
    auto it = rm.find(ch);
    assert(it != rm.end());
    auto& lhs = it->second.lhs;
    auto& rhs = it->second.rhs;
    auto factor = (q + rhs.q - 1) / rhs.q;
    auto surplus = factor * rhs.q - q;
    map<string, Quant> result;
    for (auto& qch : lhs) {
        result[qch.ch] += factor * qch.q;
    }
    return {result, surplus};
}

map<string, Quant> break_down_exact(Quant q, const string& ch, const RuleMap& rm)
{
    auto it = rm.find(ch);
    assert(it != rm.end());
    auto& lhs = it->second.lhs;
    auto& rhs = it->second.rhs;
    auto factor = q / rhs.q;
    if (factor == 0) {
        return {};
    }
    auto rem = q - factor * rhs.q;
    map<string, Quant> result;
    if (rem > 0) {
        result[ch] = rem;
    }
    for (auto& qch : lhs) {
        result[qch.ch] += factor * qch.q;
    }
    return result;
}

Quant break_down(const map<string, Quant>& input,
                 const RuleMap& rm,
                 const map<string, double>& costs)
{
    map<string, Quant> output = input;
    output["ORE"];
    for (auto& kv : rm) {
        output[kv.first];
    }
    bool change;
    do {
        change = false;
        for (auto& kv : output) {
            if (kv.first == "ORE" || kv.second <= 0) {
                continue;
            }
            auto bd = break_down_exact(kv.second, kv.first, rm);
            if (bd.empty()) {
                continue;
            }
            kv.second = 0;
            for (auto& kv : bd) {
                output[kv.first] += kv.second;
            }
            change = true;
        }
    } while (change);

    double best_w = INFINITY;
    string best_w_ch;
    for (auto it = output.begin(); it != output.end();) {
        if (it->second == 0) {
            it = output.erase(it);
        } else {
            if (it->first != "ORE" && it->second > 0) {
                auto w = waste(it->second, it->first, rm, costs);
                // printf("... %d %s is %f waste\n", it->second, it->first.c_str(), w);
                if (w < best_w) {
                    best_w = w;
                    best_w_ch = it->first;
                }
            }
            ++it;
        }
    }
    if (best_w_ch.empty()) {
        return output.at("ORE");
    }
    assert(!best_w_ch.empty() && best_w < INFINITY);

    // printf("... WINNER %d %s is %f waste\n", output[best_w_ch], best_w_ch.c_str(), best_w);

    auto[bd, surplus] = break_down(output[best_w_ch], best_w_ch, rm);
    output[best_w_ch] = -surplus;
    for (auto& kv : bd) {
        output[kv.first] += kv.second;
    }
    return break_down(output, rm, costs);
}

Quant break_down_fuel_to_ores(const RuleMap& rm, const map<string, double>& costs, Quant fuel_quant)
{
    auto it = rm.find("FUEL");
    assert(it != rm.end());
    auto& rhs = it->second.rhs;
    auto& lhs = it->second.lhs;
    assert(rhs.ch == "FUEL");
    assert(rhs.q == 1);
    map<string, Quant> input;
    input["FUEL"] = fuel_quant;
    return break_down(input, rm, costs);
}

map<string, double> calc_costs(const RuleMap& rm)
{
    map<string, double> costs;
    costs["ORE"] = 1;
    bool has_unknown = true;
    for (; has_unknown;) {
        has_unknown = false;
        for (auto& r : rm) {
            auto& rhs = r.second.rhs;
            if (costs.count(rhs.ch) > 0) {
                continue;
            }
            auto& lhs = r.second.lhs;
            bool all_known = true;
            double cost = 0;
            for (auto& l : lhs) {
                auto it = costs.find(l.ch);
                if (it == costs.end()) {
                    all_known = false;
                    break;
                }
                cost += it->second * l.q;
            }
            if (all_known) {
                costs[rhs.ch] = cost / rhs.q;
            } else {
                has_unknown = true;
            }
        }
    }
    printf("-- Got costs.\n");
    return costs;
}

void solve(const string& filename, int expected_ores, Quant fuel_quant = 1)
{
    auto lines = lines_from_file(filename);
    auto rm = parse_input(lines);
    auto costs = calc_costs(rm);
    auto r = break_down_fuel_to_ores(rm, costs, fuel_quant);
    printf("got %lld, expected %d\n", r, expected_ores);
}

void solve2(const string& filename, Quant expected_fuel)
{
    auto lines = lines_from_file(filename);
    auto rm = parse_input(lines);
    auto costs = calc_costs(rm);
    Quant one_tr_ores = 1000000000000;
    auto ores_per_fuel = break_down_fuel_to_ores(rm, costs, 1);
    Quant fuel_from_less_or_eq_1tr = one_tr_ores / ores_per_fuel;
    assert(break_down_fuel_to_ores(rm, costs, fuel_from_less_or_eq_1tr) <= one_tr_ores);
    Quant fuel_from_more_than_1tr = 2 * fuel_from_less_or_eq_1tr;
    assert(break_down_fuel_to_ores(rm, costs, fuel_from_more_than_1tr) > one_tr_ores);
    for (;;) {
        Quant new_fuel = (fuel_from_less_or_eq_1tr + fuel_from_more_than_1tr) / 2;
        auto r = break_down_fuel_to_ores(rm, costs, new_fuel);
        if (r > one_tr_ores) {
            fuel_from_more_than_1tr = new_fuel;
        } else {
            fuel_from_less_or_eq_1tr = new_fuel;
        }
        if (fuel_from_more_than_1tr - 1 == fuel_from_less_or_eq_1tr) {
            break;
        }
    }
    printf("got %lld, expected %lld\n", fuel_from_less_or_eq_1tr, expected_fuel);
}

int main()
{
    solve("d14_input1.txt", 31);
    solve("d14_input2.txt", 165);
    solve("d14_input3.txt", 13312);
    solve("d14_input4.txt", 180697);
    solve("d14_input5.txt", 2210736);
    solve("d14_input.txt", 0);

    solve2("d14_input3.txt", 82892753);
    solve2("d14_input4.txt", 5586022);
    solve2("d14_input5.txt", 460664);
    solve2("d14_input.txt", 0);

    return 0;
}