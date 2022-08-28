class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        int n = keyName.size();
        map<string, vector<int> > Hash;
        for(int i = 0; i < n; ++i) {
            int hh = (keyTime[i][0] - '0') * 10 + (keyTime[i][1] - '0');
            int mm = (keyTime[i][3] - '0') * 10 + (keyTime[i][4] - '0');
            Hash[keyName[i]].push_back(hh * 60 + mm);
        }
        vector<string> ret;
        for(auto &it: Hash) {
            auto &vec = it.second;
            sort(vec.begin(), vec.end());
            int m = vec.size();
            for(int i = 2; i < m; ++i)
                if(vec[i] - vec[i - 2] <= 60) {
                    ret.push_back(it.first);
                    break;
                }
        }
        return ret;
    }
};
