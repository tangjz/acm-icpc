class Solution {
public:
    vector<double> honeyQuotes(vector<vector<int>>& handle) {
        int cnt = 0, sum1 = 0, sum2 = 0;
        vector<double> ret;
        for(auto &it: handle) {
            switch(it[0]) {
                case 1: {
                    ++cnt;
                    sum1 += it[1];
                    sum2 += it[1] * it[1];
                    break;
                }
                case 2: {
                    --cnt;
                    sum1 -= it[1];
                    sum2 -= it[1] * it[1];
                    break;
                }
                case 3: {
                    double val = -1;
                    if(cnt > 0) {
                        val = (double)sum1 / cnt;
                    }
                    ret.push_back(val);
                    break;
                }
                case 4: {
                    double val = -1;
                    if(cnt > 0) {
                        val = (double)sum1 / cnt;
                        val = (double)sum2 / cnt - val * val;
                    }
                    ret.push_back(val);
                    break;
                }
            }
        }
        return ret;
    }
};
