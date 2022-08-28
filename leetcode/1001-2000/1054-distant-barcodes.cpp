class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        unordered_map<int, int> ctr;
        for(int x: barcodes)
            ++ctr[x];
        priority_queue<pair<int, int> > que;
        for(auto &it: ctr)
            que.push({it.second, it.first});
        vector<int> ret;
        while(!que.empty()) {
            auto it = que.top();
            que.pop();
            if(!ret.empty() && ret.back() == it.second) {
                auto jt = que.top();
                que.pop();
                ret.push_back(jt.second);
                --jt.first;
                if(jt.first > 0)
                    que.push(jt);
            }
            ret.push_back(it.second);
            --it.first;
            if(it.first > 0)
                que.push(it);
        }
        return ret;
    }
};
