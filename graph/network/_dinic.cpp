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

int prev[MAXN];
vector<vector<edge> > G;

void add_edge(int from, int to, int cap){
  G[from].push_back(edge(to, cap, G[to].size()));
  G[to].push_back(edge(from, 0, G[from].size() - 1));
}

int dinic(int s, int t){
  int minflow = 0;
  int V = G.size();
  
  while(true){
    vector<int> level(V, -1);
    level[s] = 0;
    queue<int> Q;
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
