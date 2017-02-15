/*
  Strongly connected componets decomposition
  
  Complexity:
  O(V + E)

  Verified:

 */

#include <iostream>
#include <vector

using namespace std;

struct scc{
  int V, c;
  vector<vector<int> > g;
  vector<int> idx;
  scc(int V) : V(V), g(V), idx(V, -1), c(0) {}
  
  void dfs(int i){
    for(int j = 0; j < g[i].size(); j++)
      if(idx[g[i][j]] != -1) dfs(g[i][j]);
    idx[i] = c++;
  }
};
