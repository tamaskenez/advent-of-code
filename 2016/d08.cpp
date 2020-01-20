#include "common.h"

#if 1
const int W = 50;
const int H = 6;
#else
const int W = 7;
const int H = 3;
#endif

struct Screen
{
    array<array<bool, W>, H> mx;
    void set_yx(int y, int x, bool value)
    {
        assert(0 <= y && y < H);
        assert(0 <= x && x < W);
        mx[y][x] = value;
    }
    bool get_yx(int y, int x) const
    {
        assert(0 <= y && y < H);
        assert(0 <= x && x < W);
        return mx[y][x];
    }
    Screen()
    {
        array<bool, W> er;
        er.fill(false);
        mx.fill(er);
    }
    void rect(int w, int h)
    {
        assert(0 <= w && w <= W);
        assert(0 <= h && h <= H);
        FOR (y, 0, < h) {
            FOR (x, 0, < w) {
                set_yx(y, x, true);
            }
        }
    }
    void rotate_x(int x, int by)
    {
        array<bool, H> column;
        FOR (y, 0, < H) {
            column[y] = get_yx(y, x);
        }
        FOR (y, 0, < H) {
            mx[(y + by) % H][x] = column[y];
        }
    }
    void rotate_y(int y, int by)
    {
        array<bool, W> row;
        FOR (x, 0, < W) {
            row[x] = mx[y][x];
        }
        FOR (x, 0, < W) {
            mx[y][(x + by) % W] = row[x];
        }
    }
};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d08_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    Screen screen;
    for (auto& l : lines) {
        auto vs = split(l, " ");
        assert(!vs.empty());
        if (vs[0] == "rotate") {
            assert(~vs == 5);
            if (vs[1] == "column") {
                assert(vs[2].substr(0, 2) == "x=");
                auto x = stoi(vs[2].substr(2));
                assert(vs[3] == "by");
                auto by = stoi(vs[4]);
                screen.rotate_x(x, by);
                // printf("rx %d %d\n", x, by);
            } else if (vs[1] == "row") {
                assert(vs[2].substr(0, 2) == "y=");
                auto y = stoi(vs[2].substr(2));
                assert(vs[3] == "by");
                auto by = stoi(vs[4]);
                screen.rotate_y(y, by);
                // printf("ry %d %d\n", y, by);
            } else {
                assert(false);
            }
        } else if (vs[0] == "rect") {
            assert(~vs == 2);
            auto xpos = vs[1].find('x');
            assert(xpos != string::npos);
            auto w = stoi(vs[1].substr(0, xpos));
            auto h = stoi(vs[1].substr(xpos + 1));
            screen.rect(w, h);
            // printf("rect %d %d\n", w, h);
        } else {
            assert(false);
        }
    }
    int count=0;
    FOR (y, 0, < H) {
        FOR (x, 0, < W) {
            bool b = screen.mx[y][x];
                if(b){++count;}
            printf("%c", b ? 'X' : '.');
        }
        printf("\n");
    }
    printf("count: %d\n",count);
    return 0;
}

// not UPOJFLBCEZ
