#include "common.h"
#include "md5.h"

// const string INPUT = "abc";

unordered_map<int, string> hash_cache;

string make_hash(int i, bool part2)
{
    auto it = hash_cache.find(i);
    if(it!=hash_cache.end()){
        return it->second;
    }
    const string INPUT = "ihaygndm";
    auto hash = md5(INPUT + to_string(i));
    if(part2){
        FOR(i,0,<2016){
            hash=md5(hash);
        }
    }
    hash_cache[i]=hash;
    return hash;
}

char try_get_triplet(const string& s)
{
    FOR (i, 0, <= ~s - 3) {
        auto c = s[i];
        if (s[i + 1] == c && s[i + 2] == c) {
            return c;
        }
    }
    return 0;
}

int main()
{
    VS keys;
    bool part2 = true;
    for (int hash_ix = 0; ~keys < 64; ++hash_ix) {
        auto hash = make_hash(hash_ix, part2);
        auto tc = try_get_triplet(hash);
        if (tc == 0) {
            continue;
        }
        string quintlet = string(5, tc);
        FOR (hash_jx, hash_ix + 1, <= hash_ix + 1000) {
            auto hash5 = make_hash(hash_jx, part2);
            if (hash5.find(quintlet) != string::npos) {
                keys.PB(hash);
                printf("key#%d, hash_ix: %d\n", ~keys, hash_ix);
            }
        }
    }
    return 0;
}