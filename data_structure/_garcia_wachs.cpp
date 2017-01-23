#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

typedef long long ll;
using namespace std;

struct garsia_wachs{
  struct node{
    ll w;
    node *l, *r;
    node(ll w, node *l = 0, node *r = 0) : w(w), l(l), r(r) {}
  } *root;
  struct nodecmp{
    bool operator()(const node *x, const node *y) const {return x->w > y->w;}
  };
  priority_queue<node*, vector<node*>, nodecmp> q;

  garsia_wachs(const vector<ll> &w) { build(w); }
  
  // void build(const vector<ll> &w){
  //   int N = w.size();
  //   for(int i = N - 1; i >= 0; i--){
  //     if(i >= 2 && w[i - 2] >= w[i]){
  // 	q.push(new node(w[i - 1] + w[i], 
  // 			new node(w[i - 1]), new node(w[i])));
  // 	i--;
  //     }
  //     else q.push(new node(w[i]));
  //   }
  //   while(q.size() > 1){
  //     node *a = q.top(); q.pop();
  //     node *b = q.top(); q.pop();
  //     q.push(new node(a->w + b->w, b, a));
  //   }
  //   root = q.top();
  // }
  void build(const vector<ll> &w){
    int N = w.size();
    q.push(new node(w[N - 1]));
    for(int i = N - 1; i >= 1; i--){
      node* w_i = q.top(); //w[i]
      
      if((i == 1 && w[i - 1] >= w_i->w) || (i >= 2 && w[i - 2] >= w_i->w)){
	cout << w[i - 1] << " " << w_i->w << endl;
	q.pop();
  	q.push(new node(w[i - 1] + w_i->w, 
  			new node(w[i - 1]), w_i));
  	//i--;
      }
      else{
      	cout << w[i - 1] << endl;
      	q.push(new node(w[i - 1]));	
      }
    }
    while(q.size() > 1){
      node *a = q.top(); q.pop();
      node *b = q.top(); q.pop();
      q.push(new node(a->w + b->w, b, a));
    }
    root = q.top();
  }


  ll mincost(){ return mincost(root, 0); }
  ll mincost(node *p, int depth){
    if(!p) return 0;
    if(!p->l && !p->r) return depth * p->w;
    return mincost(p->l, depth + 1) + mincost(p->r, depth + 1);
  }
  void debug(){ dbg(root, root, 0); }
   void dbg(node *p, node *par, int depth){
    if(!p) return ;
    cout << par->w << " -> " << p->w << " [ label = " << depth << " ];" << endl;
    if(!p->l && !p->r) return;
    dbg(p->l, p, depth + 1);
    dbg(p->r, p, depth + 1);
    return ;
  }
};

int main(){
  int n;
  cin >> n;
  vector<ll> weight(n);
  for(int i = 0; i < n; i++) cin >> weight[i];

  garsia_wachs gw(weight);
  cout << gw.mincost() << endl;
  gw.debug();
}
