#include "common.h"

const array<string, 3> keypad = {"123", "456", "789"};

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d02_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    {
        AI2 rc{2, 2};
        for (auto& l : lines) {
            for (auto c : l) {
                switch (c) {
                    case 'L':
                        rc[1] = clamp(rc[1] - 1, 1, 3);
                        break;
                    case 'R':
                        rc[1] = clamp(rc[1] + 1, 1, 3);
                        break;
                    case 'U':
                        rc[0] = clamp(rc[0] - 1, 1, 3);
                        break;
                    case 'D':
                        rc[0] = clamp(rc[0] + 1, 1, 3);
                        break;
                    default:
                        assert(false);
                }
            }
            printf("%c", keypad[rc[0] - 1][rc[1] - 1]);
        }
        printf("\n");
    }
    {
        const array<string, 5> bathroom = {"  1  ", " 234 ", "56789", " ABC ", "  D  "};
        AI2 rc{2, 2};
        for (auto& l : lines) {
            for (auto c : l) {
                auto rc2 = rc;
                switch (c) {
                    case 'L':
                        rc2[1] = clamp(rc2[1] - 1, 1, 5);
                        break;
                    case 'R':
                        rc2[1] = clamp(rc2[1] + 1, 1, 5);
                        break;
                    case 'U':
                        rc2[0] = clamp(rc2[0] - 1, 1, 5);
                        break;
                    case 'D':
                        rc2[0] = clamp(rc2[0] + 1, 1, 5);
                        break;
                    default:
                        assert(false);
                }
                auto d = bathroom[rc2[0] - 1][rc2[1] - 1];
                if (d != ' ') {
                    rc = rc2;
                }
            }
            printf("%c", bathroom[rc[0] - 1][rc[1] - 1]);
        }
        printf("\n");
    }
    return 0;
}
// 5 48