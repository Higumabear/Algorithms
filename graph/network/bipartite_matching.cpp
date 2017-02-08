/*
  Bipartite matching

  Complexity:
  O(V(V + E))

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
const int INF = 1 << 29;

vector<vector<int> > G; //bidirection

bool augment(int u, 
	     vector<int> &match, vector<bool> &vis){
  vis[u] = true;
  for(int i = 0; i < G[u].size(); i++){
    int v = G[u][i], w = match[v];
    if(w == -1 || (!vis[w] && augment(w, match, vis))){
      match[u] = v, match[v] = u;
      return true;
    }
  }
  return false;
}

int bipartite_matching(){
  int V = G.size(), ret = 0;
  vector<int> match(V, -1);
  for(int i = 0; i < V; i++){
    if(match[i] != -1) continue;
    vector<bool> vis(V, false);
    if(augment(i, match, vis)) ret++;
  }
  return ret;
}

int main(){
  int X, Y, E;
  cin >> X >> Y >> E;
  G.resize(X + Y);

  int s, t;
  while(E--){
    cin >> s >> t;
    G[s].push_back(X + t);
    G[X + t].push_back(s);
  }
  cout << bipartite_matching() << endl;
  return 0;
}
