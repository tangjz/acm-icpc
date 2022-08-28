class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        vector<string> ret;
        for(int i = 0, j; i < n; i = j) {
            int sum = 0;
            for(j = i; j < n && sum + words[j].length() + (i < j) <= maxWidth; ++j)
                sum += words[j].length() + (i < j);
            int cnt = j - i, rem = maxWidth - sum;
            string row = words[i];
            if(cnt == 1) {
                row += string(rem, ' ');
            } else if(j < n) {
                int adt = rem / (cnt - 1) + 1, pos = rem % (cnt - 1);
                for(int k = 1; k < cnt; ++k) {
                    row += string(adt + (k <= pos), ' ');
                    row += words[i + k];
                }
            } else {
                for(int k = 1; k < cnt; ++k)
                    row += ' ' + words[i + k];
                row += string(rem, ' ');
            }
            ret.push_back(row);
        }
        return ret;
    }
};
