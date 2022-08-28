// https://loj.ac/s/47327
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)3e5 + 1;
int n, m, sz[maxn];
vector<LL> seq[maxn];
struct Node {
	LL v;
	int x, y, z;
	bool operator < (Node const &t) const {
		return v < t.v;
	}
} ;
priority_queue<Node> Q;
bool cmp(vector<LL> const &u, vector<LL> const &v) {
	return u[1] < v[1];
}

class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        n = nums.size();
        m = k;
        // printf("n %d m %d\n", n, m);
        LL low = 0;
        for(int i = 0; i < n; ++i) {
            sz[i] = 2;
            seq[i] = {(LL)-nums[i], 0LL};
            sort(seq[i].begin(), seq[i].end());
            low += seq[i][0];
            for(int j = sz[i] - 1; j > 0; --j)
                seq[i][j] -= seq[i][j - 1];
            // printf("%d: %lld\n", i, low);
        }
        sort(seq, seq + n, cmp);
        for(int i = 0; i < n; ++i)
            sz[i] = (int)seq[i].size();
        for(; !Q.empty(); Q.pop());
        Q.push((Node){-low, 0, 0, 0});
        LL val;
        for(int i = 0; i < m; ++i) {
            Node cur = Q.top();
            Q.pop();
            val = cur.v;
            int px = cur.x, py = cur.y, pz = cur.z;
            // printf("%lld%c", val, " \n"[i == m - 1]);
            if(py + 1 < sz[px])
                Q.push((Node){val - seq[px][py + 1], px, py + 1, 0});
            if(px + 1 < n) {
                Q.push((Node){val - seq[px + 1][1], px + 1, 1, 1});
                if(pz == 1)
                    Q.push((Node){val + seq[px][1] - seq[px + 1][1], px + 1, 1, 1});
            }
        }
        return val;
    }
};
