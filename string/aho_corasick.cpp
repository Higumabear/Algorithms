#include <string>
#include <queue>
#include <iostream>

using namespace std;

class AhoCorasick{
public:
  AhoCorasick(const vector<string> &pat) : pattern(pat) { build(pat); };
  ~AhoCorasick(){};
  void build(const vector<string> &pat) {
    root = new trie();
    for(int i = 0; i < (int)pat.size(); i++){
      trie *v = root;
      for(int j = 0; j < (int)pat[i].length(); j++){
	int c = pat[i][j];
	if(v->node[c] == NULL) v->node[c] = new trie();
	v = v->node[c];
      }
      v->matched_pat.push_back(i);
    }
    
    queue<trie*> Q;
    for(int i = 0; i < 0x100; i++){
      if(root->node[i] == NULL) root->node[i] = root; //rootから出ていない文字はrootにもどす
      else{
	root->node[i]->fail = root;//root直下のノードのfail先はrootにする
	Q.push(root->node[i]);
      }
    }
    while(!Q.empty()){
      trie *cur = Q.front(); Q.pop();
      for(int c = 0; c < 0x100; c++){
	trie *next = cur->node[c];
	if(next == NULL) continue;
	Q.push(next);
	
	trie *curfail = cur->fail;
	while(curfail->node[c] == NULL) curfail = curfail->fail;
	next->fail = curfail->node[c];//子ノードのfail先は自ノードのfail先のぶら下がるノード
      }
    }
  }

  vector<pair<int, int>> match(string s){
    int L = s.length();
    trie *v = root;

    vector<pair<int, int>> ans;
    for(int i = 0; i < L; i++){
      int c = s[i];
      while(v->node[c] == NULL) v = v->fail;
      v = v->node[c];
      for(int j = 0; j < v->matched_pat.size(); j++)
	ans.push_back(make_pair(v->matched_pat[j], i + 1 - pattern[j].length()));
    }
    return ans;
  }
private:
  struct trie{
    trie *node[0x100];
    trie *fail;
    vector<int> matched_pat;
    trie(){ fill(node, node + 0x100, (trie*)0); }
  };
  trie *root;
  const vector<string> &pattern;
};


int main(){
  vector<string> pat;
  pat.push_back("ab");
  pat.push_back("br");  
  pat.push_back("cad");
  pat.push_back("ra");

  AhoCorasick ac(pat);
  string g; cin >> g;
  auto u = ac.match(g);
  for(auto v : u){
    cout << pat[v.first] << " " << v.second << endl;
  }
}
