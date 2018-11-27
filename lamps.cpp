/*
 ID: trungvt2
 TASK: lamps
 LANG: C++
 */

/*
 http://train.usaco.org/usacoprob2?S=lamps&a=wWXLqtYdfAZ
 Description: TODO Write a description
 Category: Brute Force
 Solution:
 Complexity: TODO Analyze complexity
 Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) \
    for (int i = (a); i < (b); i++)
#define FORE(i, a, b) \
    for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) \
    for (int i = (a); i >= (b); i--)

//============================================================================
// Name        : lamps.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

typedef vector<bool> BitString;

//bool lessThan(BitString a, BitString b) {
//	FOR(i, 0, a.size()) {
//		if (a[i] && !b[i]) {
//			return false;
//		}
//		if (!a[i] && b[i]) {
//			return true;
//		}
//	}
//	return false;
//}

list<int> mustMatchIndices;
BitString final;
set<BitString> results;
int n, c;


//void cerrBitString(BitString bitString) {
//	for (bool bit : bitString) {
//		cerr << bit;
//	}
//	cerr << endl;
//}

BitString applyButtonPress(int button, BitString bitString) {
//	cerr << "Before:\t";
//	cerrBitString(bitString);
	int increment = button / 2 + 1;
	int start = (button == 2 ? 1 : 0);
	for (int i = start; i < bitString.size(); i += increment) {
		bitString[i] = !bitString[i];
	}
//	cerr << "After:\t";
//	cerrBitString(bitString);
	return bitString;
}

bool canBeFinal(BitString bitString) {
//	cerrBitString(bitString);
	for (int i : mustMatchIndices) {
		if (bitString[i] != final[i]) {
			return false;
		}
	}
	return true;
}

BitString getFinal(bool combi[4]) {
	BitString bitString(n, true);
	FOR(i, 0, 4) {
		if (combi[i]) {
			bitString = applyButtonPress(i + 1, bitString);
		}
	}
	return bitString;
}

void solve() {
	if (c > 4) {
		c = 4;
	}
	int start = (c % 2 ? 1 : 0);
	FORE(noTypes, start, c)
	{
		bool combi[4];
		FORD(i, 3, 4 - noTypes)
		{
			combi[i] = true;
		}
		FORD(i, 3 - noTypes, 0)
		{
			combi[i] = false;
		}
//		FOR(i, 0, 4) {
//			cerr << combi[i];
//		}
//		cerr << endl;
		do {
			BitString bitString = getFinal(combi);
			if (canBeFinal(bitString)) {
				results.insert(bitString);
			}
		} while (next_permutation(combi, combi + 4));
	}
}

void inputFinal(const bool STATE) {
	int lamp;
	cin >> lamp;
	while (lamp > 0) {
		lamp--;
		mustMatchIndices.emplace_back(lamp);
		final[lamp] = STATE;
		cin >> lamp;
	}
}

void output() {
	if (results.empty()) {
		cout << "IMPOSSIBLE" << endl;
	} else {
		for (BitString bitString : results) {
			FOR(j, 0, bitString.size())
			{
				cout << bitString[j];
			}
			cout << endl;
		}

	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
//	freopen("lamps.err", "w", stderr);
	cin >> n >> c;
	final.resize(n);
	inputFinal(true);
	inputFinal(false);
	solve();
	output();
	return 0;
}

/* Sample input:
20
3
-1
1 3 5 -1
 */
/* Expected output:
00000000000000000000
01010101010101010101
 */

/*
USER: Trung Vu [trungvt2]
TASK: lamps
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1360 KB]
   Test 2: TEST OK [0.004 secs, 1368 KB]
   Test 3: TEST OK [0.004 secs, 1392 KB]
   Test 4: TEST OK [0.004 secs, 1432 KB]
   Test 5: TEST OK [0.004 secs, 1396 KB]
   Test 6: TEST OK [0.004 secs, 1348 KB]
   Test 7: TEST OK [0.004 secs, 1368 KB]
   Test 8: TEST OK [0.004 secs, 1396 KB]

All tests OK.
Your program ('lamps') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 11 bytes] ----
10
0
-1
-1
------- test 2 [length 13 bytes] ----
10
0
-1
1 -1
------- test 3 [length 17 bytes] ----
20
3
-1
1 3 5 -1
------- test 4 [length 15 bytes] ----
50
100
1 -1
-1
------- test 5 [length 13 bytes] ----
75
250
-1
-1
------- test 6 [length 46 bytes] ----
100
8394
1 7 13 19 25 31 37 43 49 55 -1
64 -1
------- test 7 [length 27 bytes] ----
100
2000
31 86 23 -1
42 -1
------- test 8 [length 15 bytes] ----
100
8950
-1
-1
Keep up the good work!
Thanks for your submission!
 */
