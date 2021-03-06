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
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
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
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

class MaxSegTree {
private: vi st, A;
    int n;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R)
            st[p] = A[L];
        else {
            build(left(p) , L              , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R          );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = max(p1, p2);
        } }

    int rmq(int p, int L, int R, int i, int j) {
        if (i >  R || j <  L) return -1;
        if (L >= i && R <= j) return st[p];

        int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

        if (p1 == -1) return p2;
        if (p2 == -1) return p1;
        return max(p1, p2); }

    int update_point(int p, int L, int R, int idx, int new_value) {
        int i = idx, j = idx;

        if (i > R || j < L)
            return st[p];

        if (L == i && R == j) {
            A[i] = new_value;
            return st[p] = A[L];
        }

        int p1, p2;
        p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
        p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

        return st[p] = max(p1, p2);
    }

public:
    MaxSegTree(const vi &_A) {
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

    int update_point(int idx, int new_value) {
        return update_point(1, 0, n - 1, idx, new_value); }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    int n; cin >> n;
    int A[n], B[n], revA[n], revB[n];
    F0R(i, n) {
        cin >> A[i];
        A[i]--;
        revA[A[i]] = i;
    }
    F0R(i, n) {
        cin >> B[i];
        B[i]--;
        revB[B[i]] = i;
    }
    vii points;
    F0R(i, n) {
        FOR(j, i-4, i+5) {
            if (j < 0 || j >= n) continue;
            points.emplace_back(revA[i], revB[j]);
        }
    }
    sort(points.begin(), points.end(), [](const ii &a, const ii &b) {
        return a.pA == b.pA ? a.pB > b.pB : a.pA < b.pA;
    });

    vi v = vector<int>(n, 0);
    MaxSegTree ST = MaxSegTree(v);

    int best = 0;
    for (ii point : points) {
        int bestPrev = ST.rmq(0, point.pB-1);
        ST.update_point(point.pB, bestPrev + 1);
        best = max(best, bestPrev + 1);
    }
    cout << best << endl;

    return 0;
}