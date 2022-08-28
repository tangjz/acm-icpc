class Solution {
    int dfs(int len, int mask, vector<pair<int, int> >::iterator cur, vector<pair<int, int> >::iterator end) {
        if(cur == end)
            return len;
        int ret = dfs(len, mask, cur + 1, end);
        if(!(mask & (cur -> first)))
            ret = max(ret, dfs(len + (cur -> second), mask | (cur -> first), cur + 1, end));
        return ret;
    }
public:
    int maxLength(vector<string>& arr) {
        vector<pair<int, int> > masks;
        for(auto &it : arr) {
            int mask = 0;
            bool ban = 0;
            for(char ch : it) {
                int adt = 1 << (int)(ch - 'a');
                if(mask & adt) {
                    ban = 1;
                    break;
                }
                mask |= adt;
            }
            if(!ban)
                masks.push_back({mask, (int)it.size()});
        }
        return dfs(0, 0, masks.begin(), masks.end());
    }
};
