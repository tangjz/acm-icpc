class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size();
        unordered_map<int, vector<int> > hs;
        for(int i = 0; i < n; ++i)
            hs[labels[i]].push_back(values[i]);
        values = {};
        for(auto &it: hs) {
            auto &vec = it.second;
            int m = min((int)vec.size(), useLimit);
            nth_element(vec.begin(), vec.begin() + m, vec.end(), greater<int>());
            values.insert(values.end(), vec.begin(), vec.begin() + m);
        }
        int m = min((int)values.size(), numWanted);
        nth_element(values.begin(), values.begin() + m, values.end(), greater<int>());
        values.resize(m);
        int ans = 0;
        for(int x: values)
            ans += x;
        return ans;
    }
};
