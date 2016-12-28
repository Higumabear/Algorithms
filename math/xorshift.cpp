#include <iostream>
using namespace std;

/*
  xorshift random number gen (2^128 - 1 periodical)
  by George Marsaglia
*/
unsigned int xor128(){
  static unsigned int x = 123456789, y = 362436069, 
    z = 521288629, w = 88675123;
  unsigned int t = x ^ (x << 11);
  x = y, y = z, z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int main(){
  for(int i = 0; i < 10000; i++) cout << xor128() << " ";
  cout << endl;
}
