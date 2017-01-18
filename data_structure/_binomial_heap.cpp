#include <list>
#include <algorithm>

using namespace std;

template<class T> 
class binomial_heap{
  struct node{
    node *next;
    list<node*> child;
    T key;
    int degree;
    node(const T &key) : par(0), key(key), degree(0) {}
  }*inlet;
  
  binomial_heap() : inlet(0) {}

  T findmin(){
    T ret = 100;
    list<node*>::iterator it = forest.begin();
    for(; it != forest.end(); it++) ret = min<T>(ret, (*it)->key);
    return ret;
  }
  void insert(const T &key){
    if(!inlet) inlet = new node(key);
    else meld(new node(key), inlet);
  }
};
