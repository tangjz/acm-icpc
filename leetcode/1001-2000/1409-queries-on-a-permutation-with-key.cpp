class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> vec, ret;
        for(int i = 1; i <= m; ++i)
            vec.push_back(i);
        for(int x : queries) {
            int pos = find(vec.begin(), vec.end(), x) - vec.begin();
            ret.push_back(pos);
            rotate(vec.begin(), vec.begin() + pos, vec.begin() + pos + 1);
        }
        return ret;
    }
};
