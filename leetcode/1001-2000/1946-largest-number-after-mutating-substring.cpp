class Solution {
public:
    string maximumNumber(string num, vector<int>& change) {
        int n = num.size();
        for(int i = 0; i < n; ++i) {
            int d = num[i] - '0';
            if(d >= change[d])
                continue;
            for(int j = i; j < n; ++j) {
                int d = num[j] - '0';
                if(d > change[d])
                    break;
                num[j] = '0' + change[d];
            }
            break;
        }
        return num;
    }
};
