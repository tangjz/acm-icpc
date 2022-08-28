class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        vector<int> pos(3);
        vector<vector<int> > arr = {move(arr1), move(arr2), move(arr3)};
        vector<int> ret;
        for(bool upd = 1; upd; ) {
            upd = 0;
            int low = INT_MAX;
            for(int i = 0; i < 3; ++i)
                if(pos[i] < arr[i].size())
                    low = min(low, arr[i][pos[i]]);
            if(low == INT_MAX)
                continue;
            upd = 1;
            int cnt = 0;
            for(int i = 0; i < 3; ++i)
                if(pos[i] < arr[i].size() && arr[i][pos[i]] == low) {
                    ++cnt;
                    ++pos[i];
                }
            if(cnt == 3)
                ret.push_back(low);
        }
        return ret;
    }
};
