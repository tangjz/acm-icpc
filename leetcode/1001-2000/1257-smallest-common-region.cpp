class Solution {
public:
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
        map<string, string> par;
        for(auto &it: regions)
            for(int i = 1; i < it.size(); ++i)
                par[it[i]] = it[0];
        vector<string> res1 = {region1}, res2 = {region2};
        for( ; par.count(res1.back()); res1.push_back(par[res1.back()]));
        for( ; par.count(res2.back()); res2.push_back(par[res2.back()]));
        string las;
        for( ; !res1.empty() && !res2.empty() && res1.back() == res2.back(); las = res1.back(), res1.pop_back(), res2.pop_back());
        return las;
    }
};
