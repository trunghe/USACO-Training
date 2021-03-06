/*
ID: trungvt2
TASK: castle
LANG: C++
*/

/*
http://train.usaco.org/usacoprob2?a=PnagbbLf40O&S=castle
http://olympiads.win.tue.nl/ioi/ioi94/contest/day1prb2/problem.html
Description: TODO Write a description
Category: Graph
Solution: Flood Fill
Complexity: TODO Analyze complexity
Author: Vu Thanh Trung
 */

#include <bits/stdc++.h>
using namespace std;

#define MAX 50
#define west 0
#define north 1
#define east 2
#define south 3
#define ii pair<int, int>
#define p(a, b) make_pair((a), (b))
#define FORI(i, a, b) for (int i = (a); i <= (b); i++)

const bool TESTING = false;

struct Wall {
    ii module;
    int direction;
    int potential;
};

struct Room {
    bool wall[4];
};

static Room castle[MAX + 1][MAX + 1];
static int noCols, noRows;
static bool visitedConnected[MAX + 1][MAX + 1];
static int roomNums[MAX + 1][MAX + 1];
static Wall bestWall;
static int roomNum;
static int roomSize[(int) pow(MAX, 2) + 1];
static int largestRoomSize;
static char directions[4] = {'W', 'N', 'E', 'S'};
static int noUnvisitedModules;

void displayCastle() {
    for (int k = 0; k < noCols; ++k) {
        cout << " _";
    }
    cout << endl;
    for (int i = 1; i <= noRows; ++i) {
        cout << '|';
        for (int j = 1; j <= noCols; ++j) {
            cout << (castle[i][j].wall[south] ? '_' : ' ');
            cout << (castle[i][j].wall[east] ? '|' : ' ');
        }
        cout << endl;
    }
    cout << endl;
}

void input() {
    cin >> noCols >> noRows;
    int w;
    for (int i = 1; i <= noRows; ++i) {
        for (int j = 1; j <= noCols; ++j) {
            cin >> w;
            for (int d = west; d <= south; ++d) {
                castle[i][j].wall[d] = w % 2;
                w /= 2;
            }
        }
    }
    if (TESTING) {
        displayCastle();
    }
}

bool outside(int i, int range) {
    return i <= 0 || i > range;
}

void evaluateWall(int r, int c, int d, int newR, int newC) {
    // Assume already checked that this is an interior wall.
    if (roomNums[newR][newC] == roomNums[r][c]) {
        // If the next module is unexplored or wall in the same room
        return;
    }
    // Else the next module is already explored and its size determined.
    int newPotential = roomSize[roomNums[r][c]] + roomSize[roomNums[newR][newC]];
    if (newPotential < bestWall.potential) {
        return;
    }
    if (c < newC) { // More West
        newC = c;
        newR = r;
    } else if (c == newC && r > newR) { // More South
        newR = r;
        newC = c;
    } else { // Flip the direction of the wall
        d = (d + 2) % 4;
    }
    if (newPotential > bestWall.potential) {
        bestWall.potential = newPotential;
        bestWall.module = p(newR, newC);
        bestWall.direction = d;
        return;
    }
    // Equal potential, check location.
    if (newC < bestWall.module.second
        || (newC == bestWall.module.second && newR > bestWall.module.first)) {
        bestWall.module = p(newR, newC);
        bestWall.direction = d;
    }
    if (TESTING) {
        cout << "New bestWall: " << bestWall.potential << "; ("
            << bestWall.module.first << "," << bestWall.module.second
            << ") " << directions[bestWall.direction] << endl;
    }
}

void dfs(int r, int c, int roomNum) {
    roomSize[roomNum]++;
    if (largestRoomSize < roomSize[roomNum]) {
        largestRoomSize = roomSize[roomNum];
    }
    roomNums[r][c] = roomNum;
    visitedConnected[r][c] = true;
    noUnvisitedModules--;
    Room current = castle[r][c];
    for (int d = 0; d < 4; ++d) {
        int newR = r;
        int newC = c;
        if (d % 2 != 0) {
            newR += (d - 2);
            if (outside(newR, noRows)) {
                continue;
            }
        } else {
            newC += (d - 1);
            if (outside(newC, noCols)) {
                continue;
            }
        }
        if (!current.wall[d]) {
            if (!visitedConnected[newR][newC]) {
                dfs(newR, newC, roomNum);
            }
        }
    }
}

void init() {
    noUnvisitedModules = noRows * noCols;
    roomNum = 0;
    largestRoomSize = 1;
    bestWall.module = p(1, 1);
    bestWall.direction = west;
    bestWall.potential = 1;
    FORI(i, 1, noUnvisitedModules) {
        roomSize[i] = 0;
//        cout << "Size of room " << i << ": " << roomSize[i] << endl;
    }

}

void solve() {
    init();
    for (int r = 1; r <= noRows; ++r) {
        for (int c = 1; c <= noCols; ++c) {
            if (!visitedConnected[r][c]) {
                dfs(r, c, ++roomNum);
                if (noUnvisitedModules == 0) {
                    break;
                }
            }
        }
    }
    for (int r = 1; r <= noRows; ++r) {
        for (int c = 1; c <= noCols; ++c) {
            Room current = castle[r][c];
            for (int d = 0; d < 4; ++d) {
                int newR = r;
                int newC = c;
                if (d % 2 != 0) {
                    newR += (d - 2);
                    if (outside(newR, noRows)) {
                        continue;
                    }
                } else {
                    newC += (d - 1);
                    if (outside(newC, noCols)) {
                        continue;
                    }
                }
                if (current.wall[d]) {
                    evaluateWall(r, c, d, newR, newC);
                }
            }
        }
    }
    cout << roomNum << endl << largestRoomSize << endl
         << bestWall.potential << endl
         << bestWall.module.first << ' '
         << bestWall.module.second << ' '
         << directions[bestWall.direction] << endl;
    if (TESTING) {
        FORI(i, 1, noRows) {
            FORI(j, 1, noCols) {
                cout << roomNums[i][j] << '\t';
            }
            cout << endl;
        }
        cout << endl;
        FORI(i, 1, roomNum) {
            cout << "Size of room " << i << ": " << roomSize[i] << endl;
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);

    input();
    solve();
    return 0;
}

/* Sample input:
7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13
 */
/* Sample output:
5
9
16
4 1 E
 */

/*
USER: Trung Vu [trungvt2]
TASK: castle
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1356 KB]
   Test 2: TEST OK [0.004 secs, 1472 KB]
   Test 3: TEST OK [0.004 secs, 1336 KB]
   Test 4: TEST OK [0.004 secs, 1476 KB]
   Test 5: TEST OK [0.004 secs, 1344 KB]
   Test 6: TEST OK [0.004 secs, 1364 KB]
   Test 7: TEST OK [0.004 secs, 1360 KB]
   Test 8: TEST OK [0.004 secs, 1340 KB]

All tests OK.
Your program ('castle') produced all correct answers!  This is your
submission #5 for this problem.  Congratulations!
Here are the test data inputs:
------- test 1 [length 74 bytes] ----
7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13
------- test 2 [length 10 bytes] ----
2 1
15 15
------- test 3 [length 58 bytes] ----
5 5
3 2 6 3 6
1 8 4 1 4
13 7 13 9 4
3 0 2 6 5
9 8 8 12 13
------- test 4 [length 527 bytes] ----
15 14
11 14 3 6 3 6 3 6 3 6 3 6 11 2 6
3 10 12 9 12 9 12 9 12 9 12 9 6 1 4
13 7 11 10 10 10 10 10 10 14 11 6 5 1 4
11 4 3 10 10 10 10 10 10 10 6 5 13 1 4
7 13 5 7 11 10 2 10 14 7 5 13 7 9 12
1 14 5 1 10 14 5 11 10 4 9 6 1 10 6
13 7 5 5 3 10 8 10 6 5 3 12 9 10 12
11 4 5 13 5 3 10 6 5 13 5 3 10 10 6
7 13 1 10 4 1 10 4 1 10 4 5 3 10 12
1 14 5 7 5 9 10 12 5 7 5 5 9 10 6
13 7 13 5 9 10 2 10 12 13 13 5 3 10 12
7 5 15 9 10 14 5 11 14 11 14 5 9 10 6
5 13 7 7 11 10 8 10 14 7 3 12 3 10 12
13 15 13 13 11 10 14 11 10 12 9 10 8 10 14
------- test 5 [length 222 bytes] ----
10 10
11 10 10 14 7 3 10 2 2 6
3 2 2 6 5 1 2 0 0 4
1 0 0 4 5 1 0 0 0 4
1 0 0 4 13 9 8 8 8 4
1 0 0 4 7 11 10 10 14 13
1 0 0 4 5 7 3 2 2 6
1 0 0 4 5 5 1 0 0 4
1 0 0 4 13 5 1 0 0 4
1 0 0 4 7 5 1 0 0 4
9 8 8 12 13 13 9 8 8 12
------- test 6 [length 2056 bytes] ----
32 32
3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 6 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 6
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4
9 8 8 8 8 8 8 8 8 8 8 8 8 8 8 12 9 8 8 8 8 8 8 8 8 8 8 8 8 8 8 12
------- test 7 [length 7506 bytes] ----
50 50
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15 15
------- test 8 [length 5993 bytes] ----
50 50
7 15 7 3 14 11 10 10 14 3 2 2 6 15 7 7 7 7 11 2 6 3 10 2 6 15 3 14 3 10 10 10 6 11 10 2 14 7 7 11 14 3 14 7 7 15 11 14 15 7
1 14 9 0 10 14 15 7 7 13 9 8 8 2 0 12 9 0 2 4 13 1 14 5 9 6 9 14 13 7 15 7 13 3 10 0 2 4 13 15 11 4 15 13 13 11 10 10 6 5
13 15 11 8 14 11 6 5 13 3 6 15 11 12 1 14 15 1 12 9 6 1 6 1 10 4 11 6 3 8 2 4 7 13 3 12 13 13 3 6 15 9 2 6 3 14 7 7 1 12
7 3 14 7 3 14 5 1 2 0 4 15 11 14 13 11 2 0 14 11 12 1 0 8 6 1 2 12 5 15 5 1 8 14 13 11 2 2 4 1 6 11 12 13 1 14 9 12 5 7
9 0 14 1 8 2 8 0 4 1 4 3 2 14 7 7 5 13 11 14 3 12 9 10 4 9 0 14 1 2 0 0 10 6 11 10 4 1 4 9 0 14 15 15 9 10 10 10 0 12
7 9 6 13 3 12 15 9 4 5 13 1 4 15 1 8 4 3 2 2 0 6 7 15 5 15 9 2 12 1 12 5 11 4 7 7 1 8 8 6 5 11 10 6 15 15 11 14 5 7
13 7 5 15 13 7 11 6 5 13 15 13 1 2 12 15 5 9 8 12 5 1 0 2 8 10 10 4 15 5 15 13 11 4 5 1 12 15 3 12 9 2 6 9 14 7 3 6 5 13
11 8 0 6 15 9 2 8 12 11 6 3 12 9 2 2 4 11 6 15 9 8 4 1 14 7 15 5 15 1 6 11 2 0 8 0 14 15 5 15 7 13 5 15 15 9 8 0 12 7
7 7 13 13 3 6 13 11 2 2 12 9 14 11 8 0 4 11 8 14 3 14 1 4 3 12 3 4 3 4 9 10 0 12 7 5 7 11 12 15 1 10 8 10 14 7 11 8 2 4
9 8 2 2 8 8 2 14 9 4 15 7 3 6 11 8 8 6 15 15 5 7 9 4 13 7 5 5 9 0 10 10 8 10 0 8 12 7 11 10 12 15 3 10 2 0 10 6 5 13
15 7 5 13 15 11 12 7 15 9 6 5 9 12 7 7 11 8 6 11 0 0 6 13 11 12 9 12 11 8 10 14 11 10 8 6 3 12 7 11 2 14 5 11 4 13 3 8 12 15
15 5 1 6 3 6 15 5 3 2 0 4 11 14 9 0 14 11 0 6 5 13 5 11 6 11 10 14 11 10 14 15 15 3 6 13 13 11 4 7 1 6 1 2 0 2 12 15 11 14
15 1 12 5 5 13 7 1 0 4 5 5 7 11 6 5 11 10 8 12 5 3 12 7 5 15 15 15 15 11 14 15 15 13 5 7 11 6 5 13 13 1 0 0 8 8 2 2 14 7
11 12 7 1 8 6 1 12 9 4 1 12 5 11 8 4 3 2 10 14 9 0 6 13 5 15 15 15 3 2 6 3 2 2 8 4 7 9 0 6 15 5 1 4 11 6 9 0 2 12
7 11 8 0 10 8 4 7 3 0 4 15 9 10 10 0 0 4 3 10 6 13 13 11 8 10 14 11 12 5 9 4 1 8 6 13 9 6 13 1 2 12 9 12 3 4 3 0 0 6
1 10 14 9 10 6 1 12 9 12 5 15 7 3 10 12 5 13 5 15 5 11 2 14 7 3 10 14 7 5 7 1 12 15 13 3 14 9 10 4 1 14 7 3 12 9 12 1 12 5
5 11 6 11 14 1 4 7 7 15 1 6 5 9 2 14 9 14 9 10 0 2 8 14 9 8 2 14 13 9 4 5 11 2 10 8 6 3 14 9 4 3 12 9 6 3 6 13 15 13
13 15 5 11 2 12 1 12 5 15 9 8 8 10 8 14 11 14 7 11 0 12 11 10 6 11 12 7 7 7 13 9 10 4 15 7 5 13 3 14 13 1 14 11 8 0 8 6 15 7
3 2 8 14 5 3 0 6 13 15 11 2 2 6 7 3 14 7 13 3 4 11 14 11 0 10 6 13 1 4 7 15 11 4 11 8 8 6 1 6 15 9 10 6 3 12 15 1 6 5
1 8 10 14 9 4 1 4 3 2 6 1 8 8 4 5 15 5 15 9 0 2 6 11 12 3 4 7 1 4 9 10 2 0 6 11 14 1 12 9 6 3 2 8 8 2 2 0 4 5
9 6 7 3 6 1 8 8 12 9 8 4 3 10 8 0 14 13 3 2 12 5 9 6 15 5 9 0 0 0 10 2 12 5 9 6 3 0 6 3 8 8 0 6 15 5 13 1 4 13
7 9 8 4 13 9 2 2 14 3 6 1 8 2 14 13 15 15 1 8 10 0 10 12 3 12 3 0 0 12 15 9 6 1 10 0 12 13 1 4 3 2 8 0 10 0 10 0 8 14
13 11 10 4 11 6 13 1 6 5 5 1 6 1 6 7 11 14 5 15 7 5 7 11 0 14 9 4 13 11 2 14 9 12 3 0 14 3 4 9 4 1 2 4 11 8 14 5 15 15
11 2 6 1 2 12 3 8 4 5 1 0 8 4 13 1 2 2 0 6 1 8 12 3 4 11 6 9 6 3 8 10 2 14 1 4 15 9 4 3 4 5 5 1 10 6 7 13 15 15
3 12 9 4 9 2 4 7 5 5 13 5 3 4 11 8 8 8 12 1 4 11 10 0 4 3 8 2 8 12 7 11 0 10 8 4 11 10 8 12 13 13 1 12 15 1 4 11 2 14
5 3 2 4 15 5 13 13 1 8 6 13 1 0 2 14 3 2 14 5 9 6 7 5 5 5 11 0 6 7 13 3 12 11 10 4 7 11 6 11 10 10 4 15 11 0 4 15 1 14
1 4 9 12 3 4 7 3 0 10 8 10 12 1 0 6 13 5 15 9 6 13 9 12 1 0 10 4 9 0 14 13 7 15 11 12 1 14 1 6 3 6 9 14 11 4 13 7 13 7
13 5 15 11 0 8 12 1 0 2 2 6 11 4 9 0 6 9 10 14 13 3 6 7 5 1 6 5 11 4 11 2 8 14 3 6 13 15 1 12 1 4 11 14 7 13 7 9 10 4
11 12 7 11 12 15 3 12 5 13 1 12 7 9 14 1 0 10 10 2 2 0 8 8 12 5 5 13 7 5 15 9 6 11 4 1 14 3 4 3 8 8 6 7 1 14 13 11 2 12
3 10 12 3 2 2 0 10 0 2 12 3 0 10 6 9 8 10 10 0 8 12 7 11 14 1 12 3 12 5 3 2 8 14 1 8 2 8 12 1 14 11 8 12 9 6 15 11 8 6
9 14 15 13 5 13 13 15 5 13 3 4 5 15 5 11 10 14 7 1 6 15 9 2 2 8 6 13 11 4 13 9 10 14 9 6 9 10 10 4 3 10 10 10 10 8 2 14 3 12
15 3 14 11 0 6 15 15 13 15 9 8 0 10 4 7 11 2 8 4 13 3 10 0 12 11 0 10 2 0 2 6 3 14 11 4 3 2 14 13 13 11 14 3 6 3 8 10 4 7
7 9 6 11 12 13 3 2 10 6 15 7 13 11 8 4 7 13 3 4 15 5 15 5 7 3 8 6 1 4 5 9 0 10 10 4 9 8 10 14 3 6 7 13 1 8 10 6 1 4
9 14 13 3 6 7 1 4 11 8 14 1 6 11 6 9 4 3 4 5 15 9 14 1 8 4 15 9 0 0 12 7 13 7 3 12 7 15 3 6 5 13 9 14 13 11 14 9 4 5
15 15 15 13 13 9 4 13 15 11 14 9 0 14 9 6 5 5 9 12 11 2 6 9 6 5 15 11 0 8 2 4 11 12 1 10 12 15 13 1 8 6 3 2 2 2 10 10 12 5
3 6 15 3 10 10 12 7 3 10 2 6 1 14 15 13 5 13 15 11 2 8 8 6 13 5 15 3 8 6 13 13 11 14 9 14 7 15 11 4 7 9 4 13 9 12 3 14 15 5
5 9 6 9 14 3 14 1 0 6 9 4 9 6 15 15 13 7 15 11 12 11 14 5 3 12 3 8 2 8 10 10 10 10 14 3 8 6 15 9 0 10 12 11 6 7 9 2 10 4
9 2 12 15 11 8 14 1 0 4 7 13 3 0 6 11 6 9 2 10 14 15 11 4 9 2 8 14 9 6 11 6 11 2 2 0 6 13 15 15 1 2 6 3 4 9 14 13 11 4
3 4 11 14 3 10 2 4 9 4 5 15 9 12 1 6 13 7 9 2 14 7 15 9 10 12 11 14 15 9 14 9 14 9 12 1 4 15 3 10 4 5 5 1 4 3 2 10 14 5
9 4 11 10 4 11 12 13 15 5 1 2 10 2 12 1 10 4 11 4 15 13 11 2 10 10 2 6 7 3 14 11 2 2 6 13 5 11 12 7 9 12 9 12 13 13 9 10 10 12
15 9 14 15 9 2 6 7 15 13 5 9 14 13 3 12 7 13 3 4 15 7 3 12 11 6 9 4 13 1 10 14 5 1 12 3 0 14 15 9 10 6 11 2 6 15 15 7 11 6
7 7 7 15 3 0 8 4 3 14 9 2 10 14 1 14 9 2 8 0 6 5 1 2 6 9 10 4 3 8 2 2 4 13 11 0 4 11 6 15 3 0 2 4 9 6 11 8 2 4
13 1 0 6 5 13 11 8 4 3 10 4 7 15 1 14 3 8 6 9 0 8 8 12 1 6 15 9 0 10 0 0 0 14 11 12 5 15 9 2 12 9 8 4 11 12 15 7 5 13
7 1 4 1 12 11 10 14 9 12 3 8 12 11 4 15 1 14 5 7 9 6 15 15 9 8 14 3 0 10 4 5 1 6 15 15 13 11 2 4 7 7 15 13 15 15 3 0 4 15
1 4 1 4 15 7 3 14 7 7 9 6 15 11 8 2 8 2 4 9 2 8 6 15 15 7 15 13 5 3 12 13 1 4 3 6 7 11 12 5 13 5 11 2 6 15 1 0 8 14
13 9 8 12 7 1 0 14 13 9 14 1 10 2 6 1 14 13 1 6 1 2 8 10 6 1 10 10 0 12 11 14 1 0 12 1 12 11 2 12 15 1 10 4 1 10 12 5 15 15
3 2 6 7 13 5 13 11 6 11 14 9 6 1 8 0 6 11 12 1 4 5 11 14 9 8 10 14 13 3 14 7 13 5 3 4 7 3 12 15 7 9 2 0 12 7 7 13 11 6
5 9 12 1 6 1 6 3 12 15 11 10 0 12 7 13 13 3 2 8 12 5 3 14 15 7 3 14 7 13 11 4 7 5 5 13 9 4 11 6 5 3 12 1 2 0 12 7 15 13
1 14 15 13 5 13 1 12 3 10 14 11 8 2 8 2 6 1 12 11 6 5 9 2 10 4 5 7 9 14 3 0 0 8 12 7 7 13 15 13 5 9 10 4 9 0 10 8 6 15
13 11 14 15 9 10 8 14 13 15 11 10 14 9 14 9 8 12 15 11 8 8 10 12 15 13 13 13 15 11 12 9 12 11 14 13 9 14 11 10 8 14 15 9 10 12 15 15 9 14
 */
