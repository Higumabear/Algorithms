/*
  Enumerate articulation points
  
  Complexity:
  O(V + E)
  
  verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
  
*/
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

class Graph{
public:
  int V, k;
  vector<vector<int> > g;
  vector<int> ord, low, articulation;
  vector<bool> vis;
  
  Graph(int V) :
    g(V), V(V), k(0), ord(V, -1), low(V), vis(V, false) {}

  void add_edge(int u, int v){
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void decomp(){
    for(int i = 0; i < V; i++)
      if(!vis[i]) dfs(i, -1);
  }
  
private:
  
  void dfs(int idx, int prv){
    ord[idx] = k++;
    low[idx] = ord[idx];
    vis[idx] = true;

    int degree = 0;
    bool art = false;
    for(int i = 0; i < g[idx].size(); i++){
      int nxt = g[idx][i];
      if(!vis[nxt]){
	degree++;
	dfs(nxt, idx);
	low[idx] = min(low[idx], low[nxt]);
	if(prv != -1 && ord[idx] <= low[nxt]) art = true;
      }else if(nxt != prv){
	low[idx] = min(low[idx], ord[nxt]);
      }
    }

    if(prv == -1 && degree > 1) art = true;
    if(art) articulation.push_back(idx);
  }
};

void GRL_3_A(){
  int V, E;
  scanf("%d %d", &V, &E);

  Graph g(V);
  for(int i = 0; i < E; i++){
    int u, v;
    scanf("%d %d", &u, &v);
    g.add_edge(u, v);
  }
  g.decomp();

  sort(g.articulation.begin(), 
       g.articulation.end());

  for(int i = 0; i < g.articulation.size(); i++)
    printf("%d\n", g.articulation[i]);
}

int main(){
  GRL_3_A();
  return 0;
}
