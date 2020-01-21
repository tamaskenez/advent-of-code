#include "common.h"
#include "md5.h"

//-------------
std::string md5(const std::string str, bool part2)
{
    MD5 md5 = MD5(str);
    auto s = md5.hexdigest();
    if (!part2) {
        return s;
    }
    FOR (i, 0, < 2016) {
        s = MD5(s).hexdigest();
    }
    return s;
}

const string INPUT = "ihaygndm";
// const string INPUT = "abc";

int main()
{
    for (auto part2 : {false, true}) {
        vector<pair<int, string>> keys;
        deque<pair<char, int>> d_l1k;
        map<char, int> m_l1k;
        for (int hash_ix = 0; ~keys < 64 || hash_ix < keys[63].FST + 1001; ++hash_ix) {
            auto hash = md5(INPUT + to_string(hash_ix), part2);
            char triplet_char = 0;
            FOR (i, 0, <= ~hash - 3) {
                auto c = hash[i];
                if (hash[i + 1] == c && hash[i + 2] == c) {
                    triplet_char = c;
                    break;
                }
            }
            FOR (d, '0', <= 'f') {
                if (m_l1k[d] == 0) {
                    continue;
                }
                auto ss = string(5, d);
                if (hash.find(ss) != string::npos) {
                    for (auto di : d_l1k) {
                        if (di.FST == d) {
                            keys.EB(make_pair(di.SND, md5(INPUT + to_string(di.SND), part2)));
                            sort(BE(keys));
                        }
                    }
                }
            }
            if (triplet_char) {
                d_l1k.EB(triplet_char, hash_ix);
                ++m_l1k[triplet_char];
            }
            while (!d_l1k.empty() && d_l1k[0].SND <= hash_ix - 1000) {
                auto dp = d_l1k[0];
                d_l1k.pop_front();
                --m_l1k[dp.FST];
                assert(m_l1k[dp.FST] >= 0);
            }
        }

        printf("-------- %s\n", part2 ? "PART2" : "PART1");
        FOR (i, 0, < ~keys) {
            printf("key#%d hash#%d %s\n", i, keys[i].FST, keys[i].SND.c_str());
        }
    }
    return 0;
}
// 15252 high

// p2 20346 high