class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        static mt19937_64 rnd;
        int n = nums.size();
        while(true) {
            int x = rnd() % n, y = rnd() % (n - 1);
            y += y >= x;
            if(nums[x] == nums[y])
                return nums[x];
        }
    }
};
