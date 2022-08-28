class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        long long diff = goal;
        for(int x: nums)
            diff -= x;
        return diff ? (abs(diff) - 1) / limit + 1 : 0;
    }
};
