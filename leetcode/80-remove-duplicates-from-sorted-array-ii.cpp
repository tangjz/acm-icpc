class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int tot = 0;
        for(int x: nums) {
            if(tot < 2 || x != nums[tot - 2])
                nums[tot++] = x;
        }
        return tot;
    }
};
