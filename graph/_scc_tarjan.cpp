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

using namespace std;

const int INF = 1 << 29;

struct scc{
  int V, c;
  vector<vector<int> > g;
  vector<int> disc, low;
  vector<int> cmp;
  vector<bool> onstack;
  stack<int> S;
  scc(int V) : V(V), g(V), disc(V), 
	       low(V), onstack(V), cmp(V), c(0) {}
  
  void add_edge(int from, int to){
    g[from].push_back(to);
    //g[to].push_back(from);
  }

  void dfs(int v){
    low[v] = disc[v] = ++c;
    onstack[v] = true;
    S.push(v);

    for(int i = 0; i < g[v].size(); i++){
      int u = g[v][i];
      if(disc[u] == 0){
	dfs(u);
	low[v] = min(low[v], low[u]);
      }else if(onstack[u]){
	low[v] = min(low[v], disc[u]);
      }
    }
    if(low[v] == disc[v]){
      while(1){
	int w = S.top(); S.pop();
	onstack[w] = false;
	if(v == w) break;
      }
    }
  }

  int decomp(){
    for(int i = 0; i < V; i++){
      if(disc[i] == 0) dfs(i);
    }
    
    for(int i = 0; i < V; i++){
      cout << i << " " << disc[i] << " " << low[i] << endl;
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
