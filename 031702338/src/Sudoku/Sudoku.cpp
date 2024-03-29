// Sudoku.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int>pii;
typedef vector<int>vi;

#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define fi first
#define se second
#define de(x) cout<<#x<<"="<<x<<endl;
#define dd(x) cout<<#x<<"="<<x<<" " ;
#define pb(x) push_back(x)
#define sz(x) (int)x.size()
#define lowbit(a) ((a)&-(a))
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
const int N = 1e5 + 5;
const int M = 1e3 + 5;
int m;
int mat[M][M];
struct DLX {
	int U[N], D[N], L[N], R[N], col[N], val[N], num[N];
	int cnt;
	int len;
	vi ans;
	void init(int _len) {
		len = _len;
		rep(i, 0, len + 1)U[i] = D[i] = L[i] = R[i] = col[i] = val[i] = num[i] = 0;
		ans.clear();
		rep(i, 0, len + 1) {
			U[i] = i, D[i] = i, L[i] = i - 1, R[i] = i + 1;
			col[i] = i;
		}
		L[0] = len, R[len] = 0;
		cnt = len;
	}
	void add(int ss, vector<int> ele) {
		int now = cnt + 1;
		for (int i = 0; i<sz(ele); ++i) {
			int v = ele[i];
			L[++cnt] = cnt - 1;
			R[cnt] = cnt + 1;
			U[cnt] = U[v];
			D[U[v]] = cnt;
			D[cnt] = v;
			U[v] = cnt;
			col[cnt] = v;
			num[v]++;
			val[cnt] = ss;
		}
		L[now] = cnt, R[cnt] = now;
	}
	void remove(int c) {
		R[L[c]] = R[c], L[R[c]] = L[c];
		for (int i = D[c]; i != c; i = D[i]) {
			for (int j = R[i]; j != i; j = R[j]) {
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				num[col[j]]--;
			}
		}
	}
	void restore(int c) {
		R[L[c]] = c, L[R[c]] = c;
		for (int i = U[c]; i != c; i = U[i])
			for (int j = R[i]; j != i; j = R[j]) {
				U[D[j]] = j;
				D[U[j]] = j;
				num[col[j]]++;
			}
	}
	bool dfs() {
		if (R[0] == 0)return true;
		int c = R[0];
		for (int i = R[0]; i != 0; i = R[i]) {
			if (num[i]<num[c])
				c = i;
		}

		remove(c);
		for (int i = D[c]; i != c; i = D[i]) {
			for (int j = R[i]; j != i; j = R[j])
				remove(col[j]);
			ans.pb(val[i]);
			if (dfs())return true;
			ans.pop_back();
			for (int j = L[i]; j != i; j = L[j])
				restore(col[j]);
		}
		restore(c);
		return false;
	}
}dlx;
int main(int argc, char **argv)
{
	freopen(argv[6], "r", stdin);
	freopen(argv[8], "w", stdout);
	m = atoi(argv[2]);
	int T = atoi(argv[4]);
	while (T--) {
		int gr, gc;
		bool f = false;
		if (m == 6 || m == 8 || m == 4 || m == 9) {
			f = true;
			if (m == 6)gr = 2, gc = 3;
			else if (m == 8)gr = 4, gc = 2;
			else gr = gc = sqrt(m);
			dlx.init(m*m * 4);
		}
		else dlx.init(m*m * 3);
		rep(i, 1, m + 1) {
			rep(j, 1, m + 1) {
				scanf("%d", &mat[i][j]);
				for (int k = 1; k <= m; ++k)
					if (mat[i][j] == 0 || mat[i][j] == k) {
						vi t;
						t.pb((i - 1)*m + j);
						t.pb((i - 1)*m + m*m + k);
						t.pb((j - 1)*m + 2 * m*m + k);
						if (f)t.pb(((i - 1) / gr*gr + (j - 1) / gc)*m + k + 3 * m*m);
						dlx.add((i*m + j)*m + k - 1, t);
					}
			}
		}
		dlx.dfs();
		for (int i = 0; i<sz(dlx.ans); ++i) {
			int v = dlx.ans[i];
			int k = v%m;
			int r = v / m / m;
			int c = (v / m) % m;
			if (c == 0)r--, c = m;
			mat[r][c] = k + 1;
		}
		rep(i, 1, m + 1) {
			rep(j, 1, m + 1) {
				if (j>1)printf("  ");
				printf("%d", mat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
