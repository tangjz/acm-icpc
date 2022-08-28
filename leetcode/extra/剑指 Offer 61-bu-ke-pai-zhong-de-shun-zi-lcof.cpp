class Solution {
public:
    bool isStraight(vector<int>& nums) {
        const int maxn = 5;
        sort(nums.begin(), nums.end());
        int cnt = 0;
        for( ; cnt < maxn && !nums[cnt]; ++cnt);
        if(cnt == maxn)
            return 1;
        if(nums[maxn - 1] - nums[cnt] >= 5)
            return 0;
        for(int i = cnt; i + 1 < maxn; ++i)
            if(nums[i] == nums[i + 1])
                return 0;
        return 1;
    }
};
