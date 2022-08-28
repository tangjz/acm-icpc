class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        map<int, int> ctr;
        int preSum = 0, res = 0;
        for(int x : nums) {
            ++ctr[preSum];
            preSum += x;
            map<int, int>::const_iterator it = ctr.find(preSum - k);
            if(it != ctr.end())
                res += it -> second;
        }
        return res;
    }
};
