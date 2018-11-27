/*
 ID: trungvt2
 TASK: runround
 LANG: C++
 */

/*
http://train.usaco.org/usacoprob2?S=runround&a=wWXLqtYdfAZ
 Description: TODO Write a description
 Category: Brute Force
 Solution:
 Complexity: TODO Analyze complexity
 Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
//typedef vector<int> vi;
//typedef vector<vi> vvi;
//typedef vector<ll> vl;
//typedef vector<vl> vvl;
//typedef vector<vvl> vvvl;
//typedef pair<int, int> ii;
//typedef vector<ii> vii;
//typedef vector<vii> vvii;

#define FOR(i, a, b) \
    for (int i = (a); i < (b); i++)
#define FORE(i, a, b) \
    for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) \
    for (int i = (a); i >= (b); i--)

//#define INF 1e9+7
//#define INFLL 1e18+7
//#define esp 1e-9
//#define PI 3.14159265
//
//ll nMod = 1e9 + 7;

//inline ll GCD(ll a, ll b) {while (b != 0) {ll c = a % b; a = b; b = c;} return a;};
//inline ll LCM(ll a, ll b) {return (a / GCD(a,b)) * b;};

//ll max(ll a1, ll b1) {
//	return a1 > b1 ? a1 : b1;
//}

//int m, noDigits;
//int bitMask[9];
//int digit[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
//int num[9];

//bool runaround() {
//	bool processed[noDigits];
//	memset(processed, false, noDigits);
//	int i = 0, countProcessed = 0;
//	while (!processed[i]) {
//		cerr << "i = " << i << endl;
//		processed[i] = true;
//		countProcessed++;
//		i = (i + num[i]) % noDigits;
//	}
//	return i == 0 && countProcessed == noDigits;
//}
//
//int getNoDigits(int num) {
//	int temp = num, countDigits = 0;
//	do {
//		countDigits++;
//	} while ((temp /= 10) > 0);
//	return countDigits;
//}
//
//void setBit() {
//	cerr << "noDigits = " << noDigits << endl;
//	FORD(i, 8, 9 - noDigits) {
//		bitMask[i] = 1;
//		cerr << digit[i];
//	}
//	cerr << endl;
////	FORD(i, 8 - noDigits, 0) {
////		bitMask[i] = false;
////	}
//}
//
//void setNum() {
//	int i = 0;
//	FORD(j, 8, 0) {
//		if (bitMask[j]) {
//			num[i++] = digit[j];
//			cerr << digit[j];
//		}
//	}
//	cerr << endl;
//}
//
//bool greaterNum() {
//	if (noDigits > getNoDigits(m)) {
//		return true;
//	}
//	int temp = 0;
//	FOR(i, 0, noDigits) {
//		temp = temp * 10 + num[i];
//	}
//	return temp > m;
//}
//
//void solve() {
//	noDigits = getNoDigits(m);
//	setBit();
//	bool hasNextPerm;
////	noDigits--;
////	do {
//		hasNextPerm = true;
//
//		do {
//			setNum();
//		} while (!greaterNum() && (hasNextPerm = next_permutation(bitMask, bitMask + 9)));
////	} while (!hasNextPerm);
//		if (!hasNextPerm) {
//			FOR(i, 8, 0) {
//				if (bitMask[i]) {
//					cerr << digit[i];
//				}
//			}
//			cerr << endl;
//			noDigits++;
////			bitMask[9 - noDigits] = true;
//			setBit();
//			setNum();
//		}
//
//	while (!runaround()) {
//		if (!next_permutation(bitMask, bitMask + 9)) {
//			cerr << "Hello" << endl;
//			noDigits++;
////			bitMask[9 - noDigits] = true;
//			setBit();
////			setBit();
//		}
//		setNum();
//	}
//	FOR(i, 0, noDigits) {
//		cout << num[i];
//	}
//	cout << endl;
//}

bool isRunAround(int m) {
	bool seen[10];
	memset(seen, false, 10);
	vector<int> digits;
	do {
		int digit = m % 10;
		if (seen[digit]) {
			return false;
		}
		seen[digit] = true;
 		digits.emplace_back((digit));
	} while (m /= 10);

	reverse(digits.begin(), digits.end());

//	FOR(i, 0, digits.size()) {
//		cerr << digits[i];
//	}
//	cerr << endl;

	bool processed[digits.size()];
	memset(processed, false, digits.size());
	int i = 0, countProcessed = 0;
	while (!processed[i]) {
//		cerr << "i = " << i << endl;
		processed[i] = true;
		countProcessed++;
		i = (i + digits[i]) % digits.size();
	}
	cerr << endl;
	return i == 0 && countProcessed == digits.size();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	freopen("runround.in", "r", stdin);
	freopen("runround.out", "w", stdout);
//	freopen("runround.err", "w", stderr);
	int m;
	cin >> m;
	while (!isRunAround(++m));
	cout << m << endl;
//	solve();

	return 0;
}

/* Sample input:
81361
 */
/* Sample output:
81362
 */

/*
USER: Trung Vu [trungvt2]
TASK: runround
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1424 KB]
   Test 2: TEST OK [0.045 secs, 1368 KB]
   Test 3: TEST OK [0.007 secs, 1352 KB]
   Test 4: TEST OK [0.042 secs, 1412 KB]
   Test 5: TEST OK [0.242 secs, 1348 KB]
   Test 6: TEST OK [0.189 secs, 1352 KB]
   Test 7: TEST OK [0.665 secs, 1368 KB]

All tests OK.
YOUR PROGRAM ('runround') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
Here are the test data inputs:
------- test 1 [length 3 bytes] ----
99
------- test 2 [length 7 bytes] ----
111110
------- test 3 [length 7 bytes] ----
134259
------- test 4 [length 7 bytes] ----
348761
------- test 5 [length 8 bytes] ----
1000000
------- test 6 [length 8 bytes] ----
5000000
------- test 7 [length 8 bytes] ----
9000000
Keep up the good work!
Thanks for your submission!
 */

