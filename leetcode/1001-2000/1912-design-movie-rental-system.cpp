class MovieRentingSystem {
    unordered_map<int, unordered_map<int, int> > store;
    unordered_map<int, set<pair<int, int> > > unrented;
    set<pair<int, pair<int, int> > > rented;
public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        store.clear();
        unrented.clear();
        rented.clear();
         for(auto &it: entries) {
             store[it[0]][it[1]] = it[2];
             unrented[it[1]].insert({it[2], it[0]});
         }
    }

    vector<int> search(int movie) {
        if(!unrented.count(movie))
            return {};
        vector<int> ret;
        for(auto &it: unrented[movie]) {
            ret.push_back(it.second);
            if(ret.size() == 5)
                break;
        }
        return ret;
    }

    void rent(int shop, int movie) {
        int price = store[shop][movie];
        unrented[movie].erase({price, shop});
        rented.insert({price, {shop, movie}});
    }

    void drop(int shop, int movie) {
        int price = store[shop][movie];
        rented.erase({price, {shop, movie}});
        unrented[movie].insert({price, shop});
    }

    vector<vector<int>> report() {
        vector<vector<int> > ret;
        for(auto &it: rented) {
            ret.push_back({it.second.first, it.second.second});
            if(ret.size() == 5)
                break;
        }
        return ret;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
