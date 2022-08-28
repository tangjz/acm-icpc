class Solution {
public:
    vector<int> find_left_repeat_numII(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n);
        unordered_map<int, int> pos;
        for(int i = 0; i < n; ++i) {
            auto it = pos.find(nums[i]);
            if(it == pos.end()) {
                ret[i] = -1;
                pos.insert({nums[i], i});
            } else {
                ret[i] = it -> second;
                it -> second = i;
            }
        }
        return ret;
    }
};
