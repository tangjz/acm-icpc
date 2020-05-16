#include <bits/stdc++.h>
using namespace std;
const int maxn = 601;
map<vector<int>, int> Hash;
int query(int len, int *arr) {
	if(len <= 1)
		return 0;
	vector<int> seq(arr, arr + len);
	sort(seq.begin(), seq.end());
	map<vector<int>, int>::iterator it = Hash.find(seq);
	if(it != Hash.end())
		return it -> second;
	printf("? %d\n", len);
	for(int i = 0; i < len; ++i)
		printf("%d%c", arr[i], " \n"[i == len - 1]);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	if(ret == -1)
		exit(0);
	return Hash[seq] = ret;
}
bool check(int len0, int *arr0, int len1, int *arr1) { // check connectivity of arr0 and arr1
	static int arr[maxn];
	memcpy(arr, arr0, len0 * sizeof(int));
	memcpy(arr + len0, arr1, len1 * sizeof(int));
	int lft = query(len0, arr);
	int rht = query(len1, arr + len0);
	int sum = query(len0 + len1, arr);
	return lft + rht < sum;
}
int getNode(int len0, int *arr0, int len1, int *arr1) { // get one node from arr0 that is connected with arr1
	int L = 0, R = len0 - 1;
	while(L < R) {
		int M = (L + R) >> 1;
		if(check(M - L + 1, arr0 + L, len1, arr1)) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	return arr0[L];
}
int n, col[maxn], seq[3][maxn];
int main() {
	scanf("%d", &n);
	col[1] = 1;
	seq[0][++seq[0][0]] = 1;
	seq[1][++seq[1][0]] = 1;
	for(int i = 2; i <= n; ++i) {
		static int rem[maxn];
		rem[0] = 0;
		for(int j = 1; j <= n; ++j)
			if(!col[j])
				rem[++rem[0]] = j;
		int x = getNode(rem[0], rem + 1, seq[0][0], seq[0] + 1);
		if(!check(1, &x, seq[1][0], seq[1] + 1)) {
			col[x] = 1;
			seq[1][++seq[1][0]] = x;
		} else if(!check(1, &x, seq[2][0], seq[2] + 1)) {
			col[x] = 2;
			seq[2][++seq[2][0]] = x;
		} else {
			int y = getNode(seq[1][0], seq[1] + 1, 1, &x);
			int z = getNode(seq[2][0], seq[2] + 1, 1, &x);
			static int dep[maxn] = {}, que[maxn], pre[maxn];
			dep[y] = 1;
			pre[y] = x;
			que[0] = 0;
			que[++que[0]] = y;
			for(int j = 1; j <= que[0]; ++j) {
				int u = que[j];
				rem[0] = 0;
				for(int v = 1; v <= n; ++v)
					if(col[v] > 0 && col[u] != col[v] && !dep[v])
						rem[++rem[0]] = v;
				while(rem[0] && check(rem[0], rem + 1, 1, &u)) {
					int v = getNode(rem[0], rem + 1, 1, &u);
					dep[v] = dep[u] + 1;
					pre[v] = u;
					que[++que[0]] = v;
					if(v == z)
						break;
					rem[0] = 0;
					for(int v = 1; v <= n; ++v)
						if(col[v] > 0 && col[u] != col[v] && !dep[v])
							rem[++rem[0]] = v;
				}
				if(dep[z] > 0)
					break;
			}
			puts("N");
			printf("%d\n", dep[z] + 1);
			for(int u = z; u != x; u = pre[u])
				printf("%d ", u);
			printf("%d\n", x);
			return 0;
		}
		seq[0][++seq[0][0]] = x;
	}
	puts("Y");
	int cnt = 0;
	for(int i = 1; i <= n; ++i)
		cnt += col[i] == 1;
	printf("%d\n", cnt);
	for(int i = 1; i <= n; ++i)
		if(col[i] == 1)
			printf("%d%c", i, " \n"[(--cnt) == 0]);
	return 0;
}
