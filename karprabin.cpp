#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll A = 999999997;
ll B = 999999991;

vector<ll> p;
vector<ll> x;
unordered_map<ll, unordered_map<ll, vector<ll>>> hashValues;

ll subsequence(ll a, ll b) {
	ll ret = p[b];
	if (a > 0) ret -= (p[a-1] * x[b-a+1]) % B;
	return (ret + B) % B;
}

void buildHashStructure(const string& text) {
	ll n = text.length();
	p.resize(n);
	x.resize(n);

	p[0] = text[0];
	x[0] = 1;

	for(ll i = 1; i < n; i++) {
		p[i] = ((p[i-1] * A) + text[i]) % B;
		x[i] = (x[i-1] * A) % B;
	}
}


void hashesWithLengths(const vector<string>& patterns) {
	ll index = 0;
	for (const string& s : patterns) {
		ll len = s.length();
		ll hash = 0;
		for(int i = 0; i < len; i++) {
			hash = hash * A + s[i];
			hash %= B;
		}
		hash = (hash += B) % B;

		hashValues[len][hash].push_back(index);
		index++;
	}
}

vector<pair<ll,ll>> findPatterns(const string& text, const vector<string>& patterns) {
	vector<pair<ll,ll>> output;

	for(ll i = 0; i < text.length(); i++) {
		for (auto& a : hashValues) {
			ll len = a.first;
			unordered_map<ll, vector<ll>>& hashes = a.second;
			ll hash = subsequence(i, i+len-1);

			if (hashes.count(hash) && !hashes[hash].empty()) {
				vector<ll>& strings = hashes[hash];
				for(ll index : strings) {
					if (patterns[index] == text.substr(i, len)) output.push_back({i, len});
				}
			}
		}
	}
	return output;
}

void preprocess_KR(const vector<string>& patterns, const string& text) {
	buildHashStructure(text);
	hashesWithLengths(patterns);
}
