/*
ID: trungvt2
LANG: JAVA
TASK: ariprog
*/

/*
http://train.usaco.org/usacoprob2?a=NCwlhwOwFxv&S=ariprog
Description: TODO Write a description
Category: Search
Solution: DFS
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

import java.io.*;

public class ariprog {

    static String filename = "ariprog";
    static BufferedReader br;
    static PrintWriter pw;
    static int n, m;
    static boolean[] bisquares;
    static int[] squares;
    static int twiceSquareM;

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
        StringBuilder ans = new StringBuilder();
        initBiquares();
        int nLessOne = (n - 1);
        int maxB = twiceSquareM / nLessOne;
        for (int b = 1; b <= maxB; b++) {
            int maxA = twiceSquareM - b * nLessOne;

            for (int a = 0; a <= maxA; a++) {
                if (dfs(a, b, 0)) {
                    ans.append(a);
                    ans.append(' ');
                    ans.append(b);
                    ans.append('\n');
                }
            }
        }
        if (ans.length() > 0) {
            pw.print(ans);
        } else {
            pw.println("NONE");
        }
        pw.close();                                  // close the output file
    }

    private static boolean dfs(int a, int b, int mul) {
        if (mul == n) {
            return true;
        }
        if (!bisquares[a]) {
            return false;
        }
        return dfs(a + b, b, mul + 1);
    }

    private static void initBiquares() {
        squares = new int[m + 1];
        squares[m] = (int) Math.pow(m, 2);
        twiceSquareM = 2 * squares[m];
        bisquares = new boolean[twiceSquareM + 1];
        bisquares[squares[m]] = true;
        for (int i = 0; i < m; i++) {
            squares[i] = (int) Math.pow(i, 2);
            bisquares[squares[i]] = true;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= m; j++) {
                bisquares[squares[i] + squares[j]] = true;
            }
        }
    }

    private static void input() throws IOException {
        n = Integer.parseInt(br.readLine());    // first integer
        m = Integer.parseInt(br.readLine());    // second integer
    }
/* Sample input:
5
7
 */
/* Sample output:
1 4
37 4
2 8
29 8
1 12
5 12
13 12
17 12
5 20
2 24
 */
}
