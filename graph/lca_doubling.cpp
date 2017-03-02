/*
  Lowest Common Ancestor by doubling

  Complexity:
  preprocess: O(VlogV)
  per query:  O(logV)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C

 */

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct lca{
  vector<vector<int> > g, parent;
  vector<int> depth;
  int K, V;
  lca(int V): g(V), depth(V), V(V) {
    K = 32;
    parent.assign(V, vector<int>(K, -1));
  }
  
  void add_edge(int par, int ch){ g[par].push_back(ch); }
  
  void build(int cur, int prev = 0, int d = 0){
    int k = 1;
    depth[cur] = d;
    parent[cur][0] = prev;
    for(int base = 2; base <= d; base *= 2){
      parent[cur][k] = parent[parent[cur][k - 1]][k - 1];
      k++;
    }
    for(int i = 0; i < g[cur].size(); i++)
      build(g[cur][i], cur, d + 1);
    return;
  }

  int search(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    for(int k = 0; k < K; k++)
      if((depth[v] - depth[u]) >> k & 1)
	v = parent[v][k];
    
    if(u == v) return u;
    for(int k = K - 1; k >= 0; k--){
      if(parent[u][k] != parent[v][k]){
	u = parent[u][k];
	v = parent[v][k];
      }
    }
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
