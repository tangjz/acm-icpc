class Solution {
public:
    int numTeams(vector<int>& a) {
        int n = (int)a.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                for(int k = j + 1; k < n; ++k)
                    ans += (a[i] < a[j] && a[j] < a[k]) || (a[i] > a[j] && a[j] > a[k]);
        return ans;
    }
};
