#include <iostream>

using namespace std;

const int MAXN = 10000;

struct edge{
  int to, cap, rev;
  edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

vector<edge> G[MAXN];

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, from));
  G[to].push_back(edge(from, 0, to));
}

int dfs(int cur, int t, int f){
  if(cur == t) return f;
  vis[cur] = true;
  for(int next = 0; next < G[cur].size(); next++){
    edge &e = G[cur][next];
    if(!vis[next] && G[cur][next].cap){
      int d = dfs(next, to, min(f, e.cap));
      if(d){
	e.cap -= d;
	G[e.to][e.rev].cap += d;
	return d;
      }
    }
  }
  return 0;
}

int ford_fulkerson(int s, int t){
  int flow = 0;
  for(;;){
    memset(vis, false, sizeof(vis));
    int f = dfs(s, t, INF);
    if(!f) break;
    flow += f;
  }
  return flow;
}

