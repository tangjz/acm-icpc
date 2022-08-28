class Solution {
public:
    string kthLargestNumber(vector<string>& nums, int k) {
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + (n - k), nums.end(), [&](string const &u, string const &v) {
            int uL = u.length(), vL = v.length();
            return uL < vL || (uL == vL && u < v);
        });
        return nums[n - k];
    }
};
