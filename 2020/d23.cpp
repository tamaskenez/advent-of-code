#include "common.h"

int digit_to_int(char c)
{
    assert(isdigit(c));
    return c - '0';
}
int dec_and_wrap(int n, int highest)
{
    assert(1 <= n && n <= highest);
    --n;
    return n == 0 ? highest : n;
}
char int_to_digit(int n)
{
    assert(1 <= n && n <= 9);
    return (char)n + '0';
}

string one_step(string cups)
{
    const int highest = ~cups;
    auto pickup = cups.substr(1, 3);
    cups.erase(cups.begin() + 1, cups.begin() + 4);
    int dest = dec_and_wrap(digit_to_int(cups[0]), highest);
    for (;;) {
        if (pickup.find(int_to_digit(dest)) == string::npos) {
            break;
        }
        dest = dec_and_wrap(dest, highest);
    }
    auto a = cups.find(int_to_digit(dest));
    assert(a != string::npos);
    cups.insert(a + 1, pickup);
    std::rotate(cups.begin(), cups.begin() + 1, cups.end());
    return cups;
}

void print(const vector<int>& cups)
{
    int i = 0;
    int R = 40;
    for (; i < ~cups; i += R) {
        int k = min(~cups, i + R);
        printf("%d-%d:", i + 1, k);
        for (int j = i; j < k; ++j) {
            printf(" %d", cups[j]);
        }
        printf("\n");
    }
}

vector<int> one_step(vector<int>&& cups)
{
    const int highest = ~cups;
    array<int, 3> pickup;
    std::copy(cups.begin() + 1, cups.begin() + 4, pickup.begin());
    cups.erase(cups.begin() + 1, cups.begin() + 4);
    int dest = dec_and_wrap(cups[0], highest);
    for (;;) {
        if (find(BE(pickup), dest) == pickup.end()) {
            break;
        }
        dest = dec_and_wrap(dest, highest);
    }
    auto a = find(BE(cups), dest);
    assert(a != cups.end());
    cups.insert(a + 1, BE(pickup));
    std::rotate(cups.begin(), cups.begin() + 1, cups.end());
    return move(cups);
}

// Return new current cup.
int one_step(vector<int>& next_cup_of_cup, int current_cup)
{
    const int highest = ~next_cup_of_cup;
    array<int, 3> pickup;
    pickup[0] = next_cup_of_cup[current_cup];
    pickup[1] = next_cup_of_cup[pickup[0]];
    pickup[2] = next_cup_of_cup[pickup[1]];
    auto next_current_cup = next_cup_of_cup[pickup[2]];
    int dest_cup = dec_and_wrap(current_cup, highest);
    for (;;) {
        if (find(BE(pickup), dest_cup) == pickup.end()) {
            break;
        }
        dest_cup = dec_and_wrap(dest_cup, highest);
    }
    // From this
    // before_current_cup -> current_cup -> p0 -> p1 -> p2 -> next_current -> after_next_current
    // before_dest -> dest -> after_dest

    // To this
    // before_current_cup -> current_cup -> next_current -> after_next_current
    // before_dest -> dest -> p0 -> p1 -> p2 -> after_dest
    next_cup_of_cup[current_cup] = next_current_cup;
    int after_dest_cup = next_cup_of_cup[dest_cup];
    next_cup_of_cup[dest_cup] = pickup[0];
    next_cup_of_cup[pickup[2]] = after_dest_cup;
    return next_current_cup;
}

void P1(const string& input, int steps)
{
    string cups = input;
    FOR (step, 0, < steps) {
        printf("move %d, cups %s\n", step + 1, cups.c_str());
        cups = one_step(cups);
    }
    auto a = cups.find('1');
    rotate(cups.begin(), cups.begin() + a, cups.end());
    printf("final %s\n", cups.c_str());
}

void P2(const vector<int>& input, int steps)
{
    auto cups = input;
    FOR (step, 0, < steps) {
        printf("step %d\n", step + 1);
        print(cups);
        cups = one_step(move(cups));
    }
    auto a = find(BE(cups), 1);
    rotate(cups.begin(), a, cups.end());
    printf("final:\n");
}

void P2b(const vector<int>& input, int steps)
{
    vector<int> next_cup_of_cup(~input, 0);
    for (int i = 0; i < ~input; ++i) {
        auto cup = input[i];
        auto next_cup = input[(i + 1) % ~input];
        next_cup_of_cup[cup] = next_cup;
    }
    int current_cup = input[0];
    FOR (step, 0, < steps) {
        current_cup = one_step(next_cup_of_cup, current_cup);
    }
    int cup = 1;
    auto ca = next_cup_of_cup[1];
    auto cb = next_cup_of_cup[ca];
    printf("%d %d\n", ca, cb);
    printf("product %lld\n", (int64_t)ca * cb);
    /*
    vector<int>output;
    for(;;){
        output.push_back(cup);
        cup = next_cup_of_cup[cup];
        if(cup==1||~output==~input){break;}
    }
    assert(cup==1&&~output==~input);
    printf("final:\n");
    print(output);
    */
}

int main()
{
    // P1("389125467", 100);
    P1("589174263", 100);
    vector<int> input = {5, 8, 9, 1, 7, 4, 2, 6, 3};
    // vector<int> input = {3,8,9,1,2,5,4,6,7};
    int N = 1000000;
    for (int i = *max_element(BE(input)) + 1; i <= N; ++i) {
        input.PB(i);
    }
    P2b(input, 10000000);
    return 0;
}

// 24:51
