#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d2_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int total = 0;
    int ribbon = 0;
    for (auto& l : lines) {
        auto p1 = l.find('x');
        auto p2 = l.find('x', p1 + 1);
        auto s1 = l.substr(0, p1);
        auto s2 = l.substr(p1 + 1, p2 - p1 - 1);
        auto s3 = l.substr(p2 + 1);
        auto L = stoi(s1);
        auto W = stoi(s2);
        auto H = stoi(s3);
        auto A1 = L * W;
        auto A2 = W * H;
        auto A3 = L * H;
        auto AAA = 2 * (A1 + A2 + A3) + min(min(A1, A2), A3);
        total += AAA;
        vector<int> v = {L, W, H};
        sort(BE(v));
        auto r1 = v[0] * 2 + v[1] * 2;
        auto r2 = L * W * H;
        ribbon += r1 + r2;
    }
    printf("part1 %d\n", total);
    return 0;
}
