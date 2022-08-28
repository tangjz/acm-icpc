class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        typedef long long LL;
        int n = nums.size();
        unordered_map<int, vector<pair<int, int> > > lft;
        sort(nums.begin(), nums.end());
        vector<vector<int> > ans;
        auto upd = [&](int x, int y) {
            int sum = x + y;
            lft[sum].push_back({x, y});
        };
        auto chk = [&](int x, int y) {
            LL val = (LL)target - x - y;
            if(val < INT_MIN || val > INT_MAX)
                return;
            auto it = lft.find((int)val);
            if(it == lft.end())
                return;
            for(auto &jt: it -> second) {
                ans.push_back({jt.first, jt.second, x, y});
            }
        };
        for(int a, b = 1, c = 2, d; c + 1 < n; ++b, ++c) {
            // if already insert (a, b) ?
            // 1. v[b] = v[a] => a=b-1, v[b] > v[b-2]
            // 2. v[b] > v[a] => v[b] > v[b-1], v[a]<v[a+1]
            if(nums[b] > nums[b - 1]) {
                for(a = b - 1; a >= 0; --a)
                    if(nums[a] < nums[a + 1])
                        upd(nums[a], nums[b]);
            } else if(b - 2 < 0 || nums[b] > nums[b - 2]) {
                upd(nums[b - 1], nums[b]);
            }
            // if can find further (c, d) ?
            // 1. v[c] = v[d] => d=c+1, v[c] < v[c+2]
            // 2. v[c] < v[d] => v[c] < v[c+1], v[d]>v[d-1]
            if(nums[c] < nums[c + 1]) {
                for(d = c + 1; d < n; ++d)
                    if(nums[d] > nums[d - 1])
                        chk(nums[c], nums[d]);
            } else if(c + 2 == n || nums[c] < nums[c + 2]) {
                chk(nums[c], nums[c + 1]);
            }
        }
        return ans;
    }
};
