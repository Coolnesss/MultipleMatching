#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define A 27

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

//Output matches of patterns and their positions in text
void findPattern(string text) {
	Node* v = root;
	for (int i = 0; i < text.length(); i++) {
		while (!v->children.count(text[i])) v = v->fail;
		v = v->children[text[i]];
		for (auto& a : patterns[v]) {
			cout << a << " found, ends at " << i << endl;
		}
	}
}




void buildFailFunction() {
	Node* fallback = new Node('s');

	for(int i = 0; i < A; i++) {
		fallback->children[i+'a'] = root;
	}
	root->fail = fallback;

	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* u = q.front();
		q.pop();

		for(auto& a : u->children) {
			char c = a.first;
			Node* v = a.second;
			Node* w = u->fail;

			while(!w->children.count(c)) w = w->fail;
			v->fail = w->children[c];

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

	if (patterns.count(parent)) {
		patterns[parent].insert(s);
	} else {
		set<string> pattern;
		pattern.insert(s);
		patterns[parent] = pattern;
	}
}

void buildTrie(vector<string> patterns) {
	for (int i = 0; i < A; i++) root->addChild(i + 'a');
	for (auto& a : patterns) addWord(a);
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << "Input text" << endl;
	string text;
	cin >> text;

	int n;
	cout << "How many words?" << endl;
	cin >> n;

	vector<string> matching;
	matching.resize(n);
	for (int i = 0; i < n; i++) {
		string x;
		cin >> x;
		matching[i] = x;
	}

	buildTrie(matching);
	buildFailFunction();
	findPattern(text);
}
