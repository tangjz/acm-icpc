class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        int n = arr.size(), m = pieces.size();
        unordered_map<int, int> Hash;
        for(int i = 0; i < m; ++i)
            Hash[pieces[i][0]] = i;
        for(int i = 0; i < n; ) {
            if(!Hash.count(arr[i]))
                return false;
            int j = Hash[arr[i]], sz = pieces[j].size();
            for(int k = 0; k < sz; ++k, ++i)
                if(arr[i] != pieces[j][k])
                    return false;
        }
        return true;
    }
};
