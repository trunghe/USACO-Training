/*
 ID: trungvt2
 TASK: prefix
 LANG: C++
 */

/*
 http://train.usaco.org/usacoprob2?a=wWXLqtYdfAZ&S=prefix
 Description: Given a set of primitive strings and the string S, find the length of the
			 longest prefix of S that is made up of a series of the primitive strings.
			 Example:
			 	set of primitives = {A, AB, BA, CA, BBC}
				S = ABABACABAABC
				longest prefix = ABABACABAAB
					( = AB + AB + A + CA + BA + AB)
					==> length = 11
 Category: DP
 Solution: Let us call an index i in S "available" IFF i is the first index or
		  there is a valid prefix that ends at index i-1. Now for each index i of S
		  from the first index, if i is "available" AND a primitive string of length n
		  matches at i, then we mark index i+m "available". Return the last available index
		  or the total length of the main string if the whole string S is a prefix.
 Complexity: O(m * k * n) where m is the length of S, k is the number of primitives
  	  	  	  and n is the length of the longest primitive string.
  	  	  	  m <= 2 * 10^5, k <= 200, n <= 10
  	  	  	  m * k * n <= 4 * 10^8
 Author: Vu Thanh Trung
 */

/*
 * prefix.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: T
 */

#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) \
    for (int i = (a); i < (b); i++)
#define FORE(i, a, b) \
    for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) \
    for (int i = (a); i >= (b); i--)
#define MAX 200002
vector<string> primitives;
bool available[MAX];

void inputPrimitive() {
	string primitive;
	cin >> primitive;
	while (primitive != ".") {
//		cerr << primitive << endl;
		primitives.emplace_back(primitive);
		cin >> primitive;
	}
//	cerr << endl;
}

void solve() {
	string str, temp;
	while (cin >> temp) {
		str += temp;
	}
	int maxPrefixLength = 0;
	available[0] = true;
	FOR(i, 0, str.size()) {
		if (available[i]) {
//			cerr << "i = " << i << endl;
			for (string primitive : primitives) {
				int nextIndex = i + primitive.size();
				if (nextIndex <= str.size()
						&& primitive == str.substr(i, primitive.size())) {
					if (nextIndex == str.size()) {
						cout << str.size() << endl;
						return;
					}
					available[nextIndex] = true;
					maxPrefixLength = max(maxPrefixLength, nextIndex);
				}
			}
		}
	}
	cout << maxPrefixLength << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
//	freopen("prefix.err", "w", stderr);
	inputPrimitive();
	solve();

	return 0;
}

/* Sample input:
A AB BA CA BBC
.
ABABACABAABC
 */
/* Expected output:
11
 */

/*
USER: Trung Vu [trungvt2]
TASK: prefix
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1356 KB]
   Test 2: TEST OK [0.004 secs, 1356 KB]
   Test 3: TEST OK [0.004 secs, 1364 KB]
   Test 4: TEST OK [0.011 secs, 1428 KB]
   Test 5: TEST OK [0.004 secs, 1384 KB]
   Test 6: TEST OK [0.126 secs, 3256 KB]

All tests OK.
YOUR PROGRAM ('prefix') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
 */

