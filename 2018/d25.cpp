#include "common.h"

using AI4 = array<int, 4>;

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d25_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<AI4> ss;
    for (auto& l : lines) {
        auto vs = map_to_vec(split(l, ", \t"), CALL(stoi));
        AI4 v;
        FOR (i, 0, < 4) {
            v[i] = vs[i];
        }
        ss.PB(v);
    }

    map<AI4, set<AI4>> M;
    FOR (i, 0, < ~ss - 1) {
        FOR (j, i + 1, < ~ss) {
            if (manhattan(ss[i], ss[j]) <= 3) {
                M[ss[i]].insert(ss[j]);
                M[ss[j]].insert(ss[i]);
            }
        }
    }
    set<AI4> done;
    vector<set<AI4>> groups;
    for (auto ga : ss) {
        if (contains(done, ga)) {
            continue;
        }
        set<AI4> group;
        group.insert(ga);

        vector<AI4> worklist, new_worklist;
        worklist.PB(ga);
        for (; !worklist.empty();) {
            new_worklist.clear();
            for (auto w : worklist) {
                for (auto nb : M[w]) {
                    if (!contains(done, nb)) {
                        new_worklist.PB(nb);
                        done.insert(nb);
                        group.insert(nb);
                    }
                }
            }
            new_worklist.swap(worklist);
        }
        groups.emplace_back(move(group));
    }

    printf("%d groups\n", ~groups);

    return 0;
}
