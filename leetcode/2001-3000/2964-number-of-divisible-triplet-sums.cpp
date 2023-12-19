class Solution {
public:
    int divisibleTripletCount(vector<int>& nums, int d) {
        int n = nums.size(), ans = 0;
        unordered_map<int, int> ctr;
        for(int i = 1; i + 1 < n; ++i) {
            ++ctr[nums[i - 1] % d];
            for(int j = i + 1; j < n; ++j) {
                int rem = (nums[i] + nums[j]) % d;
                rem && (rem = d - rem);
                auto it = ctr.find(rem);
                if(it != ctr.end())
                    ans += it -> second;
            }
        }
        return ans;
    }
};
