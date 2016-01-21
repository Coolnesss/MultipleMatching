#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define A 27 


void buildFailFunction();
void buildTrie(vector<string> patterns);

struct Node {
	unordered_map<char, Node*> children;
	char letter;
	Node* fail = NULL;
	
	Node(char c) {
		letter = c;
	}
	
	Node* addChild(char c) {
		if (!children.count(c))	children.insert({c, new Node(c)});
		return children[c];
	}
};

unordered_map<Node*, set<string>> patterns;
Node* root = new Node('a');

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	vector<string> kek = {"asd","dfgg", "kek"};
	buildTrie(kek);
	buildFailFunction();
}

//Output matches of patterns and their positions in text 
void find(string text, vector<string> patterns) {
	
	
	
}

void buildFailFunction() {
	Node* fallback = new Node('s');
	
	for(int i = 0; i < A; i++) {
		fallback->children[i+'a'] = root;
	}
	
	queue<Node*> q;
	while (!q.empty()) {
		Node* u = q.front();
		q.pop();
		
		for(auto& a : u->children) {
			char c = a.first;
			Node* v = a.second;
			Node* w = u->fail;
			
			while(!w->children.count(c)) w = w->fail;
			v->fail = w->children[c];
		
			//patterns(v) = patterns(v) U patterns(fail(v)) ?? 
			for (auto& p : patterns[v->fail]) {
				patterns[v].insert(p);
			}
			q.push(v);
		}
	}
}

//Add string s to trie
void addWord(string s) {
	Node* parent = root;
	for(int i = 0; i < s.length(); i++) parent = parent->addChild(s[i]);
	set<string> pattern;
	if (patterns.count(parent)) pattern.insert(s);
	patterns.insert({parent, pattern});
}

void buildTrie(vector<string> patterns) {	
	for (int i = 0; i < A; i++) root->addChild(i + 'a');	
	for (auto& a : patterns) addWord(a);
} 