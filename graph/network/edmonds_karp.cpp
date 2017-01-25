/*
  Edmonds-Karp maximum-flow algorithm

  Complexity:
  O(VE^2)

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

int prev[MAXN];
vector<vector<edge> > G;

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int edmonds_karp(int s, int t){
  int minflow = 0;
  int V = G.size();
  vector<vector<int> > flow(V, vector<int>(V, 0)),  cap(V, vector<int>(V, 0));
  for(int i = 0; i < V; i++)
    for(int j = 0; j < G[i].size(); j++)
      cap[i][G[i][j].to] += G[i][j].cap;
  
  for(;;){
    queue<int> q;
    q.push(s);
    memset(prev, -1, sizeof(prev));
    prev[s] = s;
    while(!q.empty()){
      int u = q.front(); q.pop();
      if(u == t) break;
      for(int i = 0; i < G[u].size(); i++){
	edge e = G[u][i];
	if(prev[e.to] == -1 
	   && cap[u][e.to] - flow[u][e.to] > 0){
	  q.push(e.to);
	  prev[e.to] = u;
	}
      }
    }
    if(prev[t] == -1) break;

    int minaug = INF;
    for(int v = t; v != prev[v]; v = prev[v]) 
      minaug = min(minaug, cap[prev[v]][v] - flow[prev[v]][v]);
    for(int v = t; v != prev[v]; v = prev[v]) 
      flow[prev[v]][v] += minaug, flow[v][prev[v]] -= minaug;
    minflow += minaug;
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
  cout << edmonds_karp(0, v - 1) << endl;
  return 0;
}
