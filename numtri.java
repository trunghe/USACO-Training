/*
ID: trungvt2
LANG: JAVA
TASK: numtri
*/

/*
http://train.usaco.org/usacoprob2?S=numtri&a=NCwlhwOwFxv
Description: TODO Write a description
Category:
Solution:
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

import java.io.*;
import java.util.*;

public class numtri {

    static String filename = "numtri";
    static BufferedReader br;
    static PrintWriter pw;
    static StringTokenizer st;
    static int n;
    static int[][] rows;

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
        if (n > 1) {
            for (int i = n - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    rows[i - 1][j] += Math.max(rows[i][j], rows[i][j + 1]);
                }
            }
        }
        pw.println(rows[0][0]);

        pw.close();                                  // close the output file
    }

    private static void input() throws IOException {
        n = Integer.parseInt(br.readLine());
        rows = new int[n][];
        for (int i = 0; i < n; i++) {
            rows[i] = new int[i + 1];
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j <= i; j++) {
                rows[i][j] = Integer.parseInt(st.nextToken());
            }
        }
    }
}
/* Sample input:
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
 */
/* Sample output:
30
 */
