/*
  Ford-Fulkerson maximum-flow algorithm

  Complexity:
  O(F|E|) F is the max-flow size

  Verified:
  
 */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int INF = 1 << 29;

struct edge{
  int to, cap, rev;
  edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
};

bool vis[MAXN];
vector<edge> G[MAXN];

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

int ford_fulkerson(int s, int t){
  int flow = 0;
  for(;;){
    memset(vis, false, sizeof(vis));
    int f = dfs(s, t, INF);
    if(f == 0) break;
    flow += f;
  }
  return flow;
}

int main(){
  for(int i = 0; i < MAXN; i++) G[i].clear();
  int v, e;
  cin >> v >> e;
  int s, t, c;
  while(e--){
    cin >> s >> t >> c;
    add_edge(s, t, c);
  }
  cout << ford_fulkerson(0, v - 1) << endl;
  return 0;
}
