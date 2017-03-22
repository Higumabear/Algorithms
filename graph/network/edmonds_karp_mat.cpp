#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1 << 29;

int V, E;
int flow[200][200], cap[200][200];

int max_flow(int s, int t){
  int prev[200];  
  int maxflow = 0;

  while(1){
    fill(prev, prev + 200, -1);

    queue<int> Q;
    Q.push(s);
    prev[s] = s;
    while(!Q.empty()){
      int u = Q.front(); Q.pop();
      if(u == t) break;
      for(int v = 0; v < V; v++){
	if(prev[v] == -1 && cap[u][v] - flow[u][v] > 0){
	  prev[v] = u;
	  Q.push(v);
	}
      }
    }
    if(prev[t] == -1) break;
    
    int minaug = INF;
    for(int v = t; prev[v] != v; v = prev[v])
      minaug = min(minaug, cap[prev[v]][v] - flow[prev[v]][v]);
    for(int v = t; prev[v] != v; v = prev[v])
      flow[prev[v]][v] += minaug, flow[v][prev[v]] -= minaug; 
    maxflow += minaug;
  }
  return maxflow;
}

int main(){
  memset(cap, 0, sizeof(cap));
  memset(flow, 0, sizeof(flow));

  scanf("%d %d", &V, &E);
  for(int i = 0; i < E; i++){
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    cap[u][v] += c;
  }
  printf("%d\n", max_flow(0, V - 1));
}
