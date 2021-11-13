#include "common.h"

vector<int> input = {0,14,1,3,7,9};
struct N
{
    int last_turn;
    maybe<int> second_last_turn;
};

int main()
{
    unordered_map<int, N> M;
    maybe<int> most_recent;
    FOR (turn, 1, <= 30000000) {
        int idx = turn - 1;
        int number_to_say;
        if (~input > idx) {
            number_to_say = input[idx];
        } else {
            auto& m = M.at(most_recent.value());
            if (m.second_last_turn) {
                number_to_say = m.last_turn - *m.second_last_turn;
            } else {
                number_to_say = 0;
            }
        }

        most_recent = number_to_say;
        auto it = M.find(number_to_say);
        if(it==M.end()){
          M[number_to_say] = N{turn, nullopt};
        } else {
          auto&m=it->second;
            m.second_last_turn = m.last_turn;
            m.last_turn=turn;
        }
    }
    printf("p1: %d\n", most_recent.value());
    return 0;
}

//31.48
