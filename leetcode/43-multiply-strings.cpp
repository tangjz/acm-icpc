class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size(), m = num2.size();
        vector<int> seq(n + m - 1);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                seq[i + j] += (num1[n - 1 - i] - '0') * (num2[m - 1 - j] - '0');
        while(seq.size() > 1 && !seq.back())
            seq.pop_back();
        for(int i = 0; i < (int)seq.size(); ++i) {
            int adt = seq[i] / 10;
            seq[i] %= 10;
            if(adt) {
                if(i + 1 >= (int)seq.size())
                    seq.push_back(0);
                seq[i + 1] += adt;
            }
        }
        string ret = "";
        for(int i = (int)seq.size() - 1; i >= 0; --i)
            ret.push_back('0' + seq[i]);
        return ret;
    }
};
