class Solution {
    unordered_map<string, vector<string> > edges;
    void dfs(string &u, vector<string> &out) {
        auto &vec = edges[u];
        while(!vec.empty()) {
            string v = vec.back();
            vec.pop_back();
            dfs(v, out);
            out.push_back(v);
        }
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        edges.clear();
        for(auto &it : tickets)
            edges[it[0]].push_back(it[1]);
        for(auto &it : edges) {
            auto &vec = it.second;
            sort(vec.begin(), vec.end());
            reverse(vec.begin(), vec.end());
        }
        vector<string> ret;
        string sta = "JFK";
        dfs(sta, ret);
        ret.push_back(sta);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
