class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        set<int> tb;
        set<string> fd;
        for(auto &it : orders) {
            tb.insert(stoi(it[1]));
            fd.insert(it[2]);
        }
        vector<vector<string> > ret = vector<vector<string> >(tb.size() + 1, vector<string>(fd.size() + 1, "0"));
        ret[0][0] = "Table";
        map<int, int> tbh;
        for(auto &it : tb) {
            int ctr = tbh.size() + 1;
            ret[ctr][0] = to_string(it);
            tbh.insert(make_pair(it, ctr));
        }
        map<string, int> fdh;
        for(auto &it : fd) {
            int ctr = fdh.size() + 1;
            ret[0][ctr] = it;
            fdh.insert(make_pair(it, ctr));
        }
        for(auto &it : orders) {
            string &val = ret[tbh[stoi(it[1])]][fdh[it[2]]];
            int cnt = stoi(val);
            val = to_string(cnt + 1);
        }
        return ret;
    }
};
