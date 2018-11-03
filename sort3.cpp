/*
ID: trungvt2
TASK: sort3
LANG: C++
*/

/*
http://train.usaco.org/usacoprob2?S=sort3&a=K769GfH2zFb
https://wcipeg.com/problem/ioi9621
Description: TODO Write a description
Category: Ad Hoc
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
#define MAX 1001

static int n;
static int sequence[MAX];
static list<int> lists[4][4];
static int frequency[4];
static list<int> *cycles[4];
static list<pair<int, int>> swaps;
static int minSwaps;

const bool TESTING = false;

void input() {
    cin >> n;
    FORE(i, 1, n) {
        cin >> sequence[i];
        frequency[sequence[i]]++;
        if (TESTING) {
            cout << sequence[i] << " "
                 << frequency[sequence[i]] << "th" << endl;
        }
    }
//    cout << endl;
}

void preprocess() {
    int start = 1;
    FORE(i, 1, 3) {
        int end = start + frequency[i] - 1;
        FORE(j, start, end) {
            lists[i][sequence[j]].emplace_back(j);
        }
        start += frequency[i];
    }
    if (TESTING) {
        FORE(i, 1, 3) {
            FORE(j, i + 1, 3) {
                cout << i << " has " << j << " at: ";
                for (int num : lists[i][j]) {
                    cout << num << " ";
                }
                cout << "\n" << j << " has " << i << " at: ";
                for (int num : lists[j][i]) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}

void solve() {
    minSwaps = 0;
    FORE(i, 1, 3) {
        FORE(j, i + 1, 3) {
            int minS;
            if (lists[i][j].size() < lists[j][i].size()) {
                minS = lists[i][j].size();
                cycles[i] = &lists[j][i];
            } else {
                minS = lists[j][i].size();
                cycles[i] = &lists[i][j];
            }
            minSwaps += minS;
            FOR(k, 0, minS) {
                swaps.emplace_back(make_pair(
                        lists[i][j].front(), lists[j][i].front()));
                if (TESTING) {
                    cout <<  (lists[i][j].front())
                    << " "
                    << (lists[j][i].front())
                    << "\n";
                }
                lists[i][j].pop_front();
                lists[j][i].pop_front();
            }
        }
    }
    int noCycles = cycles[1]->size();
    minSwaps += 2 * noCycles;
    cout << minSwaps << endl;
//    for (pair<int, int> swap : swaps) {
//        cout << swap.first << " " << swap.second << endl;
//    }
    if (TESTING) {
        int c1[noCycles], c2[noCycles], c3[noCycles], i = 0;
        for (int num : *cycles[1]) {
            c1[i++] = num;
            cout << num << endl;
        }
        i = 0;
        for (int num : *cycles[2]) {
            c2[i++] = num;
            cout << num << endl;
        }
        i = 0;
        for (int num : *cycles[3]) {
            c3[i++] = num;
            cout << num << endl;
        }
        FOR(i, 0, noCycles) {
            cout << c1[i] << " " << c2[i] << endl;
            cout << c3[i] << " " << c1[i] << endl;
        }
    }


    if (TESTING) {
        cout << "minSwaps = " << minSwaps
             << ", noCycles = " << noCycles << endl;
    }
//    while (!cycles[1]->empty()) {
//        FORE(j, 2, 3) {
//            swaps.emplace_back(make_pair(
//                    cycles[1]->front(), cycles[j]->front()));
//            if (TESTING) {
//                cout
//                        << cycles[1]->front()
//                        << " "
//                           << cycles[j]->front()
//                        << endl;
//            }
//
//            cycles[j]->pop_front();
//            cout << "Popped" << endl;
//        }
//        swaps.emplace_back(make_pair(
//                    cycles[1]->front(), cycles[2]->front()));
//        swaps.emplace_back(make_pair(
//                cycles[3]->front(), cycles[1]->front()));
//        cycles[1]->pop_front();
//        cycles[2]->pop_front();
//        cycles[3]->pop_front();
//    }
    if (TESTING) {
        cout << "Hello" << endl;
    }

//    int c[4][noCycles];
//    FORE(i, 1, 3) {
//        FOR(j, 0, noCycles) {
//            c[i][j] = cycles[j]->front();
//            cycles[j]->pop_front();
//        }
//    }
//    FOR(i, 0, noCycles) {
//        cout << cycles[1]->front() << " " << cycles[2]->front() << endl
//             << cycles[3]->front() << " " << cycles[1]->front();
//
//    }
//    FOR(i, 0, noCycles) {
//        cout << c[1][i] << " " << c[2][i] << endl
//             << c[3][i] << " " << c[1][i] << endl;
//    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    freopen("sort3.in", "r", stdin);
    freopen("sort3.out", "w", stdout);
    input();
    preprocess();
    solve();
    return 0;
}

/* Sample input:
9
2
2
1
3
3
3
2
3
1
 */
/* Sample output:
4
 */

/*
USER: Trung Vu [trungvt2]
TASK: sort3
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1340 KB]
   Test 2: TEST OK [0.000 secs, 1364 KB]
   Test 3: TEST OK [0.004 secs, 1356 KB]
   Test 4: TEST OK [0.000 secs, 1372 KB]
   Test 5: TEST OK [0.004 secs, 1356 KB]
   Test 6: TEST OK [0.004 secs, 1416 KB]
   Test 7: TEST OK [0.004 secs, 1376 KB]
   Test 8: TEST OK [0.004 secs, 1360 KB]

All tests OK.
Your program ('sort3') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 8 bytes] ----
3
2
1
3
------- test 2 [length 6 bytes] ----
2
1
1
------- test 3 [length 14 bytes] ----
6
1
2
3
2
3
1
------- test 4 [length 20 bytes] ----
9
2
2
1
3
3
3
2
3
1
------- test 5 [length 43 bytes] ----
20
1
1
3
2
1
1
1
3
2
1
3
3
2
1
3
1
1
2
3
1
------- test 6 [length 103 bytes] ----
50
1
1
1
3
1
3
2
1
2
3
3
1
3
2
1
1
2
3
2
2
3
3
2
3
2
2
3
1
1
1
1
1
1
1
3
1
1
2
2
3
1
1
3
3
2
1
1
1
3
2
------- test 7 [length 204 bytes] ----
100
3
2
2
3
1
2
2
2
1
2
2
3
2
3
2
2
3
3
2
2
2
3
3
3
3
2
2
1
2
2
1
1
1
3
1
1
2
2
3
3
1
1
2
2
1
1
3
1
3
1
3
2
1
2
1
3
3
3
1
2
1
1
2
1
3
2
2
1
1
1
3
1
2
2
3
3
2
3
3
2
1
2
3
1
3
1
1
3
3
1
1
1
1
3
1
1
2
3
1
2
------- test 8 [length 2005 bytes] ----
1000
3
1
3
2
1
1
3
3
2
1
3
2
3
2
3
2
3
2
1
1
3
3
3
2
1
1
2
3
2
2
1
1
3
1
3
1
1
2
3
3
3
3
2
3
2
1
2
1
3
2
1
2
2
1
1
3
1
3
3
3
1
1
1
1
1
3
2
1
2
2
3
2
1
2
1
3
2
3
3
2
2
1
1
3
1
1
3
2
3
2
2
1
3
2
2
3
1
3
1
2
1
1
1
2
2
1
2
1
3
1
2
1
1
2
1
2
3
1
1
3
2
2
1
2
1
2
1
1
2
2
3
3
2
3
2
1
1
3
1
1
3
3
2
1
2
2
3
1
2
3
3
1
2
3
2
2
2
3
3
3
1
3
2
3
3
3
3
1
2
1
1
2
3
2
2
1
1
2
2
3
2
2
3
3
2
2
2
3
1
2
3
2
2
1
1
1
1
3
2
3
1
2
1
3
1
3
1
1
1
2
3
3
3
3
2
1
2
1
1
2
3
3
3
1
1
1
2
2
1
3
1
1
2
2
3
2
2
1
3
3
2
3
2
2
3
1
3
1
1
3
3
3
3
2
1
1
3
2
2
3
2
2
3
3
1
3
1
2
3
3
1
2
3
2
3
2
2
2
2
3
2
1
3
1
3
3
1
2
2
3
1
3
2
1
2
2
3
3
3
3
3
1
1
2
3
3
3
2
2
2
1
3
2
1
1
1
1
2
3
2
1
1
2
2
1
1
3
1
3
3
3
3
3
3
1
3
3
1
1
1
2
1
1
3
1
1
1
1
3
3
3
3
3
1
2
1
1
1
1
1
1
3
3
1
3
1
3
2
2
3
3
3
1
3
3
1
1
1
2
3
1
2
3
3
3
1
1
3
2
1
1
2
1
1
2
3
2
2
2
3
1
2
3
1
2
3
2
2
3
1
1
3
2
1
3
1
1
3
1
2
1
2
3
1
2
2
1
1
3
2
3
1
1
3
1
2
2
3
3
2
3
1
1
2
1
1
3
2
3
3
3
3
2
3
1
1
1
1
1
1
3
1
1
3
3
2
1
1
2
1
2
1
2
3
3
3
3
2
1
3
2
3
3
3
2
3
3
3
1
3
1
3
3
1
2
2
3
3
3
1
1
2
2
3
1
1
2
1
2
2
3
3
2
3
3
1
2
2
3
3
2
3
2
1
1
1
3
1
1
3
1
1
1
2
3
1
3
2
2
2
1
1
1
2
1
1
3
3
2
2
2
3
2
3
1
3
3
1
3
1
3
1
1
1
3
1
2
2
3
3
3
3
1
1
1
1
1
3
3
3
2
1
3
1
3
3
1
3
1
3
3
1
1
1
1
3
2
2
2
1
2
1
3
2
2
1
2
2
1
1
2
3
2
1
3
2
1
3
2
1
3
2
1
3
2
2
2
1
3
3
1
1
1
1
3
3
1
1
2
1
2
3
1
1
3
3
2
3
3
3
1
3
1
1
2
3
3
1
3
2
1
3
3
2
3
2
1
1
3
2
2
2
1
2
2
1
2
3
3
1
3
1
3
1
2
2
3
1
3
2
3
3
2
3
2
2
2
2
2
1
3
1
2
1
2
1
1
3
1
1
1
3
1
1
3
3
2
3
3
2
2
2
1
1
1
2
2
2
1
1
3
1
1
2
2
3
2
3
2
2
3
3
2
1
3
2
3
2
1
3
3
2
1
1
2
2
3
1
1
3
2
3
1
2
1
2
1
3
1
3
2
1
2
3
2
1
2
1
3
2
1
2
1
1
2
3
3
1
1
3
1
2
2
1
3
3
2
1
2
2
1
1
3
2
3
1
3
1
2
2
3
2
3
1
2
2
1
2
2
1
1
2
2
3
2
2
2
1
3
1
3
3
1
2
2
1
2
1
1
3
3
1
1
2
1
3
1
1
1
2
2
2
1
3
1
2
2
2
3
1
2
2
1
3
3
2
3
2
2
1
2
1
1
2
3
2
2
3
3
3
2
1
1
2
1
1
1
3
3
3
1
2
1
1
1
1
2
1
3
1
1
1
2
2
3
1
1
1
1
3
1
2
1
1
3
2
2
1
1
2
3
1
3
1
1
1
2
3
1
1
3
2
1
1
3
3
2
3
1
3
3
1
1
1
2
1
2
1
1
3
3
1
3
2
2
1
3
1
1
3
1
1
1
2
2
1
2
3
3
3
2
3
1
3
3
3
1
1
1
2
1
3
3
3
1
1
1
1
2
2
1
2
2
2
1
3
2
3
3
2
 */
