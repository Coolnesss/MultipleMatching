#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using namespace chrono;
#include "karprabin.h"
#include "ahocorasick.h"

string text;
vector<string> random_patterns;

ll PATTERN_LENGTH_MAX = 500;
ll PATTERN_AMOUNT = 2000;

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

vector<pair<ll,ll>> run_kr_performance_tests() {
  return findPatterns(text, random_patterns);
}

// Argument 1 contains path to file,
// 2 should contain amount of patterns and 3 length of patterns
void load_args_and_data(int argc, char* argv[]) {
		if (argc >= 3) PATTERN_AMOUNT = (ll) argv[2];
		if (argc >= 4) PATTERN_LENGTH_MAX = (ll) argv[3];
	  string path = string(argv[1]);
	  load_text(path);
	  load_random_patterns();
}

int main(int argc, char* argv[]) {
	load_args_and_data(argc, argv);
  auto start = steady_clock::now();
  preprocess_ac(random_patterns);
  auto end = steady_clock::now();

  cout <<  duration_cast<milliseconds>(end - start).count() << endl;

  start = steady_clock::now();
  run_ac_performance_tests();
  end = steady_clock::now();

  cout <<  duration_cast<milliseconds>(end - start).count() << endl;

  start = steady_clock::now();
  preprocess_KR(random_patterns, text);
  end = steady_clock::now();

  cout <<  duration_cast<milliseconds>(end - start).count() << endl;

  start = steady_clock::now();
  run_kr_performance_tests();
  end = steady_clock::now();

  cout <<  duration_cast<milliseconds>(end - start).count() << endl;

}
