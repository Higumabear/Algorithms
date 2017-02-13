/*
  Fujishige's maximum-flow algorithm
  by capacity scaling

  Complexity:
  O(VE log u_max)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A

 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
const int INF = 1 << 29;

struct edge{
  int to, cap, rev;
  edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

vector<vector<edge> > G;

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int max_flow(int s, int t){
  int V = G.size();
  int U = 0;
  for(int i = 0; i < V; i++)
    for(int j = 0; j < G[i].size(); j++)
      U = max(U, G[i][j].cap);
  while(1){
    vector<int> b(V, 0);
    
  }
}

int main(){
  int v, e;
  cin >> v >> e;
  G.resize(v);

  int s, t, c;
  while(e--){
    cin >> s >> t >> c;
    add_edge(s, t, c);
  }
  cout << max_flow(0, v - 1) << endl;
  return 0;
}
