/*
  Strongly connected components decomposition (Gabow)
  
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
  vector<int> I;
  stack<int> S, B;
  int V, c;
  scc(int V): V(V), g(V), I(V, -1), c(V) {}

  void add_edge(int from, int to){
    g[from].push_back(to);
  }

  void dfs(int v, int &label){
    I[v] = v;
    S.push(v); B.push(v);
    for(int i = 0; i < g[v].size(); i++){
      int u = g[v][i];
      if(I[u] == -1) dfs(u, label);
      else
      	while(B.top() > I[u]) B.pop();
      // else if(cmp[u] == -1)
      // 	while(B.top() > ord[u]) B.pop();
    }
    if(I[v] == B.top()){
      c++;
      while(I[v] <= S.top()){
	I[S.top()] = c;
	S.pop();
      }
      B.pop();
    }
  }

  int decomp(){
    int label = 0;
    for(int i = 0; i < V; i++)
      if(I[i] == 0) dfs(i, label);
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
    printf("%d\n", scc.I[s] == scc.I[t]);
  }
}
