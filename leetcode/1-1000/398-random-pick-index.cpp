class Solution {
    mt19937 rnd;
    unordered_map<int, vector<int> > mp;
public:
    Solution(vector<int>& nums) {
        rnd.seed(time(NULL));
        for(int i = 0; i < (int)nums.size(); ++i)
            mp[nums[i]].push_back(i);
    }

    int pick(int target) {
        auto &vec = mp[target];
        return vec[rnd() % vec.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
