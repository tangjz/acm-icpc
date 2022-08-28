class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        const int maxd = 9 * 5 + 1;
        int ans = 0;
        vector<int> nums(highLimit + 1), ctr(maxd);
        for(int i = 1; i <= highLimit; ++i) {
            nums[i] = nums[i / 10] + (i % 10);
            if(i >= lowLimit)
                ans = max(ans, ++ctr[nums[i]]);
        }
        return ans;
    }
};
