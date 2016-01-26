#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define A 256

struct Node {
	Node* children[A];
	unsigned char letter;
	Node* fail = NULL;

	Node(unsigned char c) {
		letter = c;
		//cout << "lol" << endl;
		for(int i = 0; i < A; i++) {
			children[i] = 0;
		}
	}

	Node* addChild(unsigned char c) {
		if (!children[c])	children[c] = new Node(c);
		return children[c];
	}
};

unordered_map<Node*, set<string>> patterns;
Node* root = new Node('a');

//Output matches of patterns and their positions in text
void findPattern(string& text) {
	ll matches = 0;
	Node* v = root;

	for (int i = 0; i < text.length(); i++) {
		const unsigned char key = text[i];
		while (!v->children[key]) v = v->fail;
		v = v->children[key];
		matches += patterns[v].size();
		//for (const auto& a : patterns[v]) {
			//matches++;
			//cout << a << " found, ends at " << i << '\n';
		//}
	}
	cout << "Found " << matches << " matches" << '\n';
}

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
	for (int i = 0; i < A; i++) root->addChild(i);
	for (auto& a : patterns) addWord(a);
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	ifstream in("english.50MB");
	stringstream buffer;
	buffer << in.rdbuf();
	string text = buffer.str();
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
	cout << "kek" << endl;
	findPattern(text);
}
