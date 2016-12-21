#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SQdecomp{
  int N, L;
  vector<int> maxaid, minaid;
  vector<int> &dat;

public:
  SQdecomp(vector<int> &arr) : N(arr.size()), dat(arr){
    L = sqrt(N) + 1;
    maxaid.assign(L, -1 * (1 << 29));
    minaid.assign(L, 1 << 29);
    for(int i = 0; i < N; i++){
      maxaid[i / L] = max(maxaid[i / L], dat[i]);
      minaid[i / L] = min(minaid[i / L], dat[i]);
    }
  }
  void update(int idx, int val){ 
    dat[idx] = val;
    maxaid[idx / L] = max(maxaid[idx / L], val);
    minaid[idx / L] = min(minaid[idx / L], val);
  }
  int min_query(int l, int r){//[l, r)
    return min(*min_element(dat.begin() + l, dat.begin() + (l + L) / L * L),
	       min(*min_element(dat.begin() + r / L * L, dat.begin() + r),
		   *min_element(minaid.begin() + (l + L) / L, minaid.begin() + r / L)));
  }
  int max_query(int l, int r){//[l, r)
    return max(*max_element(dat.begin() + l, dat.begin() + (l + L) / L * L),
	       max(*max_element(dat.begin() + r / L * L, dat.begin() + r),
		   *max_element(maxaid.begin() + (l + L) / L, maxaid.begin() + r / L)));
  }
  void debug(){
    for(auto u : minaid) cerr << u << " ";
    cerr << endl;
    for(auto u : maxaid) cerr << u << " ";
    cerr << endl;
    for(auto u : dat) cerr << u << " ";
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
  vec.push_back(81);  
  vec.push_back(37);
  vec.push_back(9);   
  vec.push_back(-10);
  vec.push_back(2);  
  vec.push_back(925);
  vec.push_back(3);   
  vec.push_back(3);   
  SQdecomp sq(vec);
  cout << sq.min_query(0, 10) << endl;
  sq.debug();
  sq.update(3, -1);
  cout << sq.min_query(0, 10) << endl;
}
