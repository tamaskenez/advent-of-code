#include "common.h"

maybe<int64_t> eat_and_eval_valid_op_seq(string& s);

maybe<int64_t> eat_and_eval_single_term(string& s)
{
    eat_wspace(s);
    if (eat_char(s, '(')) {
        auto r = eat_and_eval_valid_op_seq(s);
        assert(r);
        auto b = eat_char(s, ')');
        assert(b);
        return *r;
    }
    assert(!s.empty() && isdigit(s[0]));
    if (auto r = eat_integer<int>(s)) {
        return *r;
    }
    assert(false);
    return nullopt;
}

maybe<int64_t> eat_and_eval_valid_op_seq(string& s)
{
    eat_wspace(s);
    if (s.empty()) {
        return nullopt;
    }
    auto result = eat_and_eval_single_term(s);
    assert(result);
    for (;;) {
        eat_wspace(s);
        if (eat_char(s, '+')) {
            auto t = eat_and_eval_single_term(s);
            assert(t);
            *result += *t;
        } else if (eat_char(s, '*')) {
            auto t = eat_and_eval_single_term(s);
            assert(t);
            *result *= *t;
        } else {
            return *result;
        }
    }
}

int64_t eval(string s)
{
    auto r = eat_and_eval_valid_op_seq(s);
    s = trim(s);
    assert(s.empty() && r);
    return *r;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d18_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    int64_t sum = 0;
    for (auto& l : lines) {
        auto r = eval(l);
        sum += r;
    }
    printf("P1: %lld\n", sum);
    return 0;
}

// not 10684594594 too low
