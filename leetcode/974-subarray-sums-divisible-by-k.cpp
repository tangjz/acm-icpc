class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int sum = 0, ans = 0;
        unordered_map<int, int> ctr;
        ctr[0] = 1;
        for(int x: nums) {
            sum = (sum + x) % k;
            sum < 0 && (sum += k);
            ans += ctr[sum]++;
        }
        return ans;
    }
};
