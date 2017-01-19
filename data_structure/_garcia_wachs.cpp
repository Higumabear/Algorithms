#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
using namespace std;

struct node{
  node *l, *r;
  ll w;
  node(ll w, node *l = 0, node *r = 0) : w(w), l(l), r(r) {}
  bool operator>(node *r) const {return w > r->w;}
} *root;

void garsia_wachs(int *w, int N){
  priority_queue<node*, vector<node*>, greater<node*> > q;
  for(int i = N - 1; i >= 0; i--){
    if(i >= 2 && w[i - 2] >= w[i]){
      q.push(new node(w[i - 1] + w[i], 
		      new node(w[i - 1]), new node(w[i])));
      i--;
    }else q.push(new node(w[i]));
  }
  while(q.size() > 1){
    node *a = q.top(); q.pop();
    node *b = q.top(); q.pop();
    q.push(new node(a->w + b->w, a, b));
  }
  root = q.top();
}

ll find(node *p, int depth = 0){
  if(!p) return 0;
  if(!p->l && !p->r) return depth * p->w;
  return find(p->l, depth + 1) + find(p->r, depth + 1);
}

int main(){
  int w[12] = {80,12,10,11,13,3,4,5,9,8,7,25};
  garsia_wachs(w, 12);
  cout << root->w << endl;
  cout << find(root, 0) << endl;
}
