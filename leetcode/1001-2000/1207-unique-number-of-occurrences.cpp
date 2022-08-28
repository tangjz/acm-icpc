class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> ctr;
        for(int x: arr)
            ++ctr[x];
        unordered_set<int> vis;
        for(auto &it: ctr)
            if(!vis.insert(it.second).second)
                return false;
        return true;
    }
};
