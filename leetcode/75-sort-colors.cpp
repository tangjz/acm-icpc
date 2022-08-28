class Solution {
public:
    void sortColors(vector<int>& nums) {
        int L = 0, R = (int)nums.size();
        for(int i = L; i < R; ) {
            int x = nums[i];
            if(x == 0) {
                if(i > L)
                    swap(nums[i], nums[L]);
                ++L;
            } else if(x == 2) {
                --R;
                if(i < R)
                    swap(nums[i], nums[R]);
            }
            if(x != 2)
                ++i;
        }
    }
};
