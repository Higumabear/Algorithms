#include <vector>
#include <stddef.h>

using namespace std;

template <typename T> class splay_tree{
  struct node{
    T key;
    node *l, *r, *par;
    node(const T &key = 0, node *par = 0, node *l = 0, node *r = 0) : 
      key(key), l(l), r(r), par(par) {}
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
    if(y) y->r = x;
    x->par = y;
  }
  void splay(node *x){
    while(1){
      node *p = x->par; 
      if(!p) break;
      node *pp = p->par;
      if(!pp){
	if(p->l == x) rrot(p);
	else lrot(p);
      }
      else if(p->l == x && pp->l == p) rrot(pp), rrot(p);
      else if(p->r == x && pp->l == p) lrot(p), rrot(pp);
      else if(p->l == x && pp->r == p) rrot(p), lrot(pp);
      else if(p->r == x && pp->r == p) lrot(pp), lrot(p);
    }
  }
public:
  splay_tree() : root(NULL) {};
  void insert(const T &key){
    if(!root) root = new node(key);
    else{
      node *p = root;
      while(1){
	if(p->key == key) break;
	if(p->key > key){
	  if(!p->l){
	    p->l = new node(key, p);
	    break;
	  }
	  p = p->l;
	}else{
	  if(!p->r){
	    p->r = new node(key, p);
	    break;
	  }
	  p = p->r;
	}
      }
      splay(p);
    }
  }
  node *find(const T &key){
    node *x = root;
    while(x && x->key != key) x = (x->key > key) ? x->l : x->r;
    return x;
  }
  bool erase(const T &key){
    node *z;
    if(!(z = find(key))) return false;
    splay(z);
    node *p = z->l;
    if(!p){
      root = z->r; root->par = NULL;
      delete z;
      return true;
    }
    while(p->r) p = p->r;
    if(z->r) p->r = z->r, z->r->p = p;
    root = z->l, root->p = NULL;
    delete z;
    return true;
  }
};

int main(){
  int d[10] = {22,3,45,23,56,6,85,0,5,321};
  splay_tree<int> tree;
  for(int i = 0; i < 10; i++) tree.insert(d[i]);
}
