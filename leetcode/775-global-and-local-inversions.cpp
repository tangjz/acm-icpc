class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int upp[2] = {INT_MIN, INT_MIN}, las = INT_MIN;
        for(int x: nums) {
            int cnt = (upp[0] > x) + (upp[1] > x) - (las > x);
            if(cnt)
                return 0;
            int tmp = x;
            if(upp[0] < tmp)
                swap(upp[0], tmp);
            if(upp[1] < tmp)
                swap(upp[1], tmp);
            las = x;
        }
        return 1;
    }
};
