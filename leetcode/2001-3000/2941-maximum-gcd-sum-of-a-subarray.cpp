class Solution {
public:
    long long maxGcdSum(vector<int>& nums, int k) {
        typedef long long LL;
        int n = nums.size();
        LL ans = 0;
        vector<LL> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        vector<pair<int, int> > que;
        for(int i = 0; i < n; ++i) {
            int m = 0, u = nums[i];
            for(auto &[v, p]: que) {
                v = gcd(v, u);
                if(!m || que[m - 1].first != v)
                    que[m++] = {v, p};
            }
            que.resize(m);
            if(!m || que[m - 1].first != u)
                que.push_back({u, i});
            for(auto &[v, p]: que) {
                if(i - p + 1 < k)
                    break;
                ans = max(ans, (psum[i + 1] - psum[p]) * v);
            }
        }
        return ans;
    }
};
