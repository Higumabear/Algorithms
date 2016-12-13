#include <iostream>
#include <vector>

using namespace std;

class RMQ{
  RMQ(const vector<int> &arr){
    N = 1;
    while(N < arr.size()) N *= 2;
    node.assign(2 * N, 1 << 30);
    copy(arr.begin(), arr.end(), node.begin() + N - 1);
    for(int i = N - 2; i >= 0; i--)
      node[i] = min(node[2 * i + 1], node[2 * i + 2]);
  }
  
private:
  int N;
  vector<int> node;
  int query(int l, int r){ //[l, r)
    
  }
  int update(int idx, int val){
    idx += N - 1;
    node[idx] = val;
    while((idx - 1) / 2 >= 0)
      node[(idx - 1) / 2] = min(node[idx], node[(idx - 1) / 2]);
  }
}
