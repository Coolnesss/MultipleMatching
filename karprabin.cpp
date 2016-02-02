#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ll A = 8932498438934831ll;
//ll B = 8932498438934825ll;
ll A = 999999997;
ll B = 999999991; 

vector<ll> p;
vector<ll> x;
unordered_map<ll, unordered_set<ll>> hashValues;

ll subsequence(ll a, ll b) {
	ll ret = p[b];
	if (a > 0) ret -= (p[a-1] * x[b-a+1]) % B;
	return (ret + B) % B;
}

void buildHashStructure(string& text) {
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


void hashesWithLengths(vector<string>& patterns) {
	for (string& s : patterns) {
		ll len = s.length();
		ll hash = 0;
		for(int i = 0; i < len; i++) {
			hash = hash * A + s[i];
			hash %= B;
		}
		hashValues[len].insert(hash);
	}
}

void findPatterns(string& text, vector<string> patterns) {
	ll matches = 0;
	for(ll i = 0; i < text.length(); i++) {
		for (auto& a : hashValues) {
			ll len = a.first;
			unordered_set<ll>& hashes = a.second;
			
			if (i+len-1 < text.length() && hashes.count(subsequence(i, i+len-1))) matches++;
		}
	}
	cout << "Found " << matches << " matches." << endl;
}