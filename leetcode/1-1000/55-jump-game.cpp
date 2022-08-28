class Solution {
public:
    bool canJump(vector<int>& nums) {
        int rem = 1;
        for(int x : nums) {
            if((--rem) < 0)
                return 0;
            rem = max(rem, x);
        }
        return 1;
    }
};
