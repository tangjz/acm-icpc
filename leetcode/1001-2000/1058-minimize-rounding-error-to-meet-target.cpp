class Solution {
public:
    string minimizeError(vector<string>& prices, int target) {
        int low = 0, upp = 0, sum = 0;
        vector<int> cand;
        cand.reserve(prices.size());
        for(auto &it: prices) {
            int sz = it.size();
            int hi = stoi(it.substr(0, sz - 4)), lo = stoi(it.substr(sz - 3));
            if(!lo) {
                low += hi;
                upp += hi;
                continue;
            }
            low += hi;
            upp += hi + 1;
            sum += lo;
            cand.push_back(1000 - lo - lo);
        }
        if(target < low || target > upp)
            return "-1";
        upp = target - low;
        nth_element(cand.begin(), cand.begin() + upp, cand.end());
        cand.resize(upp);
        for(int x: cand)
            sum += x;
        static char buf[9];
        sprintf(buf, "%d.%03d", sum / 1000, sum % 1000);
        return buf;
    }
};
