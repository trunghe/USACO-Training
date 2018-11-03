/*
ID: trungvt2
TASK: frac1
LANG: C++
*/

/*
http://train.usaco.org/usacoprob2?a=HDCCsaED3wO&S=frac1
Description: TODO Write a description
Category: Graph / Binary Tree / Binary Search Tree (BST) / Recursive
Solution: We notice that we can start with 0/1 and 1/1 as our ``endpoints'' and recursively generate the middle points
            by adding numerators and denominators.
=========================================================================
0/1                                                              1/1
                               1/2
                  1/3                      2/3
        1/4              2/5         3/5                 3/4
    1/5      2/7     3/8    3/7   4/7   5/8       5/7         4/5
=========================================================================
        Each fraction is created from the one up to its right and the one up to its left. This idea lends itself easily
        to a recursion that we cut off when we go too deep (in-order traversal).
        This is faster than my previous dfs solution as it finds only the correct results in the correct order.
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;

//struct fraction {
//    int up, down;
//
//    fraction(int u, int d) {
//        int g = __gcd(u, d);
//        u /= g;
//        d /= g;
//        this->up = u;
//        this->down = d;
//    }
//
//    bool operator<(const fraction &other) const {
//        return (this->up * other.down) < (other.up * this->down);
//    }
//
//    bool operator==(const fraction &other) const {
//        return (this->up * other.down) == (other.up * this->down);
//    }
//};

static int n;
//static vector<fraction> results;
//static set<fraction> results;
//static bool added[200][200];

//void dfs(int u, int d) {
//    if (d > n || u > d) {
//        return;
//    }
//    // NOTE: Simplifying the fraction here would produce
//    // the wrong results because of the nature of recursive
//    // functions???
//    // TODO Explain why!
////    int g = __gcd(u, d);
////    u /= g;
////    d /= g;
//    if (added[u][d]) {
//        return;
//    }
//    added[u][d] = true;
////    results.emplace_back(fraction(u, d));
//    results.insert(fraction(u, d));
//    dfs(u + 1, d);
//    dfs(u, d + 1);
//    dfs(u + 1, d + 1);
//}

void inOrder(int up1, int down1, int up2, int down2) {
    int downNew = down1 + down2;
    if (downNew > n) {
        return;
    }
    int upNew = up1 + up2;
    inOrder(up1, down1, upNew, downNew);
    cout << upNew << '/' << downNew << endl;
    inOrder(upNew, downNew, up2, down2);
}

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie();
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);
    cin >> n;
//    dfs(0, 1);
//    sort(results.begin(), results.end());
//    for (fraction f : results) {
//        cout << f.up << '/' << f.down << endl;
//    }
    cout << "0/1" << endl;
    inOrder(0, 1, 1, 1);
    cout << "1/1" << endl;

    return 0;
}

/* Sample input:
5
 */
/* Sample output:
0/1
1/5
1/4
1/3
2/5
1/2
3/5
2/3
3/4
4/5
1/1
 */

/*
USER: Trung Vu [trungvt2]
TASK: frac1
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1332 KB]
   Test 2: TEST OK [0.004 secs, 1376 KB]
   Test 3: TEST OK [0.004 secs, 1364 KB]
   Test 4: TEST OK [0.004 secs, 1416 KB]
   Test 5: TEST OK [0.004 secs, 1364 KB]
   Test 6: TEST OK [0.004 secs, 1396 KB]
   Test 7: TEST OK [0.007 secs, 1336 KB]
   Test 8: TEST OK [0.018 secs, 1376 KB]
   Test 9: TEST OK [0.035 secs, 1356 KB]
   Test 10: TEST OK [0.063 secs, 1376 KB]
   Test 11: TEST OK [0.158 secs, 1332 KB]

All tests OK.
Your program ('frac1') produced all correct answers!  This is your
submission #4 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 2 bytes] ----
1
------- test 2 [length 2 bytes] ----
2
------- test 3 [length 2 bytes] ----
4
------- test 4 [length 2 bytes] ----
7
------- test 5 [length 3 bytes] ----
10
------- test 6 [length 3 bytes] ----
15
------- test 7 [length 3 bytes] ----
24
------- test 8 [length 3 bytes] ----
50
------- test 9 [length 3 bytes] ----
75
------- test 10 [length 4 bytes] ----
100
------- test 11 [length 4 bytes] ----
160
 */
