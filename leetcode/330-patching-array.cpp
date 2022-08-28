class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int ans = 0;
        long long sum = 0;
        for(int x: nums) {
            while(sum < n && sum + 1 < x) {
                ++ans;
                sum += sum + 1;
            }
            sum += x;
        }
        while(sum < n) {
            ++ans;
            sum += sum + 1;
        }
        return ans;
    }
};
