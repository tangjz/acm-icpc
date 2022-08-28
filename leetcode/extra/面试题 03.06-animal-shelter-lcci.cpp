class AnimalShelf {
    int stp;
    queue<pair<int, int> > que[2];
public:
    AnimalShelf() {
        stp = 0;
    }
    
    void enqueue(vector<int> animal) {
        que[animal[1]].push({animal[0], stp++});
    }
    
    vector<int> dequeueAny() {
        vector<int> ret(2, -1);
        if(que[0].empty() && que[1].empty())
            return ret;
        if(que[1].empty() || (!que[0].empty() && que[0].front().second < que[1].front().second)) {
            ret = {que[0].front().first, 0};
            que[0].pop();
        } else {
            ret = {que[1].front().first, 1};
            que[1].pop();
        }
        return ret;
    }
    
    vector<int> dequeueDog() {
        vector<int> ret(2, -1);
        if(que[1].empty())
            return ret;
        ret = {que[1].front().first, 1};
        que[1].pop();
        return ret;
    }
    
    vector<int> dequeueCat() {
        vector<int> ret(2, -1);
        if(que[0].empty())
            return ret;
        ret = {que[0].front().first, 0};
        que[0].pop();
        return ret;
    }
};

/**
 * Your AnimalShelf object will be instantiated and called as such:
 * AnimalShelf* obj = new AnimalShelf();
 * obj->enqueue(animal);
 * vector<int> param_2 = obj->dequeueAny();
 * vector<int> param_3 = obj->dequeueDog();
 * vector<int> param_4 = obj->dequeueCat();
 */
