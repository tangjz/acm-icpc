class FoodRatings {
    map<string, set<pair<int, string> > > rnk;
    map<string, pair<int, string> > info;
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for(int i = 0; i < n; ++i) {
            info[foods[i]] = {ratings[i], cuisines[i]};
            rnk[cuisines[i]].insert({-ratings[i], foods[i]});
        }
    }
    
    void changeRating(string food, int newRating) {
        string cuisine;
        int oldRating;
        tie(oldRating, cuisine) = info[food];
        rnk[cuisine].erase({-oldRating, food});
        info[food].first = newRating;
        rnk[cuisine].insert({-newRating, food});
    }
    
    string highestRated(string cuisine) {
        return rnk[cuisine].begin() -> second;
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
