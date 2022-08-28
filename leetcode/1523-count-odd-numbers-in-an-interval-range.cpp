class Solution {
public:
    int countOdds(int low, int high) {
        low += !(low & 1);
        high -= !(high & 1);
        return low <= high ? (high - low) / 2 + 1 : 0;
    }
};
