class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> pos = {2, limit + limit + 1};
        for(int i = 0, j = n - 1; i < j; ++i, --j) {
            int val = nums[i] + nums[j];
            int low = min(nums[i], nums[j]) + 1, upp = max(nums[i], nums[j]) + limit;
            // [low, upp] +1, [val, val] +1
            pos.push_back(val);
            pos.push_back(val + 1);
            pos.push_back(low);
            pos.push_back(upp + 1);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        auto get_pos = [&](int x) {
            return lower_bound(pos.begin(), pos.end(), x) - pos.begin();
        };
        int m = pos.size();
        vector<int> ctr(m);
        for(int i = 0, j = n - 1; i < j; ++i, --j) {
            int val = nums[i] + nums[j];
            int low = min(nums[i], nums[j]) + 1, upp = max(nums[i], nums[j]) + limit;
            // [low, upp] +1, [val, val] +1
            ++ctr[get_pos(val)];
            --ctr[get_pos(val + 1)];
            ++ctr[get_pos(low)];
            --ctr[get_pos(upp + 1)];
        }
        int ans = 0;
        for(int i = 0; i + 1 < m; ++i) {
            ans = max(ans, ctr[i]);
            ctr[i + 1] += ctr[i];
        }
        return n - ans;
    }
};
