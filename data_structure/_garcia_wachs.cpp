#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
using namespace std;

struct node{
  node *l, *r;
  ll w;
  node(ll w) : w(w), l(0), r(0) {}
  bool operator>(node *r) const {return w > r->w;}
};

ll garsia_wachs(int *w, int N){
  priority_queue<node*, vector<node*>, greater<node*> > q;
  
  for(int i = N - 1; i >= 0; i--){
    if(i >= 2 && w[i - 2] >= w[i]){
      q.push(node(w[i] + w[i - 1]));
      i--;
    }else q.push(node(w[i]));
  }
  while(q.size() > 1){
    int w_new = q.top().w; q.pop();
    w_new += q.top().w; q.pop();
    q.push(new node(w_new));
  }
  return q.top().w;
}

int main(){
  int w[12] = {80,12,10,11,13,3,4,5,9,8,7,25};
  cout << garsia_wachs(w, 12) << endl;
}
