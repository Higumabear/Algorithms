/*
  Fenwick tree

  verified:
  [POJ 3067 Japan] http://poj.org/problem?id=3067
 */

// Time-stamp: <Fri Jan 06 00:38:20 “Œ‹ž (•W€Žž) 2017>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

template <class T>
struct BIT{
  int N;
  vector<T> dat;
  T sum(int i){ // return sum [0, i)
    i--;
    T s = 0;
    while(i > 0){
      s += dat[i];
      i -= i & -i;
    }
    return s;
  }
public:
  BIT(int sz) : N(sz) { dat.assign(2 * sz + 2, 0); }
    T sum(int l, int r){ // return sum [l, r)
    return sum(r + 1) - sum(l);
  }
  void add(int i, T x){
    while(i <= N){
      dat[i] += x;
      i += i & -i;
    }
  }
};

int main(int argc, char **argv){
  BIT<int> bit(10);
  return 0;
}
