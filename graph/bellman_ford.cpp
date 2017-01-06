/*
  Bellman-Ford 
  shortest path problem & negative cost circle path checker

  Complexity:
  O(nm) 
  n : number of vertices
  m : number of edges 
  
  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
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
const int INF = (1 << 31) - 1;

struct edge{
  int from, to, cost;
  edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
  bool operator<(const edge &r) const{ return cost < r.cost; }
  bool operator>(const edge &r) const{ return cost > r.cost; }
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
int bellman_ford(vector<vector<edge> > g, int s, int t){
  int V = g.size();
  fill(dist, dist + 100100, INF);
  fill(prev_node, prev_node + 100100, -1);
  
  bool update;
  dist[s] = 0;
  prev_node[s] = s;
  for(int i = 0; i < V; i++){
    update = false;
    for(int j = 0; j < V; j++){
      for(int k = 0; k < g[j].size(); k++){
	int from = j, to = g[j][k].to, cost = g[j][k].cost;
	if(dist[to] > dist[from] + cost){
	  dist[to] = dist[from] + cost;
	  prev_node[to] = from;
	  update = true;
	}
      }
    }
  }
  if(update) return -INF; 
  return dist[t];
}

int main(int argc, char **argv){
  int V, E, r;
  scanf("%d %d %d", &V, &E, &r);

  g.resize(V);
  for(int i = 0; i < E; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    add_edge(a, b, c);
  }
  dijkstra(g, r, 0);
  for(int i = 0; i < V; i++){
    if(dist[i] == INF) printf("INF\n");
    else printf("%d\n", dist[i]);
  }
}
