class Solution {
public:
    int countTestedDevices(vector<int>& A) {
        int ans = 0;
        for(int x: A)
            ans += x > ans;
        return ans;
    }
};
