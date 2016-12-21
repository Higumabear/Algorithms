#include <vector>

using namespace std;

template <typename T> class AVL{
  struct node{
    T val;
    int height;
    node *l, *r;
    node(T &val) : val(val), height(1) : { l = r = NULL; }
  } *root;
  AVL() : root(NULL) {};
  node *find(T key){ return find(root, key); }
  node *find(node *t, T key){
    if(t == NULL) return NULL;
    if(t->val == key) return t;
    return (t->val > key) ? find(t->l, key) : find(t->r, key);
  }
  node *insert(T key){ return insert(root, new node(key)); }
  node *insert(node *t, node *x){ 
    if(t == NULL) return x;
    if(t->val >= x->val) t->l = insert(t->l, x);
    else t->r = insert(t->r, x);
    t->height++;
    return balance(t);
  }
  node *balance(node *t){
    int lh = t->l ? t->l->height : 0;
    int rh = t->r ? t->r->height : 0;
    if(lh - rh >= 2){
      int llh = t->l->l ? t->l->l->height : 0;
      int lrh = t->l->r ? t->l->r->height : 0;
    }
    if(rh - lh >= 2){

    }
    if(t) t->height = max(t->l->height);
  }
};
