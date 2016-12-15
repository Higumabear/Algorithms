#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

class aho_corasick{
public:
  aho_corasick(){ root = new trie(); }
  //~aho_corasick();
  void build(const vector<string> &pat){
    root->fail = root;
    for(int i = 0; i < pat.size(); i++){
      trie *cur = root;
      for(int j = 0; j < pat[i].size(); j++){
	char c = pat[i][j];
	if(cur->node[c] == NULL) cur->node[c] = new trie();
	cur = cur->node[c];
      }
      cur->idx.push_back(i);
    }
    queue<trie*> Q;
    Q.push(root);
    while(!Q.empty()){
      trie *cur = Q.front(); Q.pop();
      for(int i = 0; i < 0xff; i++){
	if(cur->node[i] == NULL) continue;
	Q.push(cur->node[i]);
	trie *tmp = cur->fail;
	while(tmp->node[i] == NULL && tmp != root) 
	  tmp = tmp->fail;
	cur->node[i]->fail = tmp;
      }
    }
  }
  map<int, vector<int> > match(const string &s){
    int L = s.size();
    trie *v = root;
    map<int, vector<int> > ans;
    for(int i = 0; i < L; i++){
      if(v->node[s[i]] == NULL) v = v->fail;
      v = v->node[s[i]];
      for(int k = 0; k < v->idx.size(); k++) 
	ans[v->idx[k]].push_back(i);
    }
    return ans;
  }
private:
  struct trie{
    trie *node[0xff], *fail;
    vector<int> idx;
    trie(){ fill(node, node + 0xff, (trie*)0); }
  };
  trie *root;
};
int main(){
  vector<string> s;
  s.push_back("abra"); 
  s.push_back("cad");
  s.push_back("abracad");
  s.push_back("bra");
  string text("abracadabraabracadabra");
  aho_corasick ac;
  ac.build(s);
  map<int, vector<int> > ans = ac.match(text);
  map<int, vector<int> >::iterator it = ans.begin();
  for(; it != ans.end(); it++){
    cout << "[ " << s[it->first] << " ] \t";
    for(int i = 0; i < it->second.size(); i++)
      cout << it->second[i] << " ";
    cout << endl;
  }
}
