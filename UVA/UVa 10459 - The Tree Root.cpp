
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

int n; 
vi children[5000];
int dist[5000];
int dist2[5000];

ii dfs(int node, int parent) {
    int maxDepth = 0, maxNode = node;
    for (int child : children[node]) {
        if (child == parent) continue;
        ii res = dfs(child, node);
        if (res.pA > maxDepth) {
            maxDepth = res.pA;
            maxNode = res.pB;
        }
    }
    return mp(maxDepth + 1, maxNode);
}

void setDist(int node, int d, int parent) {
    dist[node] = d;
    for (int child : children[node]) {
        if (child == parent) continue;
        setDist(child, d + 1, node);
    }
}

void setDist2(int node, int d, int parent) {
    dist2[node] = d;
    for (int child : children[node]) {
        if (child == parent) continue;
        setDist2(child, d + 1, node);
    }
}

int main() {
    while (cin >> n) {
        assert(n <= 5000);
        F0R(i, n) {
            int x; cin >> x;
            children[i].clear();
            F0R(j, x) {
                int y; cin >> y;
                children[i].pb(y - 1);
            }
        }
        vi bestRoots, worstRoots;

        ii one = dfs(0, 0);
        ii two = dfs(one.pB, one.pB);

        int diameter = two.pA;
        setDist(one.pB, 0, one.pB);
        setDist2(two.pB, 0, two.pB);

        F0R(i, n) {
            if (dist[i] <= diameter/2 && dist2[i] <= diameter/2) bestRoots.pb(i);
            if (dist[i] == diameter - 1 || dist2[i] == diameter - 1) worstRoots.pb(i);
        }

        cout << "Best Roots  :";
        for (int x : bestRoots) cout << " " << x + 1;
        cout << endl;
        cout << "Worst Roots :";
        for (int x : worstRoots) cout << " " << x + 1;
        cout << endl;
    }


    return 0;
}
