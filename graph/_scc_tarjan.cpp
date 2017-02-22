/*
  Strongly connected components decomposition (Tarjan)
  
  Complexity:
  O(V + E)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
 */

#include <vector>
#include <map>
#include <cstdio>

using namespace std;

struct scc{
  int V, c;
  vector<vector<int> > g;
  vector<int> disc, low;
  vector<int> cmp;
  vector<bool> vis;
  map<pair<int, int>, bool> used;
  scc(int V) : V(V), g(V), disc(V, -1), 
	       low(V, -1), vis(V), cmp(V), c(0) {}
  
  void add_edge(int from, int to){
    g[from].push_back(to);
  }

  void dfs(int u){
    disc[u] = c++;
    low[u] = disc[u];
    vis[u] = true;
    for(int v = 0; v < g[u].size(); v++){
      if(!vis[v]){
	used[make_pair(u, v)] = true;
	dfs(v);
	low[u] = min(low[u], low[v]);
      }else if(!used.count(make_pair(u, v))){
	low[u] = min(low[u], disc[v]);
      }
    }
  }

  int decomp(){
    for(int i = 0; i < V; i++){
      if(vis[i]) continue;
      dfs(i);
    }
    
    int k = 0;
    map<int, int> label;
    for(int i = 0; i < V; i++)
      if(!label.count(low[i]))
	label[low[i]] = k++;
    for(int i = 0; i < V; i++)
      cmp[i] = label[low[i]];
    
    return label.size();
  }
};

int main(){
  int V, E;
  scanf("%d %d", &V, &E);
  
  scc scc(V);
  for(int i = 0; i < E; i++){
    int s, t;
    scanf("%d %d", &s, &t);
    scc.add_edge(s, t);
  }
  scc.decomp();

  int N;
  scanf("%d", &N);
  for(int i = 0; i < N; i++){
    int s, t;
    scanf("%d %d", &s, &t);
    if(scc.cmp[s] == scc.cmp[t]) printf("1\n");
    else printf("0\n");
  }
}
