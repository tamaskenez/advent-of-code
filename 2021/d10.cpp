#include "common.h"

char get_open_char(char c)
{
    switch (c) {
        case ']':
            return '[';
        case ')':
            return '(';
        case '>':
            return '<';
        case '}':
            return '{';
    }
    assert(false);
    return 0;
}

int score_for_char(char c)
{
    switch (c) {
        case ']':
            return 57;
        case ')':
            return 3;
        case '>':
            return 25137;
        case '}':
            return 1197;
    }
    assert(false);
    return 0;
}

int64_t p1_score_for_line(const string& s)
{
    vector<char> stack;
    for (char c : s) {
        if (c ELEM_OF{'[', '(', '{', '<'}) {
            stack.PB(c);
            continue;
        }
        auto cc = get_open_char(c);
        assert(!stack.empty());
        if (cc == stack.back()) {
            stack.pop_back();
            continue;
        }
        return score_for_char(c);
    }
    return 0;
}

int64_t p2_score_for_line(const string& s)
{
    vector<char> stack;
    for (char c : s) {
        if (c ELEM_OF{'[', '(', '{', '<'}) {
            stack.PB(c);
            continue;
        }
        auto cc = get_open_char(c);
        assert(!stack.empty());
        if (cc == stack.back()) {
            stack.pop_back();
            continue;
        }
        return 0;
    }
    reverse(BE(stack));
    int64_t score=0;
    for(auto c:stack){
        score*=5;
        switch(c){
        case '(':score+=1;break;
        case '[':score+=2;break;
        case '{':score+=3;break;
        case '<':score+=4;break;
        default:assert(false);break;
        }
    }
    return score;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d10_input.txt");
    assert(f.good());
    auto lines = read_lines(f);

    int64_t p1_score = 0;
    for (auto l : lines) {
        p1_score += p1_score_for_line(l);
    }
    printf("p1: %lld\n", p1_score);

    vector<int64_t> vs;
    for (auto l : lines) {
        auto s=p2_score_for_line(l);
        if(s!=0){
            vs.PB(s);
        }
    }
    auto it =vs.begin()+vs.size()/2;
std::nth_element(vs.begin(), it,vs.end());
    printf("p2: %lld\n", *it);
    return 0;
}
//9 4
//15 42


