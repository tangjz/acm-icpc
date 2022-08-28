class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int sft = 0;
        for(auto &it : shift)
            sft += it[0] ? -it[1] : it[1];
        int len = (int)s.length();
        (sft %= len) < 0 && (sft += len);
        rotate(s.begin(), s.begin() + sft, s.end());
        return s;
    }
};
