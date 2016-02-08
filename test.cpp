#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#include "karprabin.h"
#include "ahocorasick.h"

string text;
vector<string> random_patterns;
vector<ll> positions;

const ll PATTERN_LENGTH = 500;
const ll PATTERN_AMOUNT = 2000;

void load_text() {
	ifstream in("test");
	stringstream buffer;
	buffer << in.rdbuf();
	text = buffer.str();
}

void load_random_patterns() {
	srand(time(NULL));
	for (int i = 0; i < PATTERN_AMOUNT; i++) {
		ll b = rand() % (text.length()-PATTERN_LENGTH-1);
		random_patterns.push_back(text.substr(b, PATTERN_LENGTH));
	}
}

void run_brute() {
	for (string& sub : random_patterns) {
		ll pos = text.find(sub, 0);
		while(pos != string::npos) {
			if (find(positions.begin(), positions.end(), pos) == positions.end()) positions.push_back(pos);
			pos = text.find(sub,pos+1);
		}
	}
}

void test_AC_with_english() {
	preprocess_ac(random_patterns);
	vector<pair<ll,ll>> output = findPattern(text);
	for (ll occ : positions) {
		bool ok = true;
		for (pair<ll,ll> ac_occ : output) {
			if (occ == ac_occ.first) ok = false;
		}
			if (ok) cout << "AC FAIL, couldn't find " << occ << " from AC output" << endl;
	}

	cout << "Aho Corasick found " << output.size() << " matches" << endl;
}

void test_KR_with_english() {
	preprocess_KR(random_patterns, text);
	vector<pair<ll,ll>> output = findPatterns(text, random_patterns);
	for (ll occ : positions) {
		bool ok = true;
		for (pair<ll,ll> kr_occ : output) {
			if (occ == kr_occ.first) ok = false;
		}
			if (ok) cout << "KR FAIL, couldn't find " << occ << " from KR output" << endl;
	}

	if (positions.size() != output.size()) {
		cout << "KR FAIL: too many matches" << endl;
	}
	cout << "Karp-Rabin found " << output.size() << " matches" << endl;
}


int main() {
	load_text();
	load_random_patterns();
	run_brute();
	test_AC_with_english();
	test_KR_with_english();
	cout << "Brute force found " << positions.size() << " matches" << endl;
}
