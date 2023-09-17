class Solution {
public:
    int numberOfPoints(vector<vector<int>>& A) {
        sort(A.begin(), A.end());
        int las = 0, ans = 0;
        for(auto &it: A)
            if(it[1] > las) {
                ans += it[1] - max(las, it[0] - 1);
                las = it[1];
            }
        return ans;
    }
};
