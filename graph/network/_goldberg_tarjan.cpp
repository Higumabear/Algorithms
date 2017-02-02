/*
  Goldberg-Tarjan with gap heuristics
  maximum-flow algorithm

  Complexity:
  O(V^3)

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

vector<vector<edge> > G;

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int max_flow(int s, int t){
  int V = G.size();
  vector<vector<int> > cap(V, vector<int>(V, 0)), flow(V, vector<int>(V, 0));
  vector<int> height(V, 0), excess(V, 0);

  for(int i = 0; i < V; i++)
    for(int j = 0; j < G[i].size(); j++)
      cap[i][G[i][j].to] = G[i][j].cap;

  queue<int> Q;
  height[s] = V;
  for(int j = 0; j < V; j++) if(cap[s][j] > 0) {
    flow[s][j] = cap[s][j]; flow[j][s] = -flow[s][j];//residual edge
    excess[j] = flow[s][j];
    Q.push(j);
  }

  while(!Q.empty()){
    int u = Q.front(); Q.pop();
    int h = INF;
    bool push = false;
    //cout << u << " ";
    for(int v = 0; v < V; v++){
      int rem = cap[u][v] - flow[u][v];
      if(cap[u][v] - flow[u][v] > 0) h = min(h, height[v] + 1);
      if(rem > 0 && height[u] == height[v] + 1){ // push
	int delta = min(excess[u], rem);
	flow[u][v] += delta;    flow[v][u] -= delta;
	excess[u] -= delta;     excess[v] += delta;
	push = true;
      }
    }
    if(!push && excess[u] > 0) height[u] = h; //relabel
    for(int i = 0; i < V; i++) cout << height[i] << " ";
    cout << endl;
    if(excess[u] > 0) Q.push(u);
  }
  int maxflow = 0;
  for(int i = 0; i < V; i++) maxflow += flow[i][t];
  return maxflow;
}

int main(){
  //for(int i = 0; i < MAXN; i++) G[i].clear();
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
