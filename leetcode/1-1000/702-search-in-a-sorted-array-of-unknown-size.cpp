/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int L = 0, R = 1;
        for( ; reader.get(R) < target; R = R << 1 | 1);
        while(L < R) {
            int M = (L + R) >> 1;
            if(reader.get(M) < target) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return reader.get(L) == target ? L : -1;
    }
};
