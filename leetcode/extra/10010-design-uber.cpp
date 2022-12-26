class Uber {
    vector<vector<int> > cand;
    unordered_set<int> trip;
public:
    Uber() {

    }

    void addCab(int cabX, int cabY) {
        cand.push_back({cabX, cabY});
    }

    vector<int> startTrip(int customerID, int customerX, int customerY) {
        if(trip.count(customerID))
            return {-1, -1};
        vector<vector<int> > ret = getNearestCabs(1, customerX, customerY);
        if(ret.empty())
            return {-1, -1};
        for(int i = 0; i < (int)cand.size(); ++i)
            if(cand[i] == ret[0]) {
                cand.erase(cand.begin() + i);
                trip.insert(customerID);
                return ret[0];
            }
        assert(0);
        return {-1, -1};
    }

    void endTrip(int customerID, int customerX, int customerY) {
        auto it = trip.find(customerID);
        if(it == trip.end())
            return;
        trip.erase(it);
        addCab(customerX, customerY);
    }

    vector<vector<int>> getNearestCabs(int k, int x, int y) {
        vector<vector<int> > ret;
        if(cand.empty())
            return ret;
        for(auto &it: cand) {
            int dx = x - it[0], dy = y - it[1];
            ret.push_back({dx * dx + dy * dy, it[0], it[1]});
        }
        k = min(k, (int)ret.size());
        nth_element(ret.begin(), ret.begin() + k, ret.end());
        ret.resize(k);
        for(auto &it: ret)
            it.erase(it.begin());
        sort(ret.begin(), ret.end());
        return move(ret);
    }
};

/**
 * Your Uber object will be instantiated and called as such:
 * Uber obj = new Uber();
 * obj.addCab(cabX,cabY);
 * int[] param_2 = obj.startTrip(customerID,customerX,customerY);
 * obj.endTrip(customerID,customerX,customerY);
 * List<List<Integer>> param_4 = obj.getNearestCabs(k,x,y);
 */
