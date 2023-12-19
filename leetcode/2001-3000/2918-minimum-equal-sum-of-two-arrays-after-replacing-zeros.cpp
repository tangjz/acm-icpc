class Solution {
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        typedef long long LL;
        LL s1 = 0, s2 = 0;
        bool f1 = 0, f2 = 0;
        for(int x: nums1) {
            s1 += max(x, 1);
            f1 |= !x;
        }
        for(int x: nums2) {
            s2 += max(x, 1);
            f2 |= !x;
        }
        if(s1 == s2)
            return s1;
        if(s1 > s2) {
            swap(s1, s2);
            swap(f1, f2);
        }
        return f1 ? s2 : -1;
    }
};
