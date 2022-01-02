#include "common.h"



void P1(VS lines){
    int W = ~lines[0];
    int H = ~lines;
    for(int step = 1; ; ++step){
    bool moved=false;
    auto nl=lines;
    FOR(r,0,<~lines){
        FOR(c,0,<W){
            if(lines[r][c]=='>'&&lines[r][(c+1)%W]=='.'){
                nl[r][c] = '.';
                nl[r][(c+1)%W]='>';
                moved=true;
            }
        }
    }
    lines = nl;
    FOR(r,0,<~lines){
        FOR(c,0,<W){
            if(lines[r][c]=='v'&&lines[(r+1)%H][c]=='.'){
                nl[r][c] = '.';
                nl[(r+1)%H][c]='v';
                moved=true;
            }
        }
    }
    lines=nl;
    
    if(!moved){printf("p1: %d\n",step);break;}
    }
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d25_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    P1(lines);
    return 0;
}
