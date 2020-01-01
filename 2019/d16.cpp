#include "common.h"

const string main_input =
    "5975053022132419485301232006958931202752398985483023214416479922802916283047747207808979074990"
    "6142587998642764059439173975199276254972017316624772614925079238407309384923979338502430726930"
    "5929599918786984125379716725588325885406009634374092305508975444346352671726031323967228123343"
    "6652834471591275615400603951227249107390638921892742038715159904443506007514814294678900775680"
    "0733869891008058075303490106699737554949348715600795187032293436328810969288892220127730287766"
    "0044677308184892692959825262974309714118650280987085557095256462377130452596031753976236549507"
    "19275982134690893685598734136409536436003548128411943963263336042840301380655801969822";
// const string signal0 = "12345678";

const array<int64_t, 4> PATTERN = {0, 1, 0, -1};

struct Modulator
{
    int digit_ix;
    int counter;
    int pattern_idx = 0;
    Modulator(int64_t digit_ix) : digit_ix(digit_ix), counter(digit_ix - 1)
    {
        assert(digit_ix >= 1);
    }
    int64_t next()
    {
        --counter;
        if (counter < 0) {
            counter = digit_ix - 1;
            pattern_idx = (pattern_idx + 1) % 4;
        }
        return PATTERN[pattern_idx];
    }
};

string phase(string input)
{
    string output(~input, ' ');
    printf("%s\n", input.c_str());
    FOR (i0, 0, < ~input) {
        Modulator m(i0 + 1);
        int64_t sum = 0;
        FOR (i, 0, < ~input) {
            auto mn = m.next();
            if (mn != 0) {
                auto d = (int)(input[i] - '0');
                sum += d * mn;
                if (i0 == 1) {
                    printf("%d * %d => %d\n", d, (int)mn, (int)sum);
                }
            }
        }
        sum = abs(sum);
        auto digit = (char)((int)(sum % 10) + '0');
        output[i0] = digit;
    }
    return output;
}

struct IV
{
    int factor;  //-1 or 1
    int b, e;
    IV(int factor, int b, int e) : factor(factor), b(b), e(e) {}
};

vector<IV> intervals_for_digit(int i, int len)
{
    vector<IV> ivs;
    int qperiod = i + 1;
    int period = qperiod * 4;
    int k = (i + 1) / period;
    for (auto ix = -1 + k * period;;) {
        ix += qperiod;  // zeros
        if (ix >= len) {
            break;
        }
        int e = min(len, ix + i + 1);
        ivs.emplace_back(1, ix, e);
        if (e == len) {
            break;
        }
        ix += qperiod;
        ix += qperiod;  // zeros
        if (ix >= len) {
            break;
        }
        e = min(len, ix + i + 1);
        ivs.emplace_back(-1, ix, e);
        ix += qperiod;
    }
    return ivs;
}

int64_t summer(const string& s, const IV& iv)
{
    int64_t sum = 0;
    FOR (i, iv.b, < iv.e) {
        sum += (int64_t)(s[i] - '0');
    }
    return sum;
}

int64_t summer(const string& s)
{
    int64_t sum = 0;
    for (auto c : s) {
        sum += (int64_t)(c - '0');
    }
    return sum;
}

string calc_digits(const string& input, int phase, int b, int e);

/*
int64_t calc_digits_and_sum(const string& input, int phase, int b, int e)
{
    if (phase == 0) {
        int bb = ((b + ~input - 1) / ~input) * ~input;
        int ee = (e / ~input) * ~input;
    } else {
        return summer(calc_digits(input, phase, b, e));
    }
}
*/

/*
string calc_digits(const string& input, int phase, int b, int e)
{
    if (phase < 3) {
        printf("calc digits %d %d %d\n", phase, b, e);
    }
    if (phase == 0) {
        return "";  // input10k.substr(b, e - b);
    }
    string digits;
    FOR (i, b, < e) {
        auto ivs = intervals_for_digit(i, ~input * 10000);
        int64_t sum = 0;
        for (auto& iv : ivs) {
            sum += calc_digits_and_sum(input, phase - 1, iv.b, iv.e) * iv.factor;
        }
        digits += (char)((abs(sum) % 10) + '0');
    }
    return digits;
}
*/
string solve1(string input, int n_phases)
{
    FOR (i, 0, < n_phases) {
        input = phase(input);
    }
    return input.substr(0, 8);
}

struct Input
{
    int F;
    string input;
    VI sums;
    Input(int F, string arg_input) : F(F), input(move(arg_input))
    {
        sums.resize(~input);
        int64_t sum = 0;
        FOR (i, 0, < ~input) {
            sum = (sum + (input[i] - '0'));
            sums[i] = sum;
        }
    }
    int sum_until(int e) const
    {
        assert(0 <= e && e <= ~input);
        if (e == 0) {
            return 0;
        }
        return sums[e - 1];
    }
    int64_t sum_until_F(int e) const
    {
        assert(0 <= e && e <= F * ~input);
        if (e == 0) {
            return 0;
        }
        int k = e / ~input;
        int full_e = k * ~input;
        int part_e = e - full_e;
        return k * sums.back() + sum_until(part_e);
    }
    int64_t sum_between_F(int b, int e) const
    {
        assert(0 <= b && b < e && e <= F * ~input);
        auto se = sum_until_F(e);
        auto sb = sum_until_F(b);
        return se - sb;
    }
};

int sum(const string& s, int b, int e)
{
    int ss = 0;
    FOR (i, b, < e) {
        ss += int(s[i] - '0');
    }
    return ss;
}

Input phase(const Input& input)
{
    const int L = ~input.input * input.F;
    string output(L, ' ');
    FOR (i, 0, < L) {
        auto ivs = intervals_for_digit(i, L);
        int64_t sum = 0;
        for (auto iv : ivs) {
            auto s1 = input.sum_between_F(iv.b, iv.e);
            sum += s1 * iv.factor;
        }
        sum = abs(sum);
        auto digit = (char)((int)(sum % 10) + '0');
        output[i] = digit;
    }
    return Input(1, move(output));
}

string solve_core(Input input, int offset, int n_phases)
{
    FOR (ph, 1, <= n_phases) {
        printf("%d\n", ph);
        input = phase(input);
    }
    assert(input.F == 1);
    return input.input.substr(offset, 8);
}

string solve1(const Input input, int n_phases)
{
    return solve_core(move(input), 0, n_phases);
}

string solve2(const Input input, int n_phases)
{
    int64_t offset = std::stoi(input.input.substr(0, 7));
    return solve_core(move(input), offset, n_phases);
}

int main()
{
    // printf("Part1: %s\n", solve1(main_input).c_str());

    // auto r = solve1b(signal0);
    const string input1 = "03036732577212944063491565474664";
    // const string input1 = "19617804207202209144916044189917";
    // const string input1 = "12345678";
    {
        Input in(10000, main_input);
        int n = 100;
        auto t1 = solve2(in, n);
        printf("%s\n", t1.c_str());
        int a = 3;
    }
    //    const string signal1 = "03036732577212944063491565474664";
    //    printf("Part2: %s\n", solve2(signal1).c_str());

    return 0;
}
