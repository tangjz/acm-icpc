class Solution {
public:
    string largestWordCount(vector<string>& A, vector<string>& B) {
        int n = A.size();
        map<string, int> ctr;
        for(int i = 0; i < n; ++i) {
            int cnt = 1;
            for(char ch: A[i])
                cnt += ch == ' ';
            ctr[B[i]] += cnt;
        }
        pair<int, string> ans = {0, ""};
        for(auto &it: ctr)
            ans = max(ans, make_pair(it.second, it.first));
        return ans.second;
    }
};
