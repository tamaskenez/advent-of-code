#include "common.h"


bool is_valid(string s){
int lo, hi;
char c;
char b[9999];
  int r = sscanf(s.c_str(), "%d-%d %c: %s", &lo, &hi, &c, b);
  assert(r==4);
  char *p=b;
  unordered_map<char, int> counters;
  while(*p){
    counters[*p]++;
    ++p;
  }
  return lo <= counters[c] && counters[c] <= hi;
}

bool is_valid2(string s){
int lo, hi;
char c;
char b[9999];
  int r = sscanf(s.c_str(), "%d-%d %c: %s", &lo, &hi, &c, b);
  assert(r==4);
  int count=0;
  if(b[lo-1]==c){++count;}
  if(b[hi-1]==c){++count;}
  return count==1;
}

int main()
{
    ifstream f(CMAKE_CURRENT_SOURCE_DIR "/d2_input.txt");
    assert(f.good());
    auto lines = read_lines(f);
    printf("%d\n", (int)~lines);
    int valid_count=0;
    int valid_count2=0;
    for(auto l:lines){
      if(is_valid(l)){
        ++valid_count;
      }
      if(is_valid2(l)){
        ++valid_count2;
      }
    }
    printf("P1: %d\n", valid_count);
    printf("P2: %d\n", valid_count2);
    return 0;
}
