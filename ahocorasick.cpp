#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const short A = 256;

// Represents a node in the AC-automaton. Contains information about its
// children and its fail link.
struct Node {
	Node* children[A];
	unsigned char letter;
	Node* fail = NULL;

	Node(unsigned char c) {
		letter = c;
		for(int i = 0; i < A; i++) {
			children[i] = 0;
		}
	}

	Node* addChild(unsigned char c) {
		if (!children[c])	children[c] = new Node(c);
		return children[c];
	}
};

// Represents the nodes in the AC-automaton that are accepting states,
// contains the corresponding strings for each one
unordered_map<Node*, vector<string>> accept_states;
Node* root = new Node('a');

//Output matches of patterns and their positions in text
vector<pair<ll,ll>> findPattern(string& text) {
	vector<pair<ll,ll>> output;
	Node* v = root;

	for (int i = 0; i < text.length(); i++) {
		const unsigned char key = text[i];
		while (!v->children[key]) v = v->fail;
		v = v->children[key];
		if (accept_states.find(v) != accept_states.end()) {
			for (const string& a : accept_states[v]) {
				output.push_back({i-a.size()+1, a.size()});
			}
		}
	}
	return output;
}

// Build AC-automaton fail function
void buildFailFunction() {
	Node* fallback = new Node('s');

	for(int i = 0; i < A; i++) {
		fallback->children[i] = root;
	}
	root->fail = fallback;

	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* u = q.front();
		q.pop();

		for(int c = 0; c < A; c++) {
			Node* v = u->children[c];
			if (!v) continue;
			Node* w = u->fail;

			while(!w->children[c]) w = w->fail;
			v->fail = w->children[c];

			for (auto& p : accept_states[v->fail]) {
				accept_states[v].push_back(p);
			}
			q.push(v);
		}
	}
}

//Add string s to the AC-automaton / trie
void addWord(string s) {
	Node* parent = root;
	for(int i = 0; i < s.length(); i++) parent = parent->addChild(s[i]);
	accept_states[parent].push_back(s);
}

// Build the AC-automaton / trie
void buildTrie(vector<string> patterns) {
	for (int i = 0; i < A; i++) root->addChild(i);
	for (auto& a : patterns) addWord(a);
}

// Run preprocessing required for AC: build trie and fail function of patterns
void preprocess_ac(vector<string> patterns) {
	buildTrie(patterns);
	buildFailFunction();
}
