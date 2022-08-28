class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int ans = 0, sum = 0;
        unordered_set<int> Hash;
        for(int x : nums) {
            Hash.insert(sum);
            sum += x;
            if(Hash.count(sum - target)) {
                ++ans;
                sum = 0;
                Hash.clear();
            }
        }
        return ans;
    }
};
