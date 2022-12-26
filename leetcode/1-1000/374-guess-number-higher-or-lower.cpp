/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int L = 1, R = n;
        while(L < R) {
            int M = L + ((R - L) >> 1);
            int sgn = guess(M);
            if(!sgn)
                return M;
            if(sgn < 0) {
                R = M - 1;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
