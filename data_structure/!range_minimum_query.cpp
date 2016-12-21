#include <iostream>
#include <vector>

using namespace std;

class RMQ{
  int N;
  vector<int> node;

public:
  RMQ(const vector<int> &arr) : N(1){
    while(N < arr.size()) N *= 2;
    node.resize(2 * N - 1, 1 << 28);
    copy(arr.begin(), arr.end(), node.begin() + N - 1);
    for(int i = N - 2; i >= 0; i--)
      node[i] = min(node[2 * i + 1], node[2 * i + 2]);
  } 
  int update(int idx, int val){
    idx += N - 1;
    node[idx] = val;
    while(idx > 0){
      idx = (idx - 1) / 2;
      node[idx] = min(node[2 * idx + 1], node[2 * idx + 2]);
    }
  }
  int query(int a, int b){ return query(a, b, 0, 0, N); }
  int query(int a, int b, int k, int l, int r){ //[l, r)
    if(r <= a || b <= l) return 1 << 28;
    if(a <= l && r <= b) return node[k];
    return min(query(a, b, k * 2 + 1, l, (l + r) / 2),
	       query(a, b, k * 2 + 2, (l + r) / 2, r));
  }
  void debug(){
    for(auto u : node) cerr << u << " ";
    cerr << endl;
  }
};

int main(){
  vector<int> vec;
  vec.push_back(3);  
  vec.push_back(7);
  vec.push_back(9);   
  vec.push_back(10);
  vec.push_back(2);  
  vec.push_back(5);
  vec.push_back(3);   
  vec.push_back(4);
  RMQ rmq(vec);
  cout << rmq.query(1, 5) << endl;
  rmq.update(3, -1);
  cout << rmq.query(1, 5) << endl;
}
