/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y] 
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
public:
    int getIndex(ArrayReader &reader) {
        int L = 0, R = reader.length() - 1;
        while(L < R) {
            int len = max((R - L + 1) / 3, 1);
            int sgn = reader.compareSub(L, L + len - 1, R - len + 1, R);
            if(!sgn) {
                L += len;
                R -= len;
            } else if(sgn < 0) {
                L = R - len + 1;
            } else {
                R = L + len - 1;
            }
        }
        return L;
    }
};
