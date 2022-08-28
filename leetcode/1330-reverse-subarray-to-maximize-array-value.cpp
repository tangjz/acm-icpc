class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        typedef long long LL;
        int n = (int)nums.size();
        LL sum = 0;
        int adt = 0;
        for(int i = 1; i < n; ++i) {
            int tmp = abs(nums[i] - nums[i - 1]);
            sum += tmp;
            adt = max(adt, abs(nums[i] - nums[0]) - tmp);
            adt = max(adt, abs(nums[n - 1] - nums[i - 1]) - tmp);
        }
        int low = INT_MAX, upp = INT_MIN;
        for(int i = 1; i < n; ++i) {
            int u = nums[i - 1], v = nums[i];
            if(u > v)
                swap(u, v);
            low = min(low, v);
            upp = max(upp, u);
            if(low < u)
                adt = max(adt, (u - low) * 2);
            if(v < upp)
                adt = max(adt, (upp - v) * 2);
        }
        return (int)(sum + adt);
    }
};
