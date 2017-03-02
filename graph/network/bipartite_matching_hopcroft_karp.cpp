/*
  Bipartite matching (Hopcroft-Karp)

  Complexity:
  O(sqrt(V) * (V + E))

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
 
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1 << 29;

struct hopcroft_karp{
  int L, R, NIL, matching;
  vector<vector<int> > adj;
  vector<int> level, match;

  hopcroft_karp(int L, int R) : 
    L(L), R(R), adj(L + R), NIL(L + R), 
    level(L + R + 1), match(L + R + 1), matching(0) {}
  
  void add_edge(int from, int to){
    adj[from].push_back(L + to);
    adj[L + to].push_back(from);
  }
  
  bool dfs(int u){
    if(u == NIL) return true;
    for(int i = 0; i < adj[u].size(); i++){
      int v = adj[u][i];
      if(level[match[v]] == level[u] + 1){
	if(dfs(match[v])){
	  match[v] = u;
	  match[u] = v;
	  return true;
	}
      }
    }
    level[u] = INF;
    return false;
  }
  
  /* Construct vertex disjoint level graph */
  bool bfs(){
    fill(level.begin(), level.end(), INF);

    queue<int> Q; //enqueue disjoint vertices in L
    for(int i = 0; i < L; i++){
      if(match[i] != NIL) continue;
      Q.push(i);
      level[i] = 0;
    }

    while(!Q.empty()){
      int u = Q.front(); Q.pop();
      if(level[u] < level[NIL]){
	for(int i = 0; i < adj[u].size(); i++){
	  int v = adj[u][i];
	  if(level[match[v]] != INF) continue;
	  level[match[v]] = level[u] + 1;
	  Q.push(match[v]);
	}
      }
    }
    /* check whether vertex-disjoint augmenting path exists */
    return level[NIL] != INF ;
  }

  int bipartite_matching(){
    fill(match.begin(), match.end(), NIL);
    while(bfs()) /* while vertex-disjoint augmenting path exists */
      for(int u = 0; u < L; u++)
	if(match[u] == NIL)
	  matching += dfs(u);
    return matching;
  }
};

int main(){
  int X, Y, E;
  cin >> X >> Y >> E;
  
  hopcroft_karp bm(X, Y);
  for(int i = 0; i < E; i++){
    int s, t;
    cin >> s >> t;
    bm.add_edge(s, t);
  }
  cout << bm.bipartite_matching() << endl;
}
