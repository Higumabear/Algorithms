#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

using namespace std;

class aho_corasick{
public:
  aho_corasick(){ root = new trie(); }
  void build(const vector<string> &pattern){
    pat = pattern;
    root->fail = root;
    for(int i = 0; i < pat.size(); i++){
      trie *cur = root;
      for(int j = 0; j < pat[i].size(); j++){
	char c = pat[i][j];
	if(cur->node[c] == NULL) cur->node[c] = new trie();
	cur = cur->node[c];
      }
      //cur->match.insert(i);
      cur->match |= 1LL << i;
    }

    queue<trie*> Q;
    for(int i = 0; i < 0xff; i++) {
      if(root->node[i] != NULL){
	root->node[i]->fail = root;
	Q.push(root->node[i]);
      }else root->node[i] = root;
    }

    while(!Q.empty()){
      trie *cur = Q.front(); Q.pop();
      for(int i = 0; i < 0xff; i++){
	if(cur->node[i] == NULL) continue;
	Q.push(cur->node[i]);
	trie *r = cur->fail;
	while(r->node[i] == NULL) r = r->fail;
	// cur->node[i]->fail = r->node[i];
	// cur->node[i]->match.insert((r->node[i]->match).begin(),
	// 			   (r->node[i]->match).end());
	cur->node[i]->match |= (r->node[i]->match);
      }
    }
  }
  // map<int, vector<int> > match(const string &s){
  //   int L = s.size();
  //   trie *v = root;
  //   map<int, vector<int> > ans;
  //   for(int i = 0; i < L; i++){
  //     while(v->node[s[i]] == NULL) v = v->fail;
  //     v = v->node[s[i]];
  //     set<int>::iterator it = v->match.begin();
  //     for(; it != v->match.end(); it++) 
  // 	ans[*it].push_back(i - pat[*it].size() + 1);
  //   }
  //   return ans;
  // }
  vector<pair<int, long long> > search(const string &s){
    int L = s.size();
    trie *v = root;
    vector<pair<int, long long> > ans;
    for(int i = 0; i < L; i++){
      while(v->node[s[i]] == NULL) v = v->fail;
      v = v->node[s[i]];
      // set<int>::iterator it = v->match.begin();
      // for(; it != v->match.end(); it++) 
      // 	ans[*it].push_back(i - pat[*it].size() + 1);
      if(v->match != 0) 
	ans.push_back(make_pair(i, v->match));
    }
    return ans;
  }

private:
  struct trie{
    trie *node[0xff], *fail;
    long long match;
    trie(): match(0), fail(0) { fill(node, node + 0xff, (trie*)0); }
  };
  trie *root;
  vector<string> pat;
};

int main(){
  string text; cin >> text;

  int N;
  cin >> N;
  vector<string> s(N);
  for(int i = 0; i < N; i++) cin >> s[i];
  
  aho_corasick ac;
  ac.build(s);
  vector<pair<int, long long> > ret = ac.search(text);
  
  long long ans = 0;
  for(int i = 0; i < ret.size(); i++) 
    ans |= ret[i].second;

  for(int i = 0; i < N; i++)
    cout << (ans >> i & 1) << endl;
}
