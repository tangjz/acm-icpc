class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int las = 0;
        priority_queue<pair<int, int> > rht;
        multiset<int> upp;
        vector<vector<int> > ret;
        auto it = buildings.begin();
        while(it != buildings.end() || !rht.empty()) {
            int pos = rht.empty() || (it != buildings.end() && (*it)[0] < -rht.top().first) ? (*it)[0] : -rht.top().first;
            for( ; it != buildings.end() && (*it)[0] == pos; ++it) {
                upp.insert((*it)[2]);
                rht.push(make_pair(-(*it)[1], (*it)[2]));
            }
            for( ; !rht.empty() && -rht.top().first == pos; rht.pop())
                upp.erase(upp.find(rht.top().second));
            int cur = upp.empty() ? 0 : *upp.rbegin();
            if(las != cur) {
                ret.push_back(vector<int>{pos, cur});
                las = cur;
            }
        }
        return ret;
    }
};
