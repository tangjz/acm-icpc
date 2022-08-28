class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int best = (int)nums.size(), pos = 0;
        for(int x: nums) {
            if(x == target)
                best = min(best, abs(pos - start));
            ++pos;
        }
        return best;
    }
};
