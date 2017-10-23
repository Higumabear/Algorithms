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

struct max_flow{
  struct edge{
    int to, cap, rev;
    edge(int to, int cap, int rev) :
      to(to), cap(cap), rev(rev) {};
  };
  
  vector<vector<edge> > G;
  vector<int> level, iter;

  max_flow(int V) {
    G.assign(V, vector<edge>());
    level.assign(V, -1);
    iter.assign(V, 0);
  }
  
  void add_edge(int from, int to, int cap){
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size() - 1));
  }

  void bfs(int s, int t){
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()){
      int v = Q.front(); Q.pop();
      if(v == t) break;
      for(int u = 0; u < G[v].size(); u++){
	edge e = G[v][u];
	if(e.cap > 0 && level[e.to] == -1){
	  level[e.to] = level[v] + 1;
	  Q.push(e.to);
	}
      }
    }
  }

  int dfs(int idx, int t, int f){
    if(idx == t) return f;
    for(int &u = iter[idx]; u < G[idx].size(); u++){
      edge &e = G[idx][u];
      if(e.cap > 0 && level[idx] < level[e.to]){
	int d = dfs(e.to, t, min(e.cap, f));
	if(d > 0){
	  e.cap -= d;
	  G[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }

  int flow(int s, int t){
    int ret = 0, f;
    while(bfs(s, t), level[t] >= 0){
      fill(iter.begin(), iter.end(), 0);
      while((f = dfs(s, t, INF)) > 0) ret += f;
    }
    return ret;
  }
};

int main(){
  int v, e;
  cin >> v >> e;

  max_flow flow(v);
  int s, t, c;
  while(e--){
    cin >> s >> t >> c;
    flow.add_edge(s, t, c);
  }
  cout << flow.flow(0, v - 1) << endl;
  return 0;
}
