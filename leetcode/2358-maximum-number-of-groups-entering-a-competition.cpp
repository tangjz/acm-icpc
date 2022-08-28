class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int n = grades.size(), ans = 0;
        for( ; n > ans; n -= ++ans);
        return ans;
    }
};
