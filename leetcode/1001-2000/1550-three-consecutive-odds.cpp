class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int cnt = 0;
        for(int x : arr)
            if(!(x & 1)) {
                cnt = 0;
            } else if((++cnt) == 3) {
                return true;
            }
        return false;
    }
};
