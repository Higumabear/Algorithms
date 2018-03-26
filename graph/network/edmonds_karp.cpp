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

class Graph{
private:
  struct edge{
    int to, cap, rev;
    edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {};
  };

  int V;
  int prv[MAXN];
  vector<vector<edge> > G;
  
public:
  Graph(int V) : V(V), G(V) {}
  
  void add_edge(int from, int to, int cap){
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size() - 1));
  }

  int maxflow(int s, int t){
    int maxflow = 0;
    int V = G.size();
    vector<vector<int> > flow(V, vector<int>(V, 0)),  cap(V, vector<int>(V, 0));
    for(int i = 0; i < V; i++)
      for(int j = 0; j < G[i].size(); j++)
	cap[i][G[i][j].to] += G[i][j].cap;
  
    for(;;){
      queue<int> q;
      q.push(s);
      memset(prv, -1, sizeof(prv));
      prv[s] = s;
      while(!q.empty()){
	int u = q.front(); q.pop();
	if(u == t) break;
	for(int i = 0; i < G[u].size(); i++){
	  edge e = G[u][i];
	  if(prv[e.to] == -1 
	     && cap[u][e.to] - flow[u][e.to] > 0){
	    q.push(e.to);
	    prv[e.to] = u;
	  }
	}
      }
      if(prv[t] == -1) break;

      int minaug = INF;
      for(int v = t; v != prv[v]; v = prv[v]) 
	minaug = min(minaug, cap[prv[v]][v] - flow[prv[v]][v]);
      for(int v = t; v != prv[v]; v = prv[v]) 
	flow[prv[v]][v] += minaug, flow[v][prv[v]] -= minaug;
      maxflow += minaug;
    }
  
    return maxflow;
  }
};
  
int main(){
  int v, e;
  cin >> v >> e;

  Graph g(v);
  
  int s, t, c;
  while(e--){
    cin >> s >> t >> c;
    g.add_edge(s, t, c);
  }
  cout << g.maxflow(0, v - 1) << endl;
  return 0;
}
