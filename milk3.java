/*
ID: trungvt2
LANG: JAVA
TASK: milk3
*/

/*
http://train.usaco.org/usacoprob2?S=milk3&a=NCwlhwOwFxv
Description: TODO Write a description
Category: Search
Solution: DFS
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

import java.io.*;
import java.util.*;

public class milk3 {

    static String filename = "milk3";
    static BufferedReader br;
    static PrintWriter pw;
    static StringTokenizer st;
    static int[] capacity;
    static boolean[][] visited;
    static boolean[] valid;

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

        visited = new boolean[capacity[1] + 1][capacity[2] + 1];
        valid = new boolean[capacity[2] + 1];

        int[] buckets = {0, 0, capacity[2]};
        dfs(buckets);

        StringBuilder ans = new StringBuilder();
        for (int i = 0; i <= capacity[2]; i++) {
            if (valid[i]) {
                ans.append(i);
                ans.append(' ');
            }
        }
        ans.deleteCharAt(ans.length() - 1);
        pw.println(ans);
        pw.close();                                  // close the output file
    }

    private static void dfs(int[] buckets) {
        visited[buckets[1]][buckets[2]] = true;
        if (buckets[0] == 0) {
            valid[buckets[2]] = true;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Try to pour from bucket i to bucket j.
                if (i != j && buckets[i] > 0 && buckets[j] < capacity[j]) {
                    int[] buckets2 = new int[3];
                    for (int k = 0; k < 3; k++) {
                        buckets2[k] = buckets[k];
                    }
                    buckets2[j] += buckets2[i];
                    if (buckets2[j] > capacity[j]) {
                        buckets2[i] = buckets2[j] - capacity[j];
                        buckets2[j] = capacity[j];
                    } else {
                        buckets2[i] = 0;
                    }
                    if (!visited[buckets2[1]][buckets2[2]]) {
                        dfs(buckets2);
                    }
                }
            }
        }

    }

    private static void input() throws IOException {
        // Use StringTokenizer instead of readLine/split -- lots faster
        st = new StringTokenizer(br.readLine());
        capacity = new int[3];
        for (int i = 0; i < 3; i++) {
            capacity[i] = Integer.parseInt(st.nextToken());
        }
    }
/* Sample input:
8 9 10
 */
/*
Sample output:
1 2 8 9 10
 */
}
