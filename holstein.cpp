/*
ID: trungvt2
TASK: holstein
LANG: C++
*/

/*
Burch & Kolstad
Farmer John prides himself on having the healthiest dairy cows in the world. He knows the vitamin content for one scoop of each feed type and the minimum daily vitamin requirement for his cows. Help Farmer John feed the cows so they stay healthy while minimizing the number of scoops that a cow is fed.
Given the daily requirements of each kind of vitamin that a cow needs, identify the smallest combination of scoops of feed a cow can be fed in order to meet at least the minimum vitamin requirements.
Vitamins are measured in integer units. Cows can be fed at most one scoop of any feed type. It is guaranteed that a solution exists for all contest input data.
PROGRAM NAME: holstein
INPUT FORMAT
Line 1:
integer V (1 <= V <= 25), the number of types of vitamins
Line 2:
V integers (1 <= each one <= 1000), the minimum requirement for each of the V vitamins that a cow requires each day
Line 3:
integer G (1 <= G <= 15), the number of types of feeds available
Lines 4..G+3:
V integers (0 <= each one <= 1000), the amount of each vitamin that one scoop of this feed contains. The first line of these G lines describes feed #1; the second line describes feed #2; and so on.
SAMPLE INPUT (file holstein.in)
4
100 200 300 400
3
50   50  50  50
200 300 200 300
900 150 389 399
OUTPUT FORMAT
The output is a single line of output that contains:
the minimum number of scoops a cow must eat, followed by:
a SORTED list (from smallest to largest) of the feed types the cow is given
If more than one set of feedtypes yield a minimum of scoops, choose the set with the smallest feedtype numbers.
SAMPLE OUTPUT (file holstein.out)
2 1 3
 */

/*
http://train.usaco.org/usacoprob2?a=K769GfH2zFb&S=holstein
Description: TODO Write a description
Category:
Solution: BFS + Bitmask
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

#define FOR(i, a, b) \
    for (int i = (a); i < (b); i++)

static int v, g;
static int goal[26];
static int f[16][26];

bool enough(vi b) {
    FOR(i, 0, v) {
        if (b[i] < goal[i]) {
            return false;
        }
    }
    return true;
}

vi feed(vi a, int i) {
    vi b;
    FOR(j, 0, v) {
        b.emplace_back(a[j] + f[i][j]);
    }
    return b;
}

void input() {
    cin >> v;
    FOR(i, 0, v) {
        cin >> goal[i];
    }
    cin >> g;
    FOR(i, 0, g) {
        FOR(j, 0, v) {
            cin >> f[i][j];
        }
    }
}

void printOrder(int order) {
    FOR(i, 0, g) {
        if (order & 1 << i) {
            cout << " " << i + 1;
        }
    }
    cout << endl;
}

void solve() {
    int minT = 1;
    list<vi> q1, q2;
    list<int> order1, order2, start;
    q1.emplace_back(vi(v, 0));
    order1.emplace_back(0);
    start.emplace_back(0);
    while (true) {
        while (!q1.empty()) {
            vi a = q1.front();
            q1.pop_front();
            int order = order1.front();
            order1.pop_front();
            int s = start.front();
            start.pop_front();
            FOR(i, s, g) {
                vi b = feed(a, i);
                int tOrder = order + (1 << i);
                if (enough(b)) {
                    cout << minT;
                    printOrder(tOrder);
                    return;
                }
                q2.emplace_back(b);
                order2.emplace_back(tOrder);
                start.emplace_back(i + 1);
            }
            q2.pop_back();
            order2.pop_back();
            start.pop_back();
        }
        list<vi> emptyQ;
        list<int> emptyOrders;
        q1 = q2;
        q2 = emptyQ;
        order1 = order2;
        order2= emptyOrders;
        minT++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    freopen("holstein.in", "r", stdin);
    freopen("holstein.out", "w", stdout);

    input();
    solve();

    return 0;
}

/* Sample input:
4
100 200 300 400
3
50   50  50  50
200 300 200 300
900 150 389 399
 */
/* Sample output:
2 1 3
 */

/*
USER: Trung Vu [trungvt2]
TASK: holstein
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1336 KB]
   Test 2: TEST OK [0.004 secs, 1360 KB]
   Test 3: TEST OK [0.004 secs, 1356 KB]
   Test 4: TEST OK [0.004 secs, 1348 KB]
   Test 5: TEST OK [0.004 secs, 1368 KB]
   Test 6: TEST OK [0.004 secs, 1364 KB]
   Test 7: TEST OK [0.004 secs, 1396 KB]
   Test 8: TEST OK [0.011 secs, 3108 KB]
   Test 9: TEST OK [0.004 secs, 1344 KB]
   Test 10: TEST OK [0.049 secs, 3892 KB]

All tests OK.
Your program ('holstein') produced all correct answers!  This is your
submission #11 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 10 bytes] ----
1
50
1
50
------- test 2 [length 48 bytes] ----
3
100 200 300
3
99 199 299
2 2 2
1000 1000 1000
------- test 3 [length 44 bytes] ----
4
1 1 1 1
4
1 1 0 0
1 0 1 0
0 1 0 1
0 0 0 1
------- test 4 [length 84 bytes] ----
5
10 20 30 40 50
5
10 10 10 10 10
0 10 10 10 10
0 0 10 10 10
0 0 0 10 10
0 0 0 0 10
------- test 5 [length 154 bytes] ----
8
10 10 10 10 10 10 10 10
7
1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2
3 3 3 3 3 3 3 3
4 4 4 4 4 4 4 4
100 100 100 100 100 100 0 0
5 5 5 5 5 5 10 0
5 5 5 5 5 5 0 10
------- test 6 [length 195 bytes] ----
5
163 221 146 425 509
10
98 69 68 18 129
132 185 196 64 176
40 70 57 9 115
73 189 145 87 117
45 114 45 0 18
137 137 174 73 178
48 143 33 142 192
33 107 148 2 158
32 42 153 90 41
165 81 156 7 121
------- test 7 [length 582 bytes] ----
15
335 425 380 283 513 140 360 349 505 187 358 309 485 495 190
10
123 137 194 60 137 89 153 122 115 198 47 76 38 62 112
31 105 1 155 93 25 74 15 177 191 146 32 47 115 7
116 72 139 64 112 39 173 33 61 118 119 136 32 132 100
37 143 7 159 27 44 170 158 71 72 160 125 56 155 28
4 31 77 184 26 185 184 77 69 159 130 154 44 31 154
87 41 171 91 126 92 108 197 145 87 8 189 64 92 93
197 197 199 16 16 6 181 113 150 27 57 146 54 41 44
61 48 48 22 181 121 124 164 138 94 124 61 191 151 102
9 14 36 15 179 7 87 179 131 20 31 51 198 128 108
198 3 164 32 27 41 42 179 147 169 168 97 122 156 183
------- test 8 [length 908 bytes] ----
20
924 519 510 589 901 627 827 814 520 725 674 709 777 512 540 731 695 801 984 517
12
143 197 55 68 193 181 88 163 109 98 159 36 197 139 45 176 34 128 93 0
83 25 61 46 5 46 66 5 44 47 100 93 180 176 51 198 50 21 69 119
126 54 27 100 145 29 123 2 82 95 148 109 69 106 99 105 142 89 36 27
13 144 70 120 170 129 195 15 86 29 24 134 37 147 161 168 123 0 71 114
181 94 165 119 198 30 173 25 93 130 126 62 85 34 0 170 131 49 171 11
24 108 110 154 55 123 78 74 23 181 54 73 91 173 42 152 83 104 6 132
114 67 169 73 145 152 122 80 162 39 95 139 167 167 16 80 75 36 126 106
121 108 168 194 52 88 111 187 118 39 53 103 139 108 30 76 57 136 198 43
45 107 113 3 0 121 162 169 73 45 86 12 70 122 40 149 184 100 135 60
77 154 97 176 186 164 3 147 65 29 119 8 41 166 3 69 188 90 97 35
106 16 167 192 107 170 30 164 92 175 107 60 118 172 57 141 152 55 15 14
198 83 112 82 94 38 176 54 179 3 104 48 113 121 12 106 50 7 26 25
------- test 9 [length 1405 bytes] ----
25
325 197 200 241 175 134 182 166 146 96 51 178 71 191 37 2 196 76 160 134 383 203 120 447 143
15
119 150 191 103 8 185 79 85 16 87 2 107 50 163 179 88 14 132 65 156 138 171 28 249 290
1 129 116 25 38 12 182 43 165 120 12 24 165 171 128 117 162 93 101 36 104 157 95 49 45
108 167 12 61 28 15 36 146 136 152 33 130 60 36 133 170 182 101 22 46 289 31 177 16 40
35 76 67 75 35 128 115 73 155 24 179 193 6 43 101 7 162 13 25 144 114 73 5 167 108
115 164 0 148 79 169 125 169 158 47 66 61 87 94 179 148 190 126 69 21 250 4 53 94 160
84 176 8 48 139 26 53 23 187 30 118 13 176 86 145 80 170 19 4 66 171 104 159 134 37
161 37 196 23 39 81 71 197 23 191 154 74 163 139 72 114 60 57 73 21 117 184 45 92 178
178 112 160 182 179 84 176 126 112 132 159 189 35 153 187 108 18 191 143 41 150 194 76 27 166
61 118 68 89 60 1 146 178 178 112 1 183 75 139 180 187 12 42 181 50 17 9 11 123 64
110 177 48 127 134 24 125 85 116 46 46 141 18 79 81 124 105 9 125 149 53 95 84 197 136
149 3 83 146 66 24 187 170 144 180 17 81 102 98 160 91 15 20 109 193 92 43 116 51 106
142 155 177 199 105 155 133 85 148 173 16 166 119 78 149 173 74 14 42 65 125 6 154 193 159
191 108 55 103 25 91 52 151 145 100 175 34 58 159 37 125 119 166 160 87 163 106 151 36 75
71 77 134 49 45 57 191 22 76 193 181 30 199 60 51 180 144 65 136 187 170 108 152 157 76
51 88 172 129 20 157 163 156 56 128 24 135 137 26 41 141 90 79 16 180 2 123 127 162 64
------- test 10 [length 1384 bytes] ----
25
826 953 853 512 620 769 722 833 719 754 730 521 908 622 877 737 534 882 560 812 684 787 984 983 783
15
167 78 129 9 41 56 71 132 29 45 61 152 13 76 172 152 27 21 0 38 24 93 25 155 18
84 69 79 59 179 166 107 28 79 63 11 101 95 73 172 70 141 97 72 170 74 132 48 195 136
88 97 174 121 28 28 157 29 56 148 1 46 160 188 114 179 49 55 22 20 79 98 144 153 100
98 23 58 152 58 197 72 199 1 171 18 57 61 64 78 100 61 192 135 92 80 168 129 144 192
178 80 119 78 95 14 15 102 26 135 127 145 130 95 117 193 95 98 19 163 135 81 74 182 85
121 35 187 43 113 58 56 152 56 183 162 76 90 43 138 38 142 107 156 197 105 81 95 29 9
182 124 77 118 106 55 143 6 18 194 92 145 159 61 132 59 12 80 144 179 39 42 122 51 102
14 107 32 188 114 67 127 165 15 100 102 183 5 34 125 28 69 180 69 71 2 114 131 107 45
64 107 118 27 151 160 74 129 77 35 188 35 105 160 148 189 122 177 144 139 33 145 5 59 74
162 74 58 98 48 123 149 6 35 148 93 2 103 144 189 28 108 91 26 49 150 64 81 166 119
87 144 20 64 49 93 51 132 105 185 91 115 74 169 46 154 55 17 159 42 188 163 189 73 161
36 7 65 4 4 162 132 166 89 82 10 13 182 92 118 157 123 106 168 127 158 169 84 21 159
112 73 38 102 93 185 119 195 97 10 14 156 146 54 190 26 111 44 109 18 83 91 78 193 164
175 7 54 63 78 84 60 156 20 84 140 183 130 142 14 41 17 97 14 60 155 27 184 9 156
103 173 20 51 174 96 90 35 196 77 122 23 137 43 195 41 70 89 4 26 64 186 170 51 13
 */
