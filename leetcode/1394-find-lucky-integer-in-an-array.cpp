class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int, int> ctr;
        for(int x : arr)
            ++ctr[x];
        int ans = -1;
        for(int x : arr)
            if(ctr[x] == x)
                ans = max(ans, x);
        return ans;
    }
};
