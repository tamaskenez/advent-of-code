#include "common.h"

int react(string line)
{
    for (;;) {
        printf("~line: %d\n", ~line);
        bool changed = false;
        auto N = ~line;
        string nl;
        for (auto c : line) {
            if (nl.empty()) {
                nl += c;
                continue;
            }
            if (c != nl.back() && tolower(c) == tolower(nl.back())) {
                nl.pop_back();
                changed = true;
                continue;
            }
            nl += c;
        }
        if (!changed) {
            break;
        }
        line = move(nl);
    }
    return ~line;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d05_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    assert(~lines == 1);
    auto& line = lines[0];
    // line ="dabAcCaCBAcCcaDA";
    int c0 = react(line);
    printf("%d\n", c0);

    RunningStat<int> rs;
    for(char cc = 'a'; cc <= 'z'; ++cc){
        string nl;
        for(auto &c:line){
            if(tolower(c)!=cc){
                nl += c;
            }
        }
        auto c1 = react(nl);
        rs.add(c1);
    }
    printf("%d\n", *rs.lower);
    return 0;
}
