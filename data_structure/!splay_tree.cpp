#include <vector>

using namespace std;

template <typename T> class splay{
  struct node{
    T val;
    node *l, *r, *par;
    node(const T &val = 0, node *par = 0, node *l = 0, node *r = 0) : val(val), l(l), r(r), par(par) {}
  } *root;
  splay() : root(NULL) {};
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
    node *granpa = x->par->par;
    node *father = x->par;
    while(father){
      if(!granpa){
	if(father->left == x) rrot(father);
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
  // void insert(const T &key){ insert(root, key); };
  // void insert(node *t, const T &key){
  //   if(t == NULL) t = new node(key);
  //   else{
  //     root = splay();
  //     if(key < root->val)
  // 	node *t = new node(x, root->l, root); root->l; root = t;
  //     else
  // 	node *t = new node(x, root, root->r); root->r; root = t;
  //   }
  // }
public:
  void insert(const T &key){
    node *x = root;
    node *p = NULL;
    while(x || x->val != key){
      p = x;
      x = (x->val > key) ? x->l : x->r;
    }
    x = new node(key, par = p);
    if(!p) root = x;
    else if(p->val < x->val) p->r = x;
    else p->l = x;

    splay(z);
  }
  node *find(const T &key){
    // root = splay(key, root);
    // return root->val == key ? root : NULL;
    node *x = root;
    // while(x || x->val != key){
    //   if(x->val > key) x = x->l;
    //   else x = x->r;
    // }
    while(x || x->val != key) x = (x->val > key) ? x->l : x->r;
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
