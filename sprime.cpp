/*
ID: trungvt2
TASK: sprime
LANG: C++
*/

/*
http://train.usaco.org/usacoprob2?S=sprime&a=bmfzgE4eo0F
Description: TODO Write a description
Category:
Solution:
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;
#define MAX_N 10001

int n;
bool notPrime[MAX_N];
list<int> oddPrimes;
int firstDigits[4] = {2, 3, 5, 7};
int nextDigits[4] = {1, 3, 7, 9};
int tenPowerLessOneN;
int rootTenPowerN;

void init() {
    cin >> n;
//    cout << "n = " << n << endl;
    tenPowerLessOneN = pow(10, n - 1);
//    cout << "tenPowerLessOneN = " << tenPowerLessOneN << endl;
    rootTenPowerN = sqrt(pow(10, n)) + 1;
//    cout << "rootTenPowerN = " << rootTenPowerN << endl;
    notPrime[0] = true;
    notPrime[1] = true;
    for (int i = 2; i <= rootTenPowerN; i++) {
        if (notPrime[i]) {
            continue;
        } else {
            oddPrimes.emplace_back(i);
            for (int j = i * 2; j <= rootTenPowerN; j += i) {
                notPrime[j] = true;
            }
        }
    }
    oddPrimes.pop_front(); // Remove unnecessary number 2
}

bool isPrime(int a) {
    if (a < rootTenPowerN) {
        return !notPrime[a];
    }
    for (int oddPrime : oddPrimes) {
        if (a <= oddPrime) {
            return true;
        }
        if (a % oddPrime == 0) {
            return false;
        }
    }
    return true;
}

void dfs(int i) {
    if (!isPrime(i)) {
        return;
    }
    if (i > tenPowerLessOneN) {
        cout << i << endl;
        return;
    }
    i *= 10;
    for (int j = 0; j < 4; ++j) {
        dfs(i + nextDigits[j]);
    }
}

void solve() {
    for (int i = 0; i < 4; ++i) {
        dfs(firstDigits[i]);
    }
}

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie();
    freopen("sprime.in", "r", stdin);
    freopen("sprime.out", "w", stdout);

    init();
    solve();
    return 0;
}

/* Sample input:
4
 */
/* Sample output:
2333
2339
2393
2399
2939
3119
3137
3733
3739
3793
3797
5939
7193
7331
7333
7393
 */

/*
USER: Trung Vu [trungvt2]
TASK: sprime
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1408 KB]
   Test 2: TEST OK [0.004 secs, 1448 KB]
   Test 3: TEST OK [0.004 secs, 1264 KB]
   Test 4: TEST OK [0.004 secs, 1296 KB]
   Test 5: TEST OK [0.004 secs, 1372 KB]

All tests OK.
Your program ('sprime') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 2 bytes] ----
4
------- test 2 [length 2 bytes] ----
5
------- test 3 [length 2 bytes] ----
6
------- test 4 [length 2 bytes] ----
7
------- test 5 [length 2 bytes] ----
8
 */
