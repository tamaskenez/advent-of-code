#include "common.h"

const string INPUT = "11110010111001001";

string do_one_step(const string& a)
{
    auto b = a;
    reverse(BE(b));
    for (auto& c : b) {
        if (c == '0') {
            c = '1';
        } else {
            assert(c == '1');
            c = '0';
        }
    }
    return a + "0" + b;
}

string checksum(const string& s)
{
    auto N = ~s;
    if (N & 1) {
        return s;
    }
    string b;
    for (int i = 0; i < ~s; i += 2) {
        if (s[i] == s[i + 1]) {
            b += '1';
        } else {
            b += '0';
        }
    }
    return checksum(b);
}

int main()
{
    //const int NN = 272;
    const int NN = 35651584;
    string a = INPUT;
    while (~a < NN) {
        a = do_one_step(a);
    }
    a=a.substr(0,NN);
    auto r = checksum(a);
    printf("%s\n", r.c_str());
    return 0;
}
