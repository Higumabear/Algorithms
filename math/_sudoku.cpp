#include <iostream>

using namespace std;

struct sudoku{
  int r[9], c[9], b[3][3];
  int f[9][9];

  sudoku() {}
  void init(){
    for(int y = 0; y < 9; y++){
      for(int x = 0; x < 9; x++){
	r[y] |= (1 << f[y][x]);
	c[x] |= (1 << f[y][x]);
	b[y/3][x/3] |= (1 << f[y][x]);
      }
    }
    
  }
  
  int search(int y, int x){
  
  }
}

int main(){
  
}
