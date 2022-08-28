class Solution {
public:
    int halfQuestions(vector<int>& questions) {
        unordered_map<int, int> ctr;
        for(int x: questions)
            ++ctr[x];
        vector<int> vals;
        vals.reserve(ctr.size());
        for(auto &it: ctr)
            vals.push_back(it.second);
        int ans = 0, rem = questions.size() / 2;
        sort(vals.begin(), vals.end());
        while(rem > 0 && !vals.empty()) {
            ++ans;
            rem -= vals.back();
            vals.pop_back();
        }
        return ans;
    }
};
