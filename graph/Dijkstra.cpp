/*
	verified : http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
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

void add_edge(int from, int to, int cost){//2way
  g[from].push_back(edge(from, to, cost));
}

//distに最短距離が入る。経路がない場合はINF。
//prev_nodeにそのノードの一つ前のノードが入る。
//idx == prev_node[idx] となったら始点
int prev_node[100100];
int dist[100100];
int dijkstra(vector<vector<edge> > g, int s, int t){
  int V = g.size();
  priority_queue<edge, vector<edge>, greater<edge> > Q;
  Q.push(edge(-2, s, 0));
  fill(dist, dist + 100100, INF);
  fill(prev_node, prev_node + 100100, -1);
  
  dist[s] = 0;
  while(!Q.empty()){
    edge e = Q.top(); Q.pop();
    if(prev_node[e.to] != -1) continue;

    prev_node[e.to] = e.from;
    for(int i = 0; i < g[e.to].size(); i++){
      edge f = g[e.to][i];
      if(dist[f.to] > dist[e.to] + f.cost){
	dist[f.to] = dist[e.to] + f.cost;
	Q.push(edge(f.from, f.to, f.cost + dist[e.to]));
      }
    }
  }  
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
