class Solution {
public:
    int bestRotation(vector<int>& nums) {
        int n = nums.size();
        vector<int> ctr(n + 1);
        for(int i = 0; i < n; ++i) {
            int x = nums[i], L = i + 1, R = i - x;
            L >= n && (L -= n);
            R < 0 && (R += n);
            ++ctr[L];
            --ctr[R + 1];
            if(L > R)
                ++ctr[0];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            ctr[i + 1] += ctr[i];
            if(ctr[i] > ctr[ans])
                ans = i;
        }
        return ans;
    }
};
