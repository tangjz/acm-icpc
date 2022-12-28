class Solution {
public:
    int kBigIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> que = nums;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<int> c(m), b(m);
        for(int &x: nums) {
            x = lower_bound(que.begin(), que.end(), x) - que.begin();
            ++c[x];
        }
        for(int i = 1; i < m; ++i)
            c[i] += c[i - 1];
        int ans = 0;
        for(int x: nums) {
            int cL = 0;
            for(int y = x; y > 0; y -= y & -y)
                cL += b[y - 1];
            int cR = (x > 0 ? c[x - 1] : 0) - cL;
            ans += cL >= k && cR >= k;
            for(int y = x + 1; y <= m; y += y & -y)
                ++b[y - 1];
        }
        return ans;
    }
};
