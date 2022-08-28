/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        unordered_map<int, int> cache;
        auto get = [&](int i) {
            auto it = cache.find(i);
            if(it != cache.end()) {
                return it -> second;
            }
            return cache[i] = mountainArr.get(i);
        };
        int L = 0, R = n - 1;
        while(R - L >= 3) {
            int dt = (R - L) / 3;
            int ML = L + dt, vML = get(ML);
            int MR = R - dt, vMR = get(MR);
            if(vML <= vMR) {
                L = ML;
            }
            if(vML >= vMR) {
                R = MR;
            }
        }
        int upp = L;
        for(++L; L <= R; ++L)
            if(get(upp) < get(L))
                upp = L;
        for(L = 0, R = upp; L <= R; ) {
            int M = (L + R) >> 1, vM = get(M);
            if(vM == target) {
                return M;
            }
            if(vM < target) {
                L = M + 1;
            } else {
                R = M - 1;
            }
        }
        for(L = upp, R = n - 1; L <= R; ) {
            int M = (L + R) >> 1, vM = get(M);
            if(vM == target) {
                return M;
            }
            if(vM > target) {
                L = M + 1;
            } else {
                R = M - 1;
            }
        }
        return -1;
    }
};
