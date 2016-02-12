#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#include "karprabin.h"
#include "ahocorasick.h"

string text;
vector<string> random_patterns;
vector<pair<ll,ll>> positions;

const ll PATTERN_LENGTH_MAX = 500;
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
		ll b = rand() % (text.length() - PATTERN_LENGTH_MAX - 1);
		random_patterns.push_back(text.substr(b, 200+(PATTERN_LENGTH_MAX)));
	}
}

void run_brute() {
	for (string& sub : random_patterns) {
		ll pos = text.find(sub, 0);
		pair<ll,ll> match = {pos, sub.length()};
		while(pos != string::npos) {
			positions.push_back({pos,sub.length()});
			pos = text.find(sub,pos+1);
		}
	}
}

void test_AC_with_english() {
	preprocess_ac(random_patterns);
	vector<pair<ll,ll>> output = findPattern(text);
	sort(positions.begin(), positions.end());
	sort(output.begin(), output.end());

	if (output != positions) cout << "AC FAIL" << endl;
	cout << "Aho Corasick found " << output.size() << " matches" << endl;
}

void test_KR_with_english() {
	preprocess_KR(random_patterns, text);
	vector<pair<ll,ll>> output = findPatterns(text, random_patterns);

	sort(positions.begin(), positions.end());
	sort(output.begin(), output.end());

	if (output != positions) cout << "KR FAIL" << endl;

	cout << "Karp-Rabin found " << output.size() << " matches" << endl;
}


int main() {
	load_text();
	load_random_patterns();
	cout << "Text and patterns loaded." << endl;
	run_brute();
	cout << "Brute force found " << positions.size() << " matches" << endl;
	test_AC_with_english();
	test_KR_with_english();
}
