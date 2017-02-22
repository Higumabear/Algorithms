/*
  Topological Sort (lexically smallest)

  Complexity:
  DFS ver : O(E)
  adjacency mat : O(V^3)

  Verified:
  
 */

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// vector<int> topological(vector<vector<bool> > &E){
//   int n = (int)E.size();
//   vector<bool> V(n);
//   vector<int> R;
//   for(int i = 0; i < n; i++){
//     int c = -1;
//     for(int j = 0; j < n &&c == -1; j++)if(!V[j]){
// 	bool f = true;
// 	for(int k = 0; k < n && f; k++)
// 	  if (!V[k] && E[k][j])
// 	    f = false;
// 	if(f) c = j;
//       }
//     if(c == -1)
//       return vector<int>();
//     V[c] = true;
//     R.push_back(c);
//   }
//   return R;
// }

vector<int> tsort(const vector<vector<bool> > &g){
  int V = g.size();
  vector<int> ret;
  vector<bool> vis(V, false);
  for(int i = 0; i < V; i++){
    int c = -1;
    for(int u = 0; u < V; u++){
      if(vis[u]) continue;
      bool f = true;
      for(int v = 0; v < V; v++)
	if(!vis[v] && g[v][u]) f = false;
      if(f){
	c = u;
	break;
      }
    }
    if(c == -1) return vector<int>();
    vis[c] = true;
    ret.push_back(c);
  }
  return ret;
}

int main(){
  int N;
  cin >> N;
  while(N--){
    int V, E;
    cin >> V >> E;
    vector<vector<bool> > g(V, vector<bool>(V, false));
    for(int i = 0; i < E; i++){
      int s, t;
      cin >> s >> t;
      s--, t--;
      g[s][t] = true;
    }
    vector<int> ord = tsort(g);
    for(int i = 0; i < ord.size(); i++)
      cout << ord[i] << " ";
    cout << endl;
  }
}
