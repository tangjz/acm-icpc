class Solution {
public:
    bool isConsecutive(vector<int>& nums) {
        int low = INT_MAX, upp = INT_MIN;
        unordered_set<int> sp;
        for(int x: nums) {
            if(!sp.insert(x).second)
                return 0;
            low = min(low, x);
            upp = max(upp, x);
        }
        return upp - low == nums.size() - 1;
    }
};
