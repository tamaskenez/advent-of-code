#include "common.h"

struct Rule
{
    string container;
    set<pair<string, int>> contained;
    bool operator<(const Rule& r) const
    {
        if (container < r.container) {
            return true;
        }
        if (container > r.container) {
            return false;
        }
        return contained < r.contained;
    }
};

Rule line_to_rule(string line)
{
    line = trim(line);
    assert(!line.empty());
    auto words = split(line, " .,");
    Rule rule;
    rule.container = words.at(0) + " " + words.at(1);
    assert(words.at(2) == "bags");
    assert(words.at(3) == "contain");

    if (words.at(4) == "no") {
    } else {
        int i = 4;
        for (;;) {
            auto n = atoi(words.at(i).c_str());
            auto color = words.at(i + 1) + " " + words.at(i + 2);
            assert(starts_with(words.at(i + 3), "bag"));
            i += 4;
            rule.contained.insert(make_pair(color, n));
            if (i + 4 > ~words) {
                assert(i == ~words);
                break;
            }
        }
    }
    return rule;
}

set<string> what_contains_this(maybe<int> n,
                               string color,
                               const map<string, set<Rule>>& contained_to_rule)
{
    set<string> result;
    auto it = contained_to_rule.find(color);
    if (it == contained_to_rule.end()) {
        return result;
    }
    for (auto& rule : it->second) {
        for (auto contained : rule.contained) {
            if (contained.first == color && (!n || n == contained.second)) {
                result.insert(rule.container);
                break;
            }
        }
    }
    return result;
}

map<string, int> cache;

int count_contained(string container, const map<string, Rule>& container_to_rule)
{
    auto it_rule = container_to_rule.find(container);
    assert(it_rule != container_to_rule.end());
    int count = 0;
    for (auto& contained : it_rule->second.contained) {
        auto it = cache.find(contained.first);
        if (it == cache.end()) {
            cache[contained.first] = count_contained(contained.first, container_to_rule);
            it = cache.find(contained.first);
        }
        count += contained.second * it->second + contained.second;
    }
    return count;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d7_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, set<Rule>> contained_to_rule;
    map<string, Rule> container_to_rule;
    for (auto& l : lines) {
        auto rule = line_to_rule(l);
        for (auto contained : rule.contained) {
            contained_to_rule[contained.first].insert(rule);
        }
        assert(container_to_rule.count(rule.container) == 0);
        container_to_rule[rule.container] = rule;
    }

    set<string> results;
    set<string> checking_now = {"shiny gold"};
    while (!checking_now.empty()) {
        set<string> new_to_check;
        for (auto c : checking_now) {
            for (auto d : what_contains_this(nullopt, c, contained_to_rule)) {
                if (results.count(d) == 0) {
                    new_to_check.insert(d);
                }
            }
        }
        results.insert(BE(new_to_check));
        checking_now = new_to_check;
    }
    printf("P1: %d\n", ~results);

    auto p2 = count_contained("shiny gold", container_to_rule);
    printf("P2: %d\n", p2);
    return 0;
}

// 36.19
