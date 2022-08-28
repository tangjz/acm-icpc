class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int n = (int)days.size();
        vector<pair<int, int> > events;
        for(int i = 0; i < n; ++i) {
            if(!days[i])
                continue;
            events.push_back({i, (i + 1)});
            events.push_back({i + days[i], -(i + 1)});
        }
        sort(events.begin(), events.end());
        int ans = 0, las = -1;
        set<pair<int, int> > rem;
        for(auto const &it : events) {
            int cur = it.first;
            while(las < cur && !rem.empty()) {
                int pos = rem.begin() -> second;
                int tmp = min(apples[pos], cur - las);
                apples[pos] -= tmp;
                if(!apples[pos])
                    rem.erase(rem.begin());
                las += tmp;
                ans += tmp;
            }
            las = cur;
            int pos = abs(it.second) - 1;
            if(!apples[pos])
                continue;
            pair<int, int> state = {pos + days[pos], pos};
            if(it.second > 0) {
                rem.insert(state);
            } else {
                rem.erase(state);
            }
        }
        return ans;
    }
};
