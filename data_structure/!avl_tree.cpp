#include <vector>
#include <stddef.h>

using namespace std;

template <typename T> class AVL{
  struct node{
    T key;
    int height;
    node *l, *r;
    node(T &key) : key(key), height(1), l(NULL), r(NULL) {}
  } *root;

  int ht(node *x) { return x ? x->height : 0; }
  void fixht(node *x) { x->height = max(ht(x->l), ht(x->r)) + 1; }

  node *rrot(node *x){
    node *y = x->l;
    x->l = y->r;
    y->r = x;
    fixht(x), fixht(y);
    return y;
  }
  node lrot(node *x){
    node *y = x->r;
    x->r = y->l;
    y->l = x;
    fixht(x), fixht(y);
    return y;
  }
  node *balance(node *x){
    fixht(x);
    if(ht(x->r) - ht(x->l) == 2){
      if(ht(x->r->r) - ht(x->r->l) < 0) x->r = rrot(x->r);
      return lrot(x);
    }
    if(ht(x->r) - ht(x->l) == -2){
      if(ht(x->l->r) - ht(x->l->l) > 0) x->l = lrot(x->l);
      return rrot(x);
    }
    return x;
  }
public:
  AVL() : root(NULL) {};
  node *insert(node *x, const T &key){
    if(!x) return new node(key);
    if(key < x->key) x->l = insert(x->l, key);
    else             x->r = insert(x->r, key);
    return balance(x);
  }
  node *findmin(node *x) { return x->l ? findmin(x->l) : x; }
  node *removemin(node *x){
    if(!x->l) return x->r;
    x->l = removemin(x->l);
    return balance(x);
  }
  node *remove(node *x, const T &key){
    if(!x) return NULL;
    if(key < x->key)      x->l = remove(x->l, key);
    else if(key > x->key) x->r = remove(x->r, key);    
    else{
      node *q = x->l;
      node *r = x->r;
      delete x;
      if(!r) return q;
      node *min = findmin(r);
      min->r = removemin(r);
      min->l = q;
      return balance(min);
    }
    return balance(x);
  }
};
