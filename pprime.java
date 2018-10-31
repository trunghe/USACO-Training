/*
ID: trungvt2
LANG: JAVA
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

import java.io.*;
import java.util.*;

public class pprime {

    static String filename = "pprime";
    static BufferedReader br;
    static PrintWriter pw;
    static StringTokenizer st;
    static int a, b;
    static boolean[] notPrime;
    static LinkedList<Integer> oddPrimes;
    static boolean[] boundingDigits;
    static char[] nextBoundingDigits;

    public static void main(String[] args) throws IOException {
        System.setIn(new FileInputStream(filename + ".in"));
        System.setOut(new PrintStream(filename + ".out"));
        // Use BufferedReader rather than RandomAccessFile; it's much faster
        br = new BufferedReader(new InputStreamReader(System.in));
        // input file name goes above
        pw = new PrintWriter(new BufferedOutputStream(System.out));

        input();

        solve();

    }

    private static void solve() {
        if (solveTrivialCases()) {
            // If still has more cases
            // Remember a must be at least 3 digits long by now!
            initOddPrimes();
            initBoundingDigits();
            a = getValidPalin(a);

            StringBuilder strA = new StringBuilder(Integer.toString(a, 10));
            int len = strA.length();
            int halfLen = len / 2;
            int maxA = getMaxPalin(len, halfLen);

            while (a <= b) {
                if (isPrime(a)) {
                    pw.println(a);
                }
                a = nextValidPalin(a, strA, len, halfLen, maxA);
                if (a > maxA) {
                    strA = new StringBuilder(Integer.toString(a, 10));
                    len++;
                    halfLen = len / 2;
                    maxA = getMaxPalin(len, halfLen);
                }
            }
        }

        pw.close();                                  // close the output file
    }

    private static int getValidPalin(int a) {
        int t = 101;
        StringBuilder sb = new StringBuilder(Integer.toString(t, 10));
        int len = sb.length();
        int halfLen = len / 2;
        int maxT = getMaxPalin(len, halfLen);
        while (t < a) {
            t = nextValidPalin(t, sb, len, halfLen, maxT);
            if (t > maxT) {
                sb = new StringBuilder(Integer.toString(t, 10));
                len++;
                halfLen = len / 2;
                maxT = getMaxPalin(len, halfLen);
            }
        }
        return t;
    }

    private static int nextValidPalin(int a, StringBuilder strA,
                                      int len, int halfLen, int maxA) {
        if (a < maxA) {
            char d, nd;
            // a is at least 3 digits long --> halfLen >= 1
            if (len % 2 != 0) {
                d = strA.charAt(halfLen);
                nd = (char) ((d - '0' + 1) % 10 + '0');
                strA.setCharAt(halfLen, nd);

                if (d < '9') {
                    return Integer.parseInt(strA.toString());
                }
            }
            int i = halfLen - 1;
            do {
                d = strA.charAt(i);
                nd = (char) ((d - '0' + 1) % 10 + '0');
                strA.setCharAt(i, nd);
                strA.setCharAt(len - i - 1, nd);
            } while (i-- > -1 && d == '9');
            d = strA.charAt(0);
            if (!boundingDigits[d - '0']) {
                nd = nextBoundingDigits[d - '0'];
                strA.setCharAt(0, nd);
                strA.setCharAt(len - 1, nd);
            }
            return Integer.parseInt(strA.toString());
        }
        len++;
        return getMinPalin(len, len / 2);
    }

    private static int getMinPalin(int len, int halfLen) {
        char[] digits = new char[len];
        digits[0] = digits[len - 1] = '1';
        for (int i = 1; i < halfLen; i++) {
            digits[i] = digits[len - i - 1] = '0';
        }
        if (len % 2 != 0) {
            digits[halfLen] = '0';
        }
        return Integer.parseInt(new String(digits));
    }

    private static int getMaxPalin(int len, int halfLen) {
        char[] digits = new char[len];
        for (int i = 0; i < halfLen; i++) {
            digits[i] = digits[len - i - 1] = '9';
        }
        if (len % 2 != 0) {
            digits[halfLen] = '8';
        }
        return Integer.parseInt(new String(digits));
    }

    private static void initBoundingDigits() {
        boundingDigits = new boolean[10];
        nextBoundingDigits = new char[10];
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

    private static boolean isPrime(int a) {
        for (int i : oddPrimes) {
            if (a % i == 0) {
                return false;
            }
        }
        return true;
    }

    private static void initOddPrimes() {
        int rootB = (int) Math.sqrt(b) + 1;
        oddPrimes = new LinkedList<>();
        notPrime = new boolean[rootB + 1];
        notPrime[0] = true;
        notPrime[1] = true;
        for (int i = 2; i <= rootB; i++) {
            if (notPrime[i]) {
                continue;
            } else {
                oddPrimes.addLast(i);
                for (int j = i * 2; j <= rootB; j += i) {
                    notPrime[j] = true;
                }
                // If found a valid palindrome then output it anyway
                if (i >= a && isPalin(Integer.toString(i, 10))) {
                    pw.println(i);
                    a = i + 1;
                }
            }
        }
        oddPrimes.removeFirst(); // Remove unnecessary number 2
    }

    private static boolean isPalin(String str) {
        int len = str.length();
        int halfLen = len / 2;
        for (int j = 0; j < halfLen; j++) {
            if (str.charAt(j) != str.charAt(--len)) {
                return false;
            }
        }
        return true;
    }

    private static boolean solveTrivialCases() {
        if (a < 6) {
            pw.println(5);
        }
        if (a < 8 && b > 6) {
            pw.println(7);
        }
        if (a < 12 && b > 10) {
            pw.println(11);
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

    private static void input() throws IOException {
        // Use StringTokenizer vs. readLine/split -- lots faster
        st = new StringTokenizer(br.readLine());
        // Get line, break into tokens
        a = Integer.parseInt(st.nextToken());    // first integer
        b = Integer.parseInt(st.nextToken());    // second integer
    }

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
LANG: JAVA

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.093 secs, 23920 KB]
   Test 2: TEST OK [0.133 secs, 23872 KB]
   Test 3: TEST OK [0.103 secs, 23780 KB]
   Test 4: TEST OK [0.114 secs, 23736 KB]
   Test 5: TEST OK [0.105 secs, 23944 KB]
   Test 6: TEST OK [0.098 secs, 23360 KB]
   Test 7: TEST OK [0.177 secs, 25380 KB]
   Test 8: TEST OK [0.310 secs, 25464 KB]
   Test 9: TEST OK [0.208 secs, 26244 KB]

All tests OK.
Your program ('pprime') produced all correct answers!  This is your
submission #4 for this problem.  Congratulations!
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
