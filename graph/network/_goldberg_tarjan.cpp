/*
  Goldberg-Tarjan with gap heuristics
  maximum-flow algorithm

  Complexity:
  O(V^2Å„E)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A

 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int INF = 1 << 29;

struct edge{
  int to, cap, rev;
  edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

bool vis[MAXN];
vector<vector<edge> > G;

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int dfs(int cur, int t, int f){
  if(cur == t) return f;
  vis[cur] = true;
  for(int i = 0; i < G[cur].size(); i++){
    edge &e = G[cur][i];
    if(!vis[e.to] && e.cap){
      int d = dfs(e.to, t, min(f, e.cap));
      if(d > 0){
	e.cap -= d;
	G[e.to][e.rev].cap += d;
	return d;
      }
    }
  }
  return 0;
}

int max_flow(int s, int t){
  int V = G.size();
  vector<vector<int> > cap(V, vector<int>(V, 0)), flow(V, vector<int>(V, 0));
  vector<int> height(V, 0), gap(V, 0);

  for(int i = 0; i < V; i++)
    for(int j = 0; j < G[i].size(); j++)
      cap[i][G[i][j].to] = G[i][j].cap;

  queue<int> Q;
  height[s] = V;  
  for(int i = 0; i < G[s].size(); i++){
    flow[s][G[s][i].to] = G[s][i].cap;
    if()
  }
  
}

int main(){
  for(int i = 0; i < MAXN; i++) G[i].clear();
  int v, e;
  cin >> v >> e;
  G.resize(v);

  int s, t, c;
  while(e--){
    cin >> s >> t >> c;
    add_edge(s, t, c);
  }
  cout << ford_fulkerson(0, v - 1) << endl;
  return 0;
}
