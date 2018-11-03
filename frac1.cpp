/*
ID: trungvt2
TASK: frac1
LANG: C++
*/

/*
http://train.usaco.org/usacoprob2?a=HDCCsaED3wO&S=frac1
Description: TODO Write a description
Category: Graph
Solution: DFS
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;

//typedef long long ll;
//typedef vector<int> vi;
//typedef vector<vi> vvi;
//typedef vector<ll> vl;
//typedef vector<vl> vvl;
//typedef vector<vvl> vvvl;
//typedef pair<int, int> ii;
//typedef vector<ii> vii;
//typedef vector<vii> vvii;

//#define FOR(i, a, b) \
//    for (int i = (a); i < (b); i++)
//#define FORE(i, a, b) \
//    for (int i = (a); i <= (b); i++)
//#define FORD(i, a, b) \
//    for (int i = (a); i >= (b); i--)

//#define INF 1e9+7
//#define INFLL 1e18+7
//#define esp 1e-9
//#define PI 3.14159265
//
//ll nMod = 1e9 + 7;

//inline ll GCD(ll a, ll b) {while (b != 0) {ll c = a % b; a = b; b = c;} return a;};
//inline ll LCM(ll a, ll b) {return (a / GCD(a,b)) * b;};

//ll max(ll a1, ll b1) {
//    return a1 > b1 ? a1 : b1;
//}


//#define li list<int>
//// function to find the divisors in order
//li getDivisors(int n) {
//    // Lists to store halves of the divisors
//    li firstHalf;
//    li secondHalf;
//    int sqrtN = sqrt(n);
//    FORE(i, 1, sqrtN) {
//        if (n % i == 0) {
//            firstHalf.emplace_back(i);
//            int nOverI = n / i;
//            if (nOverI != i) // check if divisors are NOT equal
//            {
//                // push the second divisor in the second half
//                secondHalf.emplace_front(nOverI);
//            }
//        }
//    }
//    firstHalf.merge(secondHalf);
//    return firstHalf;
//}

struct fraction {
    int up, down;

    fraction(int u, int d) {
        int g = __gcd(u, d);
        u /= g;
        d /= g;
        this->up = u;
        this->down = d;
    }

    bool operator<(const fraction &other) const {
        return (this->up * other.down) < (other.up * this->down);
    }

    bool operator==(const fraction &other) const {
        return (this->up * other.down) == (other.up * this->down);
    }
};

static int n;
//static vector<fraction> results;
static set<fraction> results;
static bool added[200][200];

void dfs(int u, int d) {
    if (d > n || u > d) {
        return;
    }
    // NOTE: Simplifying the fraction here would produce
    // the wrong results because of the nature of recursive
    // functions???
    // TODO Explain why!
//    int g = __gcd(u, d);
//    u /= g;
//    d /= g;
    if (added[u][d]) {
        return;
    }
    added[u][d] = true;
//    results.emplace_back(fraction(u, d));
    results.insert(fraction(u, d));
    dfs(u + 1, d);
    dfs(u, d + 1);
    dfs(u + 1, d + 1);
}

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie();
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);
    cin >> n;
    dfs(0, 1);
//    sort(results.begin(), results.end());
    for (fraction f : results) {
        cout << f.up << '/' << f.down << endl;
    }

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
   Test 1: TEST OK [0.004 secs, 1376 KB]
   Test 2: TEST OK [0.004 secs, 1468 KB]
   Test 3: TEST OK [0.004 secs, 1348 KB]
   Test 4: TEST OK [0.000 secs, 1468 KB]
   Test 5: TEST OK [0.004 secs, 1392 KB]
   Test 6: TEST OK [0.004 secs, 1364 KB]
   Test 7: TEST OK [0.007 secs, 1336 KB]
   Test 8: TEST OK [0.018 secs, 1332 KB]
   Test 9: TEST OK [0.035 secs, 3068 KB]
   Test 10: TEST OK [0.067 secs, 3016 KB]
   Test 11: TEST OK [0.161 secs, 2924 KB]

All tests OK.
Your program ('frac1') produced all correct answers!  This is your
submission #3 for this problem.  Congratulations!
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
