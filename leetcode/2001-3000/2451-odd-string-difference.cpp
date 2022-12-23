class Solution {
public:
    string oddString(vector<string>& words) {
        int m = words.size(), n = words[0].size();
        map<vector<int>, vector<int> > ctr;
        for(int j = 0; j < m; ++j) {
            vector<int> dif;
            auto &buf = words[j];
            for(int i = 1; i < n; ++i)
                dif.push_back((int)buf[i] - (int)buf[i - 1]);
            ctr[dif].push_back(j);
        }
        for(auto &it: ctr)
            if(it.second.size() == 1)
                return words[it.second.back()];
        return "";
    }
};
