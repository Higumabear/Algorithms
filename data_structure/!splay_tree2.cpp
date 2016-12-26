#include <vector>
#include <stddef.h>

using namespace std;

template <typename T> class splay_tree{
  struct node{
    T val;
    node *l, *r, *par;
    node(const T &val = 0, node *par = 0, node *l = 0, node *r = 0) : val(val), l(l), r(r), par(par) {}
  } *root;
  void lrot(node *x){
    node *y = x->r;
    if(y){
      x->r = y->l;
      if(y->l) y->l->par = x;
      y->par = x->par;
    }
    if(!x->par) root = y;
    else if(x == x->par->l) x->par->l = y;
    else x->par->r = y;
    if(y) y->l = x;
    x->par = y;
  }
  void rrot(node *x){
    node *y = x->l;
    if(y){
      x->l = y->r;
      if(y->r) y->r->par = x;
      y->par = x->par;
    }
    if(!x->par) root = y;
    else if(x == x->par->l) x->par->l = y;
    else x->par->r = y;
    if(y) y->l = x;
    x->par = y;
  }
  void replace(node *u, node *v){
    if(!u->par) root = v;
    else if(u == u->par->l) u->par->l = v;
    else u->par->r = v;
    if(v) v->par = u->par;
  }
  void splay(node *x){
    while(x->par){
      node *father = x->par;
      node *granpa = father->par;
      if(!father->par){
	if(father->l == x) rrot(father);
	else lrot(father);
      }else if(father->l == x && granpa->l == father)
	rrot(granpa), rrot(father);
      else if(father->r == x && granpa->r == father)
	lrot(granpa), lrot(father);
      else if(father->l == x && granpa->r == father)
	rrot(father), lrot(father);
      else
	lrot(father), rrot(father);
    }
  }
public:
  splay_tree() : root(NULL) {};
  void insert(const T &key){
    node *x = root;
    node *p = NULL;
    while(x && x->val != key){
      p = x;
      x = (x->val > key) ? x->l : x->r;
    }
    x = new node(key, p);
    if(!p) root = x;
    else if(p->val < x->val) p->r = x;
    else p->l = x;

    splay(x);
  }
  node *find(const T &key){
    node *x = root;
    while(x && x->val != key) x = (x->val > key) ? x->l : x->r;
    return x;
  }
  void erase(const T &key){
    node *z;
    if(!(z = find(key))) return;
    
    splay(z);
    if(!z->l) replace(z, z->r);
    else if(!z->r) replace(z, z->l);
    else{
      node *y = z->r;
      while(y->l) y = y->l;
      if(y->par == z){
	replace(y, y->r);
	y->r = z->r;
	y->r->par = y;
      }
      replace(z, y);
      y->l = z->l;
      y->l->par = y;
    }
    delete z;
  }
};

int main(){
  int d[10] = {22,3,45,23,56,6,85,0,5,321};
  splay_tree<int> tree;
  for(int i = 0; i < 10; i++) tree.insert(d[i]);
}
