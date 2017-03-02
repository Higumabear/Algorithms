/*
  Lowest Common Ancestor by Euler tour + RMQ

  Complexity:
  preprocess: O(V)
  per query:  O(logV)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C

 */

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class RMQ{
  int N;
  vector<long long> min_dat;

public:
  RMQ(int n) : N(1) {
    while(N < n) N *= 2;
    min_dat.assign(2 * N - 1, -1 + (1LL << 31));
  }
  RMQ(vector<int> &arr) : N(1) {
    while(N < arr.size()) N *= 2;
    min_dat.assign(2 * N - 1, -1 + (1LL << 31));
    copy(arr.begin(), arr.end(), min_dat.begin() + N - 1);
    for(int i = N - 2; i >= 0; i--){
      min_dat[i] = min(min_dat[2 * i + 1], min_dat[2 * i + 2]);
    }
  }
  void update(int idx, int val){
    idx += N - 1;
    min_dat[idx] = val;
    while(idx > 0){
      idx = (idx - 1) / 2;
      min_dat[idx] = min(min_dat[2 * idx + 1], min_dat[2 * idx + 2]);
    }
  }
  int min_query(int a, int b){ return min_query(a, b, 0, 0, N); }
  int min_query(int a, int b, int k, int l, int r){
    if(r <= a || b <= l) return -1LL + (1LL << 31);
    if(a <= l && r <= b) return min_dat[k];
    return min(min_query(a, b, 2 * k + 1, l, (l + r) / 2),
	       min_query(a, b, 2 * k + 2, (l + r) / 2, r));
  }
};

struct lca{
  vector<vector<int> > g;
  vector<int> euler_path, depth;
  int V;
  lca(int V): g(V), V(V), depth(V) {}
  
  void add_edge(int par, int ch){ g[par].push_back(ch); }
  
  void euler_tour(int cur, int prev, int &idx, int d){
    depth[cur] = d;
    euler_path.push_back(cur);
    if(!g[cur].size()) return;
    for(int i = 0; i < g[cur].size(); i++)
      euler_tour(g[cur][i], cur, idx, d + 1);
    euler_path.push_back(cur);
    return;
  }
  
  void build(int root){
    euler_tour(root, -1, 0, 0);
    vector<int> v(V);
    for(int i = 0; i < euler_path.size(); i++)
      v[euler_path[i]] = i;

    RMQ rmq(euler_path);
  }

  int search(int u, int v){
    return parent[u][0];
  }
};

int main(){
  int V; cin >> V;
  lca lca(V);

  for(int i = 0; i < V; i++){
    int T;
    cin >> T;
    for(int j = 0; j < T; j++){
      int a;
      cin >> a;
      lca.add_edge(i, a);
    }
  }
  lca.build(0);

  int Q;
  cin >> Q;
  while(Q--){
    int s, t; cin >> s >> t;
    cout << lca.search(s, t) << endl;
  }
  return 0;
}
