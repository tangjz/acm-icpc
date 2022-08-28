class Solution {
public:
    int smallestEqual(vector<int>& nums) {
        int pos = 0, val = 0;
        for(int x: nums) {
            if(x == val)
                return pos;
            ++pos;
            (++val) == 10 && (val = 0);
        }
        return -1;
    }
};
