class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> masks;
        for(auto &it: words) {
            int msk = 0;
            for(char ch: it)
                msk |= 1 << (ch - 'a');
            masks.push_back(msk);
        }
        int n = words.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(!(masks[i] & masks[j]))
                    ans = max(ans, (int)words[i].size() * (int)words[j].size());
        return ans;
    }
};
