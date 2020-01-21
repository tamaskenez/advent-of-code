#include "common.h"
#include "md5.h"

// UDLR

array<bool, 4> get_open_doors(const string& path)
{
    const string INPUT = "ioramepc";
    auto hash = md5(INPUT + path);
    array<bool, 4> r;
    r.fill(false);
    FOR (i, 0, < 4) {
        auto c = hash[i];
        if (is_between_cc(c, 'b', 'f')) {
            r[i] = true;  // open
        } else {
            assert_between_cc(c, '0', 'a');
        }
    }
    return r;
}

struct State
{
    string path;
    AI2 loc;
};
// UDLR

const auto VAULT = AI2{3, 3};
const array<AI2, 4> DIRS = {AI2{-1, 0}, AI2{1, 0}, AI2{0, -1}, AI2{0, 1}};
const string DIR_CHARS = "UDLR";

int main()
{
    vector<State> front, next_front;
    bool done = false;
    front.PB(State{"",AI2{0,0}});
    for (; !done && !front.empty();) {
        next_front.clear();
        for (const auto& st : front) {
            if (st.loc == VAULT) {
                printf("~path %d path %s\n", ~st.path, st.path.c_str());
                //done = true;
                //break;
                continue;
            }
            auto ods = get_open_doors(st.path);
            FOR (i, 0, < 4) {
                if (!ods[i]) {
                    continue;
                }
                auto loc = st.loc + DIRS[i];
                if (is_between_co(loc[0], 0, 4) && is_between_co(loc[1], 0, 4)) {
                    next_front.PB(State{st.path + DIR_CHARS[i], loc});
                }
            }
        }
        next_front.swap(front);
    }
    printf("exit\n");
}

// second part was 1:52, first part failed to measure
