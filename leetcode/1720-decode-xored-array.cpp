class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int> ans;
        ans.reserve(encoded.size() + 1);
        ans.push_back(first);
        for(int x : encoded)
            ans.push_back(ans.back() ^ x);
        return ans;
    }
};
