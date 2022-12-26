class Vector2D {
    vector<vector<int> >::const_iterator vecB, vecE;
    vector<int>::const_iterator eleB, eleE;

    void adjust() {
        while(eleB == eleE) {
            if(vecB == vecE)
                break;
            eleB = vecB -> begin();
            eleE = vecB -> end();
            ++vecB;
        }
    }
public:
    Vector2D(vector<vector<int>>& vec) {
        vecB = vec.begin();
        vecE = vec.end();
        eleB = eleE = vector<int>().end();
        if(!vec.empty())
            adjust();
    }

    int next() {
        int x = *eleB;
        ++eleB;
        adjust();
        return x;
    }

    bool hasNext() {
        return vecB != vecE || eleB != eleE;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
