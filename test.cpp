#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#include "karprabin.h"
#include "ahocorasick.h"


// Search for 1000 length 1000 patterns that are randomly selected from text.
// Compare with brute force
void test_ac_with_english() {
	ifstream in("test");
	stringstream buffer;
	buffer << in.rdbuf();
	string text = buffer.str();

	vector<string> patterns;

	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		ll b = rand() % (text.length()-1000);
		patterns.push_back(text.substr(b, 100));
	}

	vector<ll> positions;

	for (string sub : patterns) {
		ll pos = text.find(sub, 0);
		while(pos != string::npos) {
			positions.push_back(pos);
			pos = text.find(sub,pos+1);
		}
	}

	preprocess_ac(patterns);
	vector<pair<ll,ll>> aho_corasick_output = findPattern(text);

	for (ll occ : positions) {
		bool ok = false;
		for (pair<ll,ll> ac_occ : aho_corasick_output) {
			if (occ == ac_occ.first) ok = true;
		}
			if (ok) cout << "FAIL, couldn't find " << occ << " from AC output" << endl;
	}

	cout << "Aho Corasick found " << aho_corasick_output.size() << " matches" << '\n';
	cout << "Brute force found " << positions.size() << " matches" << endl;
}

int main() {
	test_ac_with_english();
}
