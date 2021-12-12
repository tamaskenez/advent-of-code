#include "common.h"

using Table = array<array<int, 5>, 5>;

vector<int> get_draws(string l)
{
    vector<int> draws;
    l = trim(l);
    auto ss = split(l, ",");
    for (auto& s : ss) {
        draws.PB(stoi(s));
    }
    return draws;
}

void cross_table(Table& table, int d)
{
    FOR (r, 0, < 5) {
        FOR (c, 0, < 5) {
            if (table[r][c] == d) {
                table[r][c] = -1;
            }
        }
    }
}

bool did_win_row(const Table& table, int r)
{
    FOR (c, 0, < 5) {
        if (table[r][c] >= 0) {
            return false;
        }
    }
    return true;
}

bool did_win_column(const Table& table, int c)
{
    FOR (r, 0, < 5) {
        if (table[r][c] >= 0) {
            return false;
        }
    }
    return true;
}

bool did_win(const Table& table)
{
    FOR (i, 0, < 5) {
        if (did_win_row(table, i)) {
            return true;
        }
        if (did_win_column(table, i)) {
            return true;
        }
    }
    return false;
}

auto sum_of_unmarked(const Table& table)
{
    int s = 0;
    FOR (r, 0, < 5) {
        FOR (c, 0, < 5) {
            if (table[r][c] >= 0) {
                s += table[r][c];
            }
        }
    }
    return s;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d04_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    vector<int> draws = get_draws(lines[0]);
    int lix = 2;
    vector<Table> tables;
    for (; lix < ~lines; lix += 6) {
        assert(lix + 5 <= ~lines);
        Table table;
        FOR (j, 0, < 5) {
            auto l = trim(lines[lix + j]);
            auto ss = split(l, " ");
            assert(~ss == 5);
            FOR (c, 0, < 5) {
                table[j][c] = stoi(ss[c]);
            }
        }
        tables.PB(table);
    }
    maybe<int> p1, p2;
    set<int> tables_playing;
    FOR (i, 0, < ~tables) {
        tables_playing.insert(i);
    }
    for (auto d : draws) {
        for (auto tix : tables_playing) {
            cross_table(tables[tix], d);
        }
        FOR (tix, 0, < ~tables) {
            if (tables_playing.count(tix) == 0) {
                continue;
            }
            auto& table = tables[tix];
            if (did_win(table)) {
                if (~tables_playing == ~tables) {
                    p1 = d * sum_of_unmarked(table);
                }
                if (~tables_playing == 1) {
                    p2 = d * sum_of_unmarked(table);
                }
                tables_playing.erase(tix);
            }
        }
    }
    printf("P1: %d\n", p1.value_or(-1));
    printf("P2: %d\n", p2.value_or(-1));
    return 0;
}
