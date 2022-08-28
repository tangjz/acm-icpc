class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int tot = 0, pos = 0;
        for(char ch: s) {
            int adt = widths[(int)(ch - 'a')];
            if(pos + adt > 100) {
                ++tot;
                pos = 0;
            }
            pos += adt;
        }
        return {tot + 1, pos};
    }
};
