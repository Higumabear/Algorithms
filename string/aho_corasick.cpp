#include <string>
#include <queue>
#include <iostream>

using namespace std;

class AhoCorasick{
public:
  AhoCorasick(const vector<string> &pat);
  void build(const vector<string> &pat){
    root = new trie();
    fill(root->fail, root->fail + 0x100, (trie*)root);
    root->fail = root;
    
    queue<trie*> Q;
    Q.push(root);
    while(!Q.empty()){
      trie *cur = Q.front();
      Q.pop();
      
      for(int c = 0; c < 0x100; c++){
	trie *next = cur->node[c];
	if(next == NULL) continue;
	Q.push(next);
	
	trie *f = cur->fail;
	while(f != NULL) f = f->fail;
	next->fail = f->node[c];
      }
    }
  }
private:
  struct trie{
    trie *node[0x100];
    trie *fail;
    trie(){ fill(node, node + 0x100, (trie*)0); }
  };

  trie *root;
};
