class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2) {
        int msk1 = 0, msk2 = 0;
        for(int x: nums1)
            msk1 |= 1 << x;
        for(int x: nums2)
            msk2 |= 1 << x;
        int msk = msk1 & msk2, z = msk ? __builtin_ctz(msk & -msk) : 100;
        int x = *min_element(nums1.begin(), nums1.end());
        int y = *min_element(nums2.begin(), nums2.end());
        if(x > y)
            swap(x, y);
        return min(x * 10 + y, z);
    }
};
