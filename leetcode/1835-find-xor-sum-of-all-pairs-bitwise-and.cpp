class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int mx = 0;
        for(int x: arr1)
            while((1 << mx) <= x)
                ++mx;
        for(int x: arr2)
            while((1 << mx) <= x)
                ++mx;
        vector<int> ctr1(mx), ctr2(mx);
        for(int x: arr1)
            for(int i = 0; x > 0; x >>= 1, ++i)
                if(x & 1)
                    ++ctr1[i];
        for(int x: arr2)
            for(int i = 0; x > 0; x >>= 1, ++i)
                if(x & 1)
                    ++ctr2[i];
        int ans = 0;
        for(int i = mx - 1; i >= 0; --i) {
            ans = ans << 1 | (ctr1[i] & ctr2[i] & 1);
        }
        return ans;
    }
};
