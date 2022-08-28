class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> que = nums;
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size(), ans = 0;
        vector<int> bits(m);
        for(int x: nums) {
            long long y = x;
            y *= 2;
            if(que.back() > y) {
                int p = y < INT_MIN ? 0 : upper_bound(que.begin(), que.end(), (int)y) - que.begin();
                for(int i = p + 1; i <= m; i += i & -i)
                    ans += bits[i - 1];
            }
            int p = lower_bound(que.begin(), que.end(), x) - que.begin();
            for(int i = p + 1; i > 0; i -= i & -i)
                ++bits[i - 1];
        }
        return ans;
    }
};
