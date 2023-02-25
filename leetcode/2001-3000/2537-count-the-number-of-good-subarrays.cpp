class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        typedef long long LL;
        int n = nums.size();
        LL cnt = 0, ans = 0;
        unordered_map<int, int> ctr;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && cnt < k; ++j)
                cnt += ctr[nums[j]]++;
            if(cnt >= k)
                ans += n - j + 1;
            cnt -= --ctr[nums[i]];
        }
        return ans;
    }
};
