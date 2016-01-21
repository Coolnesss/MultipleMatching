#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define A 27 

void buildTrie(vector<string> patterns);

struct Node {
	unordered_map<char, Node*> children;
	char letter;
	
	Node(char c) {
		letter = c;
	}
	
	Node* addChild(char c) {
		assert(c-'a' < A);
		assert(c-'a' >= 0);
		
		if (!children.count(c))	children.insert({c, new Node(c)});
		
		return children[c];
	}
};


Node root('a');

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	vector<string> kek = {"asd","dfgg", "kek"};
	buildTrie(kek);
	
	
	
}

//Output matches of patterns and their positions in text 
void find(string text, vector<string> patterns) {
	
	
	
}

void buildFailFunction() {
	Node* fallback = new Node();
	
}

//Add string s to trie
void addWord(string s) {
	Node* parent = root.children[s[0]];
	
	for(int i = 1; i < s.length(); i++) {
		parent = parent->addChild(s[i]);
	}
}

void buildTrie(vector<string> patterns) {	
	for (int i = 0; i < A; i++) {
		root.addChild(i + 'a');
	}
	for (auto& a : patterns) {
		addWord(a);
	}				
} 