class Solution {
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        typedef long long LL;
        int n = nums.size();
        LL ans = 0;
        sort(nums.begin(), nums.end());
        sort(target.begin(), target.end());
        for(int o = 0; o < 2; ++o)
            for(int i = 0, j = 0; i < n; ++i) {
                if((nums[i] & 1) != o)
                    continue;
                for( ; j < n && (target[j] & 1) != o; ++j);
                ans += abs(nums[i] - target[j++]) / 2;
            }
        return ans / 2;
    }
};
