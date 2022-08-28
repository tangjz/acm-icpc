class Solution {
public:
	int numSubmat(vector<vector<int>>& mat) {
		int n = (int)mat.size(), m = (int)mat[0].size(), ans = 0, tot;
		vector<int> h(m + 1, 0), stk(m);
		for(int i = n - 1; i >= 0; --i)
			for(int j = tot = 0; j <= m; ++j) {
				h[j] = j < m && mat[i][j] > 0 ? h[j] + 1 : 0;
				for( ; tot && h[stk[tot - 1]] >= h[j]; --tot) {
					int k = 0, low = h[j], upp = h[stk[tot - 1]];
					if(tot > 1) {
						k = stk[tot - 2] + 1;
						low < h[stk[tot - 2]] && (low = h[stk[tot - 2]]);
					}
					int dx = upp - low, dy = j - k;
					if(!dx)
						continue;
					ans += dx * dy * (dy + 1) / 2;
				}
				stk[tot++] = j;
			}
		return ans;
	}
};
