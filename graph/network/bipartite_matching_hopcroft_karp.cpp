#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1 << 29;

struct hopcroft_karp{
  int L, R;
  vector<vector<int> > adj;

  hopcroft_karp(int L, int R) : 
    L(L), R(R), adj(L + R) {}
  
  void add_edge(int from, int to){
    adj[from].push_back(L + to);
    adj[L + to].push_back(from);
  }
  
  int dfs(int idx){

  }

  int match(){
    vector<int> level(L + R, INF), match(L + R, -1);
    while(true){
      queue<int> Q;
      for(int i = 0; i < L; i++){
	if(match[i] != -1) continue;
	Q.push(i);
	level[i] = 0;
      }
      while(!Q.empty()){
	int v = Q.front(); Q.pop();
	for(int i = 0; i < adj[v].size(); i++){
	  int u = adj[v][i];
	  if(level[u] == INF) continue;
	  level[u] = level[v] + 1;
	  Q.push(u);
	}
      }
    }
  }
};
