# Multiple string matching experiments

## Implementations
This library implements the Aho-Corasick and Karp-Rabin multiple pattern string matching algorithms. They search for the occurrences of multiple patterns in a single text.

### Aho-Corasick
This algorithm runs in time linear to the total length of the patterns and the text. The implementation uses structs to represent the nodes of the AC-automaton. In addition it uses a global unordered map to represent the accepting states. It contains the actual strings for which the node is an accepting state in a set.
Each node contains an array of size 256 which is used to keep pointers to its children. The trie is built in the preprocessing phase using the patterns. Each node also contains a pointer to the node that is it's failure link. These are calculated by doing a BFS of the trie.
After preprocessing the patterns to generate the automaton, the text is simply iterated through, simulating the automaton.

### Karp-Rabin
First the algorithm builds a data structure of the text from which we can in O(1) find the hash value of any substring. All the patterns are then preprocessed, their hash values stored in a hash map where each unique length of pattern has its own unordered set.
The text is then iterated through, and for each position we can check if any of the different buckets contain a hash that matches. For each window, therefore, we have to check all of the different lengths of patterns.
If the hash values indicate a match, it is checked with brute force to make sure it was not a collision.

## Testing
Both algorithms are compared with the brute force search, and verified that the results are exactly the same. `test.cpp` is responsible for this. To run the current tests, you need files "english.200MB" from http://pizzachili.dcc.uchile.cl/texts/nlang/

## Experiments
Performance is checked by running the algorithms with big inputs. Testing also includes using `fprofile-generate` to make profiling data with a certain dataset, and then using `fprofile-use` to compile the program with the profiling data included for optimization. A ruby script handles testing.
