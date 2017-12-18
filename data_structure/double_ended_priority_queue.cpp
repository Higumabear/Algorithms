/*

  Double-Ended Priority Queue

  Implementation of 
  https://topcoder.g.hatena.ne.jp/spaghetti_source/20121006#c1349522933

  Complexity: 
  amortized O(log n)

  Verified : 
  http://poj.org/problem?id=3481

 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class DoubleEndedPQ{
public:
  DoubleEndedPQ(): sz(0) {}
  const T &min(){
    erase_mintop();
    return minheap.top();
  }

  const T &max(){
    erase_maxtop();
    return maxheap.top();
  }
  
  void push(const T &x){
    maxheap.push(x);
    minheap.push(x);
    sz++;
  }

  void minpop(){
    erase_mintop();
    aux_maxheap.push(minheap.top());
    minheap.pop();
    sz--;
  }
  void maxpop(){
    erase_maxtop();
    aux_minheap.push(maxheap.top());
    maxheap.pop();
    sz--;
  }

  size_t size() { return sz; }
  bool empty() { return sz == 0; }
  
private:
  size_t sz;
  priority_queue<T> maxheap, aux_maxheap;
  priority_queue<T, vector<T>, greater<T> > minheap, aux_minheap;

  void erase_mintop(){
    while(!aux_minheap.empty() &&
	  minheap.top() == aux_minheap.top()){
      minheap.pop(); aux_minheap.pop();
    } 
  }
  void erase_maxtop(){
    while(!aux_maxheap.empty() &&
	  maxheap.top() == aux_maxheap.top()){
      maxheap.pop(); aux_maxheap.pop();
    } 
  }
};

int main(){
  DoubleEndedPQ<int> pq;

  pq.push(10);
  pq.push(20);
  pq.push(0);

  cout << pq.min() << endl; // 0
  pq.minpop();
  cout << pq.max() << endl; // 20
  pq.maxpop();
  cout << pq.max() << endl; // 10
  pq.maxpop();
  return 0;
}
