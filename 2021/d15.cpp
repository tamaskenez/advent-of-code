#include "common.h"

int W = -1;
VS m;
vector<vector<int>> risks;

bool deal(int r, int c)
{
    optional<int> minrisk;
    if (r > 0) {
        minrisk = risks[r - 1][c];
    }
    if (c > 0) {
        minrisk = std::min(minrisk.value_or(INT_MAX), risks[r][c - 1]);
    }
    if (c < W - 1) {
        minrisk = std::min(minrisk.value_or(INT_MAX), risks[r][c + 1]);
    }
    if (r < W - 1) {
        minrisk = std::min(minrisk.value_or(INT_MAX), risks[r + 1][c]);
    }
    assert(minrisk && *minrisk != INT_MAX);
    int new_risk = *minrisk + (m[r][c] - '0');
    if (new_risk != risks[r][c]) {
        risks[r][c] = new_risk;
        return true;
    }
    return false;
}

int m5(int r, int c)
{
    int rmod = r % W;
    int cmod = c % W;
    int rd = r / W;
    int cd = c / W;
    const char* cc = "01234567891234567891........";
    auto ch = int(m[rmod][cmod] - '0');
    auto dh = cc[ch + rd + cd];
    assert(isdigit(dh));
    return int(dh - '0');
}

bool deal2(int r, int c)
{
    optional<int> minrisk;
    if (r > 0) {
        minrisk = risks[r - 1][c];
    }
    if (c > 0) {
        minrisk = std::min(minrisk.value_or(INT_MAX), risks[r][c - 1]);
    }
    if (c < W - 1) {
        minrisk = std::min(minrisk.value_or(INT_MAX), risks[r][c + 1]);
    }
    if (r < W - 1) {
        minrisk = std::min(minrisk.value_or(INT_MAX), risks[r + 1][c]);
    }
    assert(minrisk && *minrisk != INT_MAX);
    int new_risk = *minrisk + m5(r, c);
    if (new_risk != risks[r][c]) {
        risks[r][c] = new_risk;
        return true;
    }
    return false;
}

void P2(const VS& lines)
{
    W = ~(lines[0]);
    int H = ~lines;
    assert(W == H);
    m = lines;
    risks = vector<VI>(5 * W, VI(5 * W, INT_MAX));
    risks[0][0] = 0;
    bool changed = true;
    for (int step = 1; changed; ++step) {
        printf("Step: %d\n", step);
        changed = false;
        FOR (i, 1, < 5 * W) {
            FOR (j, 0, < i) {
                changed = deal2(i, j) || changed;
                changed = deal2(j, i) || changed;
            }
            changed = deal2(i, i) || changed;
        }
    }
    int p1 = risks[5 * W - 1][5 * W - 1];
    printf("P2: %d\n", p1);
}

void P1(const VS& lines)
{
    W = ~(lines[0]);
    int H = ~lines;
    assert(W == H);
    m = lines;
    risks = vector<VI>(W, VI(W, INT_MAX));
    risks[0][0] = 0;
    bool changed = true;
    for (int step = 1; changed; ++step) {
        printf("Step: %d\n", step);
        changed = false;
        FOR (i, 1, < W) {
            FOR (j, 0, < i) {
                changed = deal(i, j) || changed;
                changed = deal(j, i) || changed;
            }
            changed = deal(i, i) || changed;
        }
    }
    int p1 = risks[W - 1][W - 1];
    printf("P1: %d\n", p1);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d15_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    P1(lines);
    P2(lines);
    return 0;
}

// 396 high
// 22
