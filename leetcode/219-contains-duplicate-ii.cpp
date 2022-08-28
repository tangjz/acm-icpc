class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_set<int> sp;
        for(int i = 0, j = 0; i < n; ++i) {
            if(i - j > k)
                sp.erase(nums[j++]);
            if(!sp.insert(nums[i]).second)
                return 1;
        }
        return 0;
    }
};
