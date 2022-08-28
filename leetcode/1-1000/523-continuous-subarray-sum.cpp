class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int pre = -1, cur = 0;
        unordered_set<int> Hash;
        for(int x: nums) {
            if(pre >= 0)
                Hash.insert(pre);
            pre = cur;
            cur = (cur + x) % k;
            if(Hash.count(cur))
                return 1;
        }
        return 0;
    }
};
