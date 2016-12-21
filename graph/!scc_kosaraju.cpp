#include <iostream>
#include <vector>

using namespace std;

const int MAX_V = 1000;
int V;
vector<int> g[MAX_V];
vector<int> rg[MAX_V];
bool used[MAX_V];
vector<int> vs;

void add_edge(int from, int to){
  g[from].push_back(to);
  rg[to].push_back(from);
}

void dfs(int v){
  used[v] = true;
  for(int i = 0; i < g[v].size(); i++){
    if(!used[g[v][i]]) dfs(g[v][i]);
  }
  vs.push_back(v);
}

void rdfs(int v, int k){
  used[v] = true;
  cmp[v] = k;
  for(int i = 0; i < g[v].size(); i++){
    if(!used[g[v][i]]) rdfs(g[v][i], k);
  }
}

int scc(){
  FILL(used, false);
  vs.clear();
  for(int i = 0; i < V; i++){
    if(!used[i]) dfs(i);
  }
  FILL(used, false);
  k = 0;
  for(int i = vs.size() - 1; i >= 0; i--){
    if(!used[vs[i]]) rdfs(vs[i], k++);
  }
  return k;
}
