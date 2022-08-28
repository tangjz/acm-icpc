class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, val = 0;
        for(int x: nums) {
            if(!cnt)
                val = x;
            cnt += val == x ? 1 : -1;
        }
        cnt = 0;
        for(int x: nums)
            cnt += x == val;
        return cnt + cnt > nums.size() ? val : -1;
    }
};
