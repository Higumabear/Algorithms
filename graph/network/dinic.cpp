/*
  Dinic maximum-flow algorithm

  Complexity:
  O(V^2E)

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

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int dfs(int idx, int t, vector<int> &level, int depth, int f){
  if(idx == t) return f;
  for(int u = 0; u < G[idx].size(); u++){
    edge &e = G[idx][u];
    if(e.cap > 0 && level[e.to] == depth + 1 && depth + 1 <= level[t]){
      int d = dfs(e.to, t, level, depth + 1, min(e.cap, f));
      if(d > 0){
	e.cap -= d;
	G[e.to][e.rev].cap += d;
	return d;
      }
    }
  }
  return 0;
}

int dinic(int s, int t){
  int minflow = 0;
  int V = G.size();
  
  while(true){
    vector<int> level(V, -1);
    queue<int> Q;
    level[s] = 0;
    Q.push(s);
    while(!Q.empty()){
      int v = Q.front(); Q.pop();
      for(int i = 0; i < G[v].size(); i++){
	edge &e = G[v][i];
	if(e.cap > 0 && level[e.to] == -1){
	  level[e.to] = level[v] + 1;
	  Q.push(e.to);
	}
      }
    }
    if(level[t] == -1) break;

    int f;
    while((f = dfs(s, t, level, 0, INF)) != 0) minflow += f;
  }
  
  return minflow;
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
  cout << dinic(0, v - 1) << endl;
  return 0;
}
