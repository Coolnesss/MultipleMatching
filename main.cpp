#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#include "ahocorasick.h"
#include "karprabin.h"

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ifstream in("english.50MB");
	stringstream buffer;
	buffer << in.rdbuf();
	string text = buffer.str();
	vector<string> matching;

	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		ll b = rand() % text.length()-1000;
		matching.push_back(text.substr(b, 1000));
	}
	ll ms,ms2;
	
	ms = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	buildTrie(matching);
	buildFailFunction();
	ms2 = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	cout << "Preprocessing done for Aho-Corasick" << endl;
	cout << "It took " << ms2 - ms << " milliseconds." << endl;
	
	ms = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	findPattern(text);
	ms2 = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	cout << "Search phase done for Aho-Corasick" << endl;
	cout << "It took " << ms2 - ms << " milliseconds." << endl;
	
	ms = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	buildHashStructure(text);
	hashesWithLengths(matching); 
	ms2 = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	cout << "Preprocessing done for Karp-Rabin." << endl;
	cout << "It took " << ms2 - ms << " milliseconds." << endl;
	
	ms = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	findPatterns(text, matching);
	ms2 = chrono::duration_cast< chrono::milliseconds >(chrono::system_clock::now().time_since_epoch()).count();
	cout << "Search phase done for Karp-Rabin." << endl;
	cout << "It took " << ms2 - ms << " milliseconds." << endl;
	
	
	
	
	
	
	
	
}