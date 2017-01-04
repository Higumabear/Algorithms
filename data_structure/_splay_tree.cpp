/*
  Splay tree (buttom-up ver)
  

*/

#include <vector>
#include <stddef.h>
#include <iostream>

using namespace std;

template <typename T> class splay_tree{
public:
  struct node{
    T key;
    node *l, *r, *par;
    node(const T key = 0, node *par = 0, node *l = 0, node *r = 0) : 
      key(key), l(l), r(r), par(par) {}
  } *root;

  node *rrot(node *x){
    node *y = x->l;
    x->l = y->r;
    y->r = x;
    return y;
  }
  node *lrot(node *x){
    node *y = x->r;
    x->r = y->l;
    y->l = x;
    return y;
  }
  void splay(node *x){
    node *y;
    if(!x->par) return;
    if(!x->par->par){/* zig */
      if(x->par->l == x){ y = rrot(x->par); }
      else              { y = lrot(x->par); }
    }else{
      if(x->par->l == x){
	if(x->par->par->l == x->par){ // zig-zig
	  rrot(x->par->par);
	  y = rrot(x->par);
	}else{ //zig-zag
	  rrot(x->par);
	  y = lrot(x->par);
	}
      }else{
	if(x->par->par->r == x->par){ // zig-zig
	  lrot(x->par->par);
	  y = lrot(x->par);
	}else{// zig-zag
	  lrot(x->par);
	  y = rrot(x->par);
	}
      }
    }
    splay(y);
  }
  splay_tree() : root(NULL) {};
  node *find(node *x, const T key){
    if(!x) return NULL;
    if(x->key == key){
      splay(x);
      return root;
    }
    return (x->key > key) ? find(x->l) : find(x->r);
  }
  node *find(const T key){
    node *p = root;
    while(p){
      if(p->key == key){
	splay(p);
	return root;
      }
      if(p->key > key) p = p->l;
      else p = p->r;
    }
    return NULL;
  }
  void insert(const T key){
    if(!root){
      root = new node(key);
      return;
    }
    node *p = root, *par = NULL;
    while(p){
      par = p;
      if(p->key > key) p = p->l;
      else p = p->r;
    }
    p = new node(key, par, NULL, NULL);
    if(par) (par->key > key ? par->l : par->r) = p;
    splay(p);
  }
  void func(node *x){
    if(!x) return;
    if(x->l){
      cerr << x->key << "->" << x->l->key << endl;
      func(x->l);
    }
    if(x->r){
      cerr << x->key << "->" << x->r->key << endl;
      func(x->r);
    }
  }
  void debug(){ func(root); }
};

int dat[10] = {1,3,5,2,7,6,10,848,238,12};

int main(){
  splay_tree<int> sp;
  for(int i = 0; i < 10; i++) sp.insert(dat[i]);
  cout << sp.root->key << endl;
  sp.debug();
}
