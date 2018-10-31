/*
ID: trungvt2
LANG: C++
TASK: pprime
*/

/*
http://train.usaco.org/usacoprob2?S=pprime&a=NCwlhwOwFxv
Description: TODO Write a description
Category:
Solution:
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX_N 10001

int a, b;
bool notPrime[MAX_N];
list<int> oddPrimes;
bool boundingDigits[10];
char nextBoundingDigits[10];
string str;
int len;
int halfLen;
int maxA;

bool solveTrivialCases() {
    if (a < 6) {
        cout << 5 << endl;
    }
    if (a < 8 && b > 6) {
        cout << 7 << endl;
    }
    if (a < 12 && b > 10) {
        cout << 11 << endl;
    }
    if (b > 100) {
        if (a < 101) {
            a = 101;
        }
        return true;
    } else {
        return false;
    }
}

bool isPalin(string str) {
    int len = str.length();
    int halfLen = len / 2;
    for (int j = 0; j < halfLen; j++) {
        if (str[j] != str[--len]) {
            return false;
        }
    }
    return true;
}

void initOddPrimes() {
    int rootB = (int) sqrt(b) + 1;
    notPrime[0] = true;
    notPrime[1] = true;
    for (int i = 2; i <= rootB; i++) {
        if (notPrime[i]) {
            continue;
        } else {
            oddPrimes.emplace_back(i);
            for (int j = i * 2; j <= rootB; j += i) {
                notPrime[j] = true;
            }
            // If found a valid palindrome then output it anyway
            if (i >= a && isPalin(to_string(i))) {
                cout << i << endl;
                a = i + 1;
            }
        }
    }
    oddPrimes.pop_front(); // Remove unnecessary number 2
}

void initBoundingDigits() {
    for (int i = 0; i < 10; i++) {
        if (i % 2 != 0) {
            boundingDigits[i] = i != 5;
            nextBoundingDigits[i] = (char) ('0' + (i + 2) % 10);
            if (i == 3) {
                nextBoundingDigits[i] += 2;
            }
        } else {
            nextBoundingDigits[i] = (char) ('0' + (i + 1));
            if (i == 4) {
                nextBoundingDigits[i] += 2;
            }
        }
    }
}

bool isPrime(int a) {
    for (int i : oddPrimes) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

int getMinPalin() {
    char digits[len];
    digits[0] = digits[len - 1] = '1';
    for (int i = 1; i < halfLen; i++) {
        digits[i] = digits[len - i - 1] = '0';
    }
    if (len % 2 != 0) {
        digits[halfLen] = '0';
    }
    return stoi(digits);
}

int nextValidPalin(int a) {
    if (a < maxA) {
        char d, nd;
        // a is at least 3 digits long --> halfLen >= 1
        if (len % 2 != 0) {
            d = str[halfLen];
//            cout << "d = " << d << endl;
            nd = (char) ((d - '0' + 1) % 10 + '0');
//            cout << "nd = " << nd << endl;
            str[halfLen] = nd;
//            cout << "strA = " << strA << endl;
            if (d < '9') {
                return stoi(str);
            }
        }
        int i = halfLen - 1;
        do {
            d = str[i];
            nd = (char) ((d - '0' + 1) % 10 + '0');
            str[i] = nd;
            str[len - i - 1] = nd;
        } while (i-- > -1 && d == '9');
        d = str[0];
        if (!boundingDigits[d - '0']) {
            nd = nextBoundingDigits[d - '0'];
            str[0] = nd;
            str[len - 1] = nd;
        }
        return stoi(str);
    }
    len++;
    halfLen = len / 2;
    return getMinPalin();
}

int getMaxPalin() {
    char digits[len];
    for (int i = 0; i < halfLen; i++) {
        digits[i] = digits[len - i - 1] = '9';
    }
    if (len % 2 != 0) {
        digits[halfLen] = '8';
    }
    return stoi(digits);
}

int getValidPalin() {
    int t = 101;
    str = to_string(t);
    len = str.length();
    halfLen = len / 2;
    maxA = getMaxPalin();
    while (t < a) {
        t = nextValidPalin(t);
        if (t > maxA) {
            maxA = getMaxPalin();
        }
    }
    return t;
}

void solve() {
    if (solveTrivialCases()) {
        // If still has more cases
        // Remember a must be at least 3 digits long by now!
        initOddPrimes();
        initBoundingDigits();
        a = getValidPalin();

        while (a <= b) {
            if (isPrime(a)) {
                cout << a << endl;
            }
            a = nextValidPalin(a);
//            cout << "a = " << a << endl;
            if (a > maxA) {
                maxA = getMaxPalin();
            }
        }
    }
}

int main() {
    freopen("pprime.in", "r", stdin);
    freopen("pprime.out", "w", stdout);
    cin >> a >> b;

    solve();
    return 0;
}



/* Sample input:
5 500
 */
/* Sample output:
5
7
11
101
131
151
181
191
313
353
373
383
 */

/*
USER: Trung Vu [trungvt2]
TASK: pprime
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1476 KB]
   Test 2: TEST OK [0.004 secs, 1456 KB]
   Test 3: TEST OK [0.004 secs, 1336 KB]
   Test 4: TEST OK [0.004 secs, 1468 KB]
   Test 5: TEST OK [0.004 secs, 1388 KB]
   Test 6: TEST OK [0.004 secs, 1368 KB]
   Test 7: TEST OK [0.021 secs, 1260 KB]
   Test 8: TEST OK [0.014 secs, 1480 KB]
   Test 9: TEST OK [0.025 secs, 1296 KB]

All tests OK.
Your program ('pprime') produced all correct answers!  This is your
submission #11 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 6 bytes] ----
5 500
------- test 2 [length 10 bytes] ----
750 14000
------- test 3 [length 15 bytes] ----
123456 1123456
------- test 4 [length 14 bytes] ----
97000 1299000
------- test 5 [length 16 bytes] ----
9878210 9978210
------- test 6 [length 16 bytes] ----
9902099 9902100
------- test 7 [length 11 bytes] ----
7 10000000
------- test 8 [length 16 bytes] ----
1333331 9743479
------- test 9 [length 12 bytes] ----
5 100000000
 */
