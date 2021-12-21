#include "common.h"

struct Mi
{
    set<AI2> img;
    bool inverted = false;
};

// input img    iea
//  normal     ..    // ok
//  normal     .#    // ok
//  normal     #.    // use ~iea, inverse result
//  normal     ##    // use ~iea, inverse result

// input img    iea
//  inverse     ..
//  inverse     .#
//  inverse     #.
//  inverse     ##

tuple<AI2, AI2> get_bounds_cc(const set<AI2>& img)
{
    AI2 lo = *img.begin();
    AI2 hi = *img.begin();
    for (auto rc : img) {
        FOR (i, 0, < 2) {
            lo[i] = std::min(lo[i], rc[i]);
            hi[i] = std::max(hi[i], rc[i]);
        }
    }
    return {lo, hi};
}

Mi apply_iea(const Mi& mi, const string& iea)
{
    assert(~iea == 512);
    bool raw_outside = false;
    bool actual_outside = raw_outside ^ mi.inverted;
    int code_for_outside = actual_outside ? 511 : 0;
    bool result_actual_outside = iea[code_for_outside] == '#';
    bool invert_output = result_actual_outside;
    /*
if (mi.inverted) {
    use_inverse_iea = iea[511] == '#';
} else {
    use_inverse_iea = iea[0] == '#';
}
*/

    set<AI2> result_img;
    auto [lo, hi] = get_bounds_cc(mi.img);
    FOR (r, lo[0] - 1, <= hi[0] + 1) {
        FOR (c, lo[1] - 1, <= hi[1] + 1) {
            int code = 0;
            FOR (rr, r - 1, <= r + 1) {
                FOR (cc, c - 1, <= c + 1) {
                    auto light = (mi.img.count(AI2{rr, cc}) > 0) ^ mi.inverted;
                    code = (code << 1) + (light ? 1 : 0);
                }
            }
            assert(is_between_cc(code, 0, 511));
            auto result_light = (iea[code] == '#') ^ invert_output;
            if (result_light) {
                result_img.insert(AI2{r, c});
            }
        }
    }

    /*
        for (bool raw_input : {false, true}) {
            bool actual_input = raw_input ^ mi.inverted;
            bool full_area = iea[actual_input ? 511 : 0] == '#';
            auto code = (raw_input ^ mi.inverted) ? 511 : 0;
            bool calculated_actual_output  = iea[code]=='#';
            bool raw_output = calculated_actual_output ^ use_inverse_iea;
            assert((raw_output^output_inverted)==full_area);
            if (!raw_input) {
                assert(!raw_output);
            }
        }
    */
    return Mi{move(result_img), invert_output};
}

void P1(const VS& img, const string& iea)
{
    set<AI2> mimg;
    FOR (r, 0, < ~img) {
        FOR (c, 0, < ~img[r]) {
            if (img[r][c] == '#') {
                mimg.insert(AI2{r, c});
            }
        }
    }
    auto mi = apply_iea(Mi{mimg, false}, iea);
    mi = apply_iea(mi, iea);
    printf("P1: %d\n", ~mi.img);
}

void P2(const VS& img, const string& iea)
{
    set<AI2> mimg;
    FOR (r, 0, < ~img) {
        FOR (c, 0, < ~img[r]) {
            if (img[r][c] == '#') {
                mimg.insert(AI2{r, c});
            }
        }
    }
    auto mi = Mi{mimg, false};
    FOR (step, 0, < 50) {
        mi = apply_iea(mi, iea);
    }
    int count = ~mi.img;
    if (mi.inverted) {
        auto [lo, hi] = get_bounds_cc(mi.img);
        int total = (hi[0] - lo[0] + 1) * (hi[1] - lo[1] + 1);
        count = total - count;
    }
    printf("P2: %d\n", count);
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d20_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    auto iea = lines[0];
    VS img;
    set<int> ws;
    FOR (i, 2, < ~lines) {
        img.PB(lines[i]);
        ws.insert(~lines[i]);
    }
    assert(~ws == 1);
    P1(img, iea);
    P2(img, iea);
    return 0;
}

// 16563 high
