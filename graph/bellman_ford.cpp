/*
  Bellman-Ford 
  shortest path problem & negative cost cycle path checker

  Complexity:
  O(nm) 
  n : number of vertices
  m : number of edges 
  
  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

typedef long long ll;
const int INF = (1 << 30) - 1;

struct edge{
  int from, to, cost;
  edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

vector<vector<edge> > g;

void add_edge(int from, int to, int cost){
  g[from].push_back(edge(from, to, cost));
}

//distに最短距離が入る。経路がない場合はINF。負閉路を含む場合は-INF
//prev_nodeにそのノードの一つ前のノードが入る。
//idx == prev_node[idx] となったら始点
int prev_node[100100];
int dist[100100];
int bellman_ford(const vector<vector<edge> > &g, int s, int t){
  int V = g.size();
  fill(dist, dist + 100100, INF);
  fill(prev_node, prev_node + 100100, -1);
  
  dist[s] = 0;
  prev_node[s] = s;
  for(int i = 0; i < V; i++){
    bool update = false;
    for(int j = 0; j < V; j++){
      for(int k = 0; k < g[j].size(); k++){
	edge e = g[j][k];
	if(dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost){
	  dist[e.to] = dist[e.from] + e.cost;
	  prev_node[e.to] = e.from;
	  update = true;
	}
      }
    }
    if(update && i == V - 1) return -INF; 
  }
  return dist[t];
}

int main(int argc, char **argv){
  int V, E, r;
  scanf("%d %d %d", &V, &E, &r);
  fill(dist, dist + 100100, INF);

  g.resize(V);
  for(int i = 0; i < E; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    add_edge(a, b, c);
  }
  int v = bellman_ford(g, r, 0);
  if(v == -INF) printf("NEGATIVE CYCLE\n");
  else{
    for(int i = 0; i < V; i++){
      if(dist[i] == INF) printf("INF\n");
      else printf("%d\n", dist[i]);
    }
  }
}
