class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& seq) {
        int n = seq.size(), ans = 0;
        sort(seq.begin(), seq.end());
        for(int i = n - 1, j = n - 1, c = 0; i >= 0; --i) {
            for( ; j >= 0 && seq[j][0] > seq[i][0]; --j)
                c = max(c, seq[j][1]);
            ans += seq[i][1] < c;
        }
        return ans;
    }
};
