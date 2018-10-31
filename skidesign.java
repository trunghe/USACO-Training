/*
ID: trungvt2
LANG: JAVA
TASK: skidesign
*/

/*
Description: Given a list of N integers (1 <= N <= 1000) with each integer
                within [0, 100]. Given that the cost of change an integer to 
                a different integer is the square of the difference between
                the old and new value, find the minimum total cost to change
                the list such that the max - min <= 17.
                
Category: Greedy, Complete Search
Solution: Sort the list ascendingly. Then do complete search, checking
            every 17-unit-long interval within the sequence and
            calculate the total cost to change the rest of the sequence
            to fit inside the interval. Greedily take the minimum value.


hill	|		elevation intervals and cost
height  |(0,17)  (1,18)  (2,19)  (3,20)  (4,21)  (5,22)  (6,23)  (7,24)
------------------------------------------------------------------------
 1	    |   0	      0	      1	      4	      9	      16	    25	    36
 4	    |   0	      0	      0	      0	      0	      1	      4	      9
20	    |   9	      4	      1	      0	      0	      0	      0	      0
21	    |   16	    9	      4	      1	      0	      0	      0	      0
24	    |   49	    36	    25	    16	    9	      4	      1	      0
------------------------------------------------------------------------
total	|   74	    49	    31	    21	   *18*	    21	    30	    45


Complexity: O(nlog(n))
Author: Vu Thanh Trung
 */

import java.io.*;
import java.util.*;

public class skidesign {

    static String filename = "skidesign";
    static BufferedReader br;
    static PrintWriter pw;
    static ArrayList<Long> nums;
    static int n;

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
        Collections.sort(nums);
        long min = nums.get(0);
        long max = nums.get(n - 1);
        long diff;
        if ((diff = max - min) > 17) {
            long total = Long.MAX_VALUE;
            for (long i = 0; i < diff; i++) {
                total = Math.min(total, findTotal(i + min));
            }
            pw.println(total);
        } else {
            pw.println(0);
        }
        pw.close();
    }

    private static long findTotal(long start) {
        long total = 0;
        long end = start + 17;
        for (int i = 0; i < nums.size(); i++) {
            long d = start - nums.get(i);
            if (d > 0) {
                total += Math.pow(d, 2);
            } else {
                break;
            }
        }
        for (int i = nums.size() - 1; i > -1; i--) {
            long d = nums.get(i) - end;
            if (d > 0) {
                total += Math.pow(d, 2);
            } else {
                break;
            }
        }
        return total;
    }

    private static void input() throws IOException {
        n = Integer.parseInt(br.readLine());
        nums = new ArrayList<>(n);
        // Use StringTokenizer vs. readLine/split -- lots faster
        for (int i = 0; i < n; i++) {
            nums.add(Long.parseLong(br.readLine()));
        }
    }
/* Sample input:
5
20
4
1
24
21
*/
/* Sample output:
18
*/
}
