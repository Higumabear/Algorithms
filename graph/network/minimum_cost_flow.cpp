/*
  Minimum cost flow successive shortest paths

  Complexity:
  O(VECU) 
  C is the sum of costs
  U is the sum of flows

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B

 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
const int INF = 1 << 29;

struct min_cost_flow{
  struct edge{
    int to, cap, cost, rev;
    edge(int to, int cap, int cost, int rev) : 
      to(to), cap(cap), cost(cost), rev(rev) {};
  };
  vector<vector<edge> > G;

  min_cost_flow(int V) : G(V) {}

  void add_edge(int from, int to, int cap, int cost){
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
  }

  int flow(int s, int t, int f){
    typedef pair<int, int> P;
    int V = G.size();
    vector<int> po(V);
    int res = 0;
    while(f > 0){
      vector<int> dist(V, INF), prevv(V, -1), preve(V, -1);
      priority_queue<P, vector<P>, greater<P> > Q;
      Q.push(make_pair(0, s));
      dist[s] = 0;
      while(!Q.empty()){
	P q = Q.top(); Q.pop();
	int u = q.second;
	if(dist[u] < q.first) continue;
	for(int i = 0; i < G[u].size(); i++){
	  edge &e = G[u][i];
	  if(e.cap > 0 && dist[e.to] > dist[u] + e.cost + po[u] - po[e.to]){
	    dist[e.to] = dist[u] + e.cost + po[u] - po[e.to];
	    prevv[e.to] = u;   preve[e.to] = i;
	    Q.push(P(dist[e.to], e.to));
	  }
	}
      }
      if(dist[t] == INF) return -1;
      for(int v = 0; v < V; v++) po[v] += dist[v];
      
      int scap = f;
      for(int v = t; v != s; v = prevv[v])
	scap = min(scap, G[prevv[v]][preve[v]].cap);
      
      f -= scap;
      res += scap * po[t];
      for(int v = t; v != s; v = prevv[v]){
	edge &e = G[prevv[v]][preve[v]];
	e.cap -= scap;
	G[v][e.rev].cap += scap;
      }
    }
    return res;
  }
};

int main(){
  int v, e, f;
  cin >> v >> e >> f;
  min_cost_flow mcf(v);

  int s, t, c, d;
  while(e--){
    cin >> s >> t >> c >> d;
    mcf.add_edge(s, t, c, d);
  }
  cout << mcf.flow(0, v - 1, f) << endl;
  return 0;
}
