#include "common.h"

struct AboutIng
{};
struct AboutAller
{
    set<string> ings;
};
struct AS
{
    string aller;
    vector<string> ings;
};
using ASS = vector<AS>;
struct State
{
    ASS const* ass;
    vector<string> ingOfAller;
    set<string> remainingIngs;
};

struct Sentence
{
    set<string> ings;
    set<string> allers;
};

vector<Sentence> sentences;

struct DNAResult
{
    set<string> allerFreeIngs;
    vector<string> finalIngs;
};

maybe<DNAResult> decideNextAller(const State& s)
{
    if (s.ingOfAller.size() == s.ass->size()) {
        printf("Found\n");
        DNAResult r;
        r.allerFreeIngs = s.remainingIngs;
        int n_allers = s.ass->size();
        assert(n_allers == ~s.ingOfAller);
        map<string, string> sts;
        FOR (ix, 0, < n_allers) {
            auto allerName = s.ass->at(ix).aller;
            auto ingName = s.ingOfAller[ix];
            sts[allerName] = ingName;
        }
        for (auto& [k, v] : sts) {
            r.finalIngs.PB(v);
        }
        return r;
    }
    int allerIdx = s.ingOfAller.size();
    auto& aller = s.ass->at(allerIdx);
    for (int ingIdx = 0; ingIdx < ~aller.ings; ++ingIdx) {
        auto& ingName = aller.ings[ingIdx];
        if (s.remainingIngs.count(ingName) == 0) {
            continue;
        }

        // Check sentences.
        bool ok = true;
        for (auto& s : sentences) {
            if (s.allers.count(aller.aller) > 0) {
                if (s.ings.count(ingName) == 0) {
                    // Aller is printed but corresponding ing is not.
                    ok = false;
                    break;
                } else {
                }
            }
            if (!ok) {
                break;
            }
        }
        if (!ok) {
            continue;
        }

        auto ns = s;
        ns.ingOfAller.push_back(ingName);
        ns.remainingIngs.erase(ingName);
        auto r = decideNextAller(ns);
        if (r) {
            return r;
        }
    }
    return nullopt;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d21_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<string, AboutIng> allIngs;
    map<string, AboutAller> allAllers;
    for (auto l : lines) {
        l = trim(l);
        if (l.empty()) {
            continue;
        }
        auto p0 = l.find('(');
        auto p1 = l.find(')');
        assert(p0 != string::npos && p1 != string::npos);
        auto ings = l.substr(0, p0);
        auto allers = l.substr(p0 + 1, p1 - p0 - 1);
        assert(starts_with(allers, "contains "));
        allers = allers.substr(9);
        auto ings_ = split(ings, " ");
        auto allers_ = split(allers, ", ");
        for (auto i : ings_) {
            allIngs[i];
        }
        for (auto a : allers_) {
            allAllers[a];
        }
        for (auto i : ings_) {
            for (auto a : allers_) {
                allAllers[a].ings.insert(i);
            }
        }
        Sentence s;
        s.ings.insert(BE(ings_));
        s.allers.insert(BE(allers_));
        sentences.push_back(move(s));
    }
    vector<pair<int, string>> ingCountForAller;
    for (auto& [k, v] : allAllers) {
        ingCountForAller.push_back(MKP((int)v.ings.size(), k));
    }
    sort(BE(ingCountForAller));

    int n_allers = ~ingCountForAller;
    ASS ass;
    for (auto& ic : ingCountForAller) {
        auto aller = ic.second;
        auto& ings = allAllers[aller].ings;
        ass.push_back(AS{aller, vector<string>(BE(ings))});
    }

    State state;
    state.ass = &ass;
    for (auto& [k, v] : allIngs) {
        state.remainingIngs.insert(k);
    }

    if (auto result = decideNextAller(state)) {
        auto& r = *result;
        int counter = 0;
        for (auto& s : sentences) {
            for (auto& ing : r.allerFreeIngs) {
                if (s.ings.count(ing) > 0) {
                    ++counter;
                }
            }
        }
        printf("Counter: %d\n", counter);
        string rs;
        for (auto& s : r.finalIngs) {
            rs += ",";
            rs += s;
        }
        printf("final ings: %s\n", rs.c_str());
    } else {
        printf("Not found\n");
        return EXIT_FAILURE;
    }
    return 0;
}

// P1: 1.09:28
