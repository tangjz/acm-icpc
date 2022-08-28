class Solution {
    bool isSubset(vector<int> &lft, vector<int> &rht) { // check lft <= rht
        int n = (int)lft.size(), m = (int)rht.size();
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < m && rht[j] < lft[i]; ++j);
            if(!(j < m && rht[j] == lft[i]))
                return 0;
        }
        return 1;
    }
public:
    vector<int> peopleIndexes(vector<vector<string>>& buf) {
        unordered_map<string, int> Hash;
        vector<vector<int> > vec;
        for(auto &it : buf) {
            vector<int> tmp;
            for(auto &jt : it) {
                int val;
                auto kt = Hash.find(jt);
                if(kt == Hash.end()) {
                    val = (int)Hash.size();
                    Hash.insert(make_pair(jt, val));
                } else {
                    val = kt -> second;
                } printf("%d ", val);
                tmp.push_back(val);
            } puts("");
            sort(tmp.begin(), tmp.end());
            vec.push_back(tmp);
        }
        int n = (int)vec.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            bool chk = 1;
            for(int j = 0; j < n && chk; ++j) {
                chk &= i == j || !isSubset(vec[i], vec[j]);
            }
            if(chk)
                ret.push_back(i);
        }
        return ret;
    }
};
