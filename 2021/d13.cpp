#include "common.h"

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d13_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    set<AI2> paper;
    bool first_fold = true;
    for (auto l : lines) {
        if (l.find('=') != string::npos) {
            auto ll = split(trim(l), "=");
            char letter = ll[0].back();
            auto n = stoi(ll[1]);
            set<AI2> new_paper;
            for (auto xy : paper) {
                if (letter == 'x') {
                    if (xy[0] >= n) {
                        new_paper.insert(AI2{2 * n - xy[0] , xy[1]});
                    } else {
                        new_paper.insert(xy);
                    }
                } else {
                    assert(letter == 'y');
                    if (xy[1] >= n) {
                        new_paper.insert(AI2{xy[0],2 * n - xy[1] });
                    } else {
                        new_paper.insert(xy);
                    }
                }
            }
            if(first_fold){
                first_fold=false;
                printf("P1: %d\n",~new_paper);
            }
            paper.swap(new_paper);
        } else if (l.find(',') != string::npos) {
            auto ll = split(trim(l), ",");
            auto a = stoi(ll[0]);
            auto b = stoi(ll[1]);
            paper.insert(AI2{a, b});
        }
    }
    AI2 mxy{0,0};
    for(auto xy:paper){
        mxy[0] = max(mxy[0], xy[0]);
        mxy[1] = max(mxy[1], xy[1]);
    }
    VS z(mxy[1]+1, string(mxy[0], ' '));
    for(auto xy:paper){
        z[xy[1]][xy[0]] = '#';
    }
    for(auto l:z){
    printf("%s\n",l.c_str());
    }
    return 0;
}
