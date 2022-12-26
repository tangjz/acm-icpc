class DiscountSystem {
    map<pair<int, int>, int> ctr;
    vector<vector<int> > act;
public:
    DiscountSystem() {
        ctr.clear();
        act.clear();
    }

    void addActivity(int actId, int priceLimit, int discount, int number, int userLimit) {
        act.push_back({actId, priceLimit, discount, number, userLimit});
    }

    void removeActivity(int actId) {
        auto it = act.begin();
        for( ; it != act.end() && (*it)[0] != actId; ++it);
        if(it != act.end()) {
            rotate(it, it + 1, act.end());
            act.pop_back();
        }
    }

    int consume(int userId, int cost) {
        pair<int, int> best = {cost, -1};
        for(auto &vec: act) {
            if(cost < vec[1])
                continue;
            if(ctr[{vec[0], userId}] >= vec[4])
                continue;
            if(vec[3] <= 0)
                continue;
            best = min(best, make_pair(cost - vec[2], vec[0]));
        }
        if(best.second != -1)
            for(auto &vec: act)
                if(vec[0] == best.second) {
                    ++ctr[{vec[0], userId}];
                    --vec[3];
                    break;
                }
        return best.first;
    }
};

/**
 * Your DiscountSystem object will be instantiated and called as such:
 * DiscountSystem* obj = new DiscountSystem();
 * obj->addActivity(actId,priceLimit,discount,number,userLimit);
 * obj->removeActivity(actId);
 * int param_3 = obj->consume(userId,cost);
 */
