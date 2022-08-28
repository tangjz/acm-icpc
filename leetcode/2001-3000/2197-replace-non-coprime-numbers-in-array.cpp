class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        int n = nums.size(), m = 0;
        for(int i = 0; i < n; ++i) {
            int val = nums[i];
            while(m > 0) {
                int com = gcd(nums[m - 1], val);
                if(com == 1)
                    break;
                val *= nums[--m] / com;
            }
            nums[m++] = val;
        }
        nums.resize(m);
        return nums;
    }
};
