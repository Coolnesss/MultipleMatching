#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using namespace chrono;
#include "karprabin.h"
#include "ahocorasick.h"

string text;
vector<string> random_patterns;

const ll PATTERN_LENGTH_MAX = 500;
const ll PATTERN_AMOUNT = 2000;

void load_text(string path) {
	ifstream in(path);
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

vector<pair<ll,ll>> run_ac_performance_tests() {
  return findPattern(text);
}

int main(int argc, char* ARGV[]) {
  string asd = string(ARGV[1]);
  load_text(asd);
  load_random_patterns();

  auto start = steady_clock::now();
  preprocess_ac(random_patterns);
  auto end = steady_clock::now();

  cout <<  duration_cast<milliseconds>(end - start).count() << endl;

  start = steady_clock::now();
  run_ac_performance_tests();
  end = steady_clock::now();

  cout <<  duration_cast<milliseconds>(end - start).count() << endl;

}
