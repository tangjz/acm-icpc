class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int n = nums.size();
        vector<int> pos = {-1, -1};
        for(int i = 0; i < n; ++i) {
            int p = i;
            for(int j = 0; j < 2; ++j)
                if(pos[j] == -1 || nums[p] > nums[pos[j]])
                    swap(pos[j], p);
        }
        return pos[1] == -1 || nums[pos[0]] >= nums[pos[1]] * 2 ? pos[0] : -1;
    }
};
