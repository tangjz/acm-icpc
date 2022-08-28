class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = (int)arr.size();
        unordered_map<int, int> ctr;
        for(int x : arr)
            ++ctr[x];
        vector<int> seq;
        for(auto &it : ctr)
            seq.push_back(it.second);
        sort(seq.begin(), seq.end());
        int ans = 0, cnt = 0;
        while(cnt + cnt < n) {
            ++ans;
            cnt += seq.back();
            seq.pop_back();
        }
        return ans;
    }
};
