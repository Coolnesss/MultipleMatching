#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// Co-primes to use as hash function parameters
ll A = 999999997;
ll B = 999999991;

// Store hashes of prefixs of the text, and corresponding powers of A
vector<ll> p;
vector<ll> x;
// Store hashes of patterns. Each different length has its own unordered_set,
// so it's possible to check each length in O(1). In addition stores indexes
// to the patterns vector for each hash, so we know which string it belongs to.
unordered_map<ll, unordered_map<ll, vector<ll>>> hashValues;

// Find the hash value of any substring of the text in O(1)
ll subsequence(ll a, ll b) {
	ll ret = p[b];
	if (a > 0) ret -= (p[a-1] * x[b-a+1]) % B;
	return (ret + B) % B;
}


// Build data structure from which it's possible to ask for any text's
// substring's hash value.
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

// Preprocess patterns to calculate their hash values and store them
// grouped by length of pattern
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

// Search the text for the patterns. For each window in the text, all different
// pattern lengths have to be checked. If matches are found, they are checked
// with brute force.
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

// Preprocess the text and patterns before the searching phase.
void preprocess_KR(const vector<string>& patterns, const string& text) {
	buildHashStructure(text);
	hashesWithLengths(patterns);
}
