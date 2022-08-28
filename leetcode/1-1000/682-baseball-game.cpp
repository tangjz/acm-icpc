class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> stk;
        for(auto &it: ops)
            if(it == "+") {
                int m = stk.size();
                stk.push_back(stk[m - 2] + stk.back());
            } else if(it == "D") {
                stk.push_back(stk.back() * 2);
            } else if(it == "C") {
                stk.pop_back();
            } else {
                stk.push_back(stoi(it));
            }
        int ret = 0;
        for(int x: stk)
            ret += x;
        return ret;
    }
};
