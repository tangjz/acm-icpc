class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int target) {
        int r = picture.size(), c = picture[0].size();
        unordered_map<string, int> Hash;
        vector<int> row(r), col(c), idx(r);
        vector<int> cand(c, -1);
        for(int i = 0; i < r; ++i) {
            string rep = "";
            for(char ch: picture[i])
                rep.push_back(ch);
            idx[i] = Hash.insert({rep, (int)Hash.size()}).first -> second;
            for(int j = 0; j < c; ++j) {
                if(picture[i][j] != 'B')
                    continue;
                ++row[i];
                ++col[j];
                if(cand[j] == -1) {
                    cand[j] = idx[i];
                } else if(cand[j] != idx[i]) {
                    cand[j] = -2;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(picture[i][j] == 'B' && row[i] == target && col[j] == target && cand[j] >= 0)
                    ++ans;
        return ans;
    }
};
