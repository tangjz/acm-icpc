class Solution {
public:
    string rankTeams(vector<string>& votes) {
        const int maxd = 26;
        vector<vector<int> > seq(maxd, vector<int>());
        for(auto &it : votes) {
            int pos = 0;
            for(char &ch : it) {
                seq[(int)(ch - 'A')].push_back(pos);
                ++pos;
            }
        }
        string ret = "";
        for(int i = 0; i < maxd; ++i) {
            if(seq[i].empty())
                continue;
            ret += 'A' + i;
            sort(seq[i].begin(), seq[i].end());
        }
        sort(ret.begin(), ret.end(), [&](char const &u, char const &v) {
            return seq[(int)(u - 'A')] < seq[(int)(v - 'A')];
        });
        return ret;
    }
};
