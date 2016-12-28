#include <vector>
#include <stddef.h>

using namespace std;

template <typename T> class splay_tree{
  struct node{
    T val;
    node *l, *r, *par;
    node(const T &val = 0, node *par = 0, node *l = 0, node *r = 0) : val(val), l(l), r(r), par(par) {}
  } *root;
  splay_tree() : root(NULL) {};

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
  node *find(node *x, const T &key){
    if(!x) return NULL;
    if(x->key == key){
      splay(x);
      return x;
    }
    return (x->key > key) ? find(x->l) : find(x->r);
  }
  node *insert(node *x, const T &key){
    
  }
};
