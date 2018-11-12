/*
ID: trungvt2
TASK: hamming
LANG: C++
*/

/*
http://link...
Description: TODO Write a description
Category:
Solution:
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) \
    for (int i = (a); i < (b); i++)

#define MAX 260

int noCodes, noBits, minDist;
int ans[65];
bool visited[MAX];

//void checkBitmask(int bitmask) {
//    bitset<7> bs(bitmask);
//    cerr << bs.to_string() << " " << bitmask << endl;
//}

void removeTooClose(int bitmask, int d, int i) {
    if (d < 1 || i >= noBits) {
        return;
    }
    d--;
    while (i < noBits) {
        int nextBitmask = bitmask ^(1 << i++);
//        checkBitmask(nextBitmask);
        visited[nextBitmask] = true;
        removeTooClose(nextBitmask, d, i);
    }
}

/*
 * Method 1: For each qualified code, remove all the codes within a
 * smaller Hamming distance than the min distance (similar to sieve).
 * In theory, this method does less work by not having to check
 * for invalid codes. However, this recursive implementation runs
 * slower than the brute force implementation below.
 */
void solve() {
    int i = 0;
    int bitmask = 0;
    while (i < noCodes) {
        while (visited[bitmask]) {
//            checkBitmask(bitmask);
            bitmask++;
        }
//        checkBitmask(bitmask);
        visited[bitmask] = true;
        ans[i++] = bitmask;
        removeTooClose(bitmask, minDist - 1, 0);
    }
}

//bool withinDist(int bitmask, int i) {
//    FOR(j, 0, i) {
////        checkBitmask(ans[j]);
//        bitset<8> b(bitmask ^ ans[j]);
//        if (b.count() < minDist) {
//            return true;
//        }
//    }
//    return false;
//}

/*
 * Method 2: For each code, check with all current qualified codes.
 * If the Hamming distance is large enough with all current qualified
 * codes, add the code to the output set. This brute force cheking
 * method will do some unnecessary checks (the code may be far enough
 * from most of the current qualified codes except the last one, so
 * we still have to check it until the very last to determine that
 * it is a bad code).
 */
//void solve() {
//    int i = 0;
//    int bitmask = 0;
//    while (i < noCodes) {
//        while (withinDist(bitmask, i)) {
////            checkBitmask(bitmask);
//            bitmask++;
//        }
////        checkBitmask(bitmask);
//        ans[i++] = bitmask;
//    }
//}

void output() {
    int i = 0;
    while (i < noCodes) {
        cout << ans[i++];
        FOR(j, 0, 9) {
            if (i < noCodes) {
                cout << " " << ans[i++];
            } else {
                cout << endl;
                return;
            }
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    freopen("hamming.in", "r", stdin);
    freopen("hamming.out", "w", stdout);
//    freopen("hamming.error", "w", stderr);

    cin >> noCodes >> noBits >> minDist;
    solve();
    output();
    return 0;
}

/* Sample input:
16 7 3
 */
/* Sample output:
0 7 25 30 42 45 51 52 75 76
82 85 97 102 120 127
 */

/*
USER: Trung Vu [trungvt2]
TASK: hamming
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1468 KB]
   Test 2: TEST OK [0.004 secs, 1336 KB]
   Test 3: TEST OK [0.004 secs, 1376 KB]
   Test 4: TEST OK [0.004 secs, 1352 KB]
   Test 5: TEST OK [0.004 secs, 1364 KB]
   Test 6: TEST OK [0.004 secs, 1344 KB]
   Test 7: TEST OK [0.007 secs, 1344 KB]
   Test 8: TEST OK [0.011 secs, 1372 KB]
   Test 9: TEST OK [0.011 secs, 1404 KB]
   Test 10: TEST OK [0.011 secs, 1420 KB]
   Test 11: TEST OK [0.011 secs, 1364 KB]

All tests OK.
Your program ('hamming') produced all correct answers!  This is your
submission #4 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 7 bytes] ----
16 7 3
------- test 2 [length 6 bytes] ----
2 7 7
------- test 3 [length 6 bytes] ----
3 6 4
------- test 4 [length 6 bytes] ----
5 5 1
------- test 5 [length 7 bytes] ----
10 8 4
------- test 6 [length 7 bytes] ----
20 6 2
------- test 7 [length 7 bytes] ----
32 5 1
------- test 8 [length 7 bytes] ----
50 8 2
------- test 9 [length 7 bytes] ----
60 7 2
------- test 10 [length 7 bytes] ----
16 8 3
------- test 11 [length 7 bytes] ----
15 8 4
 */
