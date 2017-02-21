/*
  Strongly connected components decomposition (Kosaraju)
  
  Complexity:
  O(V + E)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
 */

#include <vector>
#include <cstdio>

using namespace std;

struct scc{
  int V, c;
  vector<vector<int> > g, rg;
  vector<int> ord;
  vector<int> cmp;
  vector<bool> vis;
  scc(int V) : V(V), g(V), rg(V), ord(V, -1), 
	       cmp(V, -1), vis(V), c(0) {}
  
  void add_edge(int from, int to){
    g[from].push_back(to);
    rg[to].push_back(from);
  }

  void dfs(int i){
    vis[i] = true;
    for(int j = 0; j < g[i].size(); j++)
      if(!vis[g[i][j]]) dfs(g[i][j]);
    ord[c++] = i;
  }
  void rdfs(int i, int label){
    vis[i] = true;
    cmp[i] = label;
    for(int j = 0; j < rg[i].size(); j++) 
      if(!vis[rg[i][j]]) rdfs(rg[i][j], label);
  }

  int decomp(){
    int res = 0;
    fill(vis.begin(), vis.end(), false);
    for(int i = 0; i < V; i++)
      if(!vis[i]) dfs(i);
    
    fill(vis.begin(), vis.end(), false);
    for(int i = c - 1; i >= 0; i--)
      if(!vis[ord[i]]) rdfs(ord[i], res++);
    return res;
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
