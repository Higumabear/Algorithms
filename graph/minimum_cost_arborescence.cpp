#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct scc{
  vector<vector<int> > g;
  vector<int> I;
  stack<int> S, B;
  int V, c;
  scc(int V): V(V), g(V), I(V), c(V) {}

  void add_edge(int from, int to){
    g[from].push_back(to);
  }

  void dfs(int v){
    S.push(v); B.push(I[v] = S.size());
    for(int i = 0; i < g[v].size(); i++){
      int u = g[v][i];
      if(I[u] == 0) dfs(u);
      else while(B.top() > I[u]) B.pop();
    }
    if(I[v] == B.top()){
      c++;
      B.pop();
      while(I[v] <= S.size()){
	I[S.top()] = c;
	S.pop();
      }
    }
  }

  int decomp(){
    for(int i = 0; i < V; i++)
      if(I[i] == 0) dfs(i);
    return c - V;
  }
};

struct aborescence{
  struct edge{
    int from, to, cost;
  };
  int V;
  vector<edge> g;
  aborescence(int V): V(V) {}
  
  void add_edge(int from, int to, int cost){
    g.push_back({from, to, cost});
  }

  int calc(int r){
    int N = V;
    while(1){
      vector<edge> in(N, {-1, 0, INF});
      for(int i = 0; i < g.size(); i++)
	if(in[g[i].to].cost > g[i].cost)
	  in[g[i].to] = g[i];
      for(int i = 0; i < g.size(); i++)
	g[i].cost -= in[g[i].to].cost;
      for(int i = 0; i < N; i++)
	if(in[i].from < 0) return -1;
      
      scc scc(N);
      for(int i = 0; i < g.size(); i++)
	if(g[i].cost == 0) scc.add_edge(g[i].from, g[i].to);
      N = scc.decomp();
      
    }
  }
};
  
int main(){
  return 0;
}
