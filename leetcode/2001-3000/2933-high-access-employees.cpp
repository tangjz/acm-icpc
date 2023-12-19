class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        unordered_map<string, vector<int> > ctr;
        for(auto &it: access_times) {
            auto &jt = it[1];
            int hh = stoi(jt.substr(0, 2)), mm = stoi(jt.substr(2));
            ctr[it[0]].push_back(hh * 60 + mm);
        }
        vector<string> ret;
        for(auto &it: ctr) {
            auto &vec = it.second;
            sort(vec.begin(), vec.end());
            int m = vec.size();
            for(int i = 2; i < m; ++i)
                if(vec[i] - vec[i - 2] < 60) {
                    ret.push_back(it.first);
                    break;
                }
        }
        return ret;
    }
};
