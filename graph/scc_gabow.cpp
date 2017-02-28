/*
  Strongly connected components decomposition (Gabow)
  
  Complexity:
  O(V + E)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C

  Reference:
  Gabow, Harold N. (2000), "Path-based depth-first search for strong and biconnected components", Information Processing Letters, 74 (3-4): 107£ü114
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
    printf("%d\n", scc.I[s] == scc.I[t]);
  }
}
