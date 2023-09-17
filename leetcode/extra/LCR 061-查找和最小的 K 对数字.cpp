class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<vector<int> > ret;
        if(nums1.size() == 1 || nums2.size() == 1 || nums1.size() * nums2.size() <= k) {
            for(int x: nums1)
                for(int y: nums2)
                    if(ret.size() < k)
                        ret.push_back({x, y});
            return ret;
        }
        vector<vector<int> > nums = {nums1, nums2};
        bool flip = nums[0][1] - nums[0][0] > nums[1][1] - nums[1][0];
        if(flip)
            nums[0].swap(nums[1]);
        priority_queue<vector<int> > que; // -v, x, y, z, idx
        que.push({-(nums[0][0] + nums[1][0]), 0, 0, 0, 0, 0});
        while(k--) {
            vector<int> cur = que.top();
            que.pop();
            int val = cur[0], x = cur[1], y = cur[2], z = cur[3];
            ret.push_back({cur[4], cur[5]});
            if(y + 1 < (int)nums[x].size())
                que.push({val + nums[x][y] - nums[x][y + 1], x, y + 1, 0, x ? cur[4] : y + 1, x ? y + 1 : cur[5]});
            if(x + 1 < (int)nums.size()) {
                que.push({val + nums[x + 1][0] - nums[x + 1][1], x + 1, 1, 1, x + 1 ? cur[4] : 1, x + 1 ? 1 : cur[5]});
                assert(z != 1);
            }
        }
        for(auto &it: ret) {
            it[0] = nums[0][it[0]];
            it[1] = nums[1][it[1]];
            if(flip)
                swap(it[0], it[1]);
        }
        return ret;
    }
};
