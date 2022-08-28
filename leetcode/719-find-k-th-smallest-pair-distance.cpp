class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int L = 0, R = nums.back() - nums.front();
        while(L < R) {
            int M = (L + R) >> 1;
            int cnt = 0;
            for(int i = 0, j = 0; i < n; ++i) {
                for( ; j < n && nums[j] - nums[i] <= M; ++j);
                cnt += j - i - 1;
            }
            if(cnt < k) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
