#include <vector>
#include <stddef.h>

using namespace std;

template <typename T> class splay{
  struct node{
    T val;
    node *l, *r, *par;
    node(const T &val = 0, node *par = 0, node *l = 0, node *r = 0) : val(val), l(l), r(r), par(par) {}
  } *root;
  splay() : root(NULL) {};

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
  
};
