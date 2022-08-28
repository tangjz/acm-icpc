class Solution {
public:
    int minMoves(vector<int>& nums) {
        int low = *min_element(nums.begin(), nums.end()), ans = 0;
        for(int x: nums)
            ans += x - low;
        return ans;
    }
};
