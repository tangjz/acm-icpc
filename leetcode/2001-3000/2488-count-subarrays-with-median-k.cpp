class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), p = 0, ans = 0;
        vector<int> ctr(n + n + 2);
        for( ; p < n && nums[p] != k; ++p);
        for(int i = p, c = 0; i >= 0; --i) {
            if(i != p)
                c += nums[i] < k ? -1 : 1;
            ++ctr[n + c];
        }
        // for(int i = -n; i <= n; ++i)
        //     if(ctr[n + i])
        //         printf("%d: %d\n", i, ctr[n + i]);
        for(int i = p, c = 0; i < n; ++i) {
            if(i != p)
                c += nums[i] < k ? -1 : 1;
            ans += ctr[n - c] + ctr[n + 1 - c];
        }
        return ans;
    }
};
