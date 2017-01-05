/*
  Leftist heap
  
 */
#include<iostream>
using namespace std;

class leftist_heap{
  struct node{
    int key, rank;
    node *l, *r;
    node(int key) : key(key), rank(1), l(0), r(0) {}
  }*root;

  node *meld(node *a, node *b){
    if(!a && !b) return 0x0;
    if(!a) return b; if(!b) return a;
    if(a->key > b->key) swap(a, b);
    a->r = meld(a->r, b);
    if(!a->l || a->l->rank < a->r->rank) swap(a->l, a->r);
    a->rank = (!a->r ? 0 : a->r->rank) + 1;
    return a;
  }
public:
  void push(int key){ root = meld(new node(key), root); }
  int pop(){
    if(!root) return 1145141919;
    int ret = root->key;
    node *t = root;
    root = meld(t->l, t->r);
    delete t;
    return ret;
  }
  leftist_heap() : root(0) {}
};

int dat[10] = {21, 1, 6, 90, 3, 4, 73, 40, 30, 8};
int main(){
  leftist_heap lh;
  for(int i = 0; i < 10; i++) lh.push(dat[i]);
  for(int i = 0; i < 12; i++) cout << lh.pop() << endl;
}
