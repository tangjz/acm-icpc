class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        typedef long long LL;
        int las = nums.back();
        nums.pop_back();
        LL ans = 0;
        while(!nums.empty()) {
            int cur = nums.back();
            nums.pop_back();
            if(cur > las) {
                int d = cur / las, r = cur % las;
                if(r > 0)
                    d = (cur - 1) / las + 1;
                ans += d - 1;
                cur = cur / d;
            }
            las = cur;
        }
        return ans;
    }
};
