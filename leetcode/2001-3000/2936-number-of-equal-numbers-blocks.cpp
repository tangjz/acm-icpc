/**
 * Definition for BigArray.
 * class BigArray {
 * public:
 *     BigArray(vector<int> elements);
 *     int at(long long index);
 *     long long size();
 * };
 */
class Solution {
public:
    int countBlocks(BigArray* nums) {
        typedef long long LL;
        int ans = 0;
        LL n = nums -> size(), p = 0;
        for( ; p < n; ++ans) {
            LL v = nums -> at(p), L = p + 1, R = n;
            while(L < R) {
                LL M = (L + R + 1) >> 1;
                if(nums -> at(M - 1) == v) {
                    L = M;
                } else {
                    R = M - 1;
                }
            }
            p = L;
        }
        return ans;
    }
};
