#include <fstream>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "common.h"

VS read_input_file(const char* fn)
{
    VS lines;
    string sfn = CMAKE_CURRENT_SOURCE_DIR;
    sfn += "/";
    sfn += fn;
    ifstream f(sfn);
    while (f.good()) {
        string line;
        getline(f, line);
        while (!line.empty() && isspace(line.back())) {
            line.pop_back();
        }
        while (!line.empty() && isspace(line.front())) {
            line.erase(line.begin());
        }
        if (line.empty()) {
            continue;
        }
        lines.push_back(move(line));
    }
    return lines;
}

using k_orbits_v = unordered_map<string, VS>;
k_orbits_v parse_lines(const VS& lines)
{
    k_orbits_v m;
    for (auto l : lines) {
        auto p = l.find(')');
        assert(p != string::npos);
        string k = l.substr(0, p);
        string v = l.substr(p + 1);
        m[k].push_back(v);
    }
    return m;
}

int solve(const k_orbits_v& m)
{
    VS workset;
    unordered_map<string, int> orbits_count;
    workset.push_back("COM");
    while (!workset.empty()) {
        auto b = workset.back();
        int c = orbits_count[b];
        workset.pop_back();
        auto it = m.find(b);
        if (it == m.end()) {
            continue;
        }
        auto& vs = it->second;
        for (auto& v : vs) {
            workset.push_back(v);
            assert(orbits_count.find(v) == orbits_count.end());
            orbits_count[v] = c + 1;
        }
    }
    int s = 0;
    for (auto& kv : orbits_count) {
        s += kv.second;
    }
    return s;
}

int solveb(const k_orbits_v& m)
{
    unordered_map<string, VS> orbit;
    unordered_set<string> traversed;
    for (auto& kv : m) {
        for (auto v : kv.second) {
            orbit[kv.first].push_back(v);
            orbit[v].push_back(kv.first);
        }
    }
    vector<string> from;
    vector<string> to;
    from.push_back("YOU");
    traversed.insert("YOU");
    for (int distance = 1;; ++distance) {
        to.clear();
        for (auto& f : from) {
            for (auto& g : orbit[f]) {
                if (g == "SAN") {
                    return distance - 2;
                }
                if (traversed.count(g) > 0) {
                    continue;
                }
                to.push_back(g);
                traversed.insert(g);
            }
        }
        from.swap(to);
    }
}

int main()
{
    auto lines = read_input_file("d6_input.txt");
    auto m = parse_lines(lines);
    auto c = solve(m);
    printf("%d\n", c);

    auto c2 = solveb(m);
    printf("%d\n", c2);
}