#include "common.h"

bool is_real(const string& ls, const string& checksum)
{
    map<char, int> stat;
    for (auto c : ls) {
        ++stat[c];
    }
    vector<pair<int, char>> stat2;
    for (auto& kv : stat) {
        stat2.PB(make_pair(-kv.second, kv.first));
    }
    sort(BE(stat2));
    string ss;
    for (auto& pp : stat2) {
        ss += pp.second;
    }
    return starts_with(ss, checksum);
}

string myrotate(string s, int sectorid)
{
    for (auto& c : s) {
        if (c == '-') {
            c = ' ';
        } else {
            c = ((int)(c - 'a') + sectorid) % (int)(1 + 'z' - 'a') + 'a';
        }
    }
    return s;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d04_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int total = 0;
    for (auto& l : lines) {
        auto vs = split(l, "-[]");
        auto N = ~vs;
        auto checksum = vs[N - 1];
        auto sectorid = stoi(vs[N - 2]);
        string s;
        FOR (i, 0, < N - 2) {
            s += vs[i];
        }
        if (is_real(s, checksum)) {
            total += sectorid;
            auto en = myrotate(s, sectorid);
            // printf("%s\n", en.c_str());
            if (en == "northpoleobjectstorage") {
                printf("npo %d\n", sectorid);
            }
        }
    }
    printf("%d\n", total);
    auto s = myrotate("qzmt-zixmtkozy-ivhz", 343);
    return 0;
}
// 9 21