#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <ctime>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

int n, m;
char A[1000][1000];
vi order;
bool visited[2000];
bool eqVisited[2000];
int dist[2000];
vi children[2000];
set<int> finalChildren[2000];
int nodeMap[2000];
vi equalityChildren[2000];
set<int> S;

bool isCyclic(int node) {
    visited[node] = true;
    if (S.count(node) > 0) return true;
    S.insert(node);
    for (int child : finalChildren[node]) {
        if (!visited[nodeMap[child]] && isCyclic(nodeMap[child])) return true;
        else if (S.count(nodeMap[child]) > 0) return true;
    }
    S.erase(node);
    return false;
}

void dfsEq(int node, int magic) {
    nodeMap[node] = magic;
    eqVisited[node] = true;
    for (int child : equalityChildren[node]) {
        if (!eqVisited[child]) {
            dfsEq(child, magic);
            for (int otherChild : children[child]) {
                finalChildren[magic].insert(otherChild);
            }
        }
    }
    for (int child : children[node]) finalChildren[magic].insert(child);
}

void topoSort(int i) {
    visited[i] = true;
    for (int child : finalChildren[i]) {
        if (!visited[nodeMap[child]]) topoSort(nodeMap[child]);
    }
    order.pb(i);
}

int main() {
    cin >> n >> m;
    F0R(i, n) F0R(j, m) cin >> A[i][j];
    F0R(i, n + m) {
        int start, end;
        if (i < n) {
            start = n, end = n + m;
        } else {
            start = 0, end = n;
        }
        FOR(j, start, end) {
            if ((i < n && A[i][j - n] == '<') || (i >= n && A[j][i - n] == '>')) children[i].pb(j);
            if ((i < n && A[i][j - n] == '=') || (i >= n && A[j][i - n] == '=')) equalityChildren[i].pb(j);
        }
    }

    SET(eqVisited, false, 2000);
    F0R(i, n + m) {
        if (!eqVisited[i]) dfsEq(i, i);
    }

    SET(visited, false, 2000);
    F0R(i, n + m) {
        if (!visited[nodeMap[i]] && isCyclic(nodeMap[i])) {
            cout << "No" << endl;
            return 0;
        }
    }

    SET(visited, false, 2000);
    F0R(i, n + m) {
        if (!visited[nodeMap[i]]) topoSort(nodeMap[i]);
    }
    reverse(order.begin(), order.end());
    SET(dist, 1, 2000);

    for (int x : order) {
        for (int child : finalChildren[nodeMap[x]]) {
            MAX(dist[nodeMap[child]], dist[nodeMap[x]] + 1);
        }
    }

    cout << "Yes" << endl;
    cout << dist[nodeMap[0]];
    FOR(i, 1, n) cout << " " << dist[nodeMap[i]];
    cout << endl << dist[nodeMap[n]];
    FOR(i, n + 1, n + m) cout << " " << dist[nodeMap[i]];
    cout << endl;

    return 0;
}