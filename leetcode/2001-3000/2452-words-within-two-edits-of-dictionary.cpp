class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        int n = queries[0].size(), m = dictionary.size();
        vector<string> ret;
        for(auto &buf: queries) {
            int upp = n;
            for(int i = 0; i < m && upp > 2; ++i) {
                int cnt = 0;
                for(int j = 0; j < n && cnt < upp; ++j)
                    cnt += buf[j] != dictionary[i][j];
                upp = min(upp, cnt);
            }
            if(upp <= 2)
                ret.push_back(buf);
        }
        return ret;
    }
};
