class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        typedef long long LL;
        int n = nums.size();
        vector<LL> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        vector<LL> que(psum.begin() + 1, psum.end());
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        LL ans = 0;
        vector<int> bits(m);
        for(int i = n - 1; i >= 0; --i) {
            int x = lower_bound(que.begin(), que.end(), psum[i + 1]) - que.begin();
            for(int j = x + 1; j > 0; j -= j & -j)
                ++bits[j - 1];
            int L = lower_bound(que.begin(), que.end(), psum[i] + lower) - que.begin();
            int R = lower_bound(que.begin(), que.end(), psum[i] + upper + 1) - que.begin();
            if(L >= R)
                continue;
            for(int j = L + 1; j <= m; j += j & -j)
                ans += bits[j - 1];
            for(int j = R + 1; j <= m; j += j & -j)
                ans -= bits[j - 1];
        }
        return ans;
    }
};
