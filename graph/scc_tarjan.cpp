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
#include <stack>
#include <iostream>
#include <cstring>

using namespace std;

const int INF = 1 << 29;

struct scc{
  vector<vector<int> > g;
  vector<int> ord, low, cmp;
  vector<bool> instack;
  stack<int> S;
  int V, c;
  scc(int V): V(V), g(V), ord(V), low(V), cmp(V), 
	      instack(V, false), c(0) {}

  void add_edge(int from, int to){
    g[from].push_back(to);
  }

  void dfs(int v, int &label){
    ord[v] = low[v] = ++c;
    S.push(v);
    instack[v] = true;
    for(int i = 0; i < g[v].size(); i++){
      int u = g[v][i];
      if(ord[u] == 0){
	dfs(u, label);
	low[v] = min(low[v], low[u]);
      }else if(instack[u])
	low[v] = min(low[v], ord[u]);
    }
    if(low[v] == ord[v]){
      while(1){
	int w = S.top(); S.pop();
	instack[w] = false;
	cmp[w] = label;
	if(ord[w] == ord[v]) break;
      }
      label++;
    }
  }

  int decomp(){
    int label = 0;
    for(int i = 0; i < V; i++)
      if(ord[i] == 0) dfs(i, label);
    return label;
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
  while(N--){
    int s, t;
    scanf("%d %d", &s, &t);
    printf("%d\n", scc.cmp[s] == scc.cmp[t]);
  }
}
