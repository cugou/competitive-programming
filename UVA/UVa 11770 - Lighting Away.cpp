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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

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
#define MOD2 1000000007
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
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
vi children[10000], S;
int dfsLow[10000], dfsNum[10000], dfsCtr, sccNum[10000], sccCtr, inDegree[10000];
bool visited[10000];

void tarjanSCC(int node) {
    dfsNum[node] = dfsLow[node] = dfsCtr++;
    visited[node] = true;
    S.pb(node);

    for (int child : children[node]) {
        if (dfsNum[child] == INF) tarjanSCC(child);
        if (visited[child]) dfsLow[node] = min(dfsLow[node], dfsLow[child]);
    }

    if (dfsLow[node] == dfsNum[node]) {
        while (true) {
            int next = S.back(); S.pop_back(); visited[next] = false;
            sccNum[next] = sccCtr;
            if (next == node) break;
        }
        sccCtr++;
    }
}

int main() {
    int t; cin >> t;
    F0R1(caseNum, t) {
        cin >> n >> m;
        S.clear();
        F0R(i, n) children[i].clear();
        SET(dfsLow, INF, 10000);
        SET(dfsNum, INF, 10000);
        dfsCtr = 0;
        SET(visited, false, 10000);
        SET(inDegree, 0, 10000);
        sccCtr = 0;

        F0R(i, m) {
            int a, b; cin >> a >> b;
            --a; --b;
            children[a].pb(b);
        }

        F0R(i, n) {
            if (dfsNum[i] == INF) tarjanSCC(i);
        }

        F0R(i, n) {
            for (int child : children[i]) {
                if (sccNum[i] == sccNum[child]) continue;
                inDegree[sccNum[child]]++;
            }
        }

        int ans = 0;
        F0R(i, sccCtr) {
            if (inDegree[i] == 0) ans++;
        }

        cout << "Case " << caseNum << ": " << ans << endl;
    }

    return 0;
}
