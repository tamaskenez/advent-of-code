#include "common.h"

constexpr bool USE_SHORTEST_REMAINDER = false;
struct RuleRhs
{
    vector<VI> alts;  // terminal if empty
    bool is_terminal() const { return alts.empty(); }
};

struct TRuleSeq
{
    int terminal_truleno;
    VI tail;
    bool operator<(const TRuleSeq& y) const
    {
        if (terminal_truleno < y.terminal_truleno) {
            return true;
        }
        if (terminal_truleno > y.terminal_truleno) {
            return false;
        }
        return tail < y.tail;
    }
};

struct TRuleRhs
{
    vector<TRuleSeq> alts;  // terminal if empty
    bool is_terminal() const { return alts.empty(); }
    bool operator<(const TRuleRhs& y) const { return alts < y.alts; }
};

struct Wsp
{
    int next_rule_no = 0;
    map<int, TRuleRhs> trules;
    map<int, int> ruleno_to_truleno;
    map<TRuleRhs, int> rhs_to_ruleno;
};

int get_or_create_trule_for_truleseq_set(Wsp& wsp,
                                         const set<VI>& truleseq_set,
                                         maybe<int> required_trule_no)
{
    assert(!truleseq_set.empty());
    map<int, set<VI>> tterm_and_tails;
    for (const VI& truleseq : truleseq_set) {
        assert(!truleseq.empty());
        auto it = wsp.trules.find(truleseq[0]);
        if (it == wsp.trules.end()) {
            assert(false);
        }
        const TRuleRhs& thead = it->second;
        if (thead.is_terminal()) {
            tterm_and_tails[truleseq[0]].insert(VI{truleseq.begin() + 1, truleseq.end()});
        } else {
            // Split thead into terminal and rest
            for (auto& talts : thead.alts) {
                auto vs = talts.tail;
                vs.insert(vs.end(), truleseq.begin() + 1, truleseq.end());
                tterm_and_tails[talts.terminal_truleno].insert(move(vs));
            }
        }
    }
    TRuleRhs trulerhs;
    for (auto& [tterm, tails] : tterm_and_tails) {
        assert(!tails.empty());
        auto it_empty_tail = tails.find(VI{});
        if (it_empty_tail != tails.end()) {
            trulerhs.alts.PB(TRuleSeq{tterm, {}});
            tails.erase(it_empty_tail);
        }
        if (~tails == 1) {
            trulerhs.alts.PB(TRuleSeq{tterm, *tails.begin()});
        } else if (~tails > 1) {
            trulerhs.alts.PB(
                TRuleSeq{tterm, {get_or_create_trule_for_truleseq_set(wsp, tails, nullopt)}});
        }
    }
    sort(BE(trulerhs.alts));
    {
        auto it = wsp.rhs_to_ruleno.find(trulerhs);
        if (it != wsp.rhs_to_ruleno.end()) {
            return it->second;
        }
    }
    if (wsp.next_rule_no == INT_MAX) {
        int a = 3;
    }
    if (required_trule_no) {
        printf("INSERT required_trule_no %d\n", *required_trule_no);
    }
    int truleno = required_trule_no ? *required_trule_no : wsp.next_rule_no++;
    wsp.trules[truleno] = move(trulerhs);
    wsp.rhs_to_ruleno[trulerhs] = truleno;
    return truleno;
}

constexpr int FOR_RULE_333 = INT_MIN;

int get_or_create_trule_for(const map<int, RuleRhs>& rules, Wsp& wsp, int rule_no)
{
    if (rule_no == 8 || rule_no == 11) {
        printf("BEGIN get_or_create_trule_for %d\n", rule_no);
    }
    if (rule_no == 333) {
        return FOR_RULE_333;
    }
    {
        auto it = wsp.ruleno_to_truleno.find(rule_no);
        if (it != wsp.ruleno_to_truleno.end()) {
            return it->second;
        }
    }
    const RuleRhs& rule_rhs = rules.find(rule_no)->second;

    if (rule_rhs.is_terminal()) {
        int trule_no = wsp.next_rule_no++;
        assert(wsp.trules.count(trule_no) == 0);
        wsp.trules[trule_no] = TRuleRhs{};
        wsp.ruleno_to_truleno[rule_no] = trule_no;
        return trule_no;
    }

    // Not terminal.

    set<VI> truleseq_set;
    assert(!rule_rhs.alts.empty());
    maybe<int> self_trule_no;
    for (const VI& alt : rule_rhs.alts) {
        assert(!alt.empty());
        VI truleseq;
        for (int rn : alt) {
            // assert(rn!=rule_no);
            if (rn == rule_no) {
                if (!self_trule_no) {
                    self_trule_no = wsp.next_rule_no++;
                    printf("%d -> self_trule_no: %d\n", rule_no, *self_trule_no);
                }
                truleseq.PB(*self_trule_no);
            } else {
                truleseq.PB(get_or_create_trule_for(rules, wsp, rn));
            }
        }
        truleseq_set.insert(move(truleseq));
    }
    auto x = get_or_create_trule_for_truleseq_set(wsp, truleseq_set, self_trule_no);
    if (rule_no == 8 || rule_no == 11) {
        printf("END get_or_create_trule_for %d\n", rule_no);
    }
    return x;
}

struct TRuleEnv
{
    map<int, TRuleRhs> trules;
    int start_truleno;
    map<char, int> char_to_truleno;
};

TRuleEnv transform_rules(const map<int, RuleRhs>& rules, const map<char, int>& char_to_ruleno)
{
    Wsp wsp;
    TRuleEnv te;
    te.start_truleno = get_or_create_trule_for(rules, wsp, 0);
    set<int> trules_done;
    VI trules_left{1, te.start_truleno};
    while (!trules_left.empty()) {
        auto truleno = trules_left.back();
        trules_left.pop_back();
        if (trules_done.count(truleno) > 0) {
            continue;
        }
        trules_done.insert(truleno);
        auto& trule = wsp.trules.at(truleno);
        te.trules[truleno] = trule;
        for (auto& alt : trule.alts) {
            if (trules_done.count(alt.terminal_truleno) == 0) {
                trules_left.PB(alt.terminal_truleno);
            }
            for (int x : alt.tail) {
                if (trules_done.count(x) == 0) {
                    trules_left.PB(x);
                }
            }
        }
    }
    for (auto [ch, ruleno] : char_to_ruleno) {
        auto truleno = wsp.ruleno_to_truleno.at(ruleno);
        te.char_to_truleno[ch] = truleno;
    }
    return te;
}

VI resolve_terminals(const map<char, int>& terminals, const string& msg)
{
    VI r;
    for (auto c : msg) {
        auto it = terminals.find(c);
        assert(it != terminals.end());
        r.PB(it->second);
    }
    return r;
}

struct Node
{
    int rule_no;
    VI children;
};

using Tree = unordered_map<int, Node>;

// Return new node id.
int add_child_to_node(Tree& tree, maybe<int> node_id, int child_rule_no)
{
    int new_node_id = ~tree;
    if (node_id) {
        tree.at(node_id.value()).children.PB(new_node_id);
    } else {
        assert(tree.empty());
    }
    tree[new_node_id] = Node{child_rule_no, {}};
    return new_node_id;
}

struct RemAndTree
{
    VI rem;
    Tree tree;
    bool operator<(const RemAndTree& y) const { return rem < y.rem; }
};

set<RemAndTree> try_consuming_with_these_rules(const map<int, RuleRhs>& rules,
                                               const VI& msg,
                                               const Tree& tree,
                                               maybe<int> active_node_id,
                                               const VI& rule_nos);

// Return remainders.
set<RemAndTree> try_consuming_with_this_rule(const map<int, RuleRhs>& rules,
                                             const VI& msg,
                                             const Tree& tree,
                                             maybe<int> active_node_id,
                                             int rule_no)
{
    if (msg.empty()) {
        return {};
    }
    auto& rule = rules.at(rule_no);

    auto next_tree = tree;
    auto next_active_node_id = add_child_to_node(next_tree, active_node_id, rule_no);

    if (rule.is_terminal()) {
        if (msg[0] == rule_no) {
            RemAndTree rat;
            rat.rem = VI{msg.begin() + 1, msg.end()};
            rat.tree = move(next_tree);
            return set<RemAndTree>{{move(rat)}};
        } else {
            return {};
        }
    }
    // Not terminal.
    set<RemAndTree> result;
    for (auto& alt_rule_seq : rule.alts) {
        auto remainders = try_consuming_with_these_rules(rules, msg, next_tree, next_active_node_id,
                                                         alt_rule_seq);
        if (remainders.empty()) {
            continue;
        }
        for (auto& r : remainders) {
            if (r.rem.empty()) {
                return set<RemAndTree>{{move(r)}};
            }
        }
        if (USE_SHORTEST_REMAINDER) {
            // Select shortest remainder.
            for (auto& r : remainders) {
                if (result.empty() || ~r.rem < (int)result.begin()->rem.size()) {
                    result = set<RemAndTree>{{move(r)}};
                }
            }
        } else {
            // Try all of them.
            for (auto& r : remainders) {
                result.insert(move(r));
            }
        }
    }
    return result;
}

// Return remainders.
set<RemAndTree> try_consuming_with_these_rules(const map<int, RuleRhs>& rules,
                                               const VI& msg,
                                               const Tree& tree,
                                               maybe<int> active_node_id,
                                               const VI& rule_nos)
{
    if (rule_nos.empty()) {
        RemAndTree rat;
        rat.rem = msg;
        rat.tree = tree;
        return set<RemAndTree>{move(rat)};
    }
    if (msg.empty()) {
        return {};
    }

    auto remainders = try_consuming_with_this_rule(rules, msg, tree, active_node_id, rule_nos[0]);
    if (remainders.empty()) {
        return {};
    }
    auto rule_nos_tail = VI{rule_nos.begin() + 1, rule_nos.end()};
    if (USE_SHORTEST_REMAINDER) {
        // Select shortest remainder.
        const RemAndTree* shortest = nullptr;
        for (auto& r : remainders) {
            if (!shortest || ~r.rem < (int)shortest->rem.size()) {
                shortest = &r;
            }
        }
        return try_consuming_with_these_rules(rules, shortest->rem, shortest->tree, active_node_id,
                                              rule_nos_tail);
    } else {
        // Try all of them.
        set<RemAndTree> result;
        for (auto& r : remainders) {
            auto remainders_after_r =
                try_consuming_with_these_rules(rules, r.rem, r.tree, active_node_id, rule_nos_tail);
            result.insert(BE(remainders_after_r));
        }
        return result;
    }
}

void print_tree(const Tree& tree, int node_no = 0, int indent = 0)
{
    auto& node = tree.at(node_no);
    if (node.children.empty()) {
        printf("%s%d: T\n", string(indent, '.').c_str(), node.rule_no);
    } else {
        printf("%s%d: [", string(indent, '.').c_str(), node.rule_no);
        for (auto& cnid : node.children) {
            printf("%d ", tree.at(cnid).rule_no);
        }
        printf("]\n");
        for (auto cnid : node.children) {
            print_tree(tree, cnid, indent + 2);
        }
    }
}

VI generate(const map<int, RuleRhs>& rules, const Tree& tree, int node_no)
{
    VI result;
    auto& node = tree.at(node_no);
    int rule_no = node.rule_no;
    auto& rule = rules.at(rule_no);
    if (node.children.empty()) {
        // Terminal.
        assert(rule.is_terminal());
        result.PB(rule_no);
    } else {
        assert(!rule.is_terminal());
        VI child_rules;
        for (auto& child_node_id : node.children) {
            child_rules.PB(tree.at(child_node_id).rule_no);
        }
        bool found = false;
        for (auto& alt : rule.alts) {
            if (alt == child_rules) {
                found = true;
                break;
            }
        }
        assert(found);
        for (auto& child_node_id : node.children) {
            auto s = generate(rules, tree, child_node_id);
            result.insert(result.end(), BE(s));
        }
    }
    return result;
}

bool is_valid(const map<int, RuleRhs>& rules, const VI& msg)
{
    auto rems = try_consuming_with_this_rule(rules, msg, Tree{}, nullopt, 0);
    for (auto& r : rems) {
        if (r.rem.empty()) {
            print_tree(r.tree);
            auto g = generate(rules, r.tree, 0);
            if (msg != g) {
                assert(false);
            }
            return true;
        }
    }
    return false;
}

bool is_valid(const TRuleEnv& te, const VI& msg, const VI& ruleseq)
{
    if (msg.empty() != ruleseq.empty()) {
        return false;
    }
    if (ruleseq.empty()) {
        return true;
    }
    assert(!msg.empty());
    auto headruleno = ruleseq[0];
    auto& headrule = te.trules.at(headruleno);
    auto msg_tail = VI{msg.begin() + 1, msg.end()};
    if (headrule.is_terminal()) {
        if (msg[0] != headruleno) {
            return false;
        }
        return is_valid(te, msg_tail, VI{ruleseq.begin() + 1, ruleseq.end()});
    }
    for (auto& altseq : headrule.alts) {
        if (msg[0] != altseq.terminal_truleno) {
            continue;
        }
        auto new_ruleseq = altseq.tail;
        new_ruleseq.insert(new_ruleseq.end(), ruleseq.begin() + 1, ruleseq.end());
        auto b = is_valid(te, msg_tail, new_ruleseq);
        if (b) {
            return true;
        }
    }
    return false;
}

void do_part(bool part2)
{
    auto fn = part2 ? CMAKE_CURRENT_SOURCE_DIR "/d19_input2.txt"
                    : CMAKE_CURRENT_SOURCE_DIR "/d19_input.txt";
    ifstream f(fn);
    assert(f.good());
    auto lines = read_lines(f);

    int phase = 0;
    map<int, RuleRhs> rules;
    map<char, int> char_to_terminal;
    VS msgs;
    for (auto l : lines) {
        if (phase == 0) {
            if (l.empty()) {
                phase = 1;
                continue;
            }
            auto rule_no = eat_integer<int>(l).value();
            assert(rules.count(rule_no) == 0);
            auto b = eat_string(l, ": ");
            assert(b);
            assert(!l.empty());
            if (l[0] == '"') {
                assert(~l >= 3);
                assert(l[2] == '"');
                auto ch = l[1];
                assert(char_to_terminal.count(ch) == 0);

                rules[rule_no] = RuleRhs{};
                char_to_terminal[ch] = rule_no;
            } else {
                RuleRhs rhs;
                auto vs = split(l, "|");
                for (auto& v : vs) {
                    auto ns = split(v, " ");
                    VI rulenos;
                    for (auto n : ns) {
                        rulenos.PB(atoi(n.c_str()));
                    }
                    rhs.alts.PB(rulenos);
                }
                rules[rule_no] = move(rhs);
            }
        } else {
            assert(!l.empty());
            msgs.PB(l);
        }
    }

    int n_valids = 0;
    if (false) {
        auto te = transform_rules(rules, char_to_terminal);

        for (auto& msg : msgs) {
            auto ts = resolve_terminals(te.char_to_truleno, msg);
            auto b = is_valid(te, ts, {te.start_truleno});
            // printf("%s: %d\n", msg.c_str(), b);
            if (b) {
                ++n_valids;
            }
        }
        printf("P%s: %d\n", part2 ? "2" : "1", n_valids);
    } else {
        for (auto& msg : msgs) {
            auto ts = resolve_terminals(char_to_terminal, msg);
            auto b = is_valid(rules, ts);
            printf("%s: %d\n", msg.c_str(), b);
            if (b) {
                ++n_valids;
            }
        }
        printf("P%s: %d\n", part2 ? "2" : "1", n_valids);
    }
}

int main()
{
    do_part(false);
    do_part(true);
    return 0;
}

// p2: 342 too high
// p2: 19 not good
