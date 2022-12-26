class TweetCounts {
    unordered_map<string, vector<int> > rec;
public:
    TweetCounts() {
        unordered_map<string, vector<int> >().swap(rec);
    }

    void recordTweet(string tweetName, int time) {
        rec[tweetName].push_back(time);
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        static unordered_map<string, int> trans = {
            {"minute", 60},
            {"hour", 3600},
            {"day", 86400}
        };
        int stp = trans[freq], tot = (endTime - startTime) / stp + 1;
        vector<int> ctr(tot, 0);
        for(int tim : rec[tweetName])
            if(tim >= startTime && tim <= endTime)
                ++ctr[(tim - startTime) / stp];
        return ctr;
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */
