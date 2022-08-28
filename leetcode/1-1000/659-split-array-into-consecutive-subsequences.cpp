class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int n = nums.size(), cnt[3] = {};
        auto cleanUp = [&](int tot) -> bool {
            int rem[3] = {};
            for(int i = 0; i < 3; ++i) {
                rem[i] = cnt[i];
                cnt[i] = 0;
            }
            for(int i = 0; i < 3; ++i) {
                int tmp = min(tot, rem[i]);
                if(i < 2 && tmp < rem[i])
                    return 0;
                cnt[min(i + 1, 2)] += tmp;
                tot -= tmp;
            }
            cnt[0] = tot;
            return 1;
        };
        for(int i = 0, j; i < n; i = j) {
            for(j = i + 1; j < n && nums[i] == nums[j]; ++j);
            if(i > 0 && nums[i - 1] + 1 < nums[i] && !cleanUp(0))
                return 0;
            if(!cleanUp(j - i))
                return 0;
        }
        return !cnt[0] && !cnt[1];
    }
};
