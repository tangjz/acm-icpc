class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int ans = 0;
        for(int x: nums)
            ans += !(to_string(x).size() & 1);
        return ans;
    }
};
