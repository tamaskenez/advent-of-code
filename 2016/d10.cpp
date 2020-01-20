#include "common.h"

struct Desig
{
    bool output;
    int idx;
};

struct Bot
{
    VI values;
    optional<Desig> low_to, hi_to;
    bool add_value(int v)
    {
        assert(~values < 2);
        values.PB(v);
        return ~values == 2;
    }
};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d10_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    map<int, Bot> bots;
    set<int> bots_with_2;
    for (auto& l : lines) {
        auto vs = split(l, " ");
        if (vs[0] == "value") {
            assert(~vs == 6);
            auto value = stoi(vs[1]);
            assert(vs[4] == "bot");
            auto to_bot_ix = stoi(vs[5]);
            auto& bot = bots[to_bot_ix];
            bot.values.PB(value);
            assert(~bot.values <= 2);
            if (~bot.values == 2) {
                bots_with_2.insert(to_bot_ix);
            }
        } else if (vs[0] == "bot") {
            //  0   1  2      3  4   5  6  7   8    9  10  11
            // bot 125 gives low to bot 58 and high to bot 57
            auto bot_ix = stoi(vs[1]);
            assert(vs[5] == "output" || vs[5] == "bot");
            auto low_output = vs[5] == "output";
            auto low_ix = stoi(vs[6]);
            assert(vs[10] == "output" || vs[10] == "bot");
            auto hi_output = vs[10] == "output";
            auto hi_ix = stoi(vs[11]);
            bots[bot_ix].low_to = Desig{low_output, low_ix};
            bots[bot_ix].hi_to = Desig{hi_output, hi_ix};
        } else {
            UNREACHABLE;
        }
    }
    map<int, VI> outputs;
    while (!bots_with_2.empty()) {
        int bot_ix = *bots_with_2.begin();
        bots_with_2.erase(bot_ix);
        auto& bot = bots[bot_ix];
        assert(bot.low_to && bot.hi_to);
        auto& lo = *bot.low_to;
        auto& hi = *bot.hi_to;
        sort(BE(bot.values));
        if (bot.values[0] == 17 && bot.values[1] == 61) {
            printf("part1 %d\n", bot_ix);
            //            break;
        }
        if (!lo.output) {
            if (bots[lo.idx].add_value(bot.values[0])) {
                bots_with_2.insert(lo.idx);
            }
        } else {
            outputs[lo.idx].PB(bot.values[0]);
        }
        if (!hi.output) {
            if (bots[hi.idx].add_value(bot.values[1])) {
                bots_with_2.insert(hi.idx);
            }
        } else {
            outputs[hi.idx].PB(bot.values[1]);
        }
    }
    for (auto& kv : outputs) {
        printf("-- output: %d", kv.FST);
        for (auto v : kv.SND) {
            printf(" %d", v);
        }
        printf("\n");
    }
    return 0;
}
