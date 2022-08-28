class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        int ans = 0, best = 0, cur = 0, n = array.size();
        unordered_map<int, int> pos;
        for(int i = 0; i < n; ++i) {
            pos.insert({cur, i});
            cur += isdigit(array[i][0]) ? 1 : -1;
            auto it = pos.find(cur);
            if(it != pos.end() && ans < i + 1 - it -> second) {
                ans = i + 1 - it -> second;
                best = it -> second;
            }
        }
        rotate(array.begin(), array.begin() + best, array.end());
        array.resize(ans);
        return array;
    }
};
