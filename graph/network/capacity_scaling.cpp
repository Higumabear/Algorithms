/*
  capacity scaling maximum-flow algorithm

  Complexity:
  O(E^2 logU)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A

 */

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
const int INF = 1 << 29;

struct edge{
  int to, cap, rev;
  edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

vector<vector<edge> > G;
bool vis[MAXN];

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int dfs(int idx, int t, int f){
  if(idx == t) return true;
  vis[idx] = true;
  for(int u = 0; u < G[idx].size(); u++){
    edge &e = G[idx][u];
    if(e.cap >= f && !vis[e.to]){
      if(!dfs(e.to, t, f)) continue;
      e.cap -= f;
      G[e.to][e.rev].cap += f;
      return true;
    }
  }
  return false;
}

int max_flow(int s, int t){
  int maxU = 0;
  for(int i = 0; i < G.size(); i++)
    for(int j = 0; j < G[i].size(); j++)
      maxU = max(maxU, G[i][j].cap);
  
  int U = 1;
  while(U * 2 <= maxU) U *= 2;

  int flow = 0;
  while(U){
    while(1){
      memset(vis, false, sizeof(vis));
      if(!dfs(s, t, U)) break;
      flow += U;
    }
    U /= 2;
  }
  return flow;
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
