/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> tmp = binaryMatrix.dimensions();
        int r = tmp[0], c = tmp[1];
        int ans = c;
        for(int i = 0; ans > 0 && i < r; ++i) {
            if(!binaryMatrix.get(i, ans - 1))
                continue;
            int L = 0, R = ans - 1;
            while(L < R) {
                int M = (L + R) >> 1;
                if(binaryMatrix.get(i, M)) {
                    R = M;
                } else {
                    L = M + 1;
                }
            }
            ans = R;
        }
        return ans < c ? ans : -1;
    }
};
