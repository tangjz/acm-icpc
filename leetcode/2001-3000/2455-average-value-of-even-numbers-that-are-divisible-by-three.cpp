class Solution {
public:
    int averageValue(vector<int>& nums) {
        int cnt = 0, sum = 0;
        for(int x: nums)
            if(x % 6 == 0) {
                ++cnt;
                sum += x;
            }
        return cnt ? sum / cnt : 0;
    }
};
