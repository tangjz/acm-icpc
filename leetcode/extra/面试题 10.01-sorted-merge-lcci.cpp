class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos = n + m;
        while(m > 0 || n > 0) {
            if(!n || (m && nums1[m - 1] > nums2[n - 1])) {
                nums1[--pos] = nums1[--m];
            } else {
                nums1[--pos] = nums2[--n];
            }
        }
    }
};
